// @category Whiskey

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.*;

public class DumpFunctionPattern extends GhidraScript {
  private static final int MAX_FUNCTION_SIZE = 4096;
  private static final int BYTES_PER_LINE = 16;

  @Override
  public void run() throws Exception {
    Function f = getFunctionContaining(currentAddress);

    if (f == null) {
      println("No function at cursor");
      return;
    }

    AddressSetView body = f.getBody();
    Address start = body.getMinAddress();
    Address end = body.getMaxAddress();

    if (start == null || end == null) {
      println("Invalid function body");
      return;
    }

    long len = end.subtract(start) + 1;

    if (len <= 0 || len > MAX_FUNCTION_SIZE) {
      println("Function too large or invalid: " + len);
      return;
    }

    int size = (int) len;

    byte[] bytes = new byte[size];
    boolean[] wild = new boolean[size];

    try {
      currentProgram.getMemory().getBytes(start, bytes);
    } catch (Exception e) {
      println("Unable to read function memory: " + e.getMessage());
      return;
    }

    Listing listing = currentProgram.getListing();
    InstructionIterator iter = listing.getInstructions(body, true);

    while (iter.hasNext()) {
      Instruction insn = iter.next();

      long offset = insn.getAddress().subtract(start);
      int insnLength = insn.getLength();

      // Ensure the instruction starts inside the function range.
      if (offset < 0 || offset >= size) {
        continue;
      }

      // Ensure the entire instruction fits inside the range.
      if (insnLength <= 0 || offset + insnLength > size) {
        continue;
      }

      int off = (int) offset;

      byte[] ib;

      try {
        ib = insn.getBytes();
      } catch (Exception e) {
        continue;
      }

      if (ib == null || ib.length != insnLength || ib.length == 0) {
        continue;
      }

      int op = ib[0] & 0xFF;

      if (ib.length < 2) {
        continue;
      }

      if (op == 0xE8 || op == 0xE9) {
        // CALL/JMP rel32
        wildcard(wild, off, ib.length, 1, 4);

      } else if (op == 0xEB) {
        // JMP rel8
        wildcard(wild, off, ib.length, 1, 1);

      } else if (op >= 0x70 && op <= 0x7F) {
        // JCC rel8
        wildcard(wild, off, ib.length, 1, 1);

      } else if (op == 0x0F &&
                 ib.length >= 6 &&
                 (ib[1] & 0xF0) == 0x80) {
        // JCC rel32
        wildcard(wild, off, ib.length, 2, 4);

      } else if ((op == 0x48 || op == 0x4C) &&
                 ib.length >= 7 &&
                 (ib[1] & 0xFF) == 0x8D) {
        // LEA RIP-relative
        if ((ib[2] & 0xC7) == 0x05) {
          wildcard(wild, off, ib.length, 3, 4);
        }
      }
    }

    StringBuilder sb = new StringBuilder();

    for (int i = 0; i < size; i++) {
      if (wild[i]) {
        sb.append("??");
      } else {
        sb.append(String.format("%02X", bytes[i] & 0xFF));
      }

      if (i + 1 < size) {
        sb.append(' ');
      }

      if ((i + 1) % BYTES_PER_LINE == 0) {
        sb.append('\n');
      }
    }

    println("Function: " + f.getName() + " @ " + f.getEntryPoint());
    println("Size: " + size + " bytes");
    println(sb.toString());
  }

  private void wildcard(
      boolean[] wild,
      int instructionOffset,
      int instructionLength,
      int operandOffset,
      int operandLength
  ) {
    // Validate operand boundaries within the instruction.
    if (operandOffset < 0 ||
        operandLength <= 0 ||
        operandOffset + operandLength > instructionLength) {
      return;
    }

    // Validate instruction boundaries within the function.
    if (instructionOffset < 0 ||
        instructionOffset + instructionLength > wild.length) {
      return;
    }

    int start = instructionOffset + operandOffset;
    int end = start + operandLength;

    // Final defensive check.
    if (start < 0 || end > wild.length) {
      return;
    }

    for (int i = start; i < end; i++) {
      wild[i] = true;
    }
  }
}

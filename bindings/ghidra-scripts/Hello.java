import ghidra.app.script.GhidraScript;

public class Hello extends GhidraScript {
	@Override
	public void run() throws Exception {
		println("Hello");
	}
}
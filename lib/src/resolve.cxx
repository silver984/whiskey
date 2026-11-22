#include <whiskey/resolve.h>

#include <Windows.h>

namespace whiskey {

std::uintptr_t base_addr(void) {
  static std::uintptr_t const out = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
  return out;
}

} // namespace whiskey
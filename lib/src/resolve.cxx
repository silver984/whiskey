#include <whiskey/resolve.h>

#include <Windows.h>

namespace whiskey {

std::uintptr_t base_addr ( std::wstring_view name ) {
  static std::uintptr_t const out =
    reinterpret_cast<std::uintptr_t> ( GetModuleHandleW ( name.data ( ) ) );
  return out;
}

} // namespace whiskey
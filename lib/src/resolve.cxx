#include <whiskey/resolve.h>

#include <Windows.h>

namespace whiskey {

std::uintptr_t base_addr ( wchar_t const* name ) {
  return reinterpret_cast<std::uintptr_t> ( GetModuleHandleW ( name ) );
}

} // namespace whiskey
#ifndef WHISKEY_RESOLVE_H_
#define WHISKEY_RESOLVE_H_

#include <whiskey/export.h>

#include <cstdint>
#include <string_view>

namespace whiskey {

[[nodiscard]] WHISKEY_EXPORT std::uintptr_t base_addr ( std::wstring_view name );

template <typename T>
[[nodiscard]] T resolve ( std::wstring_view name, std::uintptr_t offset ) {
  T out = reinterpret_cast<T> ( base_addr ( name ) + offset );
  return out;
}

} // namespace whiskey

#endif // WHISKEY_RESOLVE_H_
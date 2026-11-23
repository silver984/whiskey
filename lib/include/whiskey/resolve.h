#ifndef WHISKEY_RESOLVE_H_
#define WHISKEY_RESOLVE_H_

#include <whiskey/export.h>

#include <cstdint>

namespace whiskey {

[[nodiscard]] WHISKEY_EXPORT std::uintptr_t base_addr ( wchar_t const* name );

template <typename T>
[[nodiscard]] T resolve ( wchar_t const* name, std::uintptr_t offset ) {
  T out = reinterpret_cast<T> ( base_addr ( name ) + offset );
  return out;
}

} // namespace whiskey

#endif // WHISKEY_RESOLVE_H_
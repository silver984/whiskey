#ifndef WHISKEY_RESOLVE_H_
#define WHISKEY_RESOLVE_H_

#include <whiskey/export.h>

#include <cstdint>

namespace whiskey {

[[nodiscard]] WHISKEY_EXPORT std::uintptr_t base_addr(void);

template <typename T>
[[nodiscard]] T resolve(std::uintptr_t offset) {
  T out = reinterpret_cast<T>(base_addr() + offset);
  return out;
}

} // namespace whiskey

#endif // WHISKEY_RESOLVE_H_
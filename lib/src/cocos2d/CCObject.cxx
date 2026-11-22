#include <whiskey/cocos2d-x/CCObject.h>

#include <Windows.h>

#include <cstdint>

namespace whiskey {

template <typename T>
[[nodiscard]] T resolve(std::uintptr_t offset) {
  // todo: hide winapi
  std::uintptr_t const base = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
  T out                     = reinterpret_cast<T>(base + offset);
  return out;
}

template <typename>
struct class_fn_sig;

// todo: qualifiers
template <typename _ret_, typename _class_, typename... _args_>
struct class_fn_sig<_ret_ (_class_::*)(_args_...)> final {
  class_fn_sig() = delete;
  using type     = _ret_ (*)(_class_*, _args_...);
};

template <typename _t_>
using class_fn_sig_t = class_fn_sig<_t_>::type;

} // namespace whiskey

namespace cocos2d {

CCCopying::CCCopying(void) {}
CCCopying::CCCopying(CCCopying const& other) {}

CCObject* CCCopying::copyWithZone(CCZone* pZone) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCCopying::copyWithZone)>;
  sig call  = whiskey::resolve<sig>(0xeb70);
  return call(this, pZone);
}

CCObject::CCObject(void) {}
CCObject::CCObject(CCObject const& other) {}

CCObject::~CCObject(void) {}

CCObject* CCObject::copy(void) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCObject::copy)>;
  sig call  = whiskey::resolve<sig>(0xeb60);
  return call(this);
}

void CCObject::release(void) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCObject::release)>;
  sig call  = whiskey::resolve<sig>(0xebb0);
  call(this);
}

void CCObject::retain(void) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCObject::retain)>;
  sig call  = whiskey::resolve<sig>(0xebd0);
  call(this);
}

int CCObject::retainCount(void) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCObject::retainCount)>;
  sig call  = whiskey::resolve<sig>(0xebe0);
  return call(this);
}

void CCObject::setTag(int ua1) {
  using sig = whiskey::class_fn_sig_t<decltype(&CCObject::setTag)>;
  sig call  = whiskey::resolve<sig>(0xebf0);
  call(this, ua1);
}

} // namespace cocos2d
#include <whiskey/libcocos2d/CCObject.h>

#include <whiskey/resolve.h>

namespace cocos2d {

CCObject* CCObject::createWithCoder(DS_Dictionary* a1) {
  return nullptr;
}

CCObject* CCObject::copy(void) {
  using sig = CCObject* (*)(CCObject*);
  sig call  = whiskey::resolve<sig>(0xeb60);
  return call(this);
}

void CCObject::release(void) {
  using sig = void (*)(CCObject*);
  sig call  = whiskey::resolve<sig>(0xebb0);
  call(this);
}

void CCObject::retain(void) {
  using sig = void (*)(CCObject*);
  sig call  = whiskey::resolve<sig>(0xebd0);
  call(this);
}

int CCObject::retainCount(void) {
  using sig = int (*)(CCObject*);
  sig call  = whiskey::resolve<sig>(0xebe0);
  return call(this);
}

void CCObject::setTag(int a1) {
  using sig = void (*)(CCObject*, int);
  sig call  = whiskey::resolve<sig>(0xebf0);
  call(this, a1);
}

} // namespace cocos2d
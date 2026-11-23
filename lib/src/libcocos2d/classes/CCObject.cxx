#include <whiskey/libcocos2d/classes/CCObject.h>

namespace cocos2d {

// CCObject* CCObject::createWithCoder ( DS_Dictionary* p1 ) {
//   return nullptr;
// }

// void CCObject::acceptVisitor ( CCDataVisitor* p1 ) {
//   // todo
// }

int CCObject::getTag ( ) const {
  return m_nTag;
}

bool CCObject::isEqual ( CCObject const* p1 ) {
  return this == p1;
}

bool CCObject::isSingleReference ( ) const {
  return m_uReference == 1;
}

void CCObject::setObjType ( int p1 ) {
  m_eObjType = p1;
}

void CCObject::setTag ( int p1 ) {
  m_nTag = p1;
}

} // namespace cocos2d
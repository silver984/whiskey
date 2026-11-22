#ifndef WHISKEY_COCOS2D_X_CCOBJECT_H_
#define WHISKEY_COCOS2D_X_CCOBJECT_H_

#include "CCZone.h"

namespace cocos2d {

struct CCObject;

struct CCCopying {
  CCCopying(void);
  CCCopying(CCCopying const& other);

  virtual CCObject* copyWithZone(CCZone* pZone);
};

struct CCObject : CCCopying {
  CCObject(void);
  CCObject(CCObject const& other);

  virtual ~CCObject(void);

  CCObject* copy(void);
  void release(void);
  void retain(void);
  int retainCount(void);
  void setTag(int ua1);

  unsigned int m_uID;
  int m_nLuaID;
  int m_nTag;
  unsigned int m_uReference;
  unsigned int m_uAutoReleaseCount;
};

} // namespace cocos2d

#endif // WHISKEY_COCOS2D_X_CCOBJECT_H_
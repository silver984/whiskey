#ifndef WHISKEY_LIBCOCOS2D_CCOBJECT_H_
#define WHISKEY_LIBCOCOS2D_CCOBJECT_H_

#include <whiskey/export.h>

#include "CCCopying.h"

struct DS_Dictionary {};

namespace cocos2d {

struct WHISKEY_EXPORT CCObject : CCCopying {
  // CCObject(void);
  // CCObject(CCObject const& other);

  // virtual ~CCObject(void);

  static CCObject* createWithCoder(DS_Dictionary* a1);

  CCObject* copy(void);
  void release(void);
  void retain(void);
  int retainCount(void);
  void setTag(int a1);

  unsigned int m_uID;
  int m_nLuaID;
  int m_nTag;
  unsigned int m_uReference;
  unsigned int m_uAutoReleaseCount;
};

} // namespace cocos2d

#endif // WHISKEY_LIBCOCOS2D_CCOBJECT_H_
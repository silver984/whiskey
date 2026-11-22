#ifndef WHISKEY_LIBCOCOS2D_CCCOPYING_H_
#define WHISKEY_LIBCOCOS2D_CCCOPYING_H_

#include <whiskey/export.h>

namespace cocos2d {

struct CCObject;
struct CCZone {};

struct WHISKEY_EXPORT CCCopying {
  // CCCopying(void);
  // CCCopying(CCCopying const& other);

  virtual CCObject* copyWithZone(CCZone* pZone);
};

} // namespace cocos2d

#endif // WHISKEY_LIBCOCOS2D_CCCOPYING_H_
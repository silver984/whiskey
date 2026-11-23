#ifndef WHISKEY_CCCOPYING_H_
#define WHISKEY_CCCOPYING_H_

#include <whiskey/export.h>
#include <whiskey/macros.h>

namespace cocos2d {

struct CCObject;
struct CCZone;

struct WHISKEY_EXPORT CCCopying {
  virtual CCObject* copyWithZone ( CCZone* pZone );
};

WHISKEY_ASSERT_TYPE_SIZE ( CCCopying, 0x8 );

} // namespace cocos2d

#endif // WHISKEY_CCCOPYING_H_
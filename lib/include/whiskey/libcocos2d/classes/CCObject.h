#ifndef WHISKEY_CCOBJECT_H_
#define WHISKEY_CCOBJECT_H_

#include <whiskey/export.h>
#include <whiskey/macros.h>

#include <whiskey/libcocos2d/classes/CCCopying.h>
// #include <whiskey/libcocos2d/enums/CCObjectType.h>

struct DS_Dictionary;

namespace cocos2d {

struct CCDataVisitor;

struct WHISKEY_EXPORT CCObject : CCCopying {
  // CCObject ( );
  // virtual ~CCObject ( );

  /// @note out of line
  // static CCObject* createWithCoder ( DS_Dictionary* p1 );

  /// @note out of line
  // virtual void     acceptVisitor ( CCDataVisitor* p1 );

  CCObject*    copy ( );

  /// @note out of line
  virtual int  getTag ( ) const;

  /// @note out of line
  virtual bool isEqual ( CCObject const* p1 );

  /// @note out of line
  bool         isSingleReference ( ) const;

  void         release ( );
  void         retain ( );
  unsigned int retainCount ( ) const;

  /// @note out of line
  void         setObjType ( int p1 );

  /// @note out of line
  virtual void setTag ( int p1 );

  unsigned int m_uID;
  int          m_nLuaID;
  int          m_nTag;
  unsigned int m_uReference;
  unsigned int m_uAutoReleaseCount;
  int          m_eObjType;
};

WHISKEY_ASSERT_TYPE_SIZE ( CCObject, 0x20 );

} // namespace cocos2d

#endif // WHISKEY_CCOBJECT_H_
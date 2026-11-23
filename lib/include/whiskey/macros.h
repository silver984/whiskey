#ifndef WHISKEY_MACROS_H_
#define WHISKEY_MACROS_H_

#define WHISKEY_ASSERT_TYPE_SIZE( __TYPE__, __SIZE__ )                                             \
  static_assert ( sizeof ( __TYPE__ ) == __SIZE__ )

#endif // WHISKEY_MACROS_H_
#include <whiskey/resolve.h>

#include <Windows.h>

#include <cstdio>
#include <iostream>
#include <print>

namespace whiskey {

void setup ( ) {
  if ( !AllocConsole ( ) ) {
    return;
  }
  FILE* fp;
  freopen_s ( &fp, "CONOUT$", "w", stdout );
  freopen_s ( &fp, "CONOUT$", "w", stderr );
  freopen_s ( &fp, "CONIN$", "r", stdin );
  std::ios::sync_with_stdio ( );
  std::println ( "{:#x} | {:#x} | {:#x}", base_addr ( nullptr ), base_addr ( L"libcocos2d.dll" ),
                 base_addr ( L"whiskey.dll" ) );
}

} // namespace whiskey

BOOL APIENTRY DllMain ( HMODULE, DWORD reason, LPVOID ) {
  if ( reason == DLL_PROCESS_ATTACH ) {
    whiskey::setup ( );
    return TRUE;
  }
  return TRUE;
}
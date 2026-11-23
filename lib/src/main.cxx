#include <whiskey/resolve.h>

#include <Windows.h>

#include <cstdio>
#include <iostream>
#include <print>

namespace whiskey {

void startup ( ) {
  if ( !AllocConsole ( ) ) {
    return;
  }
  FILE* fp;
  freopen_s ( &fp, "CONOUT$", "w", stdout );
  freopen_s ( &fp, "CONOUT$", "w", stderr );
  freopen_s ( &fp, "CONIN$", "r", stdin );
  std::ios::sync_with_stdio ( );
  std::println ( "Geomerty Dash base addr: {:#x}", base_addr ( L"GeometryDash.exe" ) );
}

} // namespace whiskey

BOOL APIENTRY DllMain ( HMODULE, DWORD reason, LPVOID ) {
  if ( reason != DLL_PROCESS_ATTACH ) {
    return TRUE;
  }
  whiskey::startup ( );
  return TRUE;
}
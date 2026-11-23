#include <Windows.h>

BOOL APIENTRY DllMain ( HMODULE, DWORD reason, LPVOID ) {
  if ( reason != DLL_PROCESS_ATTACH ) {
    return TRUE;
  }

  LPTHREAD_START_ROUTINE load_whiskey_dll = [] ( LPVOID ) -> DWORD {
    LoadLibraryW ( L"whiskey.dll" );
    return 0;
  };

  HANDLE thread = CreateThread ( nullptr, 0, load_whiskey_dll, nullptr, 0, nullptr );

  if ( thread ) {
    CloseHandle ( thread );
  }

  return TRUE;
}
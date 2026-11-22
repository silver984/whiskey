if(NOT WIN32)
  message(FATAL_ERROR "whiskey doesn't support the current operating system")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "whiskey found incompatible architecture")
endif()

add_library(whiskey SHARED)

include(GenerateExportHeader)

generate_export_header(
  whiskey
  BASE_NAME        WHISKEY
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/generated/whiskey/export.h
)

include(GNUInstallDirs)

target_include_directories(
  whiskey PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

file(GLOB WHISKEY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
target_sources(whiskey PRIVATE ${WHISKEY_SOURCES})

install(
  TARGETS             whiskey
  EXPORT              whiskey_targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  FILES       ${CMAKE_CURRENT_BINARY_DIR}/generated/whiskey/export.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(WHISKEY_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/whiskey)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/whiskey_config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/whiskey_config.cmake
  INSTALL_DESTINATION ${WHISKEY_INSTALL_DIR}
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/whiskey_config_version.cmake
  VERSION       ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  EXPORT      whiskey_targets
  FILE        whiskey_targets.cmake
  NAMESPACE   whiskey::
  DESTINATION ${WHISKEY_INSTALL_DIR}
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/whiskey_config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/whiskey_config_version.cmake
  DESTINATION ${WHISKEY_INSTALL_DIR}
)

set(WHISKEY_TEMPORARY_DIR ${CMAKE_BINARY_DIR}/.temporary)
set(FRIDA_GUM_DIR ${CMAKE_SOURCE_DIR}/vendor/frida-gum)

if(NOT IS_DIRECTORY ${FRIDA_GUM_DIR})
  set(FRIDA_GUM_DEVKIT_FILENAME frida-gum-devkit-17.25.2-windows-x86_64.tar.xz)
  set(FRIDA_GUM_DEVKIT_URL https://github.com/frida/frida/releases/download/17.25.2/${FRIDA_GUM_DEVKIT_FILENAME})
  set(FRIDA_GUM_DEVKIT_TEMPORARY ${WHISKEY_TEMPORARY_DIR}/${FRIDA_GUM_DEVKIT_FILENAME})

  file(
    DOWNLOAD
    ${FRIDA_GUM_DEVKIT_URL}
    ${FRIDA_GUM_DEVKIT_TEMPORARY}
    SHOW_PROGRESS 
    STATUS FRIDA_GUM_DOWNLOAD_STATUS
  )

  list(GET FRIDA_GUM_DOWNLOAD_STATUS 0 FRIDA_GUM_DOWNLOAD_CODE)

  if(NOT FRIDA_GUM_DOWNLOAD_CODE EQUAL 0)
    list(GET FRIDA_GUM_DOWNLOAD_STATUS 1 FRIDA_GUM_DOWNLOAD_ERROR)
    message(FATAL_ERROR "whiskey failed to vendor frida-gum devkit | what: ${FRIDA_GUM_DOWNLOAD_ERROR}")
  endif()

  file(
    ARCHIVE_EXTRACT
    INPUT       ${FRIDA_GUM_DEVKIT_TEMPORARY}
    DESTINATION ${FRIDA_GUM_DIR}
  )
endif()

file(REMOVE_RECURSE ${WHISKEY_TEMPORARY_DIR})

add_library(frida_gum STATIC IMPORTED)

set_target_properties(
  frida_gum                     PROPERTIES
  IMPORTED_LOCATION             ${FRIDA_GUM_DIR}/frida-gum.lib
  INTERFACE_INCLUDE_DIRECTORIES ${FRIDA_GUM_DIR}
)

target_link_libraries(frida_gum INTERFACE ws2_32 psapi shlwapi dnsapi iphlpapi)
target_link_libraries(whiskey PRIVATE frida_gum)
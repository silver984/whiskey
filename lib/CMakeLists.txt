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

set(FRIDA_GUM_DIR ${CMAKE_SOURCE_DIR}/vendor/frida-gum)

if(WIN32)
  set(FRIDA_GUM_OS_DIR ${FRIDA_GUM_DIR}/windows)
  set(FRIDA_GUM_LINK_LIBS ws2_32 psapi shlwapi dnsapi iphlpapi)
else()
  message(FATAL_ERROR "whiskey doesn't support the current operating system")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "whiskey found incompatible architecture")
endif()

set(FRIDA_GUM_IMPORT ${FRIDA_GUM_OS_DIR}/frida-gum.lib)

add_library(frida_gum STATIC IMPORTED)

set_target_properties (
  frida_gum                     PROPERTIES
  IMPORTED_LOCATION             ${FRIDA_GUM_IMPORT}
  INTERFACE_INCLUDE_DIRECTORIES ${FRIDA_GUM_OS_DIR}
)

target_link_libraries(frida_gum INTERFACE ${FRIDA_GUM_LINK_LIBS})
target_link_libraries(whiskey PRIVATE frida_gum)
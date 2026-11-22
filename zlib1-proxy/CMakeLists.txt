add_library(
  zlib1 SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib1.def
)

add_custom_command(
  TARGET zlib1 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE_DIR:zlib1>/zlib1.dll ${WHISKEY_OUTPUT_DIR}
)
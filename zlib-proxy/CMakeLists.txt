add_library(
  zlib1_proxy SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib1.def
)

set_target_properties(
  zlib1_proxy PROPERTIES
  OUTPUT_NAME "zlib1"
)
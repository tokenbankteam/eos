file(GLOB HEADERS "include/eosio/info_plugin/*.hpp")
add_library( info_plugin
             info_plugin.cpp
             ${HEADERS} )

target_link_libraries( info_plugin appbase fc http_plugin chain_plugin)
target_include_directories( info_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/chain/include")

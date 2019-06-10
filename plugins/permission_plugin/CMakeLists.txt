file(GLOB HEADERS "include/eosio/permission_plugin/*.hpp")
add_library( permission_plugin
             permission_plugin.cpp
             ${HEADERS} )

target_link_libraries( permission_plugin appbase fc http_plugin chain_plugin)
target_include_directories( permission_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/chain/include")

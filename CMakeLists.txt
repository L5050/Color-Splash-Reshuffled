cmake_minimum_required(VERSION 3.10)
project(mod CXX C)

file(GLOB_RECURSE MOD_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)

add_executable(mod ${MOD_SOURCES})
wut_add_exports(mod exports.def)
wut_create_rpl(mod)

target_include_directories(mod PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/cs-headers/include
)


set(CS_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cs-headers)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/source/linker.ld
    ${CMAKE_CURRENT_BINARY_DIR}/linker.ld
    @ONLY
)

target_link_options(mod PRIVATE
    "-T${CMAKE_CURRENT_BINARY_DIR}/linker.ld"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mod.rpl"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
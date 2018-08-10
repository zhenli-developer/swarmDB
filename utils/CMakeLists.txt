add_library(utils STATIC
        http_get.cpp
        http_get.hpp
        is_whitelist_member.cpp is_whitelist_member.hpp)

target_link_libraries(utils)
add_dependencies(utils jsoncpp)
target_include_directories(utils PRIVATE ${JSONCPP_INCLUDE_DIRS})

#add_subdirectory(test)

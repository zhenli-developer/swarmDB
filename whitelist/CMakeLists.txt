FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

add_library(whitelist STATIC
        whitelist_base.hpp
        whitelist.hpp
        whitelist.cpp
        )

target_link_libraries(whitelist ${CURL_LIBRARIES})


#target_link_libraries(crud proto)
add_dependencies(whitelist jsoncpp)
target_include_directories(whitelist PRIVATE ${JSONCPP_INCLUDE_DIRS})

add_subdirectory(test)

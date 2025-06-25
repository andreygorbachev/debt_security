project("${PROJECT_NAME}_bill" LANGUAGES NONE)

add_subdirectory(include)

if(${DEBT-SECURITY_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)

endif()

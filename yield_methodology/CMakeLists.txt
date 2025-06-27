project("${PROJECT_NAME}_yield-methodology" LANGUAGES NONE)

add_subdirectory(include)

if(${DEBT-SECURITY_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)
  add_subdirectory(example)

endif()

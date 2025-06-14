project("${PROJECT_NAME}_quote" LANGUAGES NONE)

add_subdirectory(include)

if(${DEBT-SECURITY_BUILD_TESTS_AND_EXAMPLES})

	add_subdirectory(test)

endif()

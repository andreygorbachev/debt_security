project("${PROJECT_NAME}_quote" LANGUAGES NONE)

add_subdirectory(include)

if(NOT DEBT_SECURITY_MINIMAL)

	enable_testing()

	add_subdirectory(test)

endif()

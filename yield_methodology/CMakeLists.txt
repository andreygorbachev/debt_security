project("${PROJECT_NAME}_yield-methodology" LANGUAGES NONE)

add_subdirectory(include)

if(NOT DEBT_SECURITY_MINIMAL)

	add_subdirectory(test)

endif()

project("${PROJECT_NAME}_test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  bond.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  debt-security_bond
  calendar_static-data
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

project("${PROJECT_NAME}_test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  quote.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  debt-security_quote
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

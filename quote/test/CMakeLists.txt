project(quote-test)

add_executable(${PROJECT_NAME}
  quote.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  quote
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

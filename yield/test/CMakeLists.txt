project(yield-test)

add_executable(${PROJECT_NAME}
  yield.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  yield
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

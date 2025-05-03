project(yield-test)

add_executable(${PROJECT_NAME}
  ANBIMA.cpp
  yield.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  yield
  bill
  price
  cash-flow
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

project(bill-test)

add_executable(${PROJECT_NAME}
  bill.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  bill
  cash-flow
  calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

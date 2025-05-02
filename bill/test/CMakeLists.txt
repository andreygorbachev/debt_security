project(bill-test)

add_executable(${PROJECT_NAME}
  bill.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  bill
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

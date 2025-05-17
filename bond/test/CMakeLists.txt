project(bond-test)

add_executable(${PROJECT_NAME}
  bond.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  bond
  calendar
  cash-flow
  business-day-convention
  frequency
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

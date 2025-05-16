project(bond-test)

add_executable(${PROJECT_NAME}
  bond.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  bond
  cash-flow
  calendar
  business-day-convention
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

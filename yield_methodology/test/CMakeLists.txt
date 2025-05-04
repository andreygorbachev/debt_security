project(yield-methodology-test)

add_executable(${PROJECT_NAME}
  ANBIMA.cpp
  yield_methodology.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  yield-methodology
  bill
  quote
  cash-flow
  calendar
  business-day-convention
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

project(yield-methodology-test)

add_executable(${PROJECT_NAME}
  ANBIMA.cpp
  yield_methodology.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  yield-methodology
  bill
  quote
  calendar
  cash-flow # should probably be FinCalendar::cash-flow
  business-day-convention # should probably be FinCalendar::business-day-convention
  day-count # should probably be FinCalendar::day-count
  Boost::multiprecision
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

project("${PROJECT_NAME}_test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  bond.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  debt-security_bond
  calendar
  fin-calendar_cash-flow
  fin-calendar_business-day-convention
  fin-calendar_frequency
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

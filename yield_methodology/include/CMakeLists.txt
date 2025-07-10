# project "debt-security_yield-methodology"

add_library(${PROJECT_NAME} INTERFACE
  ANBIMA.h
  yield_methodology.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} INTERFACE
  debt-security_bill
  debt-security_quote
  calendar
  fin-calendar_cash-flow # should probably be FinCalendar::cash-flow
  fin-calendar_business-day-convention # should probably be FinCalendar::business-day-convention
  fin-calendar_day-count # should probably be FinCalendar::day-count
  reset
  Boost::config
  Boost::multiprecision
)

#export(TARGETS yield-methodology NAMESPACE YieldMethodology:: FILE YieldMethodology.cmake)

# project "debt-security_yield-methodology"

add_library(${PROJECT_NAME} INTERFACE
  ANBIMA.h
  yield_methodology.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} INTERFACE
  debt-security_bill
  debt-security_bond
  debt-security_quote
  calendar
  fin-calendar_day-count # should probably be FinCalendar::day-count
  reset
  Boost::config # only shold be here if decimals are always used
  Boost::multiprecision
)

#export(TARGETS yield-methodology NAMESPACE YieldMethodology:: FILE YieldMethodology.cmake)

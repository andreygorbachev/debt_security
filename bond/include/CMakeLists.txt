# project "debt-security_bond"

add_library(${PROJECT_NAME} INTERFACE
  bond.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} INTERFACE
  fin-calendar_cash-flow
  fin-calendar_business-day-convention
  fin-calendar_frequency
  fin-calendar_quasi-coupon-dates
  reset
)

#export(TARGETS bond NAMESPACE Bond:: FILE Bond.cmake)

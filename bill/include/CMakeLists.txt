# project "debt-security_bill"

add_library(${PROJECT_NAME} INTERFACE
  bill.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} INTERFACE
  fin-calendar_cash-flow
  fin-calendar_business-day-convention
)

#export(TARGETS bill NAMESPACE Bill:: FILE Bill.cmake)

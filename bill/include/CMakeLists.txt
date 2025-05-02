project("bill")

add_library(${PROJECT_NAME} INTERFACE
  bill.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS bill NAMESPACE Bill:: FILE Bill.cmake)

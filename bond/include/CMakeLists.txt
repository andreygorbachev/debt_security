project("bond")

add_library(${PROJECT_NAME} INTERFACE
  bond.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS bond NAMESPACE Bond:: FILE Bond.cmake)

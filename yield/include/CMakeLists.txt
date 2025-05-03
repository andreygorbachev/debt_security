project("yield")

add_library(${PROJECT_NAME} INTERFACE
  yield.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS yield NAMESPACE Yield:: FILE Yield.cmake)

project(yield-methodology)

add_library(${PROJECT_NAME} INTERFACE
  ANBIMA.h
  yield_methodology.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS yield-methodology NAMESPACE YieldMethodology:: FILE YieldMethodology.cmake)

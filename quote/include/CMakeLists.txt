project("quote")

add_library(${PROJECT_NAME} INTERFACE
  quote.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS quote NAMESPACE Quote:: FILE Quote.cmake)

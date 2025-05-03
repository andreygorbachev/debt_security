project("price")

add_library(${PROJECT_NAME} INTERFACE
  price.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS price NAMESPACE Price:: FILE Price.cmake)

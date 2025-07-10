project("${PROJECT_NAME}_LTN" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  LTN.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  debt-security_yield-methodology
  calendar_static-data
)

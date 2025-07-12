project("${PROJECT_NAME}_test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  ANBIMA.cpp
  yield_methodology.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  debt-security_yield-methodology
  calendar_static-data
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

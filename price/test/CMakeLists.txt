project(price-test)

add_executable(${PROJECT_NAME}
  price.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  price
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

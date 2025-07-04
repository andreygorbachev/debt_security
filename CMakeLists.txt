cmake_minimum_required(VERSION 3.15)

project("debt-security" VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

include(FetchContent)

set(CALENDAR_BUILD_TESTS_AND_EXAMPLES Off)
set(FIN-CALENDAR_BUILD_TESTS_AND_EXAMPLES Off)
set(RESET_BUILD_TESTS_AND_EXAMPLES Off)

FetchContent_Declare(
  calendar
  GIT_REPOSITORY https://github.com/andreygorbachev/calendar.git
  GIT_TAG        main
)

FetchContent_Declare(
  fin-calendar
  GIT_REPOSITORY https://github.com/andreygorbachev/fin_calendar.git
  GIT_TAG        main
)

FetchContent_Declare(
  reset
  GIT_REPOSITORY https://github.com/andreygorbachev/reset.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(
  calendar
  fin-calendar
  reset
)

FetchContent_Declare(
  Boost_config
  GIT_REPOSITORY https://github.com/boostorg/config.git
  GIT_TAG        boost-1.88.0
)

FetchContent_Declare(
  Boost_multiprecision
  GIT_REPOSITORY https://github.com/boostorg/multiprecision.git # should this project and all its dependencies use decimal only? (no templating for double, float, etc.)
  GIT_TAG        boost-1.88.0
)

FetchContent_MakeAvailable(
  Boost_config
  Boost_multiprecision
)

option(DEBT-SECURITY_BUILD_TESTS_AND_EXAMPLES "Build all of debt-security's own tests and examples." On)

if(${DEBT-SECURITY_BUILD_TESTS_AND_EXAMPLES})

  set(BUILD_GMOCK Off)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
  )

  FetchContent_MakeAvailable(googletest)

  enable_testing()

endif()

add_subdirectory(bill)
add_subdirectory(bond)
add_subdirectory(quote)
add_subdirectory(yield_methodology)

#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE DebtSecurity)

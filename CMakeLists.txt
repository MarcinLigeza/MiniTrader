cmake_minimum_required(VERSION 3.20)

project(MiniTrader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(minitrader INTERFACE)
target_include_directories(minitrader INTERFACE ${PROJECT_SOURCE_DIR}/include)

include(CTest)

if(BUILD_TESTING)
	find_package(GTest CONFIG QUIET)

	if(NOT TARGET GTest::gtest_main)
		include(FetchContent)
		message(STATUS "GTest not found, downloading with FetchContent.")
		FetchContent_Declare(
			googletest
			URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
			DOWNLOAD_EXTRACT_TIMESTAMP ON
		)
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
		FetchContent_MakeAvailable(googletest)
	endif()

	include(GoogleTest)
	add_executable(minitrader_domain_test src/tests/domain_test.cpp
		src/tests/interfaces_test.cpp)
	target_link_libraries(minitrader_domain_test PRIVATE minitrader GTest::gtest_main)
	gtest_discover_tests(minitrader_domain_test)
endif()

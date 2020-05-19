cmake_minimum_required(VERSION 3.17)

project(cppredicates CXX)

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(libcppredicates INTERFACE)

target_include_directories(libcppredicates INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(libcppredicates SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

target_sources(libcppredicates INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Circle2D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/cppredicates.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Plane3D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point2D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point3D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Ray2D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Sphere.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/typedefs.hpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Circle2D.tpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Plane3D.tpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point2D.tpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point3D.tpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Ray2D.tpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Sphere.tpp
)

add_subdirectory(original)

# Enabled / Disable tests 
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

# If tests are enabled, include tests directory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	add_subdirectory(tests)
endif()

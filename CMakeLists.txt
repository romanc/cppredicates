cmake_minimum_required(VERSION 3.17)

project(cppredicates CXX)

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set a default build type to Release
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(libcppredicates src/cppredicates.cpp)

target_include_directories(libcppredicates PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(libcppredicates SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

# target_sources(libcppredicates
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/cppredicates.cpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/cppredicates.hpp
# 
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Circle2D.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Circle2D_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Plane3D.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Plane3D_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point2D.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point2D_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point3D.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point3D_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Ray2D.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Ray2D_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Sphere.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Sphere_T.hpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/typedefs.hpp
# 
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Circle2D_T.tpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Plane3D_T.tpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point2D_T.tpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Point3D_T.tpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Ray2D_T.tpp
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/cppredicates/Sphere_T.tpp
# )

add_subdirectory(original)

# Enabled / Disable tests 
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)

	# If tests are enabled, include tests directory
	if(BUILD_TESTING)
		add_subdirectory(tests)
	endif()
endif()

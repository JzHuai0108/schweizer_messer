cmake_minimum_required(VERSION 3.5)
project(sm_timing)

# Use Ament
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(sm_common REQUIRED)
find_package(sm_random REQUIRED)

# Set C++ standard and strict ANSI compliance
add_definitions(-std=c++17 -D__STRICT_ANSI__)

##################
## Building ##
##################

add_library(${PROJECT_NAME} SHARED
  src/Timer.cpp
  src/NsecTimeUtilities.cpp
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Set dependencies for the target
ament_target_dependencies(${PROJECT_NAME} Boost sm_common sm_random)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
  ${sm_common_INCLUDE_DIRS}
)
# Export dependencies
ament_export_dependencies(Boost sm_common sm_random)
ament_export_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})

##################
## Testing ##
##################

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(${PROJECT_NAME}-test
    test/test_main.cpp
    test/TestTimestampCorrector.cpp
    test/TestNsecTimeUtilities.cpp
  )

  if(TARGET ${PROJECT_NAME}-test)
    target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
  endif()
endif()

##################
## Installation ##
##################

# Install library
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install include files
install(DIRECTORY include/
  DESTINATION include
)

# Finalize package
ament_package()

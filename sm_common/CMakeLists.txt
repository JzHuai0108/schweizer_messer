cmake_minimum_required(VERSION 3.5)
project(sm_common)

# Use Ament
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Enable warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Enable C++17 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define library
add_library(${PROJECT_NAME} SHARED
  src/hash_id.cpp
  src/progress_info.cpp
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Set dependencies for the target
ament_target_dependencies(${PROJECT_NAME} Boost)

# Export dependencies
ament_export_dependencies(Boost)
ament_export_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})

# Define include directories
target_include_directories(${PROJECT_NAME} PUBLIC
  ${Boost_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

#############
## Testing ##
#############

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(${PROJECT_NAME}-test
    test/test_main.cpp
    test/assert_macros.cpp
    test/assert_macros_dbg.cpp
    test/assert_macros_always_assert.cpp
    test/maths.cpp
    test/serialization_macros.cpp
    test/numerical_comparisons.cpp
    test/hash_id.cpp
  )

  target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
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

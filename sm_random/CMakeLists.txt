cmake_minimum_required(VERSION 3.5)
project(sm_random)

# Use Ament
find_package(ament_cmake REQUIRED)

##################
## Building ##
##################

add_library(${PROJECT_NAME} SHARED
  src/random.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_export_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})

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

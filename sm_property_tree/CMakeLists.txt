cmake_minimum_required(VERSION 3.5)
project(sm_property_tree)

# Use Ament
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(sm_common REQUIRED)

# Remove old definitions and set strict ANSI compliance
add_definitions(-D__STRICT_ANSI__)

##################
## Building ##
##################

add_library(${PROJECT_NAME} SHARED
  src/PropertyTree.cpp
  src/BoostPropertyTreeImplementation.cpp
  src/BoostPropertyTree.cpp
  src/PropertyTreeImplementation.cpp
  src/BoostPropertyTreeSupport.cpp
  src/BoostPropertyTreeLoader.cpp
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Set dependencies for the target
ament_target_dependencies(${PROJECT_NAME} Boost sm_common)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
)

# Export dependencies
ament_export_dependencies(Boost sm_common)
ament_export_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})

##################
## Testing ##
##################

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(${PROJECT_NAME}-test
    test/test_main.cpp
    test/BoostPropertyTreeImplementation.cpp
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

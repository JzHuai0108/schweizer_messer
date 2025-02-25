cmake_minimum_required(VERSION 3.5)
project(sm_eigen)

# Use Ament
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(Eigen3 REQUIRED)
find_package(sm_random REQUIRED)
find_package(sm_common REQUIRED)

##################
## Building ##
##################

add_library(${PROJECT_NAME} SHARED
  src/random.cpp
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Set dependencies for the target
ament_target_dependencies(${PROJECT_NAME} Boost Eigen3 sm_random sm_common)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

# Export dependencies
ament_export_dependencies(Boost Eigen3 sm_random sm_common)
ament_export_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})

##################
## Testing ##
##################

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  # Avoid clash with tr1::tuple
  add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=0)

  ament_add_gtest(${PROJECT_NAME}-test 
    test/test_main.cpp
    test/EigenSerializationTests.cpp
    test/MatrixSqrtTest.cpp
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

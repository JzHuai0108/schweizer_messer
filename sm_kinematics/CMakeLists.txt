cmake_minimum_required(VERSION 3.5)
project(sm_kinematics)

# Use Ament
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization filesystem)
find_package(Eigen3 REQUIRED)
find_package(sm_common REQUIRED)
find_package(sm_eigen REQUIRED)
find_package(sm_boost REQUIRED)
find_package(sm_random REQUIRED)

# Set C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

##################
## Building ##
##################

add_library(${PROJECT_NAME} SHARED
  src/quaternion_algebra.cpp
  src/rotations.cpp
  src/transformations.cpp
  src/RotationalKinematics.cpp
  src/RotationVector.cpp
  src/EulerAnglesZYX.cpp
  src/EulerAnglesYawPitchRoll.cpp
  src/EulerRodriguez.cpp
  src/Transformation.cpp
  src/homogeneous_coordinates.cpp
  src/HomogeneousPoint.cpp
  src/UncertainTransformation.cpp
  src/UncertainHomogeneousPoint.cpp
  src/three_point_methods.cpp
  src/EulerAnglesZXY.cpp
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)
# Set dependencies for the target
ament_target_dependencies(${PROJECT_NAME} Boost Eigen3 sm_common sm_eigen sm_boost sm_random)

# Export dependencies
ament_export_dependencies(Boost Eigen3 sm_common sm_eigen sm_boost sm_random)
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
    test/RotationalKinematicsTests.cpp
    test/QuaternionTests.cpp
    test/TransformationTests.cpp
    test/transformations.cpp
    test/HomogeneousPoint.cpp
    test/UncertainHomogeneousPoint.cpp
    test/test_main.cpp
    test/UncertainTransformationTests.cpp
    test/homogeneous_coordinates.cpp
    test/three_point_methods.cpp
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

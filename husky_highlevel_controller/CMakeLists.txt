cmake_minimum_required(VERSION 2.8.3)
project(husky_highlevel_controller)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES husky_highlevel_controller
  CATKIN_DEPENDS roscpp sensor_msgs
#  DEPENDS system_lib
)


include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} 
    src/${PROJECT_NAME}_node.cpp 
    src/${PROJECT_NAME}.cpp
    src/pid.cpp
)


target_link_libraries(${PROJECT_NAME} 
    ${catkin_LIBRARIES}
)



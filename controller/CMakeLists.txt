cmake_minimum_required(VERSION 3.0.2)
project(controller)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
  tf
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES controller
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs tf
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(controller_node src/controller_node.cpp)

target_link_libraries(controller_node ${catkin_LIBRARIES})

add_dependencies(controller_node ${catkin_EXPORTED_TARGETS} ${_EXPORTED_TARGETS})

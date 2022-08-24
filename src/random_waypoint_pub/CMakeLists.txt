cmake_minimum_required(VERSION 3.0.2)
project(random_waypoint_pub)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(randomWaypointsPub src/randomWaypoinstPub.cpp)
target_link_libraries(randomWaypointsPub ${catkin_LIBRARIES})
add_dependencies(randomWaypointsPub ${catkin_EXPORTED_TARGETS} ${_EXPORTED_TARGETS})

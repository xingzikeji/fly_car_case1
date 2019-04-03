cmake_minimum_required(VERSION 2.8.3)
project(videoread)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages



find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  message_generation
  std_msgs
)
find_package(OpenCV REQUIRED)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   xypixel.msg
 )


## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(
  CATKIN_DEPENDS
  message_runtime)


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ./include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(video_sub src/video_sub.cpp)
target_link_libraries(video_sub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(video_pub src/video_pub.cpp)
target_link_libraries(video_pub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})





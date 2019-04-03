cmake_minimum_required(VERSION  2.8.3)
project(observe_msgs)

find_package(catkin  REQUIRED  COMPONENTS
   message_generation
   std_msgs
   geometry_msgs
   actionlib_msgs
   sensor_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_message_files(
   DIRECTORY   msg
   FILES
   ReconnaissanceInfo.msg
   InfradImage.msg
   VisibleImage.msg
   Gnss.msg
   Imu.msg
 #  BoundingBox.msg
 #  BoundingBoxes.msg
   MovObject.msg
   TotalMovObject.msg
   GetImages.msg
    xypixel.msg
   xypixelStamped.msg
)

add_service_files(
  DIRECTORY  srv
  FILES
  Reconnaissance.srv
  taskReconnaissance.srv
  loadPlugins.srv
  activatePlugins.srv
  getSensorActorTopic.srv
)

#add_action_files(
 #  DIRECTORY
 ##  action
  ## FILES

  ## example.action

#)

generate_messages(DEPENDENCIES  std_msgs   geometry_msgs  actionlib_msgs sensor_msgs)

catkin_package(
  CATKIN_DEPENDS  message_runtime   std_msgs  geometry_msgs   actionlib_msgs  sensor_msgs
)


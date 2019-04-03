cmake_minimum_required(VERSION 2.8.3)
project(plan)

set(CMAKE_CXX_STANDARD 11)
if (NOT CMAKE_BUILD_TYPE)
    # Options: Debug, Release, MinSizeRel, RelWithDebInfo
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "-fopenmp")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  commond_msgs
)
find_package(Eigen3 REQUIRED)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

# Generate dynamic reconfigure parameters in the 'cfg' folder


catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES
  CATKIN_DEPENDS roscpp rospy  commond_msgs
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIRS})

## Declare a C++ executable
#add_executable(rosplane_controller
#            src/controller_base.cpp
#            src/controller_example.cpp)
#add_dependencies(rosplane_controller ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)
#target_link_libraries(rosplane_controller ${catkin_LIBRARIES})

#add_executable(rosplane_controller99
#            src/controller_base99.cpp
#            src/controller_example99.cpp)
#add_dependencies(rosplane_controller99 ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)
#target_link_libraries(rosplane_controller99 ${catkin_LIBRARIES})




## Declare a C++ executable
add_executable(rosplan_path_planner
            src/path_planner.cpp)
add_dependencies(rosplan_path_planner ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner ${catkin_LIBRARIES})

add_executable(rosplan_path_planner1
            src/path_planner1.cpp)
add_dependencies(rosplan_path_planner1 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner1 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner2
            src/path_planner2.cpp)
add_dependencies(rosplan_path_planner2 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner2 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner3
            src/path_planner3.cpp)
add_dependencies(rosplan_path_planner3 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner3 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner4
            src/path_planner4.cpp)
add_dependencies(rosplan_path_planner4 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner4 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner5
            src/path_planner5.cpp)
add_dependencies(rosplan_path_planner5 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner5 ${catkin_LIBRARIES})


add_executable(rosplan_path_planner6
            src/path_planner6.cpp)
add_dependencies(rosplan_path_planner6 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner6 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner7
            src/path_planner7.cpp)
add_dependencies(rosplan_path_planner7 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner7 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner8
            src/path_planner8.cpp)
add_dependencies(rosplan_path_planner8 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner8 ${catkin_LIBRARIES})


add_executable(rosplan_path_planner9
            src/path_planner9.cpp)
add_dependencies(rosplan_path_planner9 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner9 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner10
            src/path_planner10.cpp)
add_dependencies(rosplan_path_planner10 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner10 ${catkin_LIBRARIES})

add_executable(rosplan_path_planner11
            src/path_planner11.cpp)
add_dependencies(rosplan_path_planner11 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosplan_path_planner11 ${catkin_LIBRARIES})



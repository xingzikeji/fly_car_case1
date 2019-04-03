cmake_minimum_required(VERSION 2.8.3)
project(Identification)

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
  observe_msgs
  nav_msgs
  geometry_msgs
 message_filters
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
  CATKIN_DEPENDS roscpp rospy  commond_msgs  observe_msgs nav_msgs
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
add_executable(rosident_path_manager
            src/ipath_planner.cpp)
add_dependencies(rosident_path_manager ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager ${catkin_LIBRARIES})


add_executable(rosident_path_manager1
            src/ipath_planner1.cpp)
add_dependencies(rosident_path_manager1 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager1 ${catkin_LIBRARIES})


add_executable(rosident_path_manager2
            src/ipath_planner2.cpp)
add_dependencies(rosident_path_manager2 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager2 ${catkin_LIBRARIES})

add_executable(rosident_path_manager3
            src/ipath_planner3.cpp)
add_dependencies(rosident_path_manager3 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager3 ${catkin_LIBRARIES})


add_executable(rosident_path_manager4
            src/ipath_planner4.cpp)
add_dependencies(rosident_path_manager4 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager4 ${catkin_LIBRARIES}
/opt/ros/kinetic/lib/libmessage_filters.so)

add_executable(rosident_path_manager5
            src/ipath_planner5.cpp)
add_dependencies(rosident_path_manager5 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager5 ${catkin_LIBRARIES})

add_executable(rosident_path_manager6
            src/ipath_planner6.cpp)
add_dependencies(rosident_path_manager6 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager6 ${catkin_LIBRARIES})

add_executable(rosident_path_manager7
            src/ipath_planner7.cpp)
add_dependencies(rosident_path_manager7 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager7 ${catkin_LIBRARIES})

add_executable(rosident_path_manager8
            src/ipath_planner8.cpp)
add_dependencies(rosident_path_manager8 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager8 ${catkin_LIBRARIES})

add_executable(rosident_path_manager9
            src/ipath_planner9.cpp)
add_dependencies(rosident_path_manager9 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager9 ${catkin_LIBRARIES})

add_executable(rosident_path_manager10
            src/ipath_planner10.cpp)
add_dependencies(rosident_path_manager10 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager10 ${catkin_LIBRARIES})


add_executable(rosident_path_manager11
            src/ipath_planner11.cpp)
add_dependencies(rosident_path_manager11 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager11 ${catkin_LIBRARIES})


add_executable(rosident_path_manager12
            src/ipath_planner12.cpp)
add_dependencies(rosident_path_manager12 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager12 ${catkin_LIBRARIES})

add_executable(rosident_path_manager13
            src/ipath_planner13.cpp)
add_dependencies(rosident_path_manager13 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager13 ${catkin_LIBRARIES})

add_executable(rosident_path_manager14
            src/ipath_planner14.cpp)
add_dependencies(rosident_path_manager14 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager14 ${catkin_LIBRARIES})

add_executable(rosident_path_manager15
            src/ipath_planner15.cpp)
add_dependencies(rosident_path_manager15 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager15 ${catkin_LIBRARIES})

add_executable(rosident_path_manager16
            src/ipath_planner16.cpp)
add_dependencies(rosident_path_manager16 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager16 ${catkin_LIBRARIES})

add_executable(rosident_path_manager17
            src/ipath_planner17.cpp)
add_dependencies(rosident_path_manager17 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager17 ${catkin_LIBRARIES})

add_executable(rosident_path_manager18
            src/ipath_planner18.cpp)
add_dependencies(rosident_path_manager18 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager18 ${catkin_LIBRARIES})

add_executable(rosident_path_manager19
            src/ipath_planner19.cpp)
add_dependencies(rosident_path_manager19 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager19 ${catkin_LIBRARIES})

add_executable(rosident_path_manager20
            src/ipath_planner20.cpp)
add_dependencies(rosident_path_manager20 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager20 ${catkin_LIBRARIES})

add_executable(rosident_path_manager21
            src/ipath_planner21.cpp)
add_dependencies(rosident_path_manager21 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager21 ${catkin_LIBRARIES})

add_executable(rosident_path_manager22
            src/ipath_planner22.cpp)
add_dependencies(rosident_path_manager22 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager22 ${catkin_LIBRARIES})

add_executable(rosident_path_manager23
            src/ipath_planner23.cpp)
add_dependencies(rosident_path_manager23 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager23 ${catkin_LIBRARIES})

add_executable(rosident_path_manager24
          src/ipath_planner24.cpp)
add_dependencies(rosident_path_manager24 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager24 ${catkin_LIBRARIES})

add_executable(rosident_path_manager27
          src/ipath_planner27.cpp)
add_dependencies(rosident_path_manager27 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager27 ${catkin_LIBRARIES})

add_executable(rosident_path_manager28
          src/ipath_planner28.cpp)
add_dependencies(rosident_path_manager28 ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosident_path_manager28 ${catkin_LIBRARIES})


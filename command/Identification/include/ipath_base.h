//* @author AIRC-DA group,questions contack kobe.


#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h>   


namespace irosplane
{



class ipath_follower_base
{
public:
  ipath_follower_base();
  float spin();

private:
  ros::NodeHandle nh_;
  ros::NodeHandle nh_private_;
  ros::Subscriber iwaypoint_sub;
  
  ros::Publisher iwaypointPublisher;

  commond_msgs:: IWaypoint iwaypoint_path;
  commond_msgs:: Waypoint   waypoint_path;
  
  
  void iwaypoint_path_Callback(const commond_msgs::IWaypoint &msg);

 
};

} // end namespace

 // PATH_FOLLOWER_BASE_H

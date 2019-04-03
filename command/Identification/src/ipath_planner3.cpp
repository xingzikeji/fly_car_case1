#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h>   
#include <observe_msgs/xypixel.h>
#include <observe_msgs/xypixelStamped.h> 
ros::Publisher iwaypointPublisher;
ros::Subscriber iwaypoint_sub;

//void iwaypoint_path_Callback(const commond_msgs::IWaypoint &msg);



void iwaypoint_path_Callback(const observe_msgs::xypixelStamped::ConstPtr &msg)
{  commond_msgs::Waypoint inew_waypoint;
   inew_waypoint.w[0]=15.0;
   inew_waypoint.w[1]=0.0;
   inew_waypoint.w[2]=-3.0;
   inew_waypoint.lat = 0;
   inew_waypoint.lon = 0;
   inew_waypoint.chi_d = 0;
   inew_waypoint.chi_valid = false;
   inew_waypoint.Va_d = 3;
   inew_waypoint.set_current =true;
   inew_waypoint.landing =false;
   inew_waypoint.takeoff =false;
   inew_waypoint.clear_wp_list = false;
  iwaypointPublisher.publish(inew_waypoint);
 }
int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
 iwaypoint_sub = nh_.subscribe("/xypixel",10, iwaypoint_path_Callback);
 iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
ros::spin();
return 0;
}              






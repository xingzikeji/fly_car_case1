#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h>   

//void iwaypoint_path_Callback(const commond_msgs::IWaypoint &msg);
commond_msgs::Waypoint inew_waypoint;


void iwaypoint_path_Callback(const commond_msgs::IWaypoint &msg)
{  inew_waypoint.w[0]=msg.w[0];
   inew_waypoint.w[1]=msg.w[1];
   inew_waypoint.w[2]=msg.w[2];
   inew_waypoint.lat = 0;
   inew_waypoint.lon = 0;
   inew_waypoint.chi_d = 0;
   inew_waypoint.chi_valid = false;
   inew_waypoint.Va_d = 0;
   inew_waypoint.set_current = true;
   inew_waypoint.landing =true;
   inew_waypoint.takeoff =false;
   inew_waypoint.clear_wp_list = false;
 }
int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
ros::Subscriber iwaypoint_sub = nh_.subscribe("iwaypoint_path",10, iwaypoint_path_Callback);
ros::Publisher iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("waypoint_path", 10);
iwaypointPublisher.publish(inew_waypoint);
ros::spin();
return 0;
}              






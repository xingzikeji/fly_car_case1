#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h>  
#include <observe_msgs/xypixelStamped.h>
 
ros::Publisher iwaypointPublisher;
ros::Subscriber iwaypoint_sub;

//void iwaypoint_path_Callback(const commond_msgs::IWaypoint &msg);



void iwaypoint_path_Callback(const observe_msgs::xypixelStamped::ConstPtr &msg)
{  ros::NodeHandle nh_;
   iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("waypoint_path", 10);
   commond_msgs::Waypoint inew_waypoint;
   observe_msgs::xypixelStamped bebop_state;
    float a;
    bebop_state =*msg;
   inew_waypoint.w[0]=bebop_state.xypixel.w[0];
   inew_waypoint.w[1]=bebop_state.xypixel.w[1];
   inew_waypoint.w[2]=bebop_state.xypixel.w[2];
   inew_waypoint.lat = 0;
   inew_waypoint.lon = 0;
   inew_waypoint.chi_d = 0;
   inew_waypoint.chi_valid = false;
   inew_waypoint.Va_d = 0;
   inew_waypoint.set_current =true;
   inew_waypoint.landing =true;
   inew_waypoint.takeoff =false;
   inew_waypoint.clear_wp_list = false;
  iwaypointPublisher.publish(inew_waypoint);
 }
int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
 iwaypoint_sub = nh_.subscribe("/xypixel",10, iwaypoint_path_Callback);
 ros::spin();
return 0;
}              






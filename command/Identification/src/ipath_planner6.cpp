#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <commond_msgs/Waypoint.h>

ros::Publisher iwaypointPublisher;
ros::Subscriber iwaypoint_sub;
ros::Subscriber iwaypoint_sub1;
float c;
void iwaypoint_path_Callback1(const nav_msgs::Odometry::ConstPtr &msg1)
{
    nav_msgs::Odometry bebop_state;
      bebop_state = *msg1;
       c=bebop_state.pose.pose.position.z;
}



void iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{ ros::NodeHandle nh;
 iwaypointPublisher = nh.advertise<commond_msgs::Waypoint>("waypoint_path", 10);
  commond_msgs::Waypoint inew_waypoint;
     if(c<=-198)
   {nav_msgs::Odometry bebop_state;
   bebop_state =*msg;
   inew_waypoint.w[0]=bebop_state.pose.pose.position.x;
   inew_waypoint.w[1]=bebop_state.pose.pose.position.y;
   inew_waypoint.w[2]=bebop_state.pose.pose.position.z;
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
 }

int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
 iwaypoint_sub = nh_.subscribe("/bebop_1/objection_xyz",10, iwaypoint_path_Callback);
 iwaypoint_sub1 = nh_.subscribe("/bebop_1/ground_truth/state",10, iwaypoint_path_Callback1);
 ros::spin();
return 0;
}              

#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h> 
#include <nav_msgs/Odometry.h>
ros::Publisher iwaypointPublisher;
ros::Subscriber iwaypoint_sub;
void state_callback(const nav_msgs::Odometry::ConstPtr &msg1)
{commond_msgs::Waypoint inew_waypoint;
 nav_msgs::Odometry bebop_state;
 float a, b;
 bebop_state = *msg1;
 a = bebop_state.pose.pose.position.x;
 b = bebop_state.pose.pose.position.y;
 if( a>10 && a<20 && b>-5 && b<5 )
 { inew_waypoint.w[0]=15.0;
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
}



int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
iwaypoint_sub = nh_.subscribe("/bebop_1/ground_truth/state",10, state_callback);
ros::spin();
return 0;

}
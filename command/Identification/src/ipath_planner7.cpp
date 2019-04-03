#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h> 
#include <observe_msgs/xypixel.h>
#include <observe_msgs/xypixelStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <nav_msgs/Odometry.h>

ros::Publisher iwaypointPublisher1;
ros::Publisher iwaypointPublisher2;
ros::Publisher iwaypointPublisher3;
ros::Subscriber iwaypoint_sub1;
ros::Subscriber iwaypoint_sub2;
float a,b;

void iwaypoint_path_Callback1(const nav_msgs::Odometry::ConstPtr &msg1)
{nav_msgs::Odometry bebop_state;
  bebop_state = *msg1;
  a = bebop_state.pose.pose.position.x;
  b = bebop_state.pose.pose.position.y;
}

 void  iwaypoint_path_Callback2 (const observe_msgs::xypixelStamped::ConstPtr &msg2)
{   ros::NodeHandle nh;
iwaypointPublisher1 = nh.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
iwaypointPublisher2 = nh.advertise<commond_msgs::Waypoint>("/bebop_3/waypoint_path", 10);
iwaypointPublisher3 = nh.advertise<commond_msgs::Waypoint>("/bebop_4/waypoint_path", 10);
commond_msgs::Waypoint inew_waypoint;
    if( a>10 && a<20 && b>-5 && b<5 )
 {inew_waypoint.w[0]=15.0;
  inew_waypoint.w[1]=0.0;
  inew_waypoint.w[2]=-3.0;
  inew_waypoint.lat = 0;
  inew_waypoint.lon = 0;
  inew_waypoint.chi_d = 0;
  inew_waypoint.chi_valid = false;
  inew_waypoint.Va_d = 5;
  inew_waypoint.set_current =true;
  inew_waypoint.landing =false;
  inew_waypoint.takeoff =false;
  inew_waypoint.clear_wp_list = false;
  iwaypointPublisher1.publish(inew_waypoint);
 }  

if( a>25 && a<35 && b>-5 && b<5 )
 { inew_waypoint.w[0]=30.0;
  inew_waypoint.w[1]=0.0;
  inew_waypoint.w[2]=-3.0;
  inew_waypoint.lat = 0;
  inew_waypoint.lon = 0;
  inew_waypoint.chi_d = 0;
  inew_waypoint.chi_valid = false;
  inew_waypoint.Va_d = 5;
  inew_waypoint.set_current =true;
  inew_waypoint.landing =false;
  inew_waypoint.takeoff =false;
  inew_waypoint.clear_wp_list = false;
  iwaypointPublisher2.publish(inew_waypoint);
 }  

if( a>40 && a<50 && b>-5 && b<5 )
 { inew_waypoint.w[0]=50.0;
  inew_waypoint.w[1]=0.0;
  inew_waypoint.w[2]=-3.0;
  inew_waypoint.lat = 0;
  inew_waypoint.lon = 0;
  inew_waypoint.chi_d = 0;
  inew_waypoint.chi_valid = false;
  inew_waypoint.Va_d = 5;
  inew_waypoint.set_current =true;
  inew_waypoint.landing =false;
  inew_waypoint.takeoff =false;
  inew_waypoint.clear_wp_list = false;
  iwaypointPublisher3.publish(inew_waypoint);
 }  



}

 

int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
iwaypoint_sub1 = nh_.subscribe("/bebop_1/ground_truth/state",10, iwaypoint_path_Callback1);
iwaypoint_sub2 = nh_.subscribe("/xypixel",10, iwaypoint_path_Callback2);
ros::spin();
return 0;

}

#include<stdio.h>
#include<math.h>
#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <nav_msgs/Odometry.h>

ros::Publisher iwaypointPublisher1;
ros::Publisher iwaypointPublisher2;
ros::Publisher iwaypointPublisher3;
ros::Subscriber iwaypoint_sub1;
ros::Subscriber iwaypoint_sub2;
ros::Subscriber iwaypoint_sub;
double a2,a3,b2,b3;

void iwaypoint_path_Callback1(const nav_msgs::Odometry::ConstPtr &msg2)
{    nav_msgs::Odometry bebop_state;
      bebop_state = *msg2;
       a2=bebop_state.pose.pose.position.x;
       b2=bebop_state.pose.pose.position.y;
}

void iwaypoint_path_Callback2(const nav_msgs::Odometry::ConstPtr &msg3)
{    nav_msgs::Odometry bebop_state;
      bebop_state = *msg3;
       a3=bebop_state.pose.pose.position.x;
       b3=bebop_state.pose.pose.position.y;
}


void  iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
ros::NodeHandle nh;
iwaypointPublisher1 = nh.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
iwaypointPublisher2 = nh.advertise<commond_msgs::Waypoint>("/bebop_3/waypoint_path", 10);
iwaypointPublisher3 = nh.advertise<commond_msgs::Waypoint>("/bebop_4/waypoint_path", 10);
commond_msgs::Waypoint inew_waypoint;
  nav_msgs::Odometry bebop_state;
  bebop_state = *msg;
  if(a2>-0.5 && a2<0.5 )
  { inew_waypoint.w[0]=bebop_state.pose.pose.position.x;
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
  iwaypointPublisher1.publish(inew_waypoint);
  }
 float c2,c3;
  c2=abs(a2-0)+abs(b2-6);
  if(c2>4&& a3>-0.5 && a3<0.5 )
  {  inew_waypoint.w[0]=bebop_state.pose.pose.position.x;
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
  iwaypointPublisher2.publish(inew_waypoint);
}
  c3=abs(a3-0)+abs(b3+6);
  if(c3>4)
  {  inew_waypoint.w[0]=bebop_state.pose.pose.position.x;
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
  iwaypointPublisher3.publish(inew_waypoint);
}

}


int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
 iwaypoint_sub1 = nh_.subscribe("/bebop_2/ground_truth/state",10, iwaypoint_path_Callback1);
 iwaypoint_sub2 = nh_.subscribe("/bebop_3/ground_truth/state",10, iwaypoint_path_Callback2);
 iwaypoint_sub = nh_.subscribe("/bebop_1/objection_xyz",10, iwaypoint_path_Callback);
 ros::spin();
return 0;
}        

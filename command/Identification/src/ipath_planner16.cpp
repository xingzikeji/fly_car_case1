#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <commond_msgs/Waypoint.h>

ros::Publisher iwaypointPublisher;
ros::Publisher iwaypointPublisher1;
ros::Subscriber iwaypoint_sub;
ros::Subscriber iwaypoint_sub1;
ros::Subscriber iwaypoint_sub2;
ros::Subscriber iwaypoint_sub3;
double n_v=0;
double n_1,n_2,n_3,n_4;

void iwaypoint_path_Callback2(const nav_msgs::Odometry::ConstPtr &msg)
{
nav_msgs::Odometry bebop_state;
   bebop_state =*msg;
n_1=bebop_state.pose.pose.position.x;
n_2=bebop_state.pose.pose.position.y;
}

void iwaypoint_path_Callback3(const nav_msgs::Odometry::ConstPtr &msg)
{
nav_msgs::Odometry bebop_state;
   bebop_state =*msg;
n_3=bebop_state.pose.pose.position.x;
n_4=bebop_state.pose.pose.position.y;
}


void iwaypoint_path_Callback1(const geometry_msgs::Twist::ConstPtr &msg)
{ geometry_msgs::Twist cmd_vel;
  cmd_vel=*msg;
  n_v=cmd_vel.linear.x;
}


void iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{  double n_x,n_y,n_z;
   double T;
   T=fabs(n_1 - n_3) + fabs(n_2 - n_4);
   commond_msgs::Waypoint inew_waypoint;
   nav_msgs::Odometry bebop_state;
   bebop_state =*msg;
   n_x=bebop_state.pose.pose.position.x;
   n_y=bebop_state.pose.pose.position.y;
   n_z=0;
   if(n_v==0&& T<0.2)
  { inew_waypoint.w[0]=n_x;
  inew_waypoint.w[1]=n_y;
  inew_waypoint.w[2]=0;
   inew_waypoint.lat = 0;
   inew_waypoint.lon = 0;
   inew_waypoint.chi_d = 0;
   inew_waypoint.chi_valid = false;
   inew_waypoint.Va_d = 0;
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
 iwaypoint_sub1= nh_.subscribe("/bebop_1/cmd_vel",10, iwaypoint_path_Callback1);
 iwaypoint_sub2= nh_.subscribe("/bebop_1/ground_truth/state",10, iwaypoint_path_Callback2);
 iwaypoint_sub3= nh_.subscribe("/bebop_2/ground_truth/state",10, iwaypoint_path_Callback3);
 iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
ros::spin();
return 0;
}              

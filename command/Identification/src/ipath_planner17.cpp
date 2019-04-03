#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <commond_msgs/Waypoint.h>

ros::Publisher iwaypointPublisher;
ros::Publisher iwaypointPublisher1;
ros::Subscriber iwaypoint_sub;
ros::Subscriber iwaypoint_sub1;
double n_v=0;
int n=0;

double tx=0;
double ty=0;
double tz=0;
void add_position(double x, double y, double z)
{
if (n<30)
{
tx= tx + x;
ty= ty + y;
tz= z;
n++;
}

}

void iwaypoint_path_Callback1(const geometry_msgs::Twist::ConstPtr &msg)
{ geometry_msgs::Twist cmd_vel;
  cmd_vel=*msg;
  n_v=cmd_vel.linear.x;
}

void iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{  double n_x,n_y,n_z;
   commond_msgs::Waypoint inew_waypoint, inew_waypoint1;
   nav_msgs::Odometry bebop_state;
   bebop_state =*msg;
   n_x=bebop_state.pose.pose.position.x;
   n_y=bebop_state.pose.pose.position.y;
   n_z=bebop_state.pose.pose.position.z;
   add_position(n_x, n_y, n_z);
if(n==30)
 { 
   inew_waypoint.w[0]=tx/n;
  inew_waypoint.w[1]=ty/n;
  inew_waypoint.w[2]=tz;
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

if(n_v>0)
{inew_waypoint1.w[0]=tx/n;
  inew_waypoint1.w[1]=ty/n;
  inew_waypoint1.w[2]=-3.6;
   inew_waypoint1.lat = 0;
   inew_waypoint1.lon = 0;
   inew_waypoint1.chi_d = 0;
   inew_waypoint1.chi_valid = false;
   inew_waypoint1.Va_d = 3;
   inew_waypoint1.set_current =true;
   inew_waypoint1.landing =false;
   inew_waypoint1.takeoff =false;
   inew_waypoint1.clear_wp_list = false;

  iwaypointPublisher1.publish(inew_waypoint1);}
}
 }

int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
 iwaypoint_sub = nh_.subscribe("/bebop_2/objection_xyz",10, iwaypoint_path_Callback);
  iwaypoint_sub1= nh_.subscribe("/bebop_2/cmd_vel",10, iwaypoint_path_Callback1);
 iwaypointPublisher = nh_.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
 iwaypointPublisher1 = nh_.advertise<commond_msgs::Waypoint>("/bebop_3/waypoint_path", 10);
ros::spin();
return 0;
}              

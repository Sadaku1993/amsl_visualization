#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>

ros::Publisher pub_x;
ros::Publisher pub_y;
ros::Publisher pub_z;

void odom_Callback(const nav_msgs::OdometryConstPtr& msg)
{
 	std_msgs::Float32 vel_x;
	vel_x.data = msg->twist.twist.linear.x;
	
	std_msgs::Float32 vel_y;
	vel_y.data = msg->twist.twist.linear.y;
 	
	pub_x.publish(vel_x);
	pub_y.publish(vel_y);
}

void imu_Callback(const sensor_msgs::ImuConstPtr& msg)
{
	std_msgs::Float32 vel_z;
	vel_z.data = msg->angular_velocity.z;
	
	pub_z.publish(vel_z);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "linear_plotter");
    ros::NodeHandle n;
    
    ros::Rate rate(10);

    ros::Subscriber sub_odom = n.subscribe("/odom", 1, odom_Callback);
	ros::Subscriber sub_imu = n.subscribe("/imu/data", 1, imu_Callback);
	pub_x = n.advertise<std_msgs::Float32>("/linear/x/plotter", 1);
	pub_y = n.advertise<std_msgs::Float32>("/linear/y/plotter", 1);
	pub_z = n.advertise<std_msgs::Float32>("/linear/z/plotter", 1);

	while(ros::ok())
	{
		ros::spinOnce();
		rate.sleep();
	}

    return 0;
}

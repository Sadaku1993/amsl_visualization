#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Header.h>

#include <jsk_rviz_plugins/Pictogram.h>

ros::Publisher pub;

void odom_Callback(const nav_msgs::OdometryConstPtr& msg)
{
    jsk_rviz_plugins::Pictogram pictogram;
    pictogram.header.frame_id = msg->header.frame_id;
    pictogram.header.stamp = ros::Time::now();

    pictogram.pose.position.x = msg->pose.pose.position.x;
    pictogram.pose.position.y = msg->pose.pose.position.y;
    pictogram.pose.position.z = 2.0;
    pictogram.pose.orientation.x = 0.7;
    pictogram.pose.orientation.y = 0;
    pictogram.pose.orientation.z = 0.7;
    pictogram.pose.orientation.w = 0;

    pictogram.action = pictogram.ROTATE_X;
    pictogram.mode   = pictogram.PICTOGRAM_MODE;
    pictogram.character = "fa-wifi";
    pictogram.size = 2;
    pictogram.speed = 2.0;
    pictogram.color.r = 25/255.0;
    pictogram.color.g = 255/255.0;
    pictogram.color.b = 240/255.0;
    pictogram.color.a = 1.0;
    pub.publish(pictogram);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_pictogram");
    ros::NodeHandle n;
    
    ros::Rate rate(20);

    ros::Subscriber sub = n.subscribe("/odom", 1, odom_Callback);
    pub = n.advertise<jsk_rviz_plugins::Pictogram>("/odom/pictogram", 1);

    ros::spin();

    return 0;
}

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

//ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

//Service function
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req_x_vel, ball_chaser::DriveToTarget::Response & res_x_vel)
{
    ROS_INFO("DriveToTarget received -linear_x:%1.2f, angular_z:%1.2f", (float)req_x_vel.linear_x, (float)req_x_vel.angular_z);
    
    //Initialize the motor command request to be published
    geometry_msgs::Twist motor_command;

    motor_command.linear.x= req_x_vel.linear_x;
    motor_command.angular.z= req_x_vel.angular_z;

    motor_command_publisher.publish(motor_command);

    //MSG_FEEDBACK(RESPONSE)
    res_x_vel.msg_feedback = "Motor command is set - linear_x: " + std::to_string(req_x_vel.linear_x) + "  angular_z: "  +std::to_string(req_x_vel.angular_z);

    ROS_INFO_STREAM(res_x_vel.msg_feedback);

return true;
}

int main(int argc, char** argv)
{
    //intialize the drive_bot node and create a handle to it
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;


    //Define the publisher to publish the std::msgs::Float64 messages on linear_x and angular_z
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    //Define a driver /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer service =n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send drive commands");

    //Handle ROS communication events
    ros::spin();

    return 0;
} 
#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/Image.h"

//Define global client that can request a service
ros::ServiceClient client;

//This function calls the command_robot service to drive the robot
//in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("DIRECT ROBOT");

    //Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = (float)lin_x;
    srv.request.angular_z =(float)ang_z;

    //Call the command_robot service and pass the motor commands
    if(!client.call(srv))
    {
        ROS_ERROR("Failed to call the service command_robot");
    }

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;
    int col = 0;
    bool ball_search = false;

    for(int i=0; i< img.height * img.step; i += 3)
    {
        if((img.data[i] == 255) && (img.data[i+1] == 255) && img.data[i+2] == 255)
        {
            col = i % img.step;

            if(col < img.step/3)
            {
                drive_robot(0.5, 1);
            }    
            else if(col < (img.step/3 * 2))
            {
                drive_robot(0.5, 0);
            }
            else
            {
                drive_robot(0.5, -1);
            }
            ball_search = true;
            break;
        }
    }
    if(ball_search == false)
    {
        drive_robot(0, 0);
    }
}


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}


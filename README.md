# Ball_Chaser_Project

In this project, two ROS packages created inside the catkin_ws/src: the drive_bot and the ball_chaser. Here are the steps to design the robot, house it inside your world, and program it to chase white-colored balls:

drive_bot:

1. Create a my_robot ROS package to hold your robot, the white ball, and the world.
2. Design a differential drive robot with the Unified Robot Description Format. Add two sensors to your robot: a lidar and a camera. Add Gazebo plugins for your robot’s differential drive, lidar, and camera. The robot you design should be significantly different from the one presented in the project lesson. Minimum required changes are adjusting the color, wheel radius, and chassis dimensions. You can also completely redesign the robot model! After all, you want to impress your future employers :-D
3. Create a new world, which is different from the world you built in the Build My World project and house your robot inside that world.
4. Add a white-colored ball to your Gazebo world and save a new copy of this world.
5. The world.launch file should launch your world with the white-colored ball and your robot.

ball_chaser:

1. Create a ball_chaser ROS package to hold your C++ nodes.
2. Write a drive_botC++ node that will provide a ball_chaser/command_robot service to drive the robot by controlling its linear x and angular z velocities. The service should publish to the wheel joints and return back the requested velocities.
3. Write a process_image C++ node that reads your robot’s camera image, analyzes it to determine the presence and position of a white ball. If a white ball exists in the image, your node should request a service via a client to drive the robot towards it.
4. The ball_chaser.launch should run both the drive_bot and the process_image nodes.

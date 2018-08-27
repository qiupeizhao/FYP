#!/usr/bin/env python

import math
from math import sin, cos, pi

import rospy
import tf
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3



wheelSep = 0.225; #m
leftFrontConv, leftBackConv, rightFrontConv, rightBackConv = 1602.8, 1551.2, 1597.5, 1561.5; #In encoder ticks/m, determined experimentally. 


#Covariance values as constants. We only care about the plane of motion, and not height or rotation in any direction but around z. 
cov_x = 1e-6;
cov_y = 1e-6;
cov_yaw = 0.01; #These values are currently guesses. 



x = 0.0;
y = 0.0;
theta = 0.0;
vx = 0.0;
vy = 0.0;
omega = 0.0;



def handleTicks(data):
	global x;
	global y;
	global theta;
	global vx;
	global vy;
	global omega;
	


	leftFront, leftBack, rightFront, rightBack, dt = [float(num) for num in str(data.data).split()];
	dt *= 0.001;	
	leftFront /= leftFrontConv;
	leftBack /= leftBackConv;
	rightFront /= rightFrontConv;
	rightBack /= rightBackConv;

	#Replace these lines with either entirely back or entirely front if needed. 
	leftAvg = (leftFront+leftBack)/2;
	rightAvg = (rightFront+rightBack)/2;
	

	dcenter = (leftAvg+rightAvg)/2; #Distance center travels. 
	dtheta = (rightAvg-leftAvg)/wheelSep;
	
	dx = dcenter*cos(theta);
	dy = dcenter*sin(theta);

	vx = dx/dt;
	vy = dy/dt;
	omega = theta/dt;

	x += dx;
	y += dy;
	theta += dtheta;
	


	currentTime = rospy.Time.now();

	# since all odometry is 6DOF we'll need a quaternion created from yaw
	odom_quat = tf.transformations.quaternion_from_euler(0, 0, theta);

    # first, we'll publish the transform over tf
#	odom_broadcaster.sendTransform(
#		(x, y, 0.),
#		odom_quat,
#		currentTime,
#		"not_base_link",
#		"odom"
#	);

	# next, we'll publish the odometry message over ROS
	odom = Odometry();
	odom.header.stamp = currentTime;
	odom.header.frame_id = "odom";

	# set the position
	odom.pose.pose = Pose(Point(x, y, 0.), Quaternion(*odom_quat));

	#set the covariances. Large numerics are used to disregard measurements. 
	odom.pose.covariance = [1.0519, -0.2223, 0, 0, 0, 4.8494, #Along diag is cov_x, 
							-0.2223, 0.3542, 0, 0, 0, -1.0578, #cov_y, 
							0, 0, 99999, 0, 0, 0, #cov_z, 
							0, 0, 0, 99999, 0, 0, #cov_roll (around x), 
							0, 0, 0, 0, 99999, 0, #cov_pitch (around y), 
							4.8494, -1.0578, 0, 0, 0, 122.7511] #cov_yaw (around z). 

	# set the velocity
	odom.child_frame_id = "base_link";
	odom.twist.twist = Twist(Vector3(vx, vy, 0), Vector3(0, 0, omega));

	# publish the message
	odom_pub.publish(odom);

	rospy.loginfo("x: " + str(x) + "  y: " + str(y) + "  theta: " + str(theta));
	print(x);



rospy.init_node('odometry_publisher')

rospy.Subscriber("serialOdom", String, handleTicks);

odom_pub = rospy.Publisher("odom", Odometry, queue_size=50)
#odom_broadcaster = tf.TransformBroadcaster()




rate = rospy.Rate(100) #10Hz
while not rospy.is_shutdown():
    
    rate.sleep()



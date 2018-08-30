#!/usr/bin/env python

import rospy
import tf
import time
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, PoseWithCovariance, Quaternion, Twist, TwistWithCovariance, Vector3, PoseWithCovarianceStamped



isInitIter = True;




def convert(data):

	global prevTime;
	global prevPose;
	global isInitIter# = True;

	currentTime = rospy.Time.now();
	if (isInitIter):
		prevTime = currentTime;
		dt = 99999999999999999;
	else:
		dt = currentTime.to_sec() - prevTime.to_sec(); #Get delta time. 



	if (isInitIter):
		prevPose = data.pose; #Note first pose is a PoseWithCovariance. 
		isInitIter = False;



	currentPose = PoseWithCovariance();
	currentPose = data.pose;	#Note first pose is a PoseWithCovariance. 

	currentTwist = TwistWithCovariance(); #Calculate velocities. 
	currentTwist.twist.linear.x = (currentPose.pose.position.x - prevPose.pose.position.x)/dt;
	currentTwist.twist.linear.y = (currentPose.pose.position.y - prevPose.pose.position.y)/dt;
	currentTwist.twist.linear.z = (currentPose.pose.position.z - prevPose.pose.position.z)/dt;
	currentTwist.twist.angular.x = (currentPose.pose.orientation.x - prevPose.pose.orientation.x)/dt;
	currentTwist.twist.angular.y = (currentPose.pose.orientation.y - prevPose.pose.orientation.y)/dt;
	currentTwist.twist.angular.z = (currentPose.pose.orientation.z - prevPose.pose.orientation.z)/dt;

	currentTwist.covariance  = data.pose.covariance;
	

	# Make the message to publish:
	odomMessage = Odometry();

	odomMessage.header = data.header;
	#odomMessage.header.frame_id = "something custom?"
	odomMessage.child_frame_id = "base_link";
	odomMessage.pose = currentPose;
	odomMessage.twist = currentTwist;

	
	# publish the message
	p.publish(odomMessage);

	prevPose = currentPose;




rospy.init_node('odom_convertor')

rospy.Subscriber("/robot_pose_ekf/odom_combined", PoseWithCovarianceStamped, convert);

p = rospy.Publisher("/odom_combined", Odometry, queue_size=50)

on = True; #Can set off for safety
rc = False;


rate = rospy.Rate(100) #10Hz
while not rospy.is_shutdown():
    
	#a = OverrideRCIn();
	#a.rssi = 0
	#a.channels = [65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535] # index 0 is yaw, index 2 is throttle. 
	#p.publish(a)
	rate.sleep()



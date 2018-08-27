#!/usr/bin/env python

import math
from math import sin, cos, pi

import rospy
import tf
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3
from mavros_msgs.msg import ActuatorControl, OverrideRCIn, RCIn







leftWheel = 0.0;
rightWheel = 0.0;

#yaw = getStartingYawFromPX4Somehow(); #Here in case accumulation or integration is needed. 


def sendViaMavlink(data):
	
	


	
	throttle = data.linear.x; #x direction of linear velocity
	yaw = data.angular.z; #rotation around z. Hopefully also a velocity, and not a setpoint...


	# next, we'll publish the actuatorControl message over ROS
	command = OverrideRCIn();

	if not on:
		command.channels = [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]; #Make stationary
		command.channels = [65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535]; #Relenquish control
	elif rc and not isSetRc:
		isSetRc = True;
		command.channels = [65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535];
	else:
		isSetRc = False;
		command.channels = [1500+500*-yaw, 1500, 1500+500*throttle, 1500, 1500, 1500, 1500, 1500]; # index 0 is yaw, index 2 is throttle. 

	# publish the message
	p.publish(command);

	rospy.loginfo("dyaw: " + str(yaw) + ", dx: " + str(throttle));




rospy.init_node('twist_mavlink_convertor')

rospy.Subscriber("twist", Twist, sendViaMavlink);


p = rospy.Publisher("mavros/rc/override", OverrideRCIn, queue_size=50)

on = True; #Can set off for safety
rc = False;


rate = rospy.Rate(100) #10Hz
while not rospy.is_shutdown():
    
	#a = OverrideRCIn();
	#a.rssi = 0
	#a.channels = [65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535] # index 0 is yaw, index 2 is throttle. 
	#p.publish(a)
	rate.sleep()



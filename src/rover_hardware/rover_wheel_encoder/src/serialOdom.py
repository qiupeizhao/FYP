#!/usr/bin/env python
import rospy
import serial
import time
from std_msgs.msg import String



serialPort = serial.Serial("/dev/ttyACM0", 115200);


def passItOn(data):
	
	serialPort.write(str(data.data));
	rospy.loginfo(str(rospy.get_caller_id()) + " said to make ROS send '" + str(data.data) + "' to " + str(serialPort.name));


def serialNode():
	
	pub = rospy.Publisher("serialOdom", String, queue_size=10);
	rospy.init_node("serialNode", anonymous=True);
	
	#serialPort.port = "/dev/ttyACM0";
	#serialPort.port = "/dev/ttyArduino";
	#serialPort.baudrate = 115200;
	
	rate = rospy.Rate(100); #10Hz
	
	rospy.Subscriber("serialTx", String, passItOn);
	

	f = open("serialOdomRaw.csv", 'w');


	rxData = ''; 
	while not rospy.is_shutdown():
		#rospy.loginfo(str(serialPort.isOpen()));
		if serialPort.isOpen():
			if not f: f = open("serialOdomRaw.csv", 'w');
			rxData = serialPort.readline();
			#time.sleep(0.01);

			pub.publish(rxData);
			rospy.loginfo(serialPort.name + " says " + rxData);					
			f.write(rxData);
		else:
			f.close();
						
	
	
	rospy.spin();
		
		
if __name__ == "__main__":
	try:
		serialNode();
	except rospy.ROSInterruptException:
		pass;
	
	
	

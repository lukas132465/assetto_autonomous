#!/usr/bin/env python

import rospy
from std_msgs.msg import Header
from sensor_msgs.msg import Image
from rc_custom_msgs.msg import GeneratedTrackLimits

import numpy as np
from cv_bridge import CvBridge
import cv2
import threading


class TrackLimitGenerator:
    def __init__(self, listening_topic, publishing_topic):
        self.listening_topic = listening_topic
        self.publishing_topic = publishing_topic

        self.header = None
        self.height = None
        self.width = None
        self.encoding = None
        self.is_bigendian = None
        self.step = None
        self.data = None

        self.keypoints = None

        rospy.init_node("track_limit_generator")
    
    def __set_attributes__(self, data):
        self.header = data.header
        self.height = data.height
        self.width = data.width
        self.encoding = data.encoding
        self.is_bigendian = data.is_bigendian
        self.step = data.step
        self.data = data.data

    def listen(self):
        rospy.Subscriber(self.listening_topic, Image, self.__set_attributes__)
        rospy.spin()

    def __check_for_white_cells__(self, img):
        center_coordinate = [960, 750]
        ratios = ((-2,-2),(-3,-1),(2,-2),(3,-1))
        square_checks = ((-1,-1),(-1,0),(-1,1),(0,-1),(0,0),(0,-1),(1,-1),(1,0),(1,1))

        result = []
        y_max, x_max = img.shape
        for add_x, add_y in ratios:
            x, y = center_coordinate
            check = True
            while (2<x<x_max-2 and 2<y<y_max-2 and check):
                x += add_x
                y += add_y
                for x_check, y_check in square_checks:
                    x_res = x+x_check
                    y_res = y+y_check
                    if (img[y_res][x_res]==255):
                        result.extend([x, y])
                        check=False
                        break
        return result

    def find_track_limits(self):
        """
        Find two real-world coordinates on each side of the road marking the track limits
        Naive approach: find the first 4 white pixels and generate real world coordinates
        """
        blub = cv2.imread("/home/lukas/Projects/autonomous-racing/DataTransfer/SharedData/test_image.jpg")
        while not rospy.is_shutdown():
            img = cv2.cvtColor(blub, cv2.COLOR_BGR2GRAY)
            img = cv2.Canny(img, 200, 400)
            pixels = self.__check_for_white_cells__(img)
            self.keypoints = pixels
            #self.keypoints = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

    def talk(self):
        pub = rospy.Publisher(self.publishing_topic, GeneratedTrackLimits, queue_size=1)
        rate = rospy.Rate(10)

        while not rospy.is_shutdown():
            if (self.keypoints == None): pass

            header = rospy.Header()
            pub.publish(header, self.keypoints)
            rate.sleep()

    def generate(self):
        t1 = threading.Thread(target=self.listen)
        t2 = threading.Thread(target=self.find_track_limits)
        t3 = threading.Thread(target=self.talk)
        
        t1.start()
        t2.start()
        t3.start()


if __name__ == '__main__':
    tlg = TrackLimitGenerator("shared_image", "generated_track_limits")
    try:
        tlg.generate()
    except rospy.ROSInterruptException:
        pass
// This file will subscribe the image from rosmessage
// and display it in window
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

/*
 *To compile this execuatble
 *rosrun face_detection face_detection_imagesubscribe
*/

// imageCallback function gets the image 
// it displays an image in window
void imageCallback(const sensor_msgs::ImageConstPtr& msg){

  try{

    cv::imshow("Face Detection", cv_bridge::toCvShare(msg, "bgr8")->image); // displays an subcribed image 
    cv::waitKey(30);
  
  }

  catch (cv_bridge::Exception& e){
  
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str()); // display Exception whwn image could not be displayed

  }

}

int main(int argc, char **argv){

  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("Face Detection"); // creates window to diplay an image
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image_processed", 1, imageCallback); // subscribe the image
  ros::spin();
  cv::destroyWindow("Face Detection"); // closes the window

}

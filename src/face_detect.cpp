// This file gets the image from the node
// and  processes it to detect a faces.
// After detecting face it draws a rectangular box that covers the detected face
// and publishes the image as rosmessage
#include <ros/ros.h>
#include <ros/console.h>
#include <iostream>
#include <stdio.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/*
 *To compile this execuatble
 *rosrun face_detection face_detection_detect
 */
using namespace std;
using namespace cv;

namespace enc = sensor_msgs::image_encodings;

// Declares publisher
image_transport::Publisher pub;

// Create the haar cascade
CascadeClassifier face_cascade("/haarcascade_frontalface_default.xml");

void imageCallback(const sensor_msgs::ImageConstPtr& original_image){
		
  // Image Pointer Declaration
  cv_bridge::CvImagePtr cv_ptr;
  //cv_bridge::CvImagePtr cv_chg;
  
  try{

    //Copying image to a pointer	
    cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
  
  }

  catch (cv_bridge::Exception& e){

    //Excetion Display
    ROS_ERROR("tutorialROSOpenCV::main.cpp::cv_bridge exception: %s", e.what());
    return;
  }

  std::vector<Rect> faces; //vector declaration
  cv::Mat frame_gray;      // Mat variable for storing gray scale image
  
  cv::cvtColor(cv_ptr->image, frame_gray, CV_BGR2GRAY ); //BGR to Gray image conversion
  cv::equalizeHist(frame_gray,frame_gray);               // Equalize Histograms the fram_gray image

  // Detect faces in image
  face_cascade.detectMultiScale(
    frame_gray,
    faces,
    1.1, 2, 0 | CASCADE_SCALE_IMAGE,
    Size(30, 30)
  );

  size_t face_index = 0; // face_index is index of current element

  // Iterate through all current elements (detected faces)
  // Draws rectangle on each detected face
  // by finding the vertex of faces
  for (face_index = 0; face_index < faces.size(); face_index++) {

    cv::Point pt1(faces[face_index].x, faces[face_index].y); 
    cv::Point pt2(
                 (faces[face_index].x + faces[face_index].height),
                 (faces[face_index].y + faces[face_index].width)
 		 );
    cv::rectangle(cv_ptr->image, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0); // draws rectangle on original image

  }

  cv::waitKey(1);
    
  if(faces.size()!=0){ // node will not publish the image unless it detects the face in it
  
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cv_ptr->image).toImageMsg(); // store image as rosmessage in msg
    pub.publish(msg); // publishes ros message  
    ROS_INFO_STREAM("Face Detected");  
  }
  else{
    
    ROS_INFO_STREAM("No Face Detected");
  
  }
	




}

int main(int argc, char **argv){

  ros::init(argc, argv, "face_detect");  // Intiliazing ros 
  ros::NodeHandle nh;
  ROS_INFO_STREAM("Face Detection Started");
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/image", 1, imageCallback); // subscribes the image for detecting face
  pub = it.advertise("camera/image_processed", 1);
  ros::spin();
  ROS_INFO("tutorialROSOpenCV::main.cpp::No error.");

}



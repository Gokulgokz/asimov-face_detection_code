// This file publishes the image as ros message 
// for other nodes
// the image path has to be provide while executing thi file
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

/*
 *To compile this execuatble
 *rosrun face_detection face_detection_image src/opencvtut/src/lena.jpg
 *
 */
const float kScaleFactor = 1.0;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/image", 1);

  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  cv::Mat new_image;
  cv::Mat gray_image, threshold_image;
  cv::cvtColor(image, gray_image, CV_BGR2GRAY);
  cv::threshold(gray_image, threshold_image, 200, 255, CV_THRESH_BINARY_INV);
  new_image = threshold_image;

  // Create dst, map_x and map_y with the same size as src:
  cv::resize(image, new_image, cvSize(0, 0), kScaleFactor, kScaleFactor);
  
  cv::waitKey(30);

  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", new_image).toImageMsg();

  ros::Rate loop_rate(5);
  
  while (nh.ok()) 
  {
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}

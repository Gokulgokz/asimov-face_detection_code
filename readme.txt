face_detection package
======================================================================================================================================
Files:

 
  image_publish.cpp
  webcam_video_show.cpp
  face_detect.cpp
  imgsubcriber.cpp

For Documentation of research : Double Click the "COMPARISON OF VARIOUS FACE DETECTION ALGORITHMS.pdf" file
For Documentation of code     : Double Click the "Link to index.html" file
For System Design             : Double Click the "face_detection_system_design.pdf" file
======================================================================================================================================

To Run the Package
=======================================================================================================================================
 1. Using roslaunch

    Launch Files:
		
	face_detection.launch       // gives image as input
    	face_detection_video.launch // gives video stream from camera as input
   
   To Execute:
  
   // To give image as input and execute
       
	$ roslaunch face_detection face_detection.launch loc:="system location of an source image"
  
   Example:
	
	$ roslaunch face_detection face_detection.launch loc:= /home/gokul/catkin_ws/src/face_detection/src/testing_images/positive_images/test1.jpg
 
   // To give video stream as input and execute

	$ roslaunch face_detection face_detection_video.launch loc:="camera port number"

   Example:
	
	$ roslaunch face_detection face_detection_video.launch loc:=0

 2. Executing each file separetly

 step 1: 

   // To give image as input and execute
	
	$ rosrun face_detection face_detection_image src/face_detection/src/testing_images/positive_images/test1.jpg

   // To give video stream as input and execute

	$ rosrun face_detection face_detection_video 0

 step 2:
   
  // Execute face_detect.cpp

	$ rosrun face_detection face_detection_detect

 step 3:

  // Execute imgsubcriber.cpp


	$ rosrun face_detection face_detection_imagesubscribe 

 step 4:

  // Run Rviz 

	$ rosrun rviz rviz
	
  // After Rviz GUI opens
	
	1. Click ADD --> Select Image ( under rviz in display type tab )
	2. Click OK
	3. Display --> Image (expand the option) --> rostopic
	4. rostopic --> select camera/image_processed option
	
	Now Image/Video will be visualized in Rviz.

===========================================================The END=========================================================== 

   

	
 

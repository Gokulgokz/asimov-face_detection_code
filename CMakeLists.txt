cmake_minimum_required(VERSION 2.8.3)
project(face_detection)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)


find_package(OpenCV REQUIRED)
if (OpenCV_VERSION VERSION_EQUAL "3")
  add_definitions("-DOPENCV3=1")
endif()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

 add_executable(face_detection_detect src/face_detect.cpp)
 add_dependencies(face_detection_detect face_detection_generate_messages_cpp)
 target_link_libraries(face_detection_detect   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS})

 add_executable(face_detection_video src/webcam_video_show.cpp)
 add_dependencies(face_detection_video face_detection_generate_messages_cpp)
 target_link_libraries(face_detection_video   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS})

 add_executable(face_detection_imagesubscribe src/imgsubcriber.cpp)
 add_dependencies(face_detection_imagesubscribe face_detection_generate_messages_cpp)
 target_link_libraries(face_detection_imagesubscribe   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS})

 add_executable(face_detection_image src/image_publish.cpp)
 add_dependencies(face_detection_image face_detection_generate_messages_cpp)
 target_link_libraries(face_detection_image   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS})



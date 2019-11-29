/*
* @Author: maykolrey
* @Date:   2019-11-29 08:37:59
* @Last Modified by:   Maykol Rey
* @Last Modified time: 2019-11-29 09:25:04
*/

#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main(){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(0); 
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
   
  cv::TickMeter tm;   
  while(1){

    tm.start();//arranco el contador de tiempo del reloj
    
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;
 
    // Display the resulting frame
    imshow( "Frame", frame );
 
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  

    tm.stop();
    cout << "FPS = " << 1000/tm.getTimeMilli() <<endl;

  }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}
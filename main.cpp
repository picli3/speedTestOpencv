/*
* @Author: maykolrey
* @Date:   2019-11-29 08:37:59
* @Last Modified by:   Maykol Rey
* @Last Modified time: 2019-11-29 11:00:51
*/

#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main(){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(0); 

  Mat otra;
  Rect myROI(10, 10, 100, 100);

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
   
  cv::TickMeter tm; 
  float acu=0;
  float averageFPS=0;
  int count=0;
  do{

    tm.start();//arranco el contador de tiempo del reloj
    
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
    
    otra = frame (myROI);

    // If the frame is empty, break immediately
    if (frame.empty())
      break;
 
    // Display the resulting frame
    imshow( "Frame", otra );
    
    tm.stop();
    cout << "FPS = " << 1000/tm.getTimeMilli() <<endl;
    // Press  ESC on keyboard to exit
    
    acu+=1000/tm.getTimeMilli();
    
    tm.reset();
    char c=(char)waitKey(25);
    if(c==27)
      break;

    count++;
  }while(count<=1000);
  

  cout << "averageFPS = " << acu/count <<endl;

  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}
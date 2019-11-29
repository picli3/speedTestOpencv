/*
* @Author: maykolrey
* @Date:   2019-11-29 08:37:59
* @Last Modified by:   Maykol Rey
* @Last Modified time: 2019-11-29 11:54:43
*/

#include "opencv2/opencv.hpp"
#include <iostream>

#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>

using namespace std;
using namespace cv;
 
int main(){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(0); 

  Mat otra;
  cuda::GpuMat _resized_gpu;
  cuda::GpuMat _facesBuf_gpu;
  cuda::GpuMat _frame_gpu;

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
  int c=0;
  do{

    tm.start();//arranco el contador de tiempo del reloj
    
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
    
    _frame_gpu.upload(frame);

    cuda::resize(_frame_gpu, _resized_gpu, Size(300,300));

    _resized_gpu.download(otra);


    //cv::resize(frame, otra, Size(300,300));
    //otra = frame (myROI);

    // If the frame is empty, break immediately
    if (frame.empty())
      break;
 
    // Display the resulting frame
    if(c==3){
      imshow( "Frame", otra );
      c=0;
    }
    
    c++;
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
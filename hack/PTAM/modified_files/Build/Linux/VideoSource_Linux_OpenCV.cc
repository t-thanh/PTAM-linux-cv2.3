/*
* Autor : Arnaud GROSJEAN (VIDE SARL)
* This implementation of VideoSource allows to use OpenCV as a source for the video input
* I did so because libCVD failed getting my V4L2 device
*
* INSTALLATION :
* - Copy the VideoSource_Linux_OpenCV.cc file in your PTAM directory
* - In the Makefile:
*	- set the linkflags to
	LINKFLAGS = -L MY_CUSTOM_LINK_PATH -lblas -llapack -lGVars3 -lcvd -lcv -lcxcore -lhighgui
*	- set the videosource to 
	VIDEOSOURCE = VideoSource_Linux_OpenCV.o
* - Compile the project
* - Enjoy !
* 
* Notice this code define two constants for the image width and height (OPENCV_VIDEO_W and OPENCV_VIDEO_H)
*/

#include "VideoSource.h"
#include <cvd/Linux/v4lbuffer.h>
#include <cvd/colourspace_convert.h>
#include <cvd/colourspaces.h>
#include <gvars3/instances.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>

#include <iostream>
#include <sstream>

using namespace CVD;
using namespace std;
using namespace GVars3;
using namespace cv;

#define OPENCV_VIDEO_W 640
#define OPENCV_VIDEO_H 480

// 2010/10/06 kameda[at]iit.tsukuba.ac.jp
extern string kmd_cameraname;

VideoSource::VideoSource()
{
  cout << "  VideoSource_Linux: Opening video source..." << endl;

  // 2010/10/06 kameda[at]iit.tsukuba.ac.jp
  // I want to be a fluent C++ speaker ...
  mptr = new VideoCapture();
  if (kmd_cameraname == "") {
    mptr = new VideoCapture(0); // default camera device
  } else {
    int kmdcamnum = -1;
    stringstream(kmd_cameraname) >> kmdcamnum; // try to find number
    if (kmdcamnum >= 0)
      mptr = new VideoCapture(kmdcamnum); // by device number
    else
      mptr = new VideoCapture(kmd_cameraname); // by url/video-file
  }

  VideoCapture* cap = (VideoCapture*)mptr;
  if(!cap->isOpened()){
    cerr << "Unable to get the camera " << kmd_cameraname << endl;
    exit(-1);
  }

  cout << "  ... got video source." << endl;
  mirSize = ImageRef(OPENCV_VIDEO_W, OPENCV_VIDEO_H);
};

ImageRef VideoSource::Size()
{ 
  return mirSize;
};

void conversionNB(Mat frame, Image<byte> &imBW){
	Mat clone = frame.clone();
	Mat_<Vec3b>& frame_p = (Mat_<Vec3b>&)clone;
	for (int i = 0; i < OPENCV_VIDEO_H; i++){
		for (int j = 0; j < OPENCV_VIDEO_W; j++){	
		imBW[i][j] = (frame_p(i,j)[0] + frame_p(i,j)[1] + frame_p(i,j)[2]) / 3;
		}
	}

}

void conversionRGB(Mat frame, Image<Rgb<byte> > &imRGB){
	Mat clone = frame.clone();
	Mat_<Vec3b>& frame_p = (Mat_<Vec3b>&)clone;
	for (int i = 0; i < OPENCV_VIDEO_H; i++){
		for (int j = 0; j < OPENCV_VIDEO_W; j++){	
		imRGB[i][j].red = frame_p(i,j)[2];
		imRGB[i][j].green = frame_p(i,j)[1];
		imRGB[i][j].blue = frame_p(i,j)[0];
		}
	}
}

void VideoSource::GetAndFillFrameBWandRGB(Image<byte> &imBW, Image<Rgb<byte> > &imRGB)
{
Mat frame;
VideoCapture* cap = (VideoCapture*)mptr;
*cap >> frame;
  conversionNB(frame, imBW);
  conversionRGB(frame, imRGB);
}



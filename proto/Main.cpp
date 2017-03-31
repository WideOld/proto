#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <iostream>
#include <conio.h>
#include "Detected.h"
using namespace cv;
using namespace std;
CvHaarClassifierCascade *cascade;
CvMemStorage            *storage;
const string camUrl = "rtsp://user:user21@10.157.197.231/rtpvideo1.sdp";
void detect(IplImage *img);
void fromUrl (string url) 
{
    cv::VideoCapture capture(url);
    if (!capture.isOpened()) {
        //Error
    }
    cv::namedWindow("1.", CV_WINDOW_AUTOSIZE);
    cv::Mat frame0;
	if (!capture.read(frame0)) {
        //Error
    }

	IplImage* frame1=cvCloneImage(&(IplImage)frame0);
	IplImage  *frame = change(frame1);
	 cascade = (CvHaarClassifierCascade*) cvLoad("cars.xml", 0, 0, 0);
  storage = cvCreateMemStorage(0);
  
    while  (1) {
        if (!capture.read(frame0)) {
            //Error
        }

		// TODO
		frame1=cvCloneImage(&(IplImage)frame0);
		 cvResize(frame1, frame);
		  detect(frame);
        cv::imshow("1.", frame0);
        //listen for 10ms for a key to be pressed
        switch (waitKey(10))
        {
            case 27:
                //'esc' has been pressed (ASCII value for 'esc' is 27)
                //exit program.
                return ;
        }
    }
}

void detect(IplImage *img)
{
  CvSize img_size = cvGetSize(img);
  CvSeq *object = cvHaarDetectObjects(
	  img,
    cascade,
    storage,
    1.1, //1.1,//1.5, //-------------------SCALE FACTOR
    1, //2        //------------------MIN NEIGHBOURS
    0, //CV_HAAR_DO_CANNY_PRUNING
    cvSize(0,0),//cvSize( 30,30), // ------MINSIZE
    img_size //cvSize(70,70)//cvSize(640,480)  //---------MAXSIZE
    );

  std::cout << "Total: " << object->total << " cars detected." << std::endl;
  for(int i = 0 ; i < ( object ? object->total : 0 ) ; i++)
  {
    CvRect *r = (CvRect*)cvGetSeqElem(object, i);
    cvRectangle(img,
      cvPoint(r->x, r->y),
      cvPoint(r->x + r->width, r->y + r->height),
      CV_RGB(255, 0, 0), 2, 8, 0);
  }

  cvShowImage("video", img);
}

int main(int argc, char* argv[])
{
	fromUrl(camUrl);
    return 0; //
}
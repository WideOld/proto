#include "Detected.h"

 
  IplImage* change( IplImage* frame1)
  { 
	  int input_resize_percent=10;
	    return cvCreateImage(cvSize((int)((frame1->width*input_resize_percent)/100) , (int)((frame1->height*input_resize_percent)/100)), frame1->depth, frame1->nChannels);
 }

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <libfreenect/libfreenect_sync.h>
#include <stdio.h>
 
freenect_context *f_ctx;
freenect_device *f_dev;

using namespace cv;
int main(int argc, char **argv)
{
	FILE * hFile;
	hFile = fopen("logs/depthData.csv","w");
	
    IplImage *image = cvCreateImageHeader(cvSize(640,480), 8, 3);
    IplImage *depth = cvCreateImageHeader(cvSize(640,480), IPL_DEPTH_16U, 1);
    char *ImageData = (char*)malloc(921600);
    uint16_t *DepthData = (uint16_t*)malloc(614400);
    int logIteration = 0;
    char *fileName = (char*)malloc(1000);
    char *streamBuffer = (char*)malloc(1000);
    bool log = false;
    while (1) {
      //key press loop
	    char key = cvWaitKey(10);
	    if(key == 'x')
	    {
		    fclose(hFile);
		    break;
	    }
	    if(key == 'c')
		    log= log ^ 1;

	unsigned int timestamp;
      freenect_sync_get_video((void**)&ImageData, &timestamp,0,FREENECT_VIDEO_RGB);
      freenect_sync_get_depth((void**)&DepthData, &timestamp, 0, FREENECT_DEPTH_11BIT);
      if(log)
      {
	      sprintf(streamBuffer,"%i, ",logIteration);
	      fputs(streamBuffer,hFile);
      }
	      
      for(int i=0;i<640*480;i++)
      {
	      DepthData[i] = DepthData[i]*200;
	      if(log)
	      {
		      sprintf(streamBuffer,"%i, ",DepthData[i]);
		      fputs(streamBuffer,hFile);

	      }
      }

      if(log)
	      fputs("\n",hFile);



      cvSetData(depth,DepthData,640*2);
      cvShowImage("Depth",depth);
      cvSetData(image, ImageData, 640*3);
      cvCvtColor(image, image, CV_RGB2BGR);
      cvShowImage("RGB", image);
      if(log) //Loggin Section
      {
	      sprintf(fileName,"logs/imgFiles/logImage%i.png",logIteration);
	      imwrite(fileName,image);
	      
	      printf("Logging data...\n");
	      logIteration++;

      }
    }
}

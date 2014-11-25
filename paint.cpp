#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/cv.h"
#include <iostream>
#include "math.h"
using namespace cv;
using namespace std;
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
bool flagx=0,flagy=0,keyd=0,feraser=0;
int flagd=0,thickd=1,thicke=1,rcolor=0,gcolor=0,bcolor=0,fmode=1,fpaint=0,fshape=0;
float startx=0.0,starty=0.0;

Mat img(Size(2000, 2000), CV_8UC3, Scalar(255, 255, 255));
Mat img2;
//CvScalar newColor = CV_RGB(rcolor,gcolor,bcolor);
CvPoint seedPoint; 
void callbackButtonp(int state,void* userdata)
{
    fshape=4;
    fmode=1;
}
void callbackButtonl(int state,void* userdata)
{
	fshape=1;
    fmode=1;
}

void callbackButtonr(int state,void* userdata)
{
	fshape=2;
	fmode=1;
}
void callbackButtonc(int state,void* userdata)
{
	fshape=3;
    fmode=1;
}
void callbackButtonbucket(int state,void* userdata)
{
    fmode=2;
    fpaint=1;
    feraser=0;
}
void callbackButtone(int state,void* userdata)
{
	feraser=1;
	fmode=2;
}
int main()
{
	// read the base image
	//Mat img(Size(200, 200), CV_8UC3, Scalar(255, 255, 255));
	//cv::imshow("some", img);
	//img = imread("img.jpg" , CV_LOAD_IMAGE_COLOR);
	
	cout<<img.size();
	//if ( img.empty() ) 
	//{ 
	//	cout << "Error loading the image" << endl;
	//	return -1; 
	//}
	//creating the window for displaying the image
	namedWindow( "Original" , 1 );
	cout<<"START";


	//creating the panel
		// buttons for drawing
		//cv::createButton("pencil",callbackButtonp,NULL,CV_PUSH_BUTTON,1); // Button 1 
	cv::createButton("line",callbackButtonl,NULL,CV_PUSH_BUTTON,1); // Button 2
	cv::createButton("rectangle",callbackButtonr,NULL,CV_PUSH_BUTTON,1); // Button 3
	cv::createButton("circle",callbackButtonc,NULL,CV_PUSH_BUTTON,1); // Button 4
	cv::createButton("pencil",callbackButtonp,NULL,CV_PUSH_BUTTON,1); // Button 4
		cout<<"\nCreated";
	    // trackbar for thickness
	cvCreateTrackbar( "thickness",NULL,&thickd, 10);//OK tested
	    //button for eraser
	cv::createButton("eraser",callbackButtone,NULL,CV_PUSH_BUTTON,1); // Button 1 
	    //trackbar for size of eraser
	cvCreateTrackbar("eraser size",NULL, &thicke, 50);//OK tested

	    // button for paint bucket and paint brush
	cv::createButton("paint bucket",callbackButtonbucket,NULL,CV_PUSH_BUTTON,1); // Button 1 
		//cv::createButton("brush",callbackButtonbrush,NULL,CV_PUSH_BUTTON,1); // Button 2
	    // 3 trackbars for choosing colour to be painted
	cvCreateTrackbar("red  ",NULL, &rcolor, 255);//OK tested
	cvCreateTrackbar("blue ",NULL, &bcolor, 255);//OK tested
	cvCreateTrackbar("green",NULL, &gcolor, 255);//OK tested





    //set the callback function for any mouse event
    	setMouseCallback("Original", CallBackFunc, NULL);
    	displayOverlay("Original", " paint application - opencv ",10000);
    //displayOverlay("Original", "open display properties", int delayms=1000 );
    	displayStatusBar("Original", "    open display properties (ctrl + P) to edit document",0);
	//show the image
	imshow("Original", img);
	// Wait until user press some key
	waitKey(0);

	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	// x- column y- row
	img2=img.clone();
	if(event==EVENT_LBUTTONDOWN)
	{
		if(fmode==1)
		{
			startx=float(x);
			starty=(float)y;
			if(fshape==1)
			{
				flagd=1;
			}
			else if(fshape==2)
			{
				flagd=2;
			}
			else if(fshape==3)
			{
				flagd=3;
			}
			else if(fshape==4)
			{
				flagd=4;
				startx=x;
				starty=y;
				keyd=1;
			}
		}
		else if(fmode==2)
		{
			if(feraser==1)
			{
				rectangle( img,Point(x-thicke,y-thicke),Point(x+thicke,y+thicke), Scalar( 255,255,255 ), CV_FILLED);
				keyd=1;
				startx=x;
				starty=y;
			}
			else
			{
				floodFill(img, Point(x,y), CV_RGB(rcolor,gcolor,bcolor));
				imshow("Original",img);
			}
		}

	}
	else if(event==EVENT_LBUTTONUP)
	{
		if((fmode==1))
		{
			if(fshape==1)
			{
				line( img2, Point( startx, starty ), Point( x, y), Scalar( bcolor, gcolor, rcolor ),thickd, 8 );
				/*line1(startx,starty,x,y);
				circle( img, Point( startx, starty ),2, Scalar( bcolor, gcolor, rcolor ), 1, 8 );
				circle( img, Point( x, y ),2, Scalar( bcolor, gcolor, rcolor ), 1, 8 );*/

				flagd=0;
			}
			else if(fshape==2)
			{
				rectangle( img2,Point( startx, starty ), Point( x, y), Scalar( bcolor, gcolor, rcolor ),thickd, 8);
				flagd=0;
			}
			else if(fshape==3)
			{
				float r=sqrt((x-startx)*(x-startx)+(y-starty)*(y-starty));
				circle( img2, Point( startx, starty ), r, Scalar( bcolor, gcolor, rcolor ),thickd, 8 );
				flagd=0;
			}
			else if(fshape==4)
			{
				flagd=0;
				keyd=0;
			}
		}
		else if(fmode==2)
		{
			if(feraser==1)
				keyd=0;
			

		}
		img=img2.clone();
		imshow("Original", img);
		//rimg=img.clone();
	}
	else if(event==EVENT_MOUSEMOVE)
	{
		if((fmode==1))
		{
			if(flagd==1)
			{
				line( img2, Point( startx, starty ), Point( x, y), Scalar( bcolor, gcolor, rcolor ),thickd, 8);
				//line1(startx,starty,x,y);
			}
			else if(flagd==2)
			{
				rectangle( img2,Point( startx, starty ), Point( x, y), Scalar( bcolor, gcolor, rcolor ),thickd, 8);
			}
			else if(flagd==3)
			{
				int r=sqrt((x-startx)*(x-startx)+(y-starty)*(y-starty));
				circle( img2, Point( startx, starty ), r, Scalar( bcolor, gcolor, rcolor ),thickd, 8 );
			}
			else if(flagd==4)
			{
				if(keyd==1)
				{
					line( img2, Point( startx, starty ), Point( x, y), Scalar( bcolor, gcolor, rcolor ),thickd, 8);
					startx=x;
					starty=y;
					img=img2.clone();
				}
			}
			
		}
		else if(fmode==2)
		{
			if(feraser==1)
			{
				rectangle( img2,Point(x-thicke,y-thicke),Point(x+thicke,y+thicke), Scalar( 255,255,255 ), CV_FILLED);
				if(keyd==1)
					img=img2.clone();
			}
			
		}
		//delete(img2);
		imshow("Original",img2);
	}
}

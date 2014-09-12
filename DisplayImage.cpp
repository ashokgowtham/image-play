#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>

#include <queue> 

using namespace cv;

double avg(std::queue<double> q) {
    std::queue<double> q1 = std::queue<double>(q);
    double size = q1.size();
    double total = 0;
    while(!q1.empty())
    {
        total += q1.front();
        q1.pop();
    }
    return total / size;
}

int main(int argc, char** argv )
{
    // if ( argc != 2 )
    // {
    //     printf("usage: DisplayImage.out <Image_Path>\n");
    //     return -1;
    // }

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", image);
    std::queue<double> q;
    CvCapture* capture = cvCreateCameraCapture(-1);  //Capture using any camera connected to your system
    while(1){ //Create infinte loop for live streaming
        clock_t begin, end;
        double time_spent;
        begin = clock();


        IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
        Mat image = cvarrToMat(frame);

        Mat gray_image;
        cvtColor( image, gray_image, CV_BGR2GRAY );
        if(!gray_image.data) {
            printf("gray_image empty\n");
            exit(-1);
        }

        imshow("Display Image", gray_image);
        // cvShowImage("Display Image", image);

        char key = waitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }


        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        q.push(time_spent);
        if(q.size() > 25) q.pop();
        printf("%3.1lf fps.  %3.5lf sec. avg:%3.1lf\n",1/time_spent, time_spent, 1/avg(q));
    }
    cvReleaseCapture(&capture); //Release capture.

    // waitKey(0);

    // cvNamedWindow("Camera_Output", 1);    //Create window
    // CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    // while(1){ //Create infinte loop for live streaming
 
    //     IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    //     cvShowImage("Camera_Output", frame);   //Show image frames on created window
    //     key = cvWaitKey(10);     //Capture Keyboard stroke
    //     if (char(key) == 27){
    //         break;      //If you hit ESC key loop will break.
    //     }
    // }
    // cvReleaseCapture(&capture); //Release capture.
    // cvDestroyWindow("Camera_Output"); //Destroy Window


    return 0;
}
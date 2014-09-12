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
    std::queue<double> q;
    double b=1000;
    CvCapture* capture = cvCreateCameraCapture(-1);  //Capture using any camera connected to your system

    namedWindow("Display Image", WINDOW_AUTOSIZE );

    while(1){ //Create infinte loop for live streaming
        clock_t begin, end;
        double time_spent;
        begin = clock();

        IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
        Mat image = cvarrToMat(frame);

        Mat blurred1;
        Mat blurred2;
        Mat diff;
        Mat powed;
        Mat normalized;
        Mat added;
        Size ksize;
        ksize.height=ksize.width=3;
        GaussianBlur( image, blurred1, ksize, 0 );
        if(!blurred1.data) {
            printf("blurred1 empty\n");
            exit(-1);
        }
        ksize.height=ksize.width=15;
        GaussianBlur( image, blurred2, ksize, 0 );
        if(!blurred2.data) {
            printf("blurred2 empty\n");
            exit(-1);
        }
        absdiff(blurred1, blurred2, diff );
        if(!diff.data) {
            printf("diff empty\n");
            exit(-1);
        }

        pow(diff, 2, powed );
        if(!powed.data) {
            printf("powed empty\n");
            exit(-1);
        }

        normalize(powed, normalized, 0, (int)b, NORM_MINMAX);
        if(!normalized.data) {
            printf("normalized empty\n");
            exit(-1);
        }
        add(image,normalized,added);
        if(!added.data) {
            printf("added empty\n");
            exit(-1);
        }
        imshow("Display Image", added);
        // cvShowImage("Display Image", frame);

        char key = waitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
        switch(char(key)) {
        case 45:
            b*=2;
            printf("Brightness Increased: %lf\n", b);
            break;
        case 61:
            b/=2;
            printf("Brightness Increased: %lf\n", b);
            break;
        default:
            printf("key press: %d\n", key);
        }

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        q.push(time_spent);
        if(q.size() > 25) q.pop();
        printf("%3.1lf fps.  %3.5lf sec. avg:%3.1lf\n",1/time_spent, time_spent, 1/avg(q));
    }
    cvReleaseCapture(&capture); //Release capture.


    return 0;
}
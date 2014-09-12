#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );
    
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );

    if (!gray_image.data) {
        printf("gray_image data null\n");
    }

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
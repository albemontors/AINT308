//James Rogers Jan 2022 (c) Plymouth University
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#define HUELOWER 70
#define HUEUPPER 90
#define SATLOWER 100
#define SATUPPER 240
#define VALLOWER 100
#define VALUPPER 240

using namespace std;
using namespace cv;

int main()
{

    VideoCapture InputStream("../Task2/Video.mp4"); //Load in the video as an input stream
    const Point pivot(592,52);                                      //Pivot position in the video

    //Open output file for angle data
    ofstream DataFile;
    DataFile.open ("../Task2/Data.csv");

    //loop through video frames
    while(true){

        //load next frame
        Mat Frame;
        InputStream.read(Frame);

        //if frame is empty then the video has ended, so break the loop
        if(Frame.empty()){
            break;
        }

        //video is very high resolution, reduce it to 720p to run faster
        resize(Frame,Frame,Size(1280,720));

        //======================================================Your code goes here====================================================
        //this code will run for each frame of the video. your task is to find the location of the swinging green target, and to find
        //its angle to the pivot. These angles will be saved to a .csv file where they can be plotted in Excel.

        Mat hvsFrame;

        Vec3b lowerBound(HUELOWER, SATLOWER, VALLOWER);
        Vec3b upperBound(HUEUPPER, SATUPPER, VALUPPER);

        Mat filteredFrame;

        cvtColor(Frame, hvsFrame, COLOR_BGR2HSV);

        inRange(hvsFrame, lowerBound, upperBound, filteredFrame);

        Moments m = moments(filteredFrame, 1);

        Point pendulum( m.m00 ? m.m10 / m.m00 : 0, m.m00 ? m.m01 / m.m00 : 0); // division by 0 avoided

        line(Frame, pendulum, pivot, 120, 10);
        circle(Frame, pendulum, 30, 120 , 10);

        char output[12];

        // IT IS BIG BRAIN TIME!
        output[0] = (pendulum.x / 1000) + '0';
        output[2] = ((pendulum.x % 1000) / 100) + '0';
        output[3] = ((pendulum.x % 100) / 10) + '0';
        output[4] = (pendulum.x % 10) + '0';
        output[5] = ',';
        output[6] = (pendulum.y / 1000) + '0';
        output[7] = ((pendulum.y % 1000) / 100) + '0';
        output[8] = ((pendulum.y % 100) / 10) + '0';
        output[9] = (pendulum.y % 10) + '0';
        output[10] = '\n';
        output[11] = '\0';
        // STRINGS LIBRARIES, WE DO NOT NEED THEM HERE

        DataFile.write(output, 12);


        //==============================================================================================================================

        //display the frame
        imshow("Video", Frame);
        waitKey(10);
    }

    DataFile.close(); //close output file
}

//James Rogers Jan 2021 (c) Plymouth University
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    //Path to image file
    string Path = "../Task3/PCB Images/";

    //loop through component images
    for(int n=0; n<10; ++n){

        //read PCB and component images
        Mat PCB = imread(Path+"PCB.png");
        Mat Component = imread(Path+"Component"+to_string(n)+".png");

        //================Your code goes here=====================

        Mat Match;

        matchTemplate(PCB, Component, Match, TM_SQDIFF_NORMED);

        double min, max;
        Point locm, locM;

        minMaxLoc(Match, &min, &max, &locm, &locM);

        cout << "Match Value is: " << min << endl;
        if(min > 0.01)
            cout << "Component " << n << " is not on the board" << endl;

        Point RectangleDim(locm.x + Component.cols, locm.y + Component.rows);

        rectangle(PCB, locm, RectangleDim, 120, 4);

        //display the results untill x is pressed
        while(waitKey(10)!='x'){
            imshow("Match", PCB);
            imshow("Component", Component);
        }

    }

}

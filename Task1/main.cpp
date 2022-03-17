//James Rogers Jan 2022 (c) Plymouth University
#include <iostream>

#include<opencv2/opencv.hpp>
#include<opencv2/opencv_modules.hpp>

#define MAXX 640 //obsolete
#define MAXY 480
#define DENSITY 50
#define PI 3.141592

//Absolute search values
#define UPPERBOUND 200
#define LOWERBOUND 100
#define BSHIFT 10
#define GSHIFT 50
#define RSHIFT 0

//relative search values
#define DIFFERENCE 0

using namespace std;
using namespace cv;

int main(){

    //Path of image folder
    string PathToFolder = "../Task1/Car Images/";

    //Loop through the 30 car images
    for(int n=30; n<39; ++n){

        //Each image is named 0.png, 1.png, 2.png, etc. So generate the image file path based on n and the folder path
        string PathToImage = PathToFolder+to_string(n)+".png";

        cout<<PathToImage<<endl;

        //Load car image at the file paths location
        Mat Car=imread(PathToImage);

        //Your code goes here. The example code below shows you how to read the red, green, and blue colour values of the
        //pixel at position (0,0). Modify this section to check not just one pixel, but all of them in the 640x480 image
        //(using for-loops), and using the RGB values classifiy if a given pixel looks red, green, blue, or other.

        //==============example code, feel free to delete=============
        int x=0;
        int y=0;
        int countB = 0;
        int countG = 0;
        int countR = 0;
        for(x = 0; x < Car.cols; x += (Car.cols / DENSITY))
            for(y = 0; y < Car.rows; y += (Car.rows / DENSITY)){
                Vec3b PixelValue = Car.at<Vec3b>(y,x);
                cout<<"The blue value at ("<< x <<","<< y <<") is "<< (int)PixelValue[0]<<endl;
                cout<<"The green value at ("<< x <<","<< y <<") is "<<(int)PixelValue[1]<<endl;
                cout<<"The red value at ("<< x <<","<< y <<") is "  <<(int)PixelValue[2]<<endl;
                /*
                // ABSOLUTE SEARCH METHOD
                if(PixelValue[0] > UPPERBOUND - BSHIFT && PixelValue[1] < LOWERBOUND - GSHIFT && PixelValue[2] < LOWERBOUND - RSHIFT) countB++;
                if(PixelValue[1] > UPPERBOUND - GSHIFT && PixelValue[0] < LOWERBOUND - BSHIFT && PixelValue[2] < LOWERBOUND - RSHIFT) countG++;
                if(PixelValue[2] > UPPERBOUND - RSHIFT && PixelValue[1] < LOWERBOUND - GSHIFT && PixelValue[0] < LOWERBOUND - BSHIFT) countR++;
                // ~70% accuracy, fails on green cars pretty often even when correcting the values using GSHIFT
                */ /*
                // RELATIVE SEARCH METHOD
                if(PixelValue[0] > PixelValue[1] + PixelValue[2] + DIFFERENCE) countB++;
                if(PixelValue[1] > PixelValue[0] + PixelValue[2] + DIFFERENCE) countG++;
                if(PixelValue[2] > PixelValue[1] + PixelValue[0] + DIFFERENCE) countR++;
                // 100% accuracy at first test run using DIFFERENCE = 0
                */
                // VECTOR NORMALIZATION METHOD
                float module = sqrt( pow(PixelValue[0], 2) + pow(PixelValue[1], 2) + pow(PixelValue[2], 2));
                float norm[3];
                float angle[3];
                norm[0] = PixelValue[0] / module;
                angle[0] = acos(norm[0]);
                norm[1] = PixelValue[1] / module;
                angle[1] = acos(norm[1]);
                norm[2] = PixelValue[2] / module;
                angle[2] = acos(norm[2]);
                if(angle[0] < PI / 5) countB++;
                if(angle[1] < PI / 5) countG++;
                if(angle[2] < PI / 5) countR++;
                cout<<"Normalized vectors: B: " << norm[0] << ", G: " << norm[1] << ", R: " << norm[2] << "." << endl;
                cout<<"Angles: B: " << angle[0] << ", G: " << angle[1] << ", R: " << angle[2] << "." << endl;

            }
        cout<<"Pixel Count B: " << countB << ", G: " << countG << ", R: " << countR << "." << endl;

        if(countB > countG && countB > countR) cout<< "THE CAR IS BLUE" << endl;
        if(countG > countB && countG > countR) cout<< "THE CAR IS GREEN" << endl;
        if(countR > countG && countR > countB) cout<< "THE CAR IS RED" << endl;

        //============================================================

        //display the car image untill x is pressed
        while(waitKey(10)!='x'){
            imshow("Car", Car);
        }

    }

}





















#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>

#include "opencv2/imgcodecs.hpp"
#include <QString>
#include <QFileDialog>

//#include "arguments.h"

using namespace std;
using namespace cv;


/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
*/


Mat src,img,ROI, src_original, src_gray, src_threshed;
Rect cropRect(0,0,0,0);
Point P1(0,0);
Point P2(0,0);
int Window = 100 ;
int const MaxThresh = 255;


const char* winName="Crop Image";
bool clicked=false;
int i=0;
char imgName[15];
//cv::Scalar     meann;
//cv::Scalar     stddev;
Mat meann(1,4,CV_64F),stddev(1,4,CV_64F);

const int maxNumSamples = 10;
Mat Object1_array[maxNumSamples];
std::vector<Mat> Object1_mean(maxNumSamples), Object1_stddev(maxNumSamples), Object1_hist(maxNumSamples), Object1_hist_Av(1);


Mat Object2_array[maxNumSamples];
std::vector<Mat> Object2_mean(maxNumSamples), Object2_stddev(maxNumSamples), Object2_hist(maxNumSamples), Object2_hist_Av(1);

Mat BackGround_array[maxNumSamples];
std::vector<Mat> BackGround_mean(maxNumSamples), BackGround_stddev(maxNumSamples), BackGround_hist(maxNumSamples), BackGround_hist_Av(1);


std::vector<Mat> Hist_current(1);


void showHistogram();


void MeanHistogram(int Object1_Index, int Object2_Index, int BackGround_Index)
{
    Mat Object1_Avg;
    Object1_Avg = cv::Mat::zeros(Object1_array[0].size(), CV_32F);

    Mat Object2_Avg;
    Object2_Avg = cv::Mat::zeros(Object2_array[0].size(), CV_32F);

    Mat BackGround_Avg;
    BackGround_Avg = cv::Mat::zeros(BackGround_array[0].size(), CV_32F);

    Mat Stack;
    Stack = cv::Mat::zeros(BackGround_array[1].size(),  CV_32F) ;

    Object1_hist_Av[0] = Mat::zeros(1, 256, CV_32SC1);
    Object2_hist_Av[0] = Mat::zeros(1, 256, CV_32SC1);
    BackGround_hist_Av[0] = Mat::zeros(1, 256, CV_32SC1);

    if (Object1_Index > 0)
    {
        for (int i = 0; i < Object1_Index; i++)
        {
            std::cout << Stack.channels() << endl;
            std::cout << Object1_Avg.channels() << endl;
            meanStdDev(Object1_array[i], Object1_mean[i], Object1_stddev[i]);
            Object1_array[i].convertTo(Stack, CV_32F);

            cout << Stack.size() << endl ;
            cout << Object1_array[i].size() << endl ;
            cout << Object1_Avg.size() << endl;

            cout << Object1_hist_Av[0] << endl;
            cout << Object1_hist[i] << endl;
            cv::add(Object1_hist[i], Object1_hist_Av[0], Object1_hist_Av[0]) ;
            cout << Object1_hist_Av[0] << endl;
        }
        cv::divide(Object1_hist_Av[0], ((Object1_hist_Av[0]*0) + Object1_Index), Object1_hist_Av[0], 1);
        cout << Object1_hist_Av[0] << endl;
        namedWindow("AvObj1",WINDOW_NORMAL);
        resizeWindow("AvObj1", Window*4, Window*4);
        Object1_Avg.convertTo(Object1_Avg, CV_8UC1);
        imshow("AvObj1",Object1_Avg);
        ROI = Object1_Avg;
        showHistogram();
        cv::waitKey(4000);

    }

    if (Object2_Index > 0)
    {
        for (int i = 0; i < Object2_Index; i++)
        {
            std::cout << Stack.channels() << endl;
            std::cout << Object2_Avg.channels() << endl;
            meanStdDev(Object2_array[i], Object2_mean[i], Object2_stddev[i]);
            Object2_array[i].convertTo(Stack, CV_32F);

            cout << Stack.size() << endl ;
            cout << Object2_array[i].size() << endl ;
            cout << Object2_Avg.size() << endl;

            cout << Object2_hist_Av[0] << endl;
            cout << Object2_hist[i] << endl;
            cv::add(Object2_hist[i], Object2_hist_Av[0], Object2_hist_Av[0]) ;
            cout << Object2_hist_Av[0] << endl;
        }
        cv::divide(Object2_hist_Av[0], ((Object2_hist_Av[0]*0) + Object2_Index), Object2_hist_Av[0], 1);
        cout << Object2_hist_Av[0] << endl;
        namedWindow("AvObj1",WINDOW_NORMAL);
        resizeWindow("AvObj1", Window*4, Window*4);
        Object2_Avg.convertTo(Object2_Avg, CV_8UC1);
        imshow("AvObj1",Object2_Avg);
        ROI = Object2_Avg;
        showHistogram();
        cv::waitKey(4000);
    }

    if (BackGround_Index > 0)
    {
        for (int i = 0; i < BackGround_Index; i++)
        {
            std::cout << Stack.channels() << endl;
            std::cout << BackGround_Avg.channels() << endl;
            meanStdDev(BackGround_array[i], BackGround_mean[i], BackGround_stddev[i]);
            BackGround_array[i].convertTo(Stack, CV_32F);

            cout << Stack.size() << endl ;
            cout << BackGround_array[i].size() << endl ;
            cout << BackGround_Avg.size() << endl;

            cout << BackGround_hist_Av[0] << endl;
            cout << BackGround_hist[i] << endl;
            cv::add(BackGround_hist[i], BackGround_hist_Av[0], BackGround_hist_Av[0]) ;
            cout << BackGround_hist_Av[0] << endl;
        }
        cv::divide(BackGround_hist_Av[0], ((BackGround_hist_Av[0]*0) + BackGround_Index), BackGround_hist_Av[0], 1);
        cout << BackGround_hist_Av[0] << endl;
        namedWindow("AvObj1",WINDOW_NORMAL);
        resizeWindow("AvObj1", Window*4, Window*4);
        BackGround_Avg.convertTo(BackGround_Avg, CV_8UC1);
        imshow("AvObj1",BackGround_Avg);
        ROI = BackGround_Avg;
        showHistogram();
        cv::waitKey(4000);
    }
}




void showHistogram()
{
    int bins = 256;             // number of bins
    int nc = ROI.channels();    // number of channels

    vector<Mat> hist(nc);       // histogram arrays


    // Initalize histogram arrays
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    // Calculate the histogram of the image
    for (int k = 0; k < nc; k++)
    {
        for (int i = 0; i < ROI.rows; i++)
        {
            for (int j = 0; j < ROI.cols; j++)
            {
                uchar val = nc == 1 ? ROI.at<uchar>(i,j) : ROI.at<Vec3b>(i,j)[k];
                hist[k].at<int>(val) += 1;
            }
        }
    }
    Hist_current[0] = hist[0];

    // For each histogram arrays, obtain the maximum (peak) value
    // Needed to normalize the display later
    int hmax[3] = {0,0,0};
    for (int i = 0; i < nc; i++)
    {
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
    }

    const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    vector<Mat> canvas(nc);

    // Display each histogram in a canvas

    for (int i = 0; i < nc; i++)
    {
        //canvas[i] = Mat::ones(425, bins, CV_8UC3);
        canvas[i] = Mat::ones(125, 300, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
        {
            line(
                canvas[i],
                Point(j, rows),
                Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                nc == 1 ? Scalar(200,200,200) : colors[i],
                1, 8, 0
            );
        }

        imshow(nc == 1 ? "value" : wname[i], canvas[i]);
        //cv::putText(img, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
    }
}




void checkBoundary()
{
   //check croping rectangle exceed image boundary
   if(cropRect.width>img.cols-cropRect.x)
     cropRect.width=img.cols-cropRect.x;

   if(cropRect.height>img.rows-cropRect.y)
     cropRect.height=img.rows-cropRect.y;

    if(cropRect.x<0)
     cropRect.x=0;

   if(cropRect.y<0)
     cropRect.height=0;
}

void showImage()
{
    img=src.clone();
    checkBoundary();
    if(cropRect.width>0&&cropRect.height>0)
    {
        //ROI=img(cropRect);
        ROI= src(cropRect);
        meanStdDev(ROI, meann, stddev);
        namedWindow("Cropped",WINDOW_NORMAL);
        resizeWindow("Cropped", Window*4, Window*4);
        imshow("Cropped",ROI);
        showHistogram();
    }
    rectangle(img, cropRect, Scalar(0,255,0), 2, 8, 0 );
    imshow(winName,img);

}


void onMouse( int event, int x, int y, int f, void* )
{

    switch(event)
    {

        case  CV_EVENT_LBUTTONDOWN  :
            clicked=true;

            P1.x=x;
            P1.y=y;
            P2.x=x;
            P2.y=y;
            break;

        case  CV_EVENT_LBUTTONUP    :
            P2.x=x;
            P2.y=y;
            clicked=false;
            break;

        case  CV_EVENT_MOUSEMOVE    :
            if(clicked)
            {
                P2.x=x;
                P2.y=y;
            }
            break;

        default                     :   break;


    }


    if(clicked){

        if(P1.x>P2.x)
        {
            cropRect.x=P2.x;
            cropRect.width=P1.x-P2.x;
        }
        else
        {
            cropRect.x=P1.x;
            cropRect.width=P2.x-P1.x;
        }

        if(P1.y>P2.y){ cropRect.y=P2.y;
                       cropRect.height=P1.y-P2.y; }
        else {         cropRect.y=P1.y;
                       cropRect.height=P2.y-P1.y; }


        cropRect.x = P2.x - Window/2;
        cropRect.y = P2.y - Window/2;
        cropRect.width = Window;
        cropRect.height= Window;

    }

    showImage();


}
//int main()
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    std::cout<< "Hello" << std::endl;
    std::cout<< w.ROII  << std::endl;

    w.show();


    cout<<"Click and drag for Selection"<<endl<<endl;
    cout<<"------> Press 's' to save"<<endl<<endl;

    cout<<"------> Press '8' to move up"<<endl;
    cout<<"------> Press '2' to move down"<<endl;
    cout<<"------> Press '6' to move right"<<endl;
    cout<<"------> Press '4' to move left"<<endl<<endl;

    cout<<"------> Press 'w' increas top"<<endl;
    cout<<"------> Press 'x' increas bottom"<<endl;
    cout<<"------> Press 'd' increas right"<<endl;
    cout<<"------> Press 'a' increas left"<<endl<<endl;

    cout<<"------> Press 't' decrease top"<<endl;
    cout<<"------> Press 'b' decrease bottom"<<endl;
    cout<<"------> Press 'h' decrease right"<<endl;
    cout<<"------> Press 'f' decrease left"<<endl<<endl;

    cout<<"------> Press 'r' to reset"<<endl;
    cout<<"------> Press 'Esc' to quit"<<endl<<endl;


    namedWindow(winName,WINDOW_NORMAL);
    QString filename = QFileDialog::getOpenFileName();
    std::string filename2 = filename.toStdString();
    //src=imread("/home/yjon701/Documents/ImageProcessing/2MicroBeed_Fresh_Transmission_Green.jpg",1);
    src = imread(filename2);
    src_original = src;

    setMouseCallback(winName,onMouse,NULL );
    resizeWindow(winName, 558, 420);
    imshow(winName,src);




    Mat img_background2;
    Mat img_background;
    Mat img_clean2;
    Mat img_clean;    int Object1_Index = 0;
    int Object2_Index = 0;
    int BackGround_Index = 0;
    //img_clean.create(2,2,CV_8UC3);
    Mat src2;

    //img.create(2,2,CV_8UC1);

    img.convertTo(img_background2, CV_32FC3); // or CV_32F works (too)
    img.convertTo(img_clean2, CV_32FC3);      // img_clean2 is a 32 bit floating point image
    src.convertTo(src2, CV_32FC3);            // src2 is a 32 bit floating point image


    //img = src.clone();
    /*
    namedWindow("Back_Subbed",WINDOW_NORMAL);
    resizeWindow("Back_Subbed", 630, 420);
    namedWindow("Cleaned",WINDOW_NORMAL);
    resizeWindow("Cleaned", 630, 420);
    namedWindow("BackGround",WINDOW_NORMAL);
    resizeWindow("BackGround", 630, 420);
    */
    /*
    for (int ii=1; ii<1102; ii=ii+200)
    {
        GaussianBlur( src2, img_background2, Size( ii, ii ), 0, 0 );
        //img_clean2 = src - img_background;
    }
    */

    int ii = 500 ;
    blur( src2, img_background2, Size( ii, ii ));
    blur( img_background2, img_background2, Size( ii, ii ));
    img_clean2 = src2 - img_background2;
    //img_clean2.convertTo(img_clean, CV_8UC3);   // img_clean2 is a 8 bit UChar image
    img_background2.convertTo(img_background, CV_8UC3);


    /// Split the image into different channels
    vector<Mat> rgbChannels(3);
    ii = 5;
    blur( img_clean2, img_clean2, Size( ii, ii ));
    split(img_clean2, rgbChannels);
    double min, max;
    // Show individual channels
    Mat g, fin_img;
    fin_img.create(2,2,CV_32FC3);
    g = Mat::zeros(Size(src.cols, src.rows), CV_32FC1);
    // Showing Red Channel
    // G and B channels are kept as zero matrix for visual perception
    {
        vector<Mat> channels;

        cv::minMaxLoc(rgbChannels[0], &min, &max);          //Blue
        rgbChannels[0] = rgbChannels[0] - min;
        channels.push_back(rgbChannels[0]);

        cv::minMaxLoc(rgbChannels[1], &min, &max);          //Green
        rgbChannels[1] = rgbChannels[1] - min;
        channels.push_back(rgbChannels[1]);

        cv::minMaxLoc(rgbChannels[2], &min, &max);          //Red
        rgbChannels[2] = rgbChannels[2] - min;
        channels.push_back(rgbChannels[2]);

        merge(channels, fin_img);
        //blur( fin_img, fin_img, Size( 10, 10 ));
        fin_img.convertTo(fin_img, CV_8UC3);

    }




    //imshow( "BackGround", img_background2 );
    //waitKeyJJ = JJ + 1;
    //int ssize[3] = { w.ROII, w.ROII, 10 };
    //cv::Mat SS(10, ssize, CV_32FC1, cv::Scalar(10));
    //std::cout << SS.channels() << endl ;
    //std::cout << SS.at<cv::Vec3f>(21,21)[3] << endl;(2000);
    namedWindow("Back_Subbed",WINDOW_NORMAL);
    resizeWindow("Back_Subbed", 558, 420);
    imshow( "Back_Subbed", img_background );
    waitKey(2000);
    namedWindow("RawImage",WINDOW_NORMAL);
    resizeWindow("RawImage", 558, 420);
    imshow( "RawImage", src );
    waitKey(2000);
    src = fin_img;
    cvtColor( src, src_gray, CV_BGR2GRAY );
    src = src_gray;

    while(1)
    {

        char c=waitKey();
        Window = w.ROII;
        if(c=='s'&&ROI.data)
        {
             sprintf(imgName,"%d.jpg",i++);
             imwrite(imgName,ROI);
             cout<<"  Saved "<<imgName<<endl;
        }
        if(c=='6') cropRect.x++;
        if(c=='4') cropRect.x--;
        if(c=='8') std::cout<< w.ROII  << std::endl; //cropRect.y--;
        if(c=='2') {double minn, maxx; cv::minMaxLoc(Hist_current[0], &minn, &maxx); cout << "Min: " << minn  << " Max: " << maxx << endl;}
            //std::cout << "Mean: " << meann << std::endl << "   StdDev: " << stddev << std::endl;
            //cerr << meann << " " << stddev << endl;
          //std::cout<< Histogram[0]; //std::cout<< w.Instance  << std::endl; //cropRect.y++;
        if(c=='3')
        {
            switch (w.Instance)
            {
                case  1:
                {
                    Object1_array[w.Object1_Index] = ROI;
                    Object1_hist[w.Object1_Index] = Mat::zeros(1, 256, CV_32SC1);
                    Object1_hist[w.Object1_Index] = Hist_current[0];

                    w.Object1_Index++;
                    break;
                }
                case  2:
                {
                    Object2_array[w.Object2_Index] = ROI;
                    Object2_hist[w.Object2_Index] = Mat::zeros(1, 256, CV_32SC1);
                    Object2_hist[w.Object2_Index] = Hist_current[0];
                    w.Object2_Index++;
                    break;
                }
                case  3:
                {
                    BackGround_array[w.BackGround_Index] = ROI;
                    BackGround_hist[w.BackGround_Index] = Mat::zeros(1, 256, CV_32SC1);
                    BackGround_hist[w.BackGround_Index] = Hist_current[0];
                    //cout << BackGround_array[w.BackGround_Index] << endl;
                    w.BackGround_Index++;
                    break;
                }
            }
        }

        if(c=='4')
        {
            MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);

        }
        if(c=='w') { cropRect.y--; cropRect.height++;}
        if(c=='d') cropRect.width++;
        if(c=='x') cropRect.height++;
        if(c=='a') { cropRect.x--; cropRect.width++;}

        if(c=='t') { cropRect.y++; cropRect.height--;}
        if(c=='h') cropRect.width--;
        if(c=='b') cropRect.height--;
        if(c=='f') { cropRect.x++; cropRect.width--;}
        if(c=='r') {cvtColor( fin_img, src, CV_BGR2GRAY );}
        if(c=='t') {threshold( src_gray, src, w.ThreshVale, MaxThresh, w.Instance );}

        if(c==27) break;
        if(c=='r') {cropRect.x=0;cropRect.y=0;cropRect.width=0;cropRect.height=0;}
        showImage();
    }
    //return a.exec();
    return 0;
}

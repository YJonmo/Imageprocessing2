#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
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
Mat src, src2, img,ROI, src_temp, src_original, src_gray, src_threshed;
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
Mat meann(1,1,CV_64F),stddev(1,1,CV_64F);
const int maxNumSamples = 50;
Mat Object1_array[maxNumSamples], Object1_array_Threshed[maxNumSamples];
std::vector<Mat> Object1_mean(maxNumSamples), Object1_stddev(maxNumSamples),Object1_hist(maxNumSamples);
std::vector<Mat> Object1_hist_Av(1);
int No_Object1;
int No_Pix1;
Mat Object2_array[maxNumSamples], Object2_array_Threshed[maxNumSamples];
std::vector<Mat> Object2_mean(maxNumSamples), Object2_stddev(maxNumSamples), Object2_hist(maxNumSamples);
std::vector<Mat> Object2_hist_Av(1);
int No_Object2;
Mat BackGround_array[maxNumSamples], BackGround_array_Threshed[maxNumSamples];
std::vector<Scalar> BackGround_mean(maxNumSamples) , BackGround_stddev(maxNumSamples);
double Min_BkGn_mean, Max_BkGn_mean, Max_BkGn_STD, Min_BkGn_STD;
std::vector<Mat> BackGround_hist_Av(1), BackGround_hist(maxNumSamples);
std::vector<Mat> Hist_current(1);
void showHistogram();
void showImage();
void showGrids(int Grid_Size, int Obj1_NoBlk_Pix)
{
    int No_Rows = src.rows/Grid_Size;
    int No_Cols= src.cols/Grid_Size;
    int  Grid_NoBlk_Pix = 0;
    float Grid_Objs = 0;
    src_temp = src_original.clone();
    namedWindow("Counted",WINDOW_NORMAL);
    resizeWindow("Counted", 800, 650);
    int TextOffset_X = Grid_Size/10;
    int TextOffset_Y = Grid_Size/3;
    cv::Point TextOrig (TextOffset_X, TextOffset_Y);
    cv::Point2i p1, p2;
    //cv::Point2i p1(1, 1 + Grid_Size);
    //cv::Point2i p2(src.cols, 1 + Grid_Size);
    //cv::line(src, p1, p2, cv::Scalar(255,255,255), 5, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
    p1.x = 1; p1.y = 1;
    p2.x = src.cols; p2.y = 1;
    for (int Row_Ind = 0; Row_Ind <= No_Rows; Row_Ind++)
    {
        TextOrig.y = TextOffset_Y + Grid_Size*Row_Ind;
        p1.y = 1 + Grid_Size*(Row_Ind+1);
        p2.y = 1 + Grid_Size*(Row_Ind+1);
        cv::line(src_temp, p1, p2, cv::Scalar(255,255,255), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
        //showImage();
        for (int Col_Ind = 0; Col_Ind <= No_Cols; Col_Ind++)
        {
            Grid_NoBlk_Pix = 0;
            for (int i = (p1.y - Grid_Size); (i < p1.y)&(i < src.rows); i++)
            {
                for (int j = p1.x + Grid_Size*Col_Ind; (j < (p1.x + Grid_Size*(Col_Ind + 1)))&(j < src.cols); j++)
                {
                    //if ( src.at<cv::Vec3b>(y,x) == cv::Vec3b(255,255,255) ) Count_Black++;
                    if (src.at<uchar>(i,j) != 0) {//src.at<uchar>(i,j) = 25+30*Row_Ind;
                        Grid_NoBlk_Pix++;}
                }
            }
            //cout << "Obj1_NoBlk_Pix: " << Obj1_NoBlk_Pix << endl;
            //cout << "Grid_NoBlk_Pix:" << Grid_NoBlk_Pix << endl;
            Grid_Objs = float(Grid_NoBlk_Pix)/float(Obj1_NoBlk_Pix);
            stringstream stream;
            stream << fixed << setprecision(1) << Grid_Objs;
            string oneDecimal = stream.str();
            TextOrig.x = TextOffset_X + Grid_Size*Col_Ind;
            //cv::putText(src_temp, std::to_string(Grid_Objs), TextOrig, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar (255,255,255), Window/10, Window/3 );
            cv::putText(src_temp, oneDecimal, TextOrig, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar (255,255,255), Window/10, Window/3 );
            /*
            cv::Point TextOrig2;
            TextOrig2.x = TextOrig.x;
            TextOrig2.y = TextOrig.y +20;
            cv::putText(src, std::to_string(TextOrig.y), TextOrig2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar (255,255,255), 3, 8 );
            */
            showImage();
            imshow("Counted",src_temp);
            cv::waitKey(11);
        }
    }
    //cv::putText(src, " text", TextOrig, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar (255,255,255), 3, 8 );
    //(img, text, Point org, fontFace, fontScale, color, thickness=1, lineType=8, bool bottomLeftOrigin=false )
    for (int Col_Ind = 1; Col_Ind <= No_Cols; Col_Ind++)
    {
        cv::Point2i p1(1 + Grid_Size*Col_Ind, 1);
        cv::Point2i p2(1 + Grid_Size*Col_Ind, src.rows);
        cv::line(src_temp, p1, p2, cv::Scalar(255,255,255), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
    }
    imshow("Counted",src_temp);
    cv::waitKey(11);
}
void countObjects(int Object1_Index, int Object2_Index, int BackGround_Index, int Thresh_Type)
{
    int Obj1_NoBlk_Pix = 0;
    int Obj2_NoBlk_Pix = 0;
    int BkGr_NoBlk_Pix = 0;
    int  src_NoBlk_Pix = 0;
    No_Object1 = 0;
    No_Object2 = 0;
    //cout << "Object1_Index: " << Object1_Index ;
    for(int ii = 0; ii < Object1_Index; ii++)
    {
        threshold( Object1_array[ii], Object1_array_Threshed[ii], (Min_BkGn_mean - Max_BkGn_STD*2), MaxThresh, Thresh_Type );
        for (int i = 0; i < Object1_array_Threshed[ii].rows; i++)
        {
            for (int j = 0; j < Object1_array_Threshed[ii].cols; j++)
            {
                //if ( src.at<cv::Vec3b>(y,x) == cv::Vec3b(255,255,255) ) Count_Black++;
                if ((Thresh_Type == 3)&&(Object1_array[ii].at<uchar>(i,j) != 0)) Obj1_NoBlk_Pix++;
                else if ((Thresh_Type == 4)&&(Object1_array[ii].at<uchar>(i,j) != 0)) Obj1_NoBlk_Pix++;
            }
        }
    }
    //cout << " Obj1_NoBlk_Pix: " << Obj1_NoBlk_Pix << endl;
    Obj1_NoBlk_Pix = Obj1_NoBlk_Pix/Object1_Index;        //Average number of the pixels belonging to the Object1
    //cout << " Obj1_NoBlk_Pix: " << Obj1_NoBlk_Pix << endl;
    for(int ii = 0; ii < Object2_Index; ii++)
    {
        threshold( Object2_array[ii], Object2_array_Threshed[ii], (Min_BkGn_mean - Max_BkGn_STD*2), MaxThresh, Thresh_Type );
    }
    for(int ii = 0; ii < BackGround_Index; ii++)
    {
        threshold( BackGround_array[ii], BackGround_array_Threshed[ii], (Min_BkGn_mean - Max_BkGn_STD*2), MaxThresh, Thresh_Type );
    }
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            //if ( src.at<cv::Vec3b>(y,x) == cv::Vec3b(255,255,255) ) Count_Black++;
            if ((Thresh_Type == 3)&&(src.at<uchar>(i,j) != 0)) src_NoBlk_Pix++;
            else if ((Thresh_Type == 4)&&(src.at<uchar>(i,j) != 0)) {src_NoBlk_Pix++;}
            //if (src.at<uchar>(i,j) == 0) src_NoBlk_Pix++;
        }
    }
    if (Obj1_NoBlk_Pix > 0)
    {
        No_Object1 = src_NoBlk_Pix/Obj1_NoBlk_Pix;
        cout << "src_NoBlk_Pix: " << src_NoBlk_Pix << endl;   //Number of the pixels passed the threshold
        cout << "Number of Object 1: " << No_Object1 << endl; //Number of Object1
        showGrids(Window*5, Obj1_NoBlk_Pix);
    }
    else
    {
        cout << "Please do thresholding before counting." << endl;
    }
}
void MeanHistogram(int Object1_Index, int Object2_Index, int BackGround_Index)
{
    Mat Object1_Avg;
    Object1_Avg = cv::Mat::zeros(Object1_array[0].size(), CV_32F);
    Mat Object2_Avg;
    Object2_Avg = cv::Mat::zeros(Object2_array[0].size(), CV_32F);
    Mat BackGround_Avg;
    BackGround_Avg = cv::Mat::zeros(BackGround_array[0].size(), CV_32F);
    Mat Stack;
    Stack = cv::Mat::zeros(BackGround_array[0].size(),  CV_32F) ;
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
        //namedWindow("AvObj1",WINDOW_NORMAL);
        //resizeWindow("AvObj1", Window*4, Window*4);
        //Object1_Avg.convertTo(Object1_Avg, CV_8UC1);
        //imshow("AvObj1",Object1_Avg);
        //ROI = Object1_Avg;
        //showHistogram();
        //cv::waitKey(200);
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
        resizeWindow("AvObj1", Window*8, Window*8);
        Object2_Avg.convertTo(Object2_Avg, CV_8UC1);
        imshow("AvObj1",Object2_Avg);
        ROI = Object2_Avg;
        showHistogram();
        cv::waitKey(122);
    }
    if (BackGround_Index > 0)
    {
        for (int i = 0; i < BackGround_Index; i++)
        {
            std::cout << Stack.channels() << endl;
            std::cout << BackGround_Avg.channels() << endl;
            cv::meanStdDev(BackGround_array[i], BackGround_mean.at(i), BackGround_stddev.at(i));
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
        //namedWindow("AvObj1",WINDOW_NORMAL);
        //resizeWindow("AvObj1", Window*4, Window*4);
        //BackGround_Avg.convertTo(BackGround_Avg, CV_8UC1);
        //imshow("AvObj1",BackGround_Avg);
        //ROI = BackGround_Avg;
        //showHistogram();
        //cv::waitKey(4000);
        for (unsigned ii=0; ii <BackGround_Index; ii++)
        {
            std::cout << ' ' << BackGround_mean.at(ii)<< endl;
                 cout << BackGround_mean.size() << endl;
        }
        std::cout << '\n';
        cout << BackGround_mean.size() << endl;
        //cout << BackGround_mean << endl;
        std::vector<double> Stack(BackGround_Index);
        for(int i=0; i < BackGround_Index; i++)
        {
            Stack[i] = BackGround_mean[i][0];
        }
        cv::minMaxLoc(Stack, &Min_BkGn_mean, &Max_BkGn_mean);
        cv::minMaxLoc(BackGround_stddev, &Min_BkGn_STD, &Max_BkGn_STD);
        cout << "Min: " << Min_BkGn_mean  << " Max: " << Max_BkGn_mean << endl;
        cout << "Min: " << Min_BkGn_STD  << " Max: " << Max_BkGn_STD << endl;
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
    rectangle(img, cropRect, Scalar(155,255,155), 2, 8, 0 );
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
    cout<<"------> Press '3' to select the sample"<<endl;
    cout<<"------> Press '2' count the objects after sample selection"<<endl;
    cout<<"------> Press '1' count the objects after sample selection (inverse thresholding)"<<endl;
    cout<<"------> Press 'a' to reset the image to the original"<<endl;
    cout<<"------> Press 't' for image thresholding"<<endl;
    cout<<"------> Press 'u' to move up"<<endl;
    cout<<"------> Press 'd' to move down"<<endl;
    cout<<"------> Press 'r' to move right"<<endl;
    cout<<"------> Press 'l' to move left"<<endl<<endl;
    cout<<"------> Press 'Esc' to quit"<<endl<<endl;
    namedWindow(winName,WINDOW_NORMAL);
    QString filename = QFileDialog::getOpenFileName();
    std::string filename2 = filename.toStdString();
    //src=imread("/home/yjon701/Documents/ImageProcessing/2MicroBeed_Fresh_Transmission_Green.jpg",1);
    src = imread(filename2);
    src_original = src;
    setWindowProperty(winName, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    imshow(winName,src);
    resizeWindow(winName, 658, 520);
    imshow(winName,src);
    waitKey(1);
    setMouseCallback(winName,onMouse,NULL );
    Mat img_background2;
    Mat img_background;
    Mat img_clean2;
    Mat img_clean;    int Object1_Index = 0;
    int Object2_Index = 0;
    int BackGround_Index = 0;
    //img_clean.create(2,2,CV_8UC3);
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
    ii = 2;
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
        //blur( fin_img, fin_img, Size( 2, 2 ));
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
        char c=waitKey(1);
        c = '~';
        while (c == '~')
        {
            Window = w.ROII;
            c=waitKey(1000);
        }
        //Window = w.ROII;

        if(c=='s'&&ROI.data)
        {
             sprintf(imgName,"%d.jpg",i++);
             imwrite(imgName,ROI);
             cout<<"  Saved "<<imgName<<endl;
        }
        if(c=='l') cropRect.x++;
        if(c=='r') cropRect.x--;
        if(c=='d') cropRect.y++;
        if(c=='u') cropRect.y--;
        //if(c=='6') cropRect.x++;
        //if(c=='4') cropRect.x--;
        //if(c=='8') std::cout<< w.ROII  << std::endl; //cropRect.y--;
        //if(c=='2') showGrids(250,22);
        /*{double minn, maxx; cv::minMaxLoc(Hist_current[0], &minn, &maxx);
            cout << "Min: " << minn  << " Max: " << maxx << endl;}*/
            //std::cout << "Mean: " << meann << std::endl << "   StdDev: " << stddev << std::endl;
            //cerr << meann << " " << stddev << endl;
          //std::cout<< Histogram[0]; //std::cout<< w.Instance  << std::endl; //cropRect.y++;
        if(c=='0')
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
        //if(c=='4')
        //{
        //    MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);
        //}
        if(c=='c')
        {
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 3);
        }
        if(c=='v')
        {
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 4);
        }
        /*
        if(c=='w') { cropRect.y--; cropRect.height++;}
        if(c=='d') cropRect.width++;
        if(c=='x') cropRect.height++;
        if(c=='a') { cropRect.x--; cropRect.width++;}
        if(c=='t') { cropRect.y++; cropRect.height--;}
        if(c=='h') cropRect.width--;
        if(c=='b') cropRect.height--;
        if(c=='f') { cropRect.x++; cropRect.width--;}
        */
        if(c=='a') {cvtColor( fin_img, src, CV_BGR2GRAY );}         // resets
        if(c=='t') {threshold( src_gray, src, w.ThreshVale, MaxThresh, w.Instance );}
        if(c=='m')
        {
            int threshh = (Min_BkGn_mean - Max_BkGn_STD*2) ;
            cout << "threshh: " << threshh << endl;
        }
        if(c=='1')
        {
            MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);
            threshold( src_gray, src, (Min_BkGn_mean - Max_BkGn_STD*2), MaxThresh, w.Instance );
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 3);
        }
        if(c=='2')
        {
            MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);
            threshold( src_gray, src, (Min_BkGn_mean - Max_BkGn_STD*2), MaxThresh, 4 );
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 4);
        }
        if(c=='3')
        {
            MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);
            //threshold( src_gray, src, (Min_BkGn_mean - Max_BkGn_STD*2), (Max_BkGn_mean + Max_BkGn_STD*2), 4 );
            threshold( src_gray, src, (Max_BkGn_mean + Max_BkGn_STD*2), MaxThresh, 3 );
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 3);
        }
        if(c=='4')
        {
            MeanHistogram(w.Object1_Index, w.Object2_Index, w.BackGround_Index);
            threshold( src_gray, src, (Max_BkGn_mean + Max_BkGn_STD*2), MaxThresh, 4 );
            countObjects(w.Object1_Index, w.Object2_Index, w.BackGround_Index, 4);
        }
        if(c==27) break;
        //if(c=='r') {cropRect.x=0;cropRect.y=0;cropRect.width=0;cropRect.height=0;}
        showImage();
    }
    //return a.exec();
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <direct.h>
#include <ctime>
#include <vector>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

char namev[100];
int sc_rows = 1920;
int sc_cols = 1080;

int fillet_flag=0;
int p_rows = 56;
int p_cols = 56;

int hole_flag=0;
int c_rows=30;
int c_cols=28;
int rect_height=80;
int rect_width=240;

int delayFlag=1;


void InitImage(Mat &imgPixel,int R ,int G, int B){

	for (int j = 0; j<imgPixel.rows; j++)
	{
		uchar *data = imgPixel.ptr<uchar>(j);
		for (int i = 0; i<imgPixel.cols * 3; i += 3)
		{

			*data++ = B;//B
			*data++ = G;//G
			*data++ = R;//R
		}
	}

}

void ImageFillet(Mat &imgPixel,int RGBW, vector<vector<int> > &pixelB, vector<vector<int> > &pixelG, vector<vector<int> > &pixelR ){

	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
		{
            switch (RGBW){
                //R
                case 0:
                    //left up
                    imgPixel.at<Vec3b>(j, i)[0] = 0;
                    imgPixel.at<Vec3b>(j, i)[1] = 0;
                    imgPixel.at<Vec3b>(j, i)[2] = pixelR[j][i];
                    //right up
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[0] = 0;
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[1] = 0;
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[2] = pixelR[j][i];
                    //left down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[0] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[1] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[2] = pixelR[j][i];
                    //right down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[0] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[1] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[2] = pixelR[j][i];
                    break;
                //G
                case 1:
                    //left up
                    imgPixel.at<Vec3b>(j, i)[0] = 0;
                    imgPixel.at<Vec3b>(j, i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(j, i)[2] = 0;
                    //right up
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[0] = 0;
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[2] = 0;
                    //left down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[0] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[2] = 0;
                    //right down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[0] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[2] = 0;
                    break;
                //B
                case 2:
                    //left up
                    imgPixel.at<Vec3b>(j, i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(j, i)[1] = 0;
                    imgPixel.at<Vec3b>(j, i)[2] = 0;
                    //right up
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[1] = 0;
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[2] = 0;
                    //left down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[1] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[2] = 0;
                    //right down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[1] = 0;
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[2] = 0;
                    break;
                //W
                default:
                    //left up
                    imgPixel.at<Vec3b>(j, i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(j, i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(j, i)[2] = pixelR[j][i];
                    //right up
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(j, sc_cols - 1 - i)[2] = pixelR[j][i];
                    //left down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, i)[2] = pixelR[j][i];
                    //right down
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[0] = pixelB[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[1] = pixelG[j][i];
                    imgPixel.at<Vec3b>(sc_rows - 1 - j, sc_cols - 1 - i)[2] = pixelR[j][i];
                    break;
            }
		}
	}
}

void ImageSetBackground(Mat &imgPixel, int leftUpX, int leftUpY, int rightDownX, int rightDownY, int R, int G, int B){

	for (int j = leftUpY; j<=rightDownY; j++)
	{
		for (int i = leftUpX; i<=rightDownX; i++)
		{
			//left up
			imgPixel.at<Vec3b>(j, i)[0] = B;
			imgPixel.at<Vec3b>(j, i)[1] = G;
			imgPixel.at<Vec3b>(j, i)[2] = R;
		}
	}

}

void ImageSetRegion(Mat &imgPixel,int RGBW, int leftUpX, int leftUpY, int rightDownX, int rightDownY, vector<vector<int> > &topholeB, vector<vector<int> > &topholeG, vector<vector<int> > &topholeR ){

    int height = rightDownY-leftUpY+1;
    int width = rightDownX-leftUpX+1;

	for (int j = 0; j<height; j++)
	{
		for (int i = 0; i<width; i++)
		{
            switch (RGBW){
                //R
                case 0:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = topholeR[j][i];
                    break;
                //G
                case 1:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = topholeG[j][i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = 0;
                    break;
                 //B
                case 2:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = topholeB[j][i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = 0;
                    break;
                 //W
                default :
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = topholeB[j][i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = topholeG[j][i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = topholeR[j][i];
                    break;
            }
		}
	}
}

void ImageSetRegionMirrorY(Mat &imgPixel, int RGBW, int leftUpX, int leftUpY, int rightDownX, int rightDownY, vector<vector<int> > &topholeB, vector<vector<int> > &topholeG, vector<vector<int> > &topholeR ){

    int height = rightDownY-leftUpY+1;
    int width = rightDownX-leftUpX+1;

	for (int j = 0; j<height; j++)
	{
		for (int i = 0; i<width; i++)
		{
            switch (RGBW){
                //R
                case 0:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = topholeR[j][width-1-i];
                    break;
                //G
                case 1:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = topholeG[j][width-1-i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = 0;
                    break;
                 //B
                case 2:
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = topholeB[j][width-1-i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = 0;
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = 0;
                    break;
                 //W
                default :
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[0] = topholeB[j][width-1-i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[1] = topholeG[j][width-1-i];
                    imgPixel.at<Vec3b>(leftUpY + j, leftUpX + i)[2] = topholeR[j][width-1-i];
                    break;
            }
		}
	}
}


void ReadData(vector<vector<int> > &pixel, string filename, int rows, int cols)
{
	fstream file(filename);
	if (!file.is_open())
	{
		cout << "Error opening file." << endl; exit(1);
	}

	for (int j = 0; j<rows; j++)
	{
		for (int i = 0; i<cols; i++)
		{
			file >> pixel[j][i];
			//cout<<pixel[j][i];
		}
	}
	//cout << "read data successe"<<endl;
	file.close();
}

void ReadConfig(string filename) {

	fstream file(filename);
	if (!file.is_open())
	{
		cout << "Error opening config file." << endl; exit(1);
	}

    file >> namev;
    file >> sc_rows;
    file >> sc_cols;

    file >> fillet_flag;
    file >> p_rows;
    file >> p_cols;

	file >> hole_flag;
    file >> c_rows;
    file >> c_cols;
    file >> rect_height;
    file >> rect_width;

    file >> delayFlag;
	file.close();
}

void Delay(int time){
    clockid_t now = clock();
    while(clock() - now < time);
}

int main()
{

	char* buffer;
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");

	string path = buffer;
	free(buffer);

	string::size_type pos = 0;
	while ((pos = path.find('\\', pos)) != string::npos) {
		//path.insert(pos,"\\");
		path.replace(pos, 1, "/");
		pos++;
		pos++;
	}

	string filename, fileversion, imgname;;
	filename = path + "/config.txt";
	ReadConfig(filename);
	fileversion = namev;

	Mat imgPixel(sc_rows, sc_cols, CV_8UC3);

/////////////////////////////////////////////////////////////////////////
	vector<vector<int> > pixelB(p_rows, vector<int>(p_cols));
	vector<vector<int> > pixelG(p_rows, vector<int>(p_cols));
	vector<vector<int> > pixelR(p_rows, vector<int>(p_cols));

    if(fillet_flag==1){

	filename = path + "/pixel_blue.txt";
	ReadData(pixelB, filename,p_rows, p_cols);

	filename = path + "/pixel_green.txt";
	ReadData(pixelG, filename,p_rows, p_cols);

	filename = path + "/pixel_red.txt";
	ReadData(pixelR, filename,p_rows, p_cols);

    //W
	InitImage(imgPixel,255,255,255);
    ImageFillet(imgPixel,3,pixelB,pixelG,pixelR);
	imgname = path + "/imgPixel_w"+ fileversion+".bmp";
	imwrite(imgname, imgPixel);

    // R
	InitImage(imgPixel,255,0,0);
    ImageFillet(imgPixel,0,pixelB,pixelG,pixelR);
	imgname = path + "/imgPixel_r" + fileversion + ".bmp";
	imwrite(imgname, imgPixel);

	// G
	InitImage(imgPixel,0,255,0);
    ImageFillet(imgPixel,1,pixelB,pixelG,pixelR);
	imgname = path + "/imgPixel_g" + fileversion + ".bmp";
	imwrite(imgname, imgPixel);

	//B
	InitImage(imgPixel,0,0,255);
    ImageFillet(imgPixel,2,pixelB,pixelG,pixelR);
	imgname = path + "/imgPixel_b" + fileversion + ".bmp";
	imwrite(imgname, imgPixel);

    }
/////////////////////////////////////////////////////////////////////////
    vector<vector<int> > topholeB(c_rows, vector<int>(c_cols));
    vector<vector<int> > topholeG(c_rows, vector<int>(c_cols));
    vector<vector<int> > topholeR(c_rows, vector<int>(c_cols));

    if(hole_flag==1){

    filename = path + "/tophole_blue.txt";
    ReadData(topholeB, filename,c_rows, c_cols);

    filename = path + "/tophole_green.txt";
    ReadData(topholeG, filename,c_rows, c_cols);

    filename = path + "/tophole_red.txt";
    ReadData(topholeR, filename,c_rows, c_cols);


    //W
    InitImage(imgPixel,255,255,255);
    if(fillet_flag==1)
        ImageFillet(imgPixel,3,pixelB,pixelG,pixelR);

    int leftUpX = (sc_cols-rect_width)/2;
    int leftUpY = 0;
    int rightDownX = leftUpX + rect_width -1;
    int rightDownY = rect_height -1;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = leftUpX;
    leftUpY = rightDownY + 1;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = leftUpY + c_rows -1;
    ImageSetRegion(imgPixel,3,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + (rect_width-c_cols*2) -1;
    rightDownY = rightDownY;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = rightDownY;
    ImageSetRegionMirrorY(imgPixel,3,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    imgname = path + "/imgPixelwithTopHole_w"+ fileversion+".bmp";
    imwrite(imgname, imgPixel);


    //R
    InitImage(imgPixel,255,0,0);
    if(fillet_flag==1)
        ImageFillet(imgPixel,0,pixelB,pixelG,pixelR);

    leftUpX = (sc_cols-rect_width)/2;
    leftUpY = 0;
    rightDownX = leftUpX + rect_width -1;
    rightDownY = rect_height -1;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = leftUpX;
    leftUpY = rightDownY + 1;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = leftUpY + c_rows -1;
    ImageSetRegion(imgPixel,0,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + (rect_width-c_cols*2) -1;
    rightDownY = rightDownY;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = rightDownY;
    ImageSetRegionMirrorY(imgPixel,0,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    imgname = path + "/imgPixelwithTopHole_r"+ fileversion+".bmp";
    imwrite(imgname, imgPixel);

    //G
    InitImage(imgPixel,0,255,0);
    if(fillet_flag==1)
        ImageFillet(imgPixel,1,pixelB,pixelG,pixelR);

    leftUpX = (sc_cols-rect_width)/2;
    leftUpY = 0;
    rightDownX = leftUpX + rect_width -1;
    rightDownY = rect_height -1;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = leftUpX;
    leftUpY = rightDownY + 1;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = leftUpY + c_rows -1;
    ImageSetRegion(imgPixel,1,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + (rect_width-c_cols*2) -1;
    rightDownY = rightDownY;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = rightDownY;
    ImageSetRegionMirrorY(imgPixel,1,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    imgname = path + "/imgPixelwithTopHole_g"+ fileversion+".bmp";
    imwrite(imgname, imgPixel);

    //B
    InitImage(imgPixel,0,0,255);
    if(fillet_flag==1)
        ImageFillet(imgPixel,2,pixelB,pixelG,pixelR);

    leftUpX = (sc_cols-rect_width)/2;
    leftUpY = 0;
    rightDownX = leftUpX + rect_width -1;
    rightDownY = rect_height -1;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = leftUpX;
    leftUpY = rightDownY + 1;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = leftUpY + c_rows -1;
    ImageSetRegion(imgPixel,2,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + (rect_width-c_cols*2) -1;
    rightDownY = rightDownY;
    ImageSetBackground(imgPixel,leftUpX,leftUpY,rightDownX,rightDownY,0,0,0);

    leftUpX = rightDownX + 1;
    leftUpY = leftUpY;
    rightDownX = leftUpX + c_cols -1;
    rightDownY = rightDownY;
    ImageSetRegionMirrorY(imgPixel,2,leftUpX,leftUpY,rightDownX,rightDownY,topholeB,topholeG,topholeR);

    imgname = path + "/imgPixelwithTopHole_b"+ fileversion+".bmp";
    imwrite(imgname, imgPixel);

    }

/////////////////////////////////////////////////////////////////////


	//namedWindow("imgPixel",WINDOW_NORMAL);
	//imshow("imgPixel",imgPixel);


	//cout << p_rows << p_cols << sc_rows << sc_cols << endl;
	//system("pause");

    if(delayFlag==1)
        cout << "Image generate successful!\n@fundou"<<endl;
        Delay(1000);

	//waitKey(0);
	return 0;
}


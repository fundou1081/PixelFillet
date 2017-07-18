#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <direct.h>
#include <ctime>
#include <vector>
#include <opencv2/opencv.hpp>



int p_rows = 56;
int p_cols = 56;
int sc_rows = 1920;
int sc_cols = 1080;
char namev[100];
int delayFlag=1;


using namespace cv;
using namespace std;

void ReadData(vector<vector<int> > &pixel, string filename)
{
	fstream file(filename);
	if (!file.is_open())
	{
		cout << "Error opening file." << endl; exit(1);
	}

	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
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

	file >> p_rows;
	file >> p_cols;
	file >> sc_rows;
	file >> sc_cols;
	file >> namev;
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

	string filename, fileversion;
	filename = path + "/config.txt";
	ReadConfig(filename);
	fileversion = namev;

	Mat imgPixel(sc_rows, sc_cols, CV_8UC3);
	vector<vector<int> > pixelB(p_rows, vector<int>(p_cols));
	vector<vector<int> > pixelG(p_rows, vector<int>(p_cols));
	vector<vector<int> > pixelR(p_rows, vector<int>(p_cols));


	filename = path + "/pixel_blue.txt";
	ReadData(pixelB, filename);

	filename = path + "/pixel_red.txt";
	ReadData(pixelR, filename);

	filename = path + "/pixel_green.txt";
	ReadData(pixelG, filename);

	//init imgPixel
	for (int j = 0; j<imgPixel.rows; j++)
	{
		uchar *data = imgPixel.ptr<uchar>(j);
		for (int i = 0; i<imgPixel.cols * 3; i += 3)
		{
			//初始化图片
			*data++ = 255;//B
			*data++ = 255;//G
			*data++ = 255;//R
		}
	}
	// W
	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
		{
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
		}
	}
	string imgname;
	imgname = path + "/imgPixel_w"+ fileversion+".bmp";

	imwrite(imgname, imgPixel);
	// R
	for (int j = 0; j<imgPixel.rows; j++)
	{
		uchar *data = imgPixel.ptr<uchar>(j);
		for (int i = 0; i<imgPixel.cols * 3; i += 3)
		{
			//初始化图片
			*data++ = 0;//B
			*data++ = 0;//G
			*data++ = 255;//R
		}
	}

	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
		{
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
		}
	}

	imgname = path + "/imgPixel_r" + fileversion + ".bmp";

	imwrite(imgname, imgPixel);

	// G
	for (int j = 0; j<imgPixel.rows; j++)
	{
		uchar *data = imgPixel.ptr<uchar>(j);
		for (int i = 0; i<imgPixel.cols * 3; i += 3)
		{
			//初始化图片
			*data++ = 0;//B
			*data++ = 255;//G
			*data++ = 0;//R
		}
	}

	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
		{
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
		}
	}

	imgname = path + "/imgPixel_g" + fileversion + ".bmp";

	imwrite(imgname, imgPixel);

	//B
	for (int j = 0; j<imgPixel.rows; j++)
	{
		uchar *data = imgPixel.ptr<uchar>(j);
		for (int i = 0; i<imgPixel.cols * 3; i += 3)
		{
			//初始化图片
			*data++ = 255;//B
			*data++ = 0;//G
			*data++ = 0;//R
		}
	}

	for (int j = 0; j<p_rows; j++)
	{
		for (int i = 0; i<p_cols; i++)
		{
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
		}
	}

	imgname = path + "/imgPixel_b" + fileversion + ".bmp";

	imwrite(imgname, imgPixel);
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


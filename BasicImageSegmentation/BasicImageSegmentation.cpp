// BasicImageSegmentation.cpp : �������̨Ӧ�ó������ڵ㡣
//
// Author: hujiagao@gmail.com
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

#include "Timer.h"
#include "ConfigReader.h"

#include "segmentor.h"
#include "SLICSegmentor.h"
#include "MeanShiftSegmentor.h"
#include "SEEDSSegmentor.h";
#include "GraphBasedSegmentor.h"
#include "GrabCutSegmentor.h"
#include "OneCutSegmentor.h"

IMPLEMENT_DYNCRT_BASE(Segmentor);
IMPLEMENT_DYNCRT_CLASS(SLICSegmentor);
IMPLEMENT_DYNCRT_CLASS(MeanShiftSegmentor);
IMPLEMENT_DYNCRT_CLASS(SEEDSSegmentor);
IMPLEMENT_DYNCRT_CLASS(GraphBasedSegmentor);
IMPLEMENT_DYNCRT_CLASS(GrabCutSegmentor);
IMPLEMENT_DYNCRT_CLASS(OneCutSegmentor);


int main(int argc, char* argv[])
{
	Mat inImage;
	string imgName;

	/*�жϵ����������Ƿ�����ڲ�����*/
	if (argc > 1)
	{
		imgName = string(argv[1]);
	} else {
		cout<<"Please input the image name:";
		cin>>imgName;
		cout<<endl;
	}

	inImage = imread(imgName);

	//�������ñ���,vector<x> y ��ʾ����һ��x���y���飬ֻ�Ǹ�����Ĵ�Сδ֪
	vector<SegReq> segList;   //SegReq ��ʾ��pair<string, vector<float>>
	//�������ú�����
	ConfigReader re;
	re.GetSegRequire(segList);

	for (int i = 0; i < segList.size(); i++)
	{
		SegReq seg = segList[i];
		cout << seg.first << endl;
		string segName = seg.first;
		vector<float> segArgs = seg.second;
		Timer t(segName);
		t.Start();
		Segmentor* s = Segmentor::Create(segName+string("Segmentor"));
		if (s == NULL)
		{
			cout<<"--Error: Cannot create segmentor: "<<segName<<endl;
			continue;
		}
		s->SetImage(inImage);
		s->SetArgs(segArgs);
		s->Run();
		s->ShowResult();
		s->SaveResult();
		t.Stop();	
		waitKey(1);
	}

	waitKey(0);
	return 0;
}


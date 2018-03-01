//
// Author: hujiagao@gmail.com
//

#pragma once

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

// �����������ж�̬�������ܵĻ���
// �ο� http://blog.csdn.net/freefalcon/article/details/109275
#define DECLARE_DYNCRT_BASE(base) \
public: \
    typedef base* (*ClassGen)(); \
	static void Register(string class_name, ClassGen class_gen) \
    { \
        class_set.insert(map<string, ClassGen>::value_type(class_name, class_gen)); \
    } \
public: \
    static base* Create(string class_name) \
    { \
        map<string, ClassGen>::iterator iter; \
        if((iter = class_set.find(class_name)) != class_set.end()) \
        { \
            return ((*iter).second)(); \
        } \
        return NULL; \
    } \
protected: \
    static map<string, ClassGen> class_set; 

// ����ʵ�ֻ��� 
#define IMPLEMENT_DYNCRT_BASE(base) \
map<string, base::ClassGen> base::class_set;

// ��������һ���ܹ�����̬�������� 
#define DECLARE_DYNCRT_CLASS(derived, base) \
public: \
    struct derived##Register \
    { \
        derived##Register() \
        { \
            static bool bRegistered = false; \
            if(!bRegistered) \
            { \
                base::Register(#derived, Create); \
                bRegistered = true; \
            } \
        } \
    }; \
    static base* Create() \
    { \
        return new derived; \
    }

// ����ʵ��һ���ܹ�����̬��������  
#define IMPLEMENT_DYNCRT_CLASS(derived) \
static derived::derived##Register derived##_for_registering;

class Segmentor
{
	DECLARE_DYNCRT_BASE(Segmentor);

public:
	Segmentor();
	~Segmentor(void);

	virtual void Run() = 0;
	virtual void SetArgs(const vector<float> args) = 0;

	//static void onMouse(int event, int x, int y, int flags, void* param);
	virtual void SetImage(const Mat& _img);
	void ShowResult(const Vec3b& _color = Vec3b(0,0,255));
	void SaveResult();
	
	void fixResult();

protected:
	Mat m_Img;		// Input Image
	string m_Name;
	string m_ResultName;
	int m_argNum;

public:
	Mat m_Result;	// Result Mask
};

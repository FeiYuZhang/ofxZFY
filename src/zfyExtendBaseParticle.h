#pragma once
/*
	����������չ������,���zfyBaseParticle��ʹ��
*/

#include "zfyBaseParticle.h"

//=============����С����=================
/*
	����������λ�ñ��ݣ���������
*/
class MyShakeBubble : public MyBaseBubble
{
public:
	MyShakeBubble(void){
		img = NULL;
		cout << "�������� MyShakeBubble imgΪ NULL" << endl;
	};
	virtual ~MyShakeBubble(void){
		img = NULL;
		cout << "�������� MyShakeBubble imgΪ NULL" << endl;
	};

	virtual void setup(ofImage& _img, ofPoint& _position, float _fShakeRegion);
	virtual void init();
	virtual void update();
	virtual void draw();

	virtual bool isTouched(int x, int y);
	virtual bool doubleTouched(int x, int y);
	virtual void setEnableUse(){bIsTouchDown = false;};
	virtual bool getUseState(){return bIsTouchDown;};

	virtual ofPoint& getPosition(){return position;}

//protected:
	ofImage*	img;
	ofPoint		positionTemp;
	float		fShakeRegion;
	bool		bIsTouchDown;
	int			iImgAlpha;
};

//=============����С����=================
class MyUpBubble : public MyBaseBubble
{
public:
	MyUpBubble()
	{
		img = NULL;
	};
	virtual ~MyUpBubble(){
		img = NULL;
	};

	void setup(ofImage* _img,ofPoint& _pos,ofPoint& _edPos);
	void init();
	void update();
	void draw();

	bool getIsAlive(){return bIsAlive;}

protected:
	ofImage*	img;			//���������ز�
	ofPoint		startPosition;	//��ʼλ��
	ofPoint		endPosition;	//ĩ��λ��

	float		size;			//���ݴ�С
	float		sizeTemp;		//���ݴ�С����
	float		sizeAdd;		//���ݴ�С����
	float		fUpArg;			//������������
	float		fMoveDistanceY;	//�����ƶ�����-->update��
	float		fMoveDistanceX;	//�����ƶ�����-->update��

	ofPoint		velocity;		//�˶��ٶ�
	ofPoint		acceleration;	//�˶����ٶ�
	bool		bIsAlive;		//����״̬
};
class MyUpWaterBubble
{
public:
	MyUpWaterBubble()
	{pList.clear();};
	virtual ~MyUpWaterBubble(){};

	void setup(ofImage* _img,ofPoint& _pos,ofPoint& _edPos,int iBubbleNum=1);
	void init();
	void update();
	void draw();

protected:
	vector<MyUpBubble>	pList;
};

//=============��������===================
class MyStarParticle : public MyBaseParticle
{
public:
	MyStarParticle(void)
	{
		//color = ofColor(ofRandom(0,100),ofRandom(0,100),ofRandom(200,255));
		color = ofColor(255,255,255);
	};
	virtual ~MyStarParticle(void){};

	//virtual void setup();
	virtual void setup(ofImage* _img,ofPoint& _pos,ofPoint& _v);
	virtual void update();
	virtual	void draw();
	/*virtual void mousePressed(int x, int y);
	virtual void mouseDrag(int x,int y);*/

	bool	getState(){return existState;}//��ȡ����״̬

protected:
};
class MyStar
{
public:
	MyStar(void){
		pList.clear();
	};
	virtual ~MyStar(void){};

	void setup();
	void update();
	virtual void draw();

	void addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v);

	vector<MyStarParticle>		pList;
};

//============Ʈ������======================
class MyFallStarParticle : public MyStarParticle
{
public:
	MyFallStarParticle(void)
	{
		color = ofColor(255,255,255);
	};
	virtual ~MyFallStarParticle(void){};
	void update();

protected:
};
class MyFallStar
{
public:
	MyFallStar(void){
		pList.clear();
	};
	virtual ~MyFallStar(void){};

	void setup();
	void update();
	virtual void draw();

	void addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v);

	vector<MyFallStarParticle>		pList;
};

//============��ת��Ƭ======================
class MyPicStarParticle : public MyStarParticle
{
public:
	MyPicStarParticle(void)
	{
		size = ofRandom(.3,.7);
		//windowsRect = ofRectangle(-img->width*size/2,-img->height*size/2, ofGetWidth()+img->width*size,ofGetHeight()+img->height*size);
	};
	virtual ~MyPicStarParticle(void){};

	void setup(ofImage* _img,ofPoint& _pos,ofPoint& _v);
	void update();
	void draw();

protected:
	ofRectangle		windowsRect;
};
class MyPicStar : MyPicStarParticle
{
public:
	MyPicStar(void){
		pList.clear();
	};
	virtual ~MyPicStar(void){};

	void setup();
	void update();
	virtual void draw();

	void addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v);

	vector<MyPicStarParticle>		pList;
};

//=============�ƹ�����===================
/*
	����������ͼƬ�߶ȱ���
*/
class MyLightParticle : public MyBaseParticle
{
public:
	MyLightParticle(void){};
	virtual ~MyLightParticle(){};

	virtual void setup(ofImage* _img,ofPoint& _pos,float _rotation);
	virtual void update();
	virtual	void draw();

protected:
	float		fHeight;
	float		fArg;
};
class MyLight
{
public:
	MyLight(){
		pList.clear();
	};
	virtual ~MyLight(){};

	void setup();
	void update();
	void draw();

	void addLightParticle(ofImage* _img,ofPoint& _pos,float _rotation);

	vector<MyLightParticle>		pList;
};
#pragma once
/*
	本类用于扩展粒子类,配合zfyBaseParticle类使用
*/

#include "zfyBaseParticle.h"

//=============抖动小泡泡=================
/*
	包含变量：位置备份，抖动区域
*/
class MyShakeBubble : public MyBaseBubble
{
public:
	MyShakeBubble(void){
		img = NULL;
		cout << "构造设置 MyShakeBubble img为 NULL" << endl;
	};
	virtual ~MyShakeBubble(void){
		img = NULL;
		cout << "析构设置 MyShakeBubble img为 NULL" << endl;
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

//=============上升小泡泡=================
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
	ofImage*	img;			//上升泡泡素材
	ofPoint		startPosition;	//起始位置
	ofPoint		endPosition;	//末了位置

	float		size;			//泡泡大小
	float		sizeTemp;		//泡泡大小缓存
	float		sizeAdd;		//泡泡大小增量
	float		fUpArg;			//泡泡上升参数
	float		fMoveDistanceY;	//泡泡移动距离-->update中
	float		fMoveDistanceX;	//泡泡移动距离-->update中

	ofPoint		velocity;		//运动速度
	ofPoint		acceleration;	//运动加速度
	bool		bIsAlive;		//生存状态
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

//=============星星粒子===================
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

	bool	getState(){return existState;}//获取生存状态

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

//============飘落粒子======================
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

//============旋转照片======================
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

//=============灯光粒子===================
/*
	包含变量：图片高度比例
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
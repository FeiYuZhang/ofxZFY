#pragma once
/*
	本类中存放自己用到的基本的粒子类型
*/
#include "ofMain.h"

//=============抖动小泡泡=================
/*
	包含属性：位置
*/
class MyBaseBubble
{
public:
	MyBaseBubble(void){
		position	= ofPoint(-1,-1);
	};
	virtual ~MyBaseBubble(void){};

protected:
	ofPoint		position;
};

//==============粒子======================
/*
	包含属性：粒子素材，位置，速度，加速度，质量，大小，透明度，旋转角度，旋转变量，生存状态，颜色
*/
class MyBaseParticle
{
public:
	MyBaseParticle(void){
		img				= NULL;
		position		= ofPoint(-1,-1)  ;		//位置
		velocity		= ofPoint(0,0);         //速度 
		acceleration	= ofPoint(0);           //加速度
		mass			= 0;                    //质量
		size			= 1;
		alpha			= 255;                  //透明度
		rotation		= ofRandom(0,360);            //旋转角度
		rotationChange	= sin(PI/ofRandom(-6,6));
		existState		= true;                       //生存状态，为true时存在，为false时消失
	};
	virtual ~MyBaseParticle(void){
		img		= NULL;
	};

protected:
	ofImage*	img;             //粒子素材
	ofPoint		position;        //位置
	ofPoint		velocity;        //速度 
	ofPoint		acceleration;    //加速度
	float		mass;            //质量
	float		size;            //大小
	float		alpha;           //透明度
	float		rotation;        //旋转角度
	float		rotationChange;
	bool		existState;      //生存状态，为true时存在，为false时消失
	ofColor		color;
};
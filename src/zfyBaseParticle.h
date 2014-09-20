#pragma once
/*
	�����д���Լ��õ��Ļ�������������
*/
#include "ofMain.h"

//=============����С����=================
/*
	�������ԣ�λ��
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

//==============����======================
/*
	�������ԣ������زģ�λ�ã��ٶȣ����ٶȣ���������С��͸���ȣ���ת�Ƕȣ���ת����������״̬����ɫ
*/
class MyBaseParticle
{
public:
	MyBaseParticle(void){
		img				= NULL;
		position		= ofPoint(-1,-1)  ;		//λ��
		velocity		= ofPoint(0,0);         //�ٶ� 
		acceleration	= ofPoint(0);           //���ٶ�
		mass			= 0;                    //����
		size			= 1;
		alpha			= 255;                  //͸����
		rotation		= ofRandom(0,360);            //��ת�Ƕ�
		rotationChange	= sin(PI/ofRandom(-6,6));
		existState		= true;                       //����״̬��Ϊtrueʱ���ڣ�Ϊfalseʱ��ʧ
	};
	virtual ~MyBaseParticle(void){
		img		= NULL;
	};

protected:
	ofImage*	img;             //�����ز�
	ofPoint		position;        //λ��
	ofPoint		velocity;        //�ٶ� 
	ofPoint		acceleration;    //���ٶ�
	float		mass;            //����
	float		size;            //��С
	float		alpha;           //͸����
	float		rotation;        //��ת�Ƕ�
	float		rotationChange;
	bool		existState;      //����״̬��Ϊtrueʱ���ڣ�Ϊfalseʱ��ʧ
	ofColor		color;
};
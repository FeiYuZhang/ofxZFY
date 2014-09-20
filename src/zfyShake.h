#pragma once

//                                         fXSpace
//   O: Num Bone   +: draw points          |-----|
//     +-----+-----+-----+-----+-----+-----+-----+ -
//     |     |     |     |     |     |     |     | |
// head|     |neck |     |     |     |     |     | |
//     O-----O-----O-----O-----O-----O-----O-----O |fYSpace
//     |     |     |     |     |     |     |     | |
//     |     |     |     |     |     |     |     | |
//     +-----+-----+-----+-----+-----+-----+-----+ -

#include "ofMain.h"

#define ROTATE_RANGETwo 6
#define BONE_POINT_NUMTwo 2

// �����ṹ
struct BoneTwo
{
	float x, y;
	int contourIndexUp, contourIndexDown;		// һ������������
};

// ������ṹ
struct ContourPointTwo
{
	float vertex[3];
	float texCoord[3];
};

class zfyShake
{
public:
	zfyShake(void);
	~zfyShake(void);

	// -- Attribute --

	// ��̬����
	ofPoint position;		

	// ��̬����
	float fzfyShakeWidth, fzfyShakeHeight;		// ����

	int   iNumBones;					// ��������
	float fXSpace, fYSpace;				// ���� x,y ���       
	float fAngleDeg;					// ��ת��, ����, �Ƕ�

	float fRotateRangeDeg;				// ��ת����  
	float fRotateFreqRad;				// ��תƵ��
	float fCurRotateRad;				// ��ǰ��ת����

	BoneTwo* bones;						// �����ڵ�
	ContourPointTwo* ctPoint;				// �����ڵ�
	unsigned short *ctIndex;			// �����ڵ��������

	GLuint skinID;						// ����ID
	ofTexture*	skinImg;

	// -- Operation --

	//************************************
	// Method:    setup
	// Access:    public 
	// Returns:   void
	// Qualifier: ���ýṹ
	// Parameter: ofPoint _pos  : λ��
	// Parameter: int _numBones  : ��������
	// Parameter: int _xspace	 : �������
	// Parameter: int _yspace	 : �����߶�
	// Parameter: GLuint _texID	 : ��������ID
	//************************************
	void setup(ofPoint _pos,int _numBones, int _xspace, int _yspace, ofTexture* _skinImg);

	void wriggling();					// Ť��
	void updateSatic();					// ��̬����	
	void draw();
};

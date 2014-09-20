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

// 骨骼结构
struct BoneTwo
{
	float x, y;
	int contourIndexUp, contourIndexDown;		// 一个骨骼两个点
};

// 轮廓点结构
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

	// 动态变量
	ofPoint position;		

	// 静态变量
	float fzfyShakeWidth, fzfyShakeHeight;		// 长宽

	int   iNumBones;					// 骨骼数量
	float fXSpace, fYSpace;				// 骨骼 x,y 间距       
	float fAngleDeg;					// 旋转角, 整体, 角度

	float fRotateRangeDeg;				// 旋转幅度  
	float fRotateFreqRad;				// 旋转频率
	float fCurRotateRad;				// 当前旋转幅度

	BoneTwo* bones;						// 骨骼节点
	ContourPointTwo* ctPoint;				// 轮廓节点
	unsigned short *ctIndex;			// 轮廓节点绘制索引

	GLuint skinID;						// 纹理ID
	ofTexture*	skinImg;

	// -- Operation --

	//************************************
	// Method:    setup
	// Access:    public 
	// Returns:   void
	// Qualifier: 设置结构
	// Parameter: ofPoint _pos  : 位置
	// Parameter: int _numBones  : 骨骼数量
	// Parameter: int _xspace	 : 骨骼宽度
	// Parameter: int _yspace	 : 骨骼高度
	// Parameter: GLuint _texID	 : 骨骼纹理ID
	//************************************
	void setup(ofPoint _pos,int _numBones, int _xspace, int _yspace, ofTexture* _skinImg);

	void wriggling();					// 扭动
	void updateSatic();					// 静态更新	
	void draw();
};

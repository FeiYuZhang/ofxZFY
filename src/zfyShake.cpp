#include "zfyShake.h"

zfyShake::zfyShake(void)
{
	skinImg = NULL;
}

zfyShake::~zfyShake(void)
{
	skinImg = NULL;
}

void zfyShake::setup(ofPoint _pos,int _numBones, int _xspace, int _yspace, ofTexture* _skinImg)
{
	// 动态变量
	position	 = _pos;

	// 静态变量
	iNumBones = _numBones;

	fXSpace = _xspace;
	fYSpace = _yspace;

	fAngleDeg = 180;

	fRotateRangeDeg = ROTATE_RANGETwo+int(ofRandomuf()*.2);
	fRotateFreqRad  = ofRandomuf()*0.015 + 0.03;
	fCurRotateRad   = 0;

	//skinID = _texID;
	skinImg = _skinImg;

	// 初始化骨骼 及索引
	bones = new BoneTwo[iNumBones];
	for ( int i = 0; i < iNumBones; i++ )
	{
		bones[i].contourIndexUp		= i;
		bones[i].contourIndexDown	= i+iNumBones;
	}

	// 初始化轮廓点
	ctPoint = new ContourPointTwo[iNumBones*BONE_POINT_NUMTwo];
	fzfyShakeWidth  = fXSpace*(iNumBones-1);
	fzfyShakeHeight = fYSpace; 
	for ( int i = 0; i < BONE_POINT_NUMTwo; i++ )
	{
		float yPos = i*fYSpace;

		for ( int j = 0; j < iNumBones; j++ )
		{
			int index = i*iNumBones + j;

			ctPoint[index].vertex[0] = j*fXSpace;
			ctPoint[index].vertex[1] = yPos;
			ctPoint[index].vertex[2] = 0;

			ctPoint[index].texCoord[0] = ctPoint[index].vertex[0]/fzfyShakeWidth;
			ctPoint[index].texCoord[1] = ctPoint[index].vertex[1]/fzfyShakeHeight;
			ctPoint[index].texCoord[2] = 0;
		}
	}

	// 初始化轮廓绘制索引
	// 0 2 4 6 8 
	// 1 3 5 7 9
	ctIndex = new unsigned short[iNumBones*BONE_POINT_NUMTwo];
	int index = 0;
	for ( int i = 0; i < iNumBones; i++ )
	{
		ctIndex[index++] = i;
		ctIndex[index++] = i + iNumBones;
	}

}

void zfyShake::updateSatic()
{
	wriggling();

	float dx, dy, angle;
	float xup, yup,xdown, ydown;
	float tpSpace = fYSpace/2;
	for ( int i = 0; i < iNumBones; i++ )
	{
		if ( i == 0 )
		{
			dx = bones[1].x - bones[0].x;
			dy = bones[1].y - bones[0].y;
		}
		else
		{
			dx = bones[i].x - bones[i-1].x;
			dy = bones[i].y - bones[i-1].y;
		}
		angle = -atan2(dy, dx);
		xup   = bones[i].x - tpSpace * sin(angle);
		yup   = bones[i].y - tpSpace * cos(angle);
		xdown = bones[i].x + tpSpace * sin(angle);
		ydown = bones[i].y + tpSpace * cos(angle);

		ctPoint[bones[i].contourIndexUp].vertex[0]   = xup;
		ctPoint[bones[i].contourIndexUp].vertex[1]   = yup;
		ctPoint[bones[i].contourIndexDown].vertex[0] = xdown;
		ctPoint[bones[i].contourIndexDown].vertex[1] = ydown;
	}
}


void zfyShake::draw()
{
	ofDisableArbTex();
	float theta =  0;
	ofPushMatrix();
		ofTranslate(position.x, position.y);
		//ofRotate(90);

		glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

		//ofEnableAlphaBlending();
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, skinID);
		skinImg->bind();

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(ContourPointTwo), ctPoint);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT, sizeof(ContourPointTwo), &(ctPoint[0].texCoord[0]));

		glDrawElements(GL_QUAD_STRIP, iNumBones*BONE_POINT_NUMTwo, GL_UNSIGNED_SHORT, ctIndex);

		skinImg->unbind();
		//glDisable(GL_TEXTURE_2D);
		//ofDisableAlphaBlending();

		glPopClientAttrib();
	ofPopMatrix();

	fAngleDeg = ofRadToDeg(theta);
	ofEnableArbTex();
}

void zfyShake::wriggling()
{
	// 头
	bones[0].x = cos(ofDegToRad(fAngleDeg));
	bones[0].y = sin(ofDegToRad(fAngleDeg));

	// 扭动脖子
	fCurRotateRad += fRotateFreqRad;
	ofNormalize(fCurRotateRad, 0, PI);
	float fAngleWriggleDeg = fRotateRangeDeg * sin(fCurRotateRad);
	bones[1].x = -fXSpace * cos(ofDegToRad(fAngleDeg+fAngleWriggleDeg)) + bones[0].x;
	bones[1].y = -fXSpace * sin(ofDegToRad(fAngleDeg+fAngleWriggleDeg)) + bones[0].y;

	// 扭动脊椎
	float dx, dy, dist;
	for ( int i = 2; i < iNumBones; i++)
	{
		dx = bones[i].x - bones[i-2].x;
		dy = bones[i].y - bones[i-2].y;
		dist = sqrt(dx*dx+dy*dy);

		bones[i].x = bones[i-1].x + (dx * fXSpace)/dist;
		bones[i].y = bones[i-1].y + (dy * fXSpace)/dist;

	}
}



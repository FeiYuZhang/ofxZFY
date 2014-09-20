#include "zfyExtendBaseParticle.h"

////////////抖动小泡泡////////////////
void MyShakeBubble::setup(ofImage& _img, ofPoint& _position, float _fShakeRegion)
{
	img = &_img;
	position	= _position;
	positionTemp = position;
	fShakeRegion = _fShakeRegion;

	init();
}

void MyShakeBubble::init()
{
	//后续加的属性
	bIsTouchDown = false;
	iImgAlpha = 255;
}

void MyShakeBubble::update()
{
	//位置更新  
	position = ofPoint(positionTemp.x, positionTemp.y + fShakeRegion*sin(ofGetElapsedTimef()*2));
	//有触摸,执行触摸事件
	iImgAlpha += 15;
	if (iImgAlpha>=255)
	{
		iImgAlpha = 255;
	}
	if (bIsTouchDown)
	{
		
	}
}

void MyShakeBubble::draw()
{
	ofPushStyle();
	ofSetColor(255,255,255, iImgAlpha);
	img->draw(position);
	ofPopStyle();
	//ofDrawBitmapString(ofToString(iImgAlpha),position);
}

bool MyShakeBubble::isTouched(int x, int y)
{
	if ( !bIsTouchDown && (x>position.x && x<position.x+img->width) && (y>position.y && y<position.y+img->height) )
	{
		bIsTouchDown = true;
		iImgAlpha = 100;
		return true;
	}
	return false;
}

bool MyShakeBubble::doubleTouched(int x, int y)
{
	if ( bIsTouchDown && (x>position.x && x<position.x+img->width) && (y>position.y && y<position.y+img->height) )
	{
		//bIsTouchDown = false;
		iImgAlpha = 100;
		return true;
	}
	return false;
}

////////////上升小泡泡////////////////
void MyUpBubble::setup(ofImage* _img,ofPoint& _pos,ofPoint& _edPos)
{
	img			= _img;
	position	= _pos;
	startPosition	= position + ofPoint(ofRandom(0,130), 0);
	endPosition		= _edPos;

	size			= ofRandom(.1,.3);
	sizeTemp		= size;
	sizeAdd			= ofRandom(0.01,0.1);
	fMoveDistanceX	= ofRandom(5,10);
	fUpArg			= ofRandom(-PI/300,PI/2);
	velocity		= ofPoint(ofRandom(0,10), size*0.1);
	acceleration	= ofPoint(0.01, 0.02);
	bIsAlive		= true;
}

void MyUpBubble::init()
{
	
}

void MyUpBubble::update()
{
	if (bIsAlive)
	{
		//位置更新
		//Y
		fUpArg += PI/ofRandom(300,320);
		if (fUpArg>=PI/2)
		{
			fUpArg = PI/2;
		}
		fMoveDistanceY = ofDist(startPosition.x,startPosition.y, endPosition.x,endPosition.y);
		position.y = startPosition.y - fMoveDistanceY*sin(fUpArg);
		//X
		position.x = startPosition.x + fMoveDistanceX*sin(fUpArg*12);
		//size
		size = sizeTemp + sizeAdd*sin(fUpArg);

		//位置判断
		if (position.y-15<=endPosition.y)
		{
			bIsAlive = false;
		}
	}
}

void MyUpBubble::draw()
{
	if (bIsAlive)
	{
		img->draw(position, img->width*size,img->height*size);
	}
}
//=====实现上升水泡泡=====
void MyUpWaterBubble::setup(ofImage* _img,ofPoint& _pos,ofPoint& _edPos,int iBubbleNum)
{
	for (int i = 0; i < iBubbleNum; i++)
	{
		MyUpBubble	myupbubble;
		myupbubble.setup(_img,_pos/*+ofPoint(ofMap(i, 0,iBubbleNum, _pos.x-15,_pos.x+15,true),0)*/,_edPos);
		pList.push_back(myupbubble);
	}
}

void MyUpWaterBubble::init()
{

}

void MyUpWaterBubble::update()
{
	for (int i = 0; i < pList.size(); i++)
	{
		if (!pList[i].getIsAlive())               //删除已经死亡的泡泡
		{
			pList.erase(pList.begin()+i);
			i--;
			continue;
		}
		pList[i].update();
	}
}

void MyUpWaterBubble::draw()
{
	for (int i = 0; i < pList.size(); i++)
	{
		pList[i].draw();
	}
}

////////////星光粒子///////////////////
void MyStarParticle::setup(ofImage* _img,ofPoint& _pos,ofPoint& _v)
{
	img			= _img;
	position	= _pos;
	velocity	= _v;
}

void MyStarParticle::update()
{
	//位置更新
	velocity+=acceleration;
	position+=velocity;

	//透明度变化
	alpha-=1.5;
	if (alpha<=0)
	{
		existState = false;
	}
	//大小变化
	size = alpha/255.0 ;

	rotation -= rotationChange;
}

void MyStarParticle::draw()
{
	ofPushMatrix();
	ofTranslate(position.x,position.y);
	//ofPushStyle();     注意：这里不保存绘制环境，是为了在后面绘制的时候进行blend混合操作，否则就看不到效果了！！
	ofSetColor(color.r,color.g,color.b,alpha);
	ofRotate(rotation);
	img->setAnchorPercent(0.5,0.5);
	img->draw(0,0,img->width*size,img->height*size);
	ofPopMatrix();
}

void MyFallStarParticle::update()
{
	//位置更新
	velocity+=acceleration;
	position+=velocity;

	//透明度变化
	alpha-=1.0;
	if (alpha<=0)
	{
		existState = false;
	}
	//大小变化
	size = alpha/255.0 ;

	rotation -= rotationChange;
}

void MyPicStarParticle::setup(ofImage* _img,ofPoint& _pos,ofPoint& _v)
{
	img			= _img;
	position	= _pos;
	velocity	= _v;
	//rect
	windowsRect = windowsRect = ofRectangle(-img->width*size/2,-img->height*size/2, ofGetWidth()+img->width*size,ofGetHeight()+img->height*size);
}

void MyPicStarParticle::update()
{
	//位置更新
	velocity+=acceleration;
	position+=velocity;

	//透明度变化
	alpha-=0.5;
	if (alpha<=0 || !windowsRect.inside(position))
	{
		existState = false;
	}
	//大小变化
	//size = alpha/255.0 ;

	rotation -= rotationChange;
}

void MyPicStarParticle::draw()
{
	ofPushMatrix();
	ofTranslate(position.x,position.y);
	//ofPushStyle();     注意：这里不保存绘制环境，是为了在后面绘制的时候进行blend混合操作，否则就看不到效果了！！
	ofSetColor(color.r,color.g,color.b,alpha);
	ofRotate(rotation);
	img->setAnchorPercent(0.5,0.5);
	img->draw(0,0,img->width*size,img->height*size);
	ofPopMatrix();
}

//=====实现粒子类=====
void MyStar::setup()
{
	pList.clear();
}

void MyStar::update()
{
	for (int i=0;i<pList.size();i++)
	{
		if (!pList[i].getState())               //删除已经死亡的粒子
		{
			pList.erase(pList.begin()+i);
			i--;
			continue;
		}
		pList[i].update();                      //更新粒子属性
	}
}

void MyStar::draw()
{
	glPushAttrib(GL_CURRENT_BIT);
	ofPushStyle();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	for (int i=0;i<pList.size();i++)
	{
		pList[i].draw();
	}
	glDisable(GL_BLEND);
	ofPopStyle();
	glPopAttrib();
}

void MyStar::addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v)
{
	MyStarParticle StarParticle;
	StarParticle.setup(_img,_pos,_v);
	pList.push_back(StarParticle);
}

void MyFallStar::setup()
{
	pList.clear();
}

void MyFallStar::update()
{
	for (int i=0;i<pList.size();i++)
	{
		if (!pList[i].getState())               //删除已经死亡的粒子
		{
			pList.erase(pList.begin()+i);
			i--;
			continue;
		}
		pList[i].update();                      //更新粒子属性
	}
}

void MyFallStar::draw()
{
	glPushAttrib(GL_CURRENT_BIT);
	ofPushStyle();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	for (int i=0;i<pList.size();i++)
	{
		pList[i].draw();
	}
	glDisable(GL_BLEND);
	ofPopStyle();
	glPopAttrib();
}

void MyFallStar::addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v)
{
	MyFallStarParticle StarParticle;
	StarParticle.setup(_img,_pos,_v);
	pList.push_back(StarParticle);
}

void MyPicStar::setup()
{
	pList.clear();
}

void MyPicStar::update()
{
	for (int i=0;i<pList.size();i++)
	{
		if (!pList[i].getState())               //删除已经死亡的粒子
		{
			pList.erase(pList.begin()+i);
			i--;
			continue;
		}
		pList[i].update();                      //更新粒子属性
	}
}

void MyPicStar::draw()
{
	//glPushAttrib(GL_CURRENT_BIT);
	ofPushStyle();
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	for (int i=0;i<pList.size();i++)
	{
		pList[i].draw();
	}
	//glDisable(GL_BLEND);
	ofPopStyle();
	//glPopAttrib();
}

void MyPicStar::addStarParticle(ofImage* _img,ofPoint& _pos,ofPoint& _v)
{
	MyPicStarParticle StarParticle;
	StarParticle.setup(_img,_pos,_v);
	pList.push_back(StarParticle);
}


////////////灯光粒子///////////////////
void MyLightParticle::setup(ofImage* _img,ofPoint& _pos,float _rotation)
{
	img			= _img;
	position	= _pos;
	rotation	= _rotation;
	color		= ofColor(44, 114, 255);
	//alpha		= ofRandom(0,105);
	fArg		= ofRandom(0,PI);
	fHeight		= ofMap(fabs(rotation), 0,45, 1,0.6);
	//cout << rotation << "  "<< fHeight << endl;
}

void MyLightParticle::update()
{
	//位置不变
	//改变透明度
	fArg += PI/ofRandom(300,320);
	if (fArg>=PI)
	{
		fArg = 0;
	}
	alpha = 70*sin(fArg);
	/*if (alpha<=0)
	{
	alpha = 0;
	}
	else if (alpha>=105)
	{
	alpha=105;
	}*/
}

void MyLightParticle::draw()
{
	//alpha = ofRandom(0,200);
	//cout << alpha << endl;
	ofPushStyle();
	glPushAttrib(GL_CURRENT_BIT);
	ofSetColor(color,alpha);
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rotation, 0,0,1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	img->draw(0,0, img->width,img->height*fHeight);
	glDisable(GL_BLEND);
	ofPopMatrix();
	glPopAttrib();
	ofPopStyle();
}

//=====实现灯光类======
void MyLight::setup()
{
	pList.clear();
}

void MyLight::update()
{
	for (int i=0;i<pList.size();i++)
	{
		pList[i].update();
	}
}

void MyLight::draw()
{
	/*glPushAttrib(GL_CURRENT_BIT);
	ofPushStyle();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);*/
	for (int i=0;i<pList.size();i++)
	{
		pList[i].draw();
	}
	/*glDisable(GL_BLEND);
	ofPopStyle();
	glPopAttrib();*/
}

void MyLight::addLightParticle(ofImage* _img,ofPoint& _pos,float _rotation)
{
	MyLightParticle		lightParticle;
	lightParticle.setup(_img,_pos,_rotation);
	pList.push_back(lightParticle);
}

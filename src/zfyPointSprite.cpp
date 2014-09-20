#include "zfyPointSprite.h"


zfyPointSprite::zfyPointSprite(void)
{
}


zfyPointSprite::~zfyPointSprite(void)
{
}

void zfyPointSprite::setup(ofImage* _texture)
{
	// load the bilboard shader 
	// this is used to change the
	// size of the particle
	billboardShader.load("Billboard");

	//ofDisableArbTex();
	texture = _texture;
	//ofEnableArbTex();

	zoom = -700;
	zoomTarget = 500;

	billboards.getVertices().resize(NUM_BILLBOARDS);
	billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));

	// ------------------------- billboard particles
	for (int i=0; i<NUM_BILLBOARDS; i++) {

		billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
		billboards.getVertices()[i].set(ofRandom(-500, 500), 
			ofRandom(-500, 500), 
			ofRandom(-500, 500));

		billboardSizeTarget[i] = ofRandom(texture->getWidth()*.125, texture->getWidth()*.75);

	}

	billboards.setUsage( GL_DYNAMIC_DRAW );
	billboards.setMode(OF_PRIMITIVE_POINTS);

}

void zfyPointSprite::update()
{
	float t = (ofGetElapsedTimef()) * 0.9f;
	float div = 250.0;

	for (int i=0; i<NUM_BILLBOARDS; i++) {

		// noise 
		ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
			ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
			ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));

		vec *= 1 * ofGetLastFrameTime();
		billboardVels[i] += vec;
		billboards.getVertices()[i] += billboardVels[i]; 
		billboardVels[i] *= 0.94f; 
		billboards.setNormal(i,ofVec3f(billboardSizeTarget[i] /*+ billboardSizeTarget[i] * ofNoise(t+i)*/,0,0));
	}

	// move the camera around
	zoom += (zoomTarget - zoom) * 0.03;
}

void zfyPointSprite::begin()
{
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
	// bind the shader so that wee can change the
	// size of the points via the vert shader
	billboardShader.begin();

	ofDisableArbTex();
	ofEnablePointSprites();
}

void zfyPointSprite::end()
{
	ofDisablePointSprites();
	ofEnableArbTex();

	billboardShader.end();
	ofPopMatrix();
}

void zfyPointSprite::draw()
{	
	texture->getTextureReference().bind();
	billboards.draw();
	texture->getTextureReference().unbind();	
}

void zfyPointSprite::keyPressed(int key)
{
	if(key == OF_KEY_UP) zoomTarget +=10;
	if(key == OF_KEY_DOWN) zoomTarget -=10;
}

void zfyPointSprite::mousePressed(int x, int y)
{

}

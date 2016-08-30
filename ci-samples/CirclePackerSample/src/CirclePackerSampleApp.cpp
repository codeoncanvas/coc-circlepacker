#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "ciCirclePacker.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CirclePackerSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
    
    coc::ciCirclePackerRef circlePacker;
};

void CirclePackerSampleApp::setup() {
    
    circlePacker = coc::ciCirclePacker::create();
}

void CirclePackerSampleApp::update() {

    int circleAddPerFrame = 10;
    for(int i=0; i<circleAddPerFrame; i++) {

        float x = coc::rand(getWindowWidth());
        float y = coc::rand(getWindowHeight());
        float radiusMin = 2.0;
        float radiusMax = 200.0;
        float radiusGrowth = (radiusMax - radiusMin) / 100.0;
        float gap = 1.0;
        
        const coc::CirclePacker::CircleRef & circleRef = circlePacker->addCircle(x, y, radiusMin, radiusMax, radiusGrowth, gap);
        coc::ciCirclePacker::ciCircle * circle = (coc::ciCirclePacker::ciCircle *)circleRef.get();
        circle->colorFill = ci::ColorA(0.9, 0.9, 0.9, 1.0);
        circle->colorStroke = ci::ColorA(0.0, 0.0, 0.0, 1.0);
    }
    
    circlePacker->update();
}

void CirclePackerSampleApp::draw() {
	
    gl::clear(Color(1.0, 1.0, 1.0));
    
    circlePacker->draw();
}

void CirclePackerSampleApp::mouseMove( MouseEvent event ) {
    //
}

void CirclePackerSampleApp::mouseDown( MouseEvent event ) {
    //
}

void CirclePackerSampleApp::mouseDrag( MouseEvent event ) {
    //
}

void CirclePackerSampleApp::mouseUp( MouseEvent event ) {
    //
}

void CirclePackerSampleApp::keyDown( KeyEvent event ) {
    if(event.getChar() == 'r' || event.getChar() == 'R') {
        circlePacker->reset();
    }
}

CINDER_APP( CirclePackerSampleApp, RendererGl )

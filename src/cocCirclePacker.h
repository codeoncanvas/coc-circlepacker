/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#pragma once

#include "cocCore.h"

namespace coc {

//--------------------------------------------------------------
class CirclePacker;
typedef std::shared_ptr<CirclePacker> CirclePackerRef;

class CirclePacker {
public:

    static CirclePackerRef create() { return CirclePackerRef(new CirclePacker()); }

    //----------------------------------------------------------
    class Circle;
    typedef std::shared_ptr<Circle> CircleRef;

    class Circle {
    public:
        
        Circle():
        uid(0),
        pos(0, 0),
        radius(0),
        radiusMin(0),
        radiusMax(0),
        radiusGrowth(0),
        gap(0),
        count(0),
        bAlive(true) {
            //
        }
        
        float getRadius() const { return radius + gap; }
        float getRadiusNext() const { return radius + radiusGrowth + gap; }
        float getRadiusMax() const { return radiusMax + gap; }
        
        unsigned int uid; // unique id.
        glm::vec2 pos;
        float radius;
        float radiusMin;
        float radiusMax;
        float radiusGrowth;
        float gap;
        int	count;
        bool bAlive;
        
        std::vector<CircleRef> neighbours;
    };

    //----------------------------------------------------------
    virtual CircleRef initCircle() const { return CircleRef(new Circle()); }
    
    void reset();
    
    CircleRef & addCircle(const CircleRef & circle);
    CircleRef & addCircle(float x, float y, float radius, float gap=0);
	CircleRef & addCircle(float x, float y, float radiusMin, float radiusMax, float radiusGrowth, float gap=0);
    CircleRef & addCircleToRandomPositionWithinBounds(float radius, const coc::Rect & bounds, float gap=0);
    CircleRef & addCircleToRandomPositionWithinBounds(float radiusMin, float radiusMax, float radiusGrowth, const coc::Rect & bounds, float gap=0);
    
    std::vector<CircleRef> & getCircles() { return circles; }
    
    virtual void update(float timeDelta=0);
    
    virtual void draw() const {}
    
protected:

    std::vector<CircleRef> circles;
    std::vector<CircleRef> circlesToAdd;
    
};

}
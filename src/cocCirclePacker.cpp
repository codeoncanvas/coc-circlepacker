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

#include "cocCirclePacker.h"

namespace coc {

//--------------------------------------------------------------
void CirclePacker::reset() {
    circlesToAdd.clear();
    circles.clear();
}

//--------------------------------------------------------------
void CirclePacker::addCircle(const CircleRef & circle) {
    circlesToAdd.push_back(circle);
}

void CirclePacker::addCircle(float x, float y, float radius, float gap) {
    addCircle(x, y, radius, radius, 0, gap);
}

void CirclePacker::addCircle(float x, float y, float radiusMin, float radiusMax, float radiusGrowth, float gap) {
    CircleRef circle(new Circle());
    circle->pos.x = x;
    circle->pos.y = y;
    circle->radius = radiusMin;
    circle->radiusMin = radiusMin;
    circle->radiusMax = radiusMax;
    circle->radiusGrowth = radiusGrowth;
    circle->gap = gap;
    addCircle(circle);
}

void CirclePacker::addCircleToRandomPositionWithinBounds(float radius, const coc::Rect & bounds, float gap) {
    addCircleToRandomPositionWithinBounds(radius, radius, 0, bounds, gap);
}

void CirclePacker::addCircleToRandomPositionWithinBounds(float radiusMin, float radiusMax, float radiusGrowth, const coc::Rect & bounds, float gap) {
    bool bFits = true;
    bFits = bFits && (bounds.getW() >= radiusMin * 2);
    bFits = bFits && (bounds.getH() >= radiusMin * 2);
    if(bFits == false) {
        return;
    }

    coc::Rect rect = bounds;
    rect.grow(-radiusMin);
    
    float x = coc::rand(rect.getX(), rect.getX() + rect.getW());
    float y = coc::rand(rect.getY(), rect.getY() + rect.getH());
    
    addCircle(x, y, radiusMin, radiusMax, radiusGrowth, gap);
}

//--------------------------------------------------------------
void CirclePacker::update(float timeDelta) {

    //---------------------------------------------------------- add new circles.
    for(int i=0; i<circlesToAdd.size(); i++) {
        const CircleRef & c1 = circlesToAdd[i];
        
        for(int j=0; j<circles.size(); j++) {
            const CircleRef & c2 = circles[j];
            
            float d  = glm::length(c1->pos - c2->pos);
            float r1 = c1->getRadiusMax();
            float r2 = c2->bAlive ? c2->getRadiusMax() : c2->getRadius();
            float r  = r1 + r2;
            
            if(d <= r) {
                c1->neighbours.push_back(c2);
                c2->neighbours.push_back(c1);
            }
        }
        
        circles.push_back(c1);
    }
    circlesToAdd.clear();
    
	if(circles.size() == 0) {
		return;
    }
    
    //---------------------------------------------------------- check collisions.
	for(int i=0; i<circles.size(); i++) {
        const CircleRef & c1 = circles[i];
        
		for(int j=0; j<c1->neighbours.size(); j++) {
            const CircleRef & c2 = c1->neighbours[j];
            
			if((c1->bAlive == false) && (c2->bAlive == false)) {
				continue;
            }
			
            float d  = glm::length(c1->pos - c2->pos);
            float r1 = (c1->bAlive == true) ? c1->getRadiusNext() : c1->getRadius();
            float r2 = (c2->bAlive == true) ? c2->getRadiusNext() : c2->getRadius();
            float r  = r1 + r2;
            
            if(r >= d) {
				c1->bAlive = false;
				c2->bAlive = false;
            }
		}
	}
	
    //---------------------------------------------------------- remove dead circles.
	for(int i=0; i<circles.size(); i++) {
        const CircleRef & c1 = circles[i];
        
		if(c1->count == 0 && c1->bAlive == false) {
            for(int j=0; j<c1->neighbours.size(); j++) {
                const CircleRef & c2 = c1->neighbours[j];
                
                for(int k=0; k<c2->neighbours.size(); k++) {
                    if(c2->neighbours[k] == c1) {
                        c2->neighbours.erase(c2->neighbours.begin() + k);
                        break;
                    }
                }
            }
            
			circles.erase(circles.begin() + i--);
		}
	}
	
    //---------------------------------------------------------- update.
	for(int i=0; i<circles.size(); i++) {
        const CircleRef & c1 = circles[i];
        
		if(c1->bAlive == true) {
			c1->radius += c1->radiusGrowth;
			c1->count  += 1;
			
			if(c1->radius >= c1->radiusMax) {
                c1->radius = c1->radiusMax;
				c1->bAlive = false;
            }
		}
	}
}

}
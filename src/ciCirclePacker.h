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

#include "cocCirclePacker.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace coc {

class ciCirclePacker;
typedef std::shared_ptr<ciCirclePacker> ciCirclePackerRef;
  
class ciCirclePacker : public coc::CirclePacker {
public:

    static ciCirclePackerRef create() { return ciCirclePackerRef(new ciCirclePacker()); }
    
    //----------------------------------------------------------
    class ciCircle;
    typedef std::shared_ptr<ciCircle> ciCircleRef;

    class ciCircle : public coc::CirclePacker::Circle {
    public:
        
        ciCircle():
        coc::CirclePacker::Circle(),
        colorFill(1.0, 1.0, 1.0, 1.0),
        colorStroke(0.0, 0.0, 0.0, 1.0) {
            //
        }
        
        ci::ColorA colorFill;
        ci::ColorA colorStroke;
    };
    
    //----------------------------------------------------------
    virtual CircleRef initCircle() const override { return ciCircleRef(new ciCircle()); }
    
    virtual void draw() const override;
};

}
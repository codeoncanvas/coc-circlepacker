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

#include "ciCirclePacker.h"

namespace coc {

void ciCirclePacker::draw() const {
    for(int i=0; i<circles.size(); i++) {
        ciCircle * circle = (ciCircle *)circles[i].get();
        if(circle->colorFill.a > 0.0) {
            ci::gl::color(circle->colorFill);
            ci::gl::drawSolidCircle(circle->pos, circle->radius);
        }
        if(circle->colorStroke.a > 0.0) {
            ci::gl::color(circle->colorStroke);
            ci::gl::drawStrokedCircle(circle->pos, circle->radius);
        }
    }
    ci::gl::color(ci::Color::white());
}

}
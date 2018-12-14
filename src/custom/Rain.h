/*
  Custom effect that combines the fireworks effect and running effect
  to produce a rain-like effect. Depending on the size of your LED strip, you
  may need to play with the FADE and SIZE options. If color[0] is the same as
  color[1], the rain will be a random color.
  
  Keith Lord - 2018

  LICENSE

  The MIT License (MIT)

  Copyright (c) 2018  Keith Lord 

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
  CHANGELOG
  2018-12-14 initial version
*/

#ifndef Rain_h
#define Rain_h

#include <WS2812FX.h>

extern WS2812FX ws2812fx;

uint16_t rain(void) {
  WS2812FX::Segment* seg = ws2812fx.getSegment(); // get the current segment
  uint16_t seglen = seg->stop - seg->start + 1;
  uint32_t rainColor = seg->colors[0];
  uint32_t bgColor = seg->colors[1];
  if(rainColor == bgColor) rainColor = ws2812fx.color_wheel(ws2812fx.random8());
  bool isReverse = (seg->options & REVERSE) != 0;

  ws2812fx.fireworks(rainColor);

  // shift everything two pixels
  if(isReverse) {
    ws2812fx.copyPixels(seg->start + 2, seg->start, seglen - 2);
  } else {
    ws2812fx.copyPixels(seg->start, seg->start + 2, seglen - 2);
  }

  return(seg->speed / seglen);
}

#endif

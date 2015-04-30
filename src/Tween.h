#ifndef __Tween__
#define __Tween__

#include "AwesomeGL.h"

class Tween {
public:
   enum EASE {NONE, IN_QUAD, OUT_QUAD, INOUT_QUAD, IN_CUBIC, OUT_CUBIC, INOUT_CUBIC,
   IN_QUART, OUT_QUART, INOUT_QUART, IN_QUINT, OUT_QUINT, INOUT_QUINT, IN_SINE,
   OUT_SINE, INOUT_SINE, IN_EXPO, OUT_EXPO, INOUT_EXPO, IN_CIRC, OUT_CIRC, INOUT_CIRC,
   IN_BOUNCE, OUT_BOUNCE, INOUT_BOUNCE};
   Tween(float *target, EASE tweenType, float startVal, float endVal, float time, float waitTime=0.01, bool repeat=false);

   ~Tween();

   void pause(bool pauseVal);

   bool paused;
   bool complete;
   void start();
   void stop();
   void reset();
   void setStartVal(int startVal);
   void setEndVal(float endVal);
   void setTime(float time);
   void updateTween(float elapsed);

private:
   float interpolateTween();

   bool repeat;
   float tweenTime;
   float localTargetVal;
   float endTime;
   float cVal;
   float endVal;
   float startVal;
   EASE tweenType;
   float *targetVal;
   float waitTime;
};

#endif /* defined(__RealTimeTacticsXCODE__Tween__) */

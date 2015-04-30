#include "Tween.h"

using namespace AwesomeGL;

Tween::Tween(float *target, EASE tweenType, float startVal, float endVal, float time, float waitTime, bool repeat) {
   targetVal = target;
   this->repeat = repeat;
   this->tweenType = tweenType;
   this->endVal = endVal;
   this->startVal = startVal;
   cVal = endVal - startVal;
   this->endTime = time;
   paused = false;
   complete = false;
   tweenTime = 0;
   localTargetVal = startVal;
   if (waitTime != 0.01) {
      this->waitTime = waitTime;
   }
}

Tween::~Tween() {

}

void Tween::start() {
   addTween(this);
}

void Tween::stop() {
   removeTween(this);
   reset();
}

void Tween::setStartVal(int startVal) {
   this->startVal = startVal;
}

void Tween::setEndVal(float endVal) {
   this->endVal = endVal;
}

void Tween::setTime(float time) {
   endTime = time;
}

void Tween::updateTween(float elapsed) {
   tweenTime += elapsed;

   if (complete == true) {
      stop();
   }
   
   if (tweenTime < endTime + waitTime && !complete) {
      localTargetVal = interpolateTween();
      *targetVal = localTargetVal;
   }
   else {
      *targetVal = endVal;
      complete = true;
      if (repeat) {
	 reset();
      }
   }
}

void Tween::reset() {
   tweenTime = 0;
   cVal = endVal - startVal;
   complete = false;
}

float Tween::interpolateTween() {
   float t = tweenTime-waitTime;

   switch(tweenType) {
      case IN_QUAD:
	 t /= endTime;
	 return cVal*t*t + startVal;
	 break;
      case OUT_QUAD:
			t /= endTime;
			return -cVal * t*(t-2.0f) + startVal;
			break;
      case INOUT_QUAD:
			t /= endTime/2.0f;
			if (t < 1.0f) return cVal/2.0f*t*t + startVal;
			t--;
			return -cVal/2.0f * (t*(t-2.0f) - 1.0f) + startVal;
			break;
      case IN_CUBIC:
			t /= endTime;
			return cVal*t*t*t + startVal;
			break;
      case OUT_CUBIC:
			t /= endTime;
			t--;
			return cVal*(t*t*t + 1.0f) + startVal;
			break;
      case INOUT_CUBIC:
			t /= endTime/2.0f;
			if (t < 1.0f) return cVal/2.0f*t*t*t + startVal;
			t -= 2.0f;
			return cVal/2.0f*(t*t*t + 2.0f) + startVal;
			break;
		case IN_QUART:
			t /= endTime;
			return cVal*t*t*t*t + startVal;
			break;
		case OUT_QUART:
			t /= endTime;
			t--;
			return -cVal * (t*t*t*t - 1.0f) + startVal;
			break;
		case INOUT_QUART:
			t /= endTime/2.0f;
			if (t < 1.0f) return cVal/2.0f*t*t*t*t + startVal;
			t -= 2.0f;
			return -cVal/2.0f * (t*t*t*t - 2.0f) + startVal;
			break;
		case IN_QUINT:
			t /= endTime;
			return cVal*t*t*t*t*t + startVal;
			break;
		case OUT_QUINT:
			t /= endTime;
			t--;
			return cVal*(t*t*t*t*t + 1.0f) + startVal;
			break;
		case INOUT_QUINT:
			t /= endTime/2.0f;
			if (t < 1.0f) return cVal/2.0f*t*t*t*t*t + startVal;
			t -= 2.0f;
			return cVal/2.0f*(t*t*t*t*t + 2.0f) + startVal;
			break;
		case IN_SINE:
			return -cVal * cos(t/endTime * (PI/2.0f)) + cVal + startVal;
			break;
		case OUT_SINE:
			return cVal * sin(t/endTime * (PI/2.0f)) + startVal;
			break;
		case INOUT_SINE:
			return -cVal/2.0f * (cos(PI*t/endTime) - 1.0f) + startVal;
			break;
		case IN_EXPO:
			return cVal * powf( 2.0f, 10.0f * (t/endTime - 1.0f) ) + startVal;
			break;
		case OUT_EXPO:
			return cVal * ( -powf( 2.0f, -10.0f * t/endTime ) + 1.0f ) + startVal;
			break;
		case INOUT_EXPO:
			t /= endTime/2.0f;
			if (t < 1.0f) return cVal/2.0f * powf( 2.0f, 10.0f * (t - 1.0f) ) + startVal;
			t--;
			return cVal/2.0f * ( -powf( 2.0f, -10.0f * t) + 2.0f ) + startVal;
			break;
		case IN_CIRC:
			t /= endTime;
			return -cVal * (sqrt(1.0f - t*t) - 1.0f) + startVal;
			break;
		case OUT_CIRC:
			t /= endTime;
			t--;
			return cVal * sqrt(1.0f - t*t) + startVal;
			break;
		case INOUT_CIRC:
			t /= endTime/2.0f;
			if (t < 1.0f) return -cVal/2.0f * (sqrt(1.0f - t*t) - 1.0f) + startVal;
			t -= 2.0f;
			return cVal/2.0f * (sqrt(1.0f - t*t) + 1.0f) + startVal;
			break;
		case OUT_BOUNCE:
		case INOUT_BOUNCE:
		case IN_BOUNCE:
			if ((t/=endTime) < (1/2.75)) {
				return cVal*(7.5625*t*t) + startVal;
			} else if (t < (2/2.75)) {
				return cVal*(7.5625*(t-=(1.5/2.75))*t + .75) + startVal;
			} else if (t < (2.5/2.75)) {
				return cVal*(7.5625*(t-=(2.25/2.75))*t + .9375) + startVal;
			} else {
				return cVal*(7.5625*(t-=(2.625/2.75))*t + .984375) + startVal;
			}
			break;
		default:
		case NONE:
			// return c*t/d + b;
			return cVal*t/endTime+startVal;
			break;

   }
}
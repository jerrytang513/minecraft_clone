#ifndef MOVERIGHTEVENT_H_
#define MOVERIGHTEVENT_H_

#include "event.h"
class MoveRightEvent : public Event{

public:
  MoveRightEvent();
  void action(WorldSpace& ws);
};

#endif

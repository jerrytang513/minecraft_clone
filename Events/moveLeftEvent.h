#ifndef MOVELEFTEVENT_H_
#define MOVELEFTEVENT_H_

#include "event.h"
class MoveLeftEvent : public Event{

public:
  MoveLeftEvent();
  void action(WorldSpace& ws);
};

#endif

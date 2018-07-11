#ifndef MOVEBACKEVENT_H_
#define MOVEBACKEVENT_H_

#include "event.h"
class MoveBackEvent : public Event{

public:
  MoveBackEvent();
  void action(WorldSpace& ws);
};

#endif

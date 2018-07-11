#ifndef MOVEFRONTEVENT_H_
#define MOVEFRONTEVENT_H_

#include "event.h"
class MoveFrontEvent : public Event{

public:
  MoveFrontEvent();
  void action(WorldSpace& ws);
};

#endif

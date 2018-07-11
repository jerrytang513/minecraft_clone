#ifndef EVENT_H_
#define EVENT_H_

#include "eventId.h"
#include "../WorldGenerator/worldSpace.h"

class Event{
  EventID eventID;
  virtual void init();
public:
  Event(EventID eventID);
  virtual void action(WorldSpace& ws) = 0;

};

#endif

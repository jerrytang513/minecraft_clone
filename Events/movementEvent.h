#ifndef MOVEMENTEVENT_H_
#define MOVEMENTEVENT_H_

#include "event.h"
#include "../WorldGenerator/Renderer/direction.h"
class MovementEvent : public Event{
  // If they reached a number of counts, update the chunk so that it will load a new row of chunk and delete a row of chunk in the opposite movement direction
  // Move left and left count ++, move right and left count --
  // If they reach 3 count or -3 count, then set it to 0 and activate the action
  int leftMoveCount;
  int frontMoveCount;
  void init();

public:
  MovementEvent();
  void action(WorldSpace& ws);
  void updateDir(Direction dir);
};

#endif

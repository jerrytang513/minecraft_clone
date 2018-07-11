#include "moveRightEvent.h"

MoveRightEvent::MoveRightEvent():Event{EventID::MOVERIGHT}{}

void MoveRightEvent::action(WorldSpace& ws){
  ws.moveRight();
}

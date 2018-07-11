#include "moveLeftEvent.h"

MoveLeftEvent::MoveLeftEvent():Event{EventID::MOVELEFT}{}

void MoveLeftEvent::action(WorldSpace& ws){
  ws.moveLeft();
}

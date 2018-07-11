#include "moveFrontEvent.h"

MoveFrontEvent::MovementEvent():Event{EventID::MOVEFRONT}{}

void MoveFrontEvent::action(WorldSpace& ws){
  ws.moveFront();
}

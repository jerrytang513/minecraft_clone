#include "moveBackEvent.h"

MoveBackEvent::MoveBackEvent():Event{EventID::MOVEBACK}{}

void MoveBackEvent::action(WorldSpace& ws){
  ws.moveBack();
}

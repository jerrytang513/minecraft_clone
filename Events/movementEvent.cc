#include "movementEvent.h"

MovementEvent::MovementEvent():Event{EventID::MOVEMENT}{
  init();
}

void MovementEvent::init(){
  leftMoveCount = 0;
  frontMoveCount = 0;
}

void MovementEvent::action(WorldSpace& ws){
  if(leftMoveCount == 3){
    ws.moveLeft();
  } else if(leftMoveCount == -3){
    ws.moveRight();
  }

  if(frontMoveCount == 3){
    ws.moveFront();
  } else if(frontMoveCount == -3){
    ws.moveBack();
  }
}

void updateDir(Direction dir){
  switch(dir){
    case Direction::LEFT:
      leftMoveCount ++;
      break;
    case Direction::RIGHT:
      leftMoveCount --;
      break;
    case Direction::FRONT:
      frontMoveCount ++;
      break;
    case Direction::BACK:
      frontMoveCount --;
      break;
    default:
      break;
  }
}

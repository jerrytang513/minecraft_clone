#ifndef BLOCKINFO_H_
#define BLOCKINFO_H_
struct BlockInfo{
  int x;
  int y;
  int z;
  bool visible;
  BlockInfo(){visible = false;}
};
#endif
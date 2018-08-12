#ifndef WORLDGENERATOR_BLOCKINFO_H_
#define WORLDGENERATOR_BLOCKINFO_H_

enum class BLOCKTYPE {
	SAND,
	DIRT,
	GRASS,
	ROCK,
	WATER,
	AIR
};

struct BlockInfo{
  bool visible;
  BLOCKTYPE type;
  BlockInfo():visible{false},type{BLOCKTYPE::AIR}{}
  BlockInfo(BLOCKTYPE type):visible{true},type{type}{}
};
#endif

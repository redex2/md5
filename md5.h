#pragma once
#include <sstream>

typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
static_assert(sizeof(uint16) == 2, "Change type of var for uint16");
static_assert(sizeof(uint32) == 4, "Change type of var for uint32");
static_assert(sizeof(uint64) == 8, "Change type of var for uint64");

class MD5
{
private:
	uint16 i = 0;
	uint32** data = NULL;
	uint32 hash[4];
	uint32 temp[6];
	uint32 word[16];
	uint64 out_len = 0, j = 0;
	static const uint32 k[64];
	static const uint16 s[64];
	std::stringstream sstring;

	uint32 rotate(uint32, uint16);
	uint32 permutation(uint32);
	uint32 F(uint32, uint32, uint32);
	uint32 G(uint32, uint32, uint32);
	uint32 H(uint32, uint32, uint32);
	uint32 I(uint32, uint32, uint32);
	void init(void);
	void rewriting(void);
	void split_message(const char*, uint64, uint32**&, uint64&, uint16);

public:
	std::string create(char*, uint64);

};

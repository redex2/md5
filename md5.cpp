#include "md5.h"

void _md5::split_message(const char* message, uint64 len, uint32**& out, uint64& out_len, uint16 block_size)
{
	block_size = (block_size + 31) / 32;
	out = new uint32 * [block_size];

	for (i = 0; i < block_size; i++)
	{
		out[i] = new uint32[((len + 8 + block_size * 4 - 1) / (block_size * 4))];
	}

	i = 0;
	if (len > 3)
	{
		for (i = 0; i < len - 3; i += 4)
		{
			out[i / 4 % block_size][i / (block_size * 4)] = (uint32)message[i + 3] << 24 | message[i + 2] << 16 | message[i + 1] << 8 | message[i];
		}
	}

	if (len % 4 == 1)
	{
		out[i / 4 % block_size][i / (block_size * 4)] = (uint32)message[i] | 1 << 15;
	}
	else if (len % 4 == 2)
	{
		out[i / 4 % block_size][i / (block_size * 4)] = (uint32)message[i] | (uint32)message[i + 1] << 8 | 1 << 23;
	}
	else if (len % 4 == 3)
	{
		out[i / 4 % block_size][i / (block_size * 4)] = (uint32)message[i] | (uint32)message[i + 1] << 8 | (uint32)message[i + 2] << 16 | 1 << 31;
	}
	else
	{
		out[i / 4 % block_size][i / (block_size * 4)] = 1 << 7;
	}

	while ((i / 4 % block_size) != (block_size - 3))
	{
		i += 4;
		out[i / 4 % block_size][i / (block_size * 4)] = 0;
	}
	i += 4;
	len *= 8;
	out[(i) / 4 % block_size][(i) / (block_size * 4)] = len;
	out[(i + 4) / 4 % block_size][(i) / (block_size * 4)] = len >> 32;

	out_len = i / (block_size * 4) + 1;
}

uint32 _md5::rotate(uint32 data, uint16 num)
{
	return ((data << num) | (data >> (32 - num)));
}

uint32 _md5::permutation(uint32 data)
{
	return (((data & 0xFF) << 24) | ((data & 0xFF00) << 8) | ((data & 0xFF0000) >> 8) | ((data & 0xFF000000) >> 24));
}

uint32 _md5::F(uint32 B, uint32 C, uint32 D)
{
	return (B & C) | ((~B) & D);
}

uint32 _md5::G(uint32 B, uint32 C, uint32 D)
{
	return (B & D) | (C & (~D));
}

uint32 _md5::H(uint32 B, uint32 C, uint32 D)
{
	return B ^ C ^ D;
}

uint32 _md5::I(uint32 B, uint32 C, uint32 D)
{
	return C ^ (B | (~D));
}

void _md5::init(void)
{
	hash[0] = 0x67452301;
	hash[1] = 0xefcdab89;
	hash[2] = 0x98badcfe;
	hash[3] = 0x10325476;
}

void _md5::rewriting(void)
{
	temp[4] = temp[4] + temp[0] + k[i] + word[temp[5]];
	temp[0] = temp[3];
	temp[3] = temp[2];
	temp[2] = temp[1];
	temp[1] += rotate(temp[4], s[i]);
}

std::string _md5::create(char* message, uint64 len)
{
	init();
	sstring.str(std::string());
	split_message(message, len, data, out_len, 512);

	for (j = 0; j < out_len; j++)
	{
		temp[0] = hash[0];
		temp[1] = hash[1];
		temp[2] = hash[2];
		temp[3] = hash[3];

		for (i = 0; i < 16; i++)
		{
			word[i] = (*(*(data + i) + j));
		}

		for (i = 0; i < 16; i++)
		{
			temp[4] = F(temp[1], temp[2], temp[3]);
			temp[5] = i;
			rewriting();
		}
		for (i = 16; i < 32; i++)
		{
			temp[4] = G(temp[1], temp[2], temp[3]);
			temp[5] = (5 * i + 1) % 16;
			rewriting();
		}
		for (i = 32; i < 48; i++)
		{
			temp[4] = H(temp[1], temp[2], temp[3]);
			temp[5] = (3 * i + 5) % 16;
			rewriting();
		}
		for (i = 48; i < 64; i++)
		{
			temp[4] = I(temp[1], temp[2], temp[3]);
			temp[5] = (7 * i) % 16;
			rewriting();
		}

		hash[0] += temp[0];
		hash[1] += temp[1];
		hash[2] += temp[2];
		hash[3] += temp[3];
	}


	for (j = 0; j < 4; j++)
	{
		sstring.width(8);
		sstring.fill('0');
		sstring << std::hex << permutation(hash[j]);
	}
	return sstring.str();
}

const uint32 _md5::k[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint16 _md5::s[64] =
{
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

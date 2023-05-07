#include <gtest/gtest.h>
#include <md5.h>

TEST(md5, md5) {
	MD5 md5;
	std::string data = "foobarbaz";
	EXPECT_EQ(md5.Create((char*)data.c_str(), data.length()), "6df23dc03f9b54cc38a0fc1483df6e21");
	data = "hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_hello_world_md5_";
	EXPECT_EQ(md5.Create((char*)data.c_str(), data.length()), "80ed53b09aad72224ec4d5912fdad58c");
	data = "";
	EXPECT_EQ(md5.Create((char*)data.c_str(), data.length()), "d41d8cd98f00b204e9800998ecf8427e");
}
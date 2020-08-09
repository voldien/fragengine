#include<gtest/gtest.h>
#include<sched.h>
#include<Core/RefPtr.h>
#include <Core/IO/IP.h>
#include <Core/IO/NetSocket.h>

using namespace fragcore;

class IPTest : public testing::Test {
protected:

};

TEST_F(IPTest, IP) {

	IP ip;
}

TEST_F(IPTest, Socket) {

	IP ip;

	NetSocket netSocket;
}

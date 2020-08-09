#ifndef FRAGVIEW_ICONFIGTEST_H_
#define FRAGVIEW_ICONFIGTEST_H_ 1
#include"common.h"
//#include"../../../client/include/OptionDicSet.h"


class IConfigTest : public CommonBaseTest {
protected:
	void TearDown() override;

	void SetUp() override;

	fragcore::IConfig* config;
};

#endif
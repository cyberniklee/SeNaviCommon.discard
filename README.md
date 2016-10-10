# SeNaviCommon
# Test code as below
# build with -lSeNaviCommon


#include <iostream>
#include <DataSet/DataType/DataBase.h>
#include <DataSet/Dispitcher.h>
#include <boost/bind.hpp>
#include <DataSet/DataType/DataBase.h>
#include <Service/ServiceType/RequestBase.h>
#include <Service/ServiceType/ResponseBase.h>
#include <Service/Service.h>
#include <Time/Time.h>

using namespace std;

class TestData : public NS_NaviCommon::DataBase
{
public:
	int i;
	float f;
};

class TestReq : public NS_NaviCommon::RequestBase
{
public:
	int req;
};

class TestRep : public NS_NaviCommon::ResponseBase
{
public:
	int rep;
};

void TestSrvFun(NS_NaviCommon::RequestBase* q, NS_NaviCommon::ResponseBase* p)
{
	((TestRep*)p)->rep = ((TestReq*)q)->req + 100;
}

class Test
{
public:
	void cb(NS_NaviCommon::DataBase* d)
	{
		cout << ((TestData*)d)->i << "  "<< ((TestData*)d)->f << endl;
	};
};

int main(int argc, char* argv[])
{
	NS_NaviCommon::Time::init();

	NS_NaviCommon::Dispitcher dispitcher;

	dispitcher.initialize();

	NS_NaviCommon::Service service;

	service.initialize();

	Test test;


	dispitcher.subscribe(NS_NaviCommon::DATA_TYPE_TWIST,
			boost::bind(&Test::cb, &test, _1));


	TestData test_data;
	test_data.i = 1;
	test_data.f = 0.1;

	service.advertise(NS_NaviCommon::SERVICE_TYPE_NONE,
			boost::bind(&TestSrvFun, _1, _2));

	TestReq test_req;
	TestRep test_rep;
	test_req.req = 8;

	NS_NaviCommon::Rate r(1);

	while(1)
	{
		dispitcher.publish(NS_NaviCommon::DATA_TYPE_TWIST, &test_data);

		service.call(NS_NaviCommon::SERVICE_TYPE_NONE, &test_req, &test_rep);
		cout << test_rep.rep << endl;

		r.sleep();
	}


	return 0;
}

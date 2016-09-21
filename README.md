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

class TestData : public _Navi_Common_::DataBase
{
public:
	int i;
	float f;
};

class TestReq : public _Navi_Common_::RequestBase
{
public:
	int req;
};

class TestRep : public _Navi_Common_::ResponseBase
{
public:
	int rep;
};

void TestSrvFun(_Navi_Common_::RequestBase* q, _Navi_Common_::ResponseBase* p)
{
	((TestRep*)p)->rep = ((TestReq*)q)->req + 100;
}

class Test
{
public:
	void cb(_Navi_Common_::DataBase* d)
	{
		cout << ((TestData*)d)->i << "  "<< ((TestData*)d)->f << endl;
	};
};

int main(int argc, char* argv[])
{
	_Navi_Common_::Time::init();

	_Navi_Common_::Dispitcher dispitcher;

	dispitcher.initialize();

	_Navi_Common_::Service service;

	service.initialize();

	Test test;


	dispitcher.subscribe(_Navi_Common_::DATA_TYPE_TWIST,
			boost::bind(&Test::cb, &test, _1));


	TestData test_data;
	test_data.i = 1;
	test_data.f = 0.1;

	service.advertise(_Navi_Common_::SERVICE_TYPE_NONE,
			boost::bind(&TestSrvFun, _1, _2));

	TestReq test_req;
	TestRep test_rep;
	test_req.req = 8;

	_Navi_Common_::Rate r(1);

	while(1)
	{
		dispitcher.publish(_Navi_Common_::DATA_TYPE_TWIST, &test_data);

		service.call(_Navi_Common_::SERVICE_TYPE_NONE, &test_req, &test_rep);
		cout << test_rep.rep << endl;

		r.sleep();
	}


	return 0;
}

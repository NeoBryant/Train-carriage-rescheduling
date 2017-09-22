#ifndef RESCHDEDULINGSTSTEM_HPP
#define RESCHDEDULINGSTSTEM_HPP value

#include <iostream>
#include <stack>
#define MAX_CARRIAGE_NUMBER 12
using namespace std;

class ReschedulingSystem
{
public:
	ReschedulingSystem();
	~ReschedulingSystem();
	
	bool GetCarriageNumber();
	void Rescheduling();

private:
    stack injection;
    stcak rail;
    stcak *buffer;
    int number_buffers;
    int number_carriages;
    int step;
};

ReschedulingSystem::ReschedulingSystem() {
	buffer = NULL;
	number_buffers = 0;
	step = 0;
}

ReschedulingSystem::~ReschedulingSystem() {
	if (buffer != NULL) {
		delete []buffer;
		buffer = NULL;
	}
}

bool GetCarriageNumber() {
	cout << "How many train carriages do you need to reschedul: ";
	cin >> number_carriages;

	while (number_carriages > MAX_CARRIAGE_NUMBER) {
		
	}


}


#endif
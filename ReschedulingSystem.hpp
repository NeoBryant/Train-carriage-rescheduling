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
	
	void read(); //read the information from user
	void rescheduling(); //excute the system
	void print(); //print the result of rescheduling

private:
    stack<int> rail_in;
    stack<int> rail_out;
    stack<int> *buffer;
    int number_buffers; // the number of buffers using
    int number_carriages; //the total number of carriages
    int step; 
    int count; // the current carriage that should leave
};

ReschedulingSystem::ReschedulingSystem() {
	buffer = NULL;
	number_buffers = 0;
	step = 0;
	count = 1;
}

ReschedulingSystem::~ReschedulingSystem() {
	if (buffer != NULL) {
		delete []buffer;
		buffer = NULL;
	}
}


void ReschedulingSystem::read() {
	int number;
	cout << "How many train carriages do you need to reschedul: ";
	cin >> number_carriages;

	while (number_carriages > MAX_CARRIAGE_NUMBER) {
		cout << "The number of carriages need to be less than " 
			 << MAX_CARRIAGE_NUMBER 
			 << endl;
		cout << "How many train carriages do you need to reschedul: ";
		cin >> number_carriages;	 
	}

	buffer = new stack<int> [number_carriages - 1];

	cout << "Please input the serial number of train carriages." << endl
		 << "--> " ;
	for (int i = 0; i < number_carriages; ++i) {
		cin >> number;
		rail_in.push(number);
	}
}

void ReschedulingSystem::rescheduling() {
	bool isInBuffers = false;
	while (rail_out.size() != number_carriages) {
		isInBuffers = false;

		//is the current number on the top of the rail
		if (rail_in.size() && rail_in.top() == count) {


			cout << "Step " << step+1 << ": "
				 << "From entance |-- " << rail_in.top() << " --> "
				 << "exit" << endl;

			rail_out.push(rail_in.top());
			rail_in.pop();

			++count;
			++step;
		} else {
			//is the current number in one of the tops of buffers
			for (int i = 0; i < number_buffers; ++i) {
				if (buffer[i].size() && buffer[i].top() == count) {

					cout << "Step " << step+1 << ": "
						 << "From No." << i+1 << " buffer rail |-- " 
						 << buffer[i].top() << " --> "
						 << "exit" << endl;

					rail_out.push(buffer[i].top());
					buffer[i].pop();

					++count;
					++step;
					isInBuffers = true;
					break;
				}
			}

			//put the top of the rail to the buffers
			if (!isInBuffers) {
				bool openNewBuffer = true; //do it need to open a new buffer rail
				for (int i = 0; i < number_buffers; ++i) {
					if (rail_in.top() && buffer[i].size() 
						&& rail_in.top() < buffer[i].top()) {

						cout << "Step " << step+1 << ": "
							 << "From entance |-- " << rail_in.top() << " --> "
							 << "No." << i+1 << " buffer rail" << endl;

						buffer[i].push(rail_in.top());
						rail_in.pop();

						++step;
						openNewBuffer = false;
						break;
					}

					if (buffer[i].size() == 0) {

						cout << "Step " << step+1 << ": "
							 << "From entance |-- " << rail_in.top() << " --> "
							 << "No." << i+1 << " buffer rail" << endl;

						buffer[i].push(rail_in.top());
						rail_in.pop();
						
						++step;
						openNewBuffer = false;
						break;						
					}
				}	

				//open a new buffer rail
				if (openNewBuffer) {

					cout << "Step " << step+1 << ": "
						 << "From entance |-- " << rail_in.top() << " --> "
						 << "No." << number_buffers+1 << " buffer rail(new one)" << endl;

					buffer[number_buffers].push(rail_in.top());
					rail_in.pop();

					++step;
					++number_buffers;
				}
			}
		}
	}
}

void ReschedulingSystem::print() {
	cout << endl
		 << number_buffers << " buffers is used" << endl
		 << step << " steps totally" << endl
		 << "The result is : " << endl;

	while (!rail_out.empty()) {
		cout << rail_out.top() << ' ';
		rail_out.pop();
	}
	cout << "-->" << endl;

}

#endif
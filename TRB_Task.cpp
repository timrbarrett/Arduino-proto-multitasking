#ifndef TRB_TASK_CPP
#define TRB_TASK_CPP

#include <Arduino.h>
#include <TRB_Task.h>

TRB_Task::TRB_Task() {
}

TRB_Task::TRB_Task(char first, char second, char third, 
	int hertz, functionWithNoArgs work) {
	
	//capture name
	name[0] = first;
	name[1] = second;
	name[2] = third;
	
	// calculate microPerRepetition	
	microsPerTask = oneSecondInMicroSeconds / hertz;

	//Serial.begin(115200);
	//while (!Serial);
	
	nameToSerial();
	Serial.print(F("microsPerTask:"));
	Serial.println(microsPerTask);
	
	// store the callback function
	_work = work;
	
	// reset the Count
	count = 0;
	
	// set the processedUntil
	processedUntil = 0;
}
	
void TRB_Task::work() {
	_work();
	count++;
}

bool TRB_Task::shouldRun(unsigned long now) {
	
	bool response = ((now / microsPerTask) > processedUntil);
	
	if (response) {
		
		// update where we consider we are processed ntil
		processedUntil = (now / microsPerTask);
		
	}
	
	return response;
	
}

unsigned long TRB_Task::getCount() {
	return count;
}

void TRB_Task::nameToSerial() {
	Serial.print(name[0]);
	Serial.print(name[1]);
	Serial.print(name[2]);
	Serial.print(':');
}
#endif
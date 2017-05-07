#ifndef TRB_SCHEDULER_CPP
#define TRB_SCHEDULER_CPP

#include <Arduino.h>
#include <MemoryFree.h>
#include <TRB_Scheduler.h>
#include <TRB_Task.h>

TRB_Scheduler::TRB_Scheduler(int secondsToRunFor/*, int maxTasks*/) {
	_secondsToRunFor = secondsToRunFor;
	_maxTasks = 0;
}

void TRB_Scheduler::addTask(TRB_Task newtask) {
	_taskList[_maxTasks++]=newtask;
}

void TRB_Scheduler::inSetup() {
	
	microsNow = micros();
	if (outputInSetup) { 
		Serial.print(F("microsNow = "));
		Serial.println(microsNow);
	}

	startTime = microsNow;
	stopAtTime = microsNow + (2 * 1000000);
	if (outputInSetup) { 
		Serial.print(F("stopAtTime = "));
		Serial.println(stopAtTime);
		Serial.println();
	}
	
}

void TRB_Scheduler::inLoop() {
	
	// the price of the - startTime is intuitive working.
	microsNow = micros()-startTime;
	
	// is now the time to stop?
	if (microsNow >= stopAtTime) {
		
		Serial.println();
		// wrap up with conclusions
		inConclusion();
		
	    exit(0);
	}

	// step through each task
	for (int taskIndex = 0; taskIndex < _maxTasks; taskIndex++) {
		
		if(_taskList[taskIndex].shouldRun(microsNow)) {
			
			// if it needs to run - let it
			_taskList[taskIndex].work();
			
		}
	}
}

// one can start setup with this and have 
void TRB_Scheduler::setOutputInSetup(bool choice) {
	outputInSetup = choice;
	
	// create a serial link and wait for it
	// if serial output has been requested
	if (outputInSetup) {
		Serial.begin(115200);
		while (!Serial); 
		// wait for Serial to initialise before continuing
	}
	
}

void TRB_Scheduler::inConclusion() {
	
	/*
        Returns the number of bytes free in the heap,
        i.e. the number of bytes free to be allocated using malloc().
    */
    Serial.println("Free memory: " + String(freeMemory()));

    /*
        Returns the number of bytes free in the stack,
        i.e. the space between the current stack frame and the end of the stack area.
        This function will return a negative number in the event of a stack overflow,
        representing the size of the overflow; for example,
        a return value of -20 means that the current stack frame is 20 bytes
        past the end of the stack area.
    */
    Serial.println("Free Stack: " + String(freeStack()));

    /*
        Returns the number of bytes free in both the stack and the heap.
        If a stack overflow has occurred,
        only the number of bytes free in the heap is returned.
    */
    Serial.println("Free Heap: " + String(freeHeap()));
	
	for (int taskIndex = 0; taskIndex < _maxTasks; taskIndex++) {
		
		//Serial.print(_taskList[taskIndex].name[0]);
		//Serial.print(_taskList[taskIndex].name[1]);
		//Serial.print(_taskList[taskIndex].name[2]);
		_taskList[taskIndex].nameToSerial();
		Serial.print(F(":ran "));
		Serial.print(_taskList[taskIndex].getCount());
		Serial.println(F("times"));
		
	}
}
#endif
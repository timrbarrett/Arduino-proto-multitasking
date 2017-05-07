#ifndef TRB_SCHEDULER_H
#define TRB_SCHEDULER_H

#include <TRB_Task.h>


class TRB_Scheduler {
	public:
		TRB_Scheduler(int secondToRunFor/*, int maxTasks*/);
		void addTask(TRB_Task task);
		void inSetup();
		void inLoop();
		void setOutputInSetup(bool choice);
		void inConclusion();
		
	private:
		long stopAtTime;
		long startTime;
		long microsNow;
		bool outputInSetup = false;
		int _secondsToRunFor;
		int _maxTasks;
		TRB_Task _taskList[2];
};

#endif
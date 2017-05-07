#ifndef TRB_TASK_H
#define TRB_TASK_H

// define FunctionWithNoArgs
typedef void (*functionWithNoArgs) (); 

const int oneSecondInMicroSeconds = 1000000;   // one second in micro seconds

class TRB_Task {
	
	public:
		TRB_Task();
		TRB_Task(char first, char second, char third, 
			int hertz, functionWithNoArgs work);
		void work();
		bool shouldRun(unsigned long now);
		unsigned long getCount();
		void nameToSerial();
		
	private:
		//int hertzOfTask;
		unsigned long microsPerTask;
		unsigned long processedUntil;
		unsigned long count;
		char name[3];
		functionWithNoArgs _work;
		
};

#endif
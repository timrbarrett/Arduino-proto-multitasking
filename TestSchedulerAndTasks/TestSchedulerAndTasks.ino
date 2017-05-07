#include <TRB_Scheduler.h>
#include <TRB_Task.h>

// define a global variable for the scheduler
// create the object that manages all the tasks, timings and final report out

TRB_Scheduler scheduler(1);

void setup() {  // put your setup code here, to run once:

  scheduler.setOutputInSetup(true);

  // create the object that tells the Schduler how frequently to un a second
  // and what task to perform very repetition
  TRB_Task task1('t', 's', 't', 10, repeatingTask);

  // add the Task to the Scheduler
  scheduler.addTask(task1);

  // run the once code for scheduler
  scheduler.inSetup();
  
}

void loop() {  // put your main code here, to run repeatedly:
  scheduler.inLoop();
}

// define the work done by the task
void repeatingTask() {
  // the payload
  Serial.println(micros());
}

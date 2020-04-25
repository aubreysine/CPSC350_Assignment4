#include "Simulation.h"
//simulation implementation

Simulation::Simulation(){
  studentQ = new GenQueue<Student>();
  freeList = new Window*[100];
  fullList = new Window*[100];

  waitTime = new GenQueue<int>;
  idleTime = new GenQueue<int>;

  time = 0;
}

Simulation::Simulation(ifstream &inFS){
  studentQ = new GenQueue<Student>();

  time = 0;
  inFS >> numWindows;
  numFree = numWindows;
  numFull = 0;

  freeList = new Window*[numWindows];
  fullList = new Window*[numWindows];

  waitTime = new GenQueue<int>;
  idleTime = new GenQueue<int>;

  numWait = 0;
  numIdle = 0;

  //Adds empty windows to list of free windows
  for(int i = 0; i < numWindows; ++i){
    freeList[i] = new Window();
  }

  int total, arrival, numStudents, winTime;

  while(true){
    inFS >> arrival;
    inFS >> numStudents;
    if(inFS.eof()){
      break;
    }

    if(!inFS.fail()){
      arrival += total; //Makes total absolute time instead of relative time

      //Adds students to queue with specified arrival and window times
      for(int i = 0; i < numStudents; ++i){
        inFS >> winTime;
        studentQ->insert(Student(arrival,winTime));
      }
    }

    total = arrival;
  }

  inFS.close();
}

Simulation::~Simulation(){
  delete studentQ;
  delete[] freeList;
  delete[] fullList;
  delete waitTime;
  delete idleTime;
}

//Starts the Simulation
void Simulation::start(){
  while(true){

    //Ends simulation if no more students are in the queue and all windows are free
    if(studentQ->isEmpty() && numFree == numWindows){
      break;
    }

    //Adds window to free list if the time helping student is up
    if(fullList[0] != nullptr){
      if(fullList[0]->getTimeFree() == time){
        addFree();
        continue;
      }
    }

    //Adds Windows to full List if there is a student waiting and there are free windows
    if(!studentQ->isEmpty()){
      if(studentQ->peek().getArrivalTime() <= time && freeList[0] != nullptr){
        if((time - studentQ->peek().getArrivalTime()) > 0){
          waitTime->insert(time - studentQ->peek().getArrivalTime()); //Adds wait time to queue of wait times
          numWait++;
        } else if((time - freeList[0]->getTimeArrived()) > 0){
          idleTime->insert(time - freeList[0]->getTimeArrived()); //Adds idle time to queue of idle times
          numIdle++;
        }
        freeList[0]->setTimeFree(studentQ->peek().getWindowTime() + time); //Gives window free time based on student they are helping
        studentQ->remove();
        addFull();
        continue;
      }
    }
    time++;
  }

  //Adds idle times at the end of the simulation
  for(int i = 0; i < numWindows; ++i){
    if((time - freeList[i]->getTimeArrived()) > 0){
      idleTime->insert(time - freeList[i]->getTimeArrived());
      numIdle++;
    }
  }
}

//Adds window to full list from free list
void Simulation::addFull(){
  //Adding and sorting list of full windows by time free
  for(int i = 0; i <= numFull; ++i){
    if(fullList[i] == nullptr){
      fullList[i] = freeList[0];
      break;
    } else if(fullList[i]->getTimeFree() > freeList[0]->getTimeFree()){
      for(int x = numFull; x > i; --x){
        fullList[x] = fullList[x-1];
      }
      fullList[i] = freeList[0];
      break;
    }
  }
  numFull++;
  freeList[0] = nullptr;

  //moving windows forward to account for removed window
  for(int i = 1; i < numFree; ++i){
    if(freeList[i] == nullptr){
      break;
    } else{
      freeList[i-1] = freeList[i];
      freeList[i] = nullptr;
    }
  }
  numFree--;
}

//Adds window to free list from full list
void Simulation::addFree(){
    fullList[0]->setTimeArrived(time); //Setting time that the window begins waiting
    freeList[numFree] = fullList[0];
    numFree++;

    fullList[0] = nullptr;
    //moving windows forward to account for removed window
    for(int i = 1; i < numFull; ++i){
      if(fullList[i] == nullptr){
        break;
      } else{
        fullList[i-1] = fullList[i];
        fullList[i] = nullptr;
      }
    }
    numFull--;
}

//Displays calculated metrics
void Simulation::displayMetrics(){
  float meanWait, medianWait, meanIdle;
  int longestWait = 0, longWaitCount = 0, totalWait = 0;
  int longestIdle = 0, longIdleCount = 0, totalIdle = 0;
  int temp, waitArr[numWait];

  //Metrics for window idle times
  for(int i = 0; i < numIdle; ++i){
    temp = idleTime->remove();
    totalIdle += temp;

    if(temp > 5){
      longIdleCount++;
    }

    if(temp > longestIdle){
      longestIdle = temp;
    }
  }
  meanIdle = totalIdle / (float) numIdle;

  //Metrics for student wait times
  for(int i = 0; i < numWait; ++i){
    temp = waitTime->remove();
    totalWait += temp;

    if(temp > 10){
      longWaitCount++;
    }

    if(temp > longestWait){
      longestWait = temp;
    }
    waitArr[i] = temp;
  }

  sort(waitArr, waitArr+numWait); //Sorting list of wait times to claculate median
  medianWait = waitArr[numWait/2];
  if(numWait % 2 == 0){
    medianWait = (medianWait + waitArr[(numWait/2)-1]) / (float) 2;
  }

  meanWait = totalWait / (float) numWait;

  cout << "Student Wait Time Statistics:" << endl;
  cout << "\tMean Wait Time: " << meanWait << endl;
  cout << "\tMedian Wait Time: " << medianWait << endl;
  cout << "\tLongest Wait Time: " << longestWait << endl;
  cout << "\tNumber of Wait Times Over 10 Minutes: " << longWaitCount << endl << endl;

  cout << "Window Idle Time Statistics: " << endl;
  cout << "\tMean Idle Time: " << meanIdle << endl;
  cout << "\tLongest Idle Time: " << longestIdle << endl;
  cout << "\tNumber of Idle Times Over 5 Minutes: " << longIdleCount << endl;
}

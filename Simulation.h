#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <fstream>
#include <string>
#include <algorithm>

class Simulation{
  public:
    Simulation();//default
    Simulation(ifstream &inFS);//overloaded
    ~Simulation();//destructor

    void start(); //runs function
    void displayMetrics();//function shows the metrics neccessary the specs of the assignments
  private:
    GenQueue<Student>* studentQ; //Queue of students
    Window** freeList; //List of free Windows
    Window** fullList; //List of full windows

    int numFree;
    int numFull;

    //queues for waittime and idle time to make metric calculations easier
    GenQueue<int>* waitTime;
    GenQueue<int>* idleTime;

    int numWait;
    int numIdle;
    int time;
    int numWindows;

    //functions to add a window
    void addFull();
    void addFree();
};

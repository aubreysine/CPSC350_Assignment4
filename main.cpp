#include "Simulation.h"

int main(int argc, char const *argv[]) {
  //Checks for command line parameter
  if( argc < 2){
    cout << "Invalid command line parameters" << endl;
    return 1;
  }

  //ifstream class to read in a file
  ifstream inFS;
  //open the test text file to simulate the regisitrar
  inFS.open(argv[1]);

  if(!inFS.is_open()){
    cout << "Could Not open file" << endl;
    return 1;
  }
  Simulation *mySim = new Simulation(inFS);

  mySim->start();
  mySim->displayMetrics();

  delete mySim;
  return 0;
}

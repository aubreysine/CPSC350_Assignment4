#include "Student.h"

//default constructor
Student::Student(){
  m_arrivalTime = 0;
  m_windowTime = 0;
}
//overloaded constructor
Student::Student(int arrivalTime, int windowTime){
  m_arrivalTime = arrivalTime;
  m_windowTime = windowTime;
}
//destructor
Student::~Student(){}

//get arrival time
int Student::getArrivalTime(){
  return m_arrivalTime;
}
//function to get window time
int Student::getWindowTime(){
  return m_windowTime;
}

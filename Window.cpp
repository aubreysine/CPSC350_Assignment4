#include "Window.h"
//default
Window::Window(){
  m_timeFree = 0;
  m_timeArrived = 0;
}
//destructor
Window::~Window(){

}
//function to get the free times of the window
int Window::getTimeFree(){
  return m_timeFree;
}
//set free time
void Window::setTimeFree(int timeFree){
  m_timeFree = timeFree;
}
//get the time that the student arrived to the window
int Window::getTimeArrived(){
  return m_timeArrived;
}
//set the arrived time so we can keep track of the metrics
void Window::setTimeArrived(int timeArrived){
  m_timeArrived = timeArrived;
}

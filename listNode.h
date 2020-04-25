#include <iostream>

using namespace std;
template<class T>
class ListNode{
  public:
    T data;
    ListNode *next;
    ListNode *prev;
//default
    ListNode(){
      next = NULL;
      prev = NULL;
    }
//overloaded
    ListNode(T d){
      data = d;
      next = NULL;
      prev = NULL;
    }
//destructor
    ~ListNode(){};
};

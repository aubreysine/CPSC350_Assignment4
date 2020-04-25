#include "DoublyLinkedList.h"

template<class T>
class GenQueue{
  public:
    GenQueue(){
      myQueue = new DoublyLinkedList<T>();
    }

    ~GenQueue(){
      delete myQueue;
    }

    //Inserts Node in the back of Queue
    void insert(T d){
      myQueue->insertBack(d);
    }

    //Removes first element of Queue
    T remove(){
      myQueue->removeFront();
    }

    //Returns top node
    T peek(){
      return myQueue->getFront();
    }

    //Returns whether Queue is empty or not
    bool isEmpty(){
      return myQueue->isEmpty();
    }

    //Returns size of Queue
    int getSize(){
      return myQueue->getSize();
    }

    DoublyLinkedList<T> *myQueue; //memory adress of the first block
};

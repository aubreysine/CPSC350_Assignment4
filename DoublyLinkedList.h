#include "ListNode.h"

template <class T>
class DoublyLinkedList{
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;
  public:
    DoublyLinkedList(){
      size = 0;
      front = NULL;
      back = NULL;
    }

    ~DoublyLinkedList(){
      if(!isEmpty()){
        //iterates through list until empty and deletes nodes
        while(front->next != NULL){
          front->next->prev = NULL;

          ListNode<T> *temp = front;
          front = front->next;
          delete temp;
          size--;
        }
        delete front;
      }
    }

    //Inserts node to front of list
    void insertFront(T d){
      ListNode<T> *node = new ListNode<T>(d);

      if(isEmpty()){
        back = node;
      } else{
        front->prev = node;
        node->next = front;
      }
      front = node;
      size++;
    }

    //Inserts node to back of list
    void insertBack(T d){
      ListNode<T> *node = new ListNode<T>(d);

      if(isEmpty()){
        front = node;
      } else{
        back->next = node;
        node->prev = back;
      }
      back = node;
      size++;
    }

    //insert at postition-> search list until position is found and insert data
    void insertAtPos(T d, int pos){
      if(pos >= size){
        cout << "Error: Position " << pos << " exceeds list size of " << size << endl;
        return;
      }

      ListNode<T> *node = new ListNode<T>(d);
      ListNode<T> *curr = front;
      int idx = 0;

      while(idx != pos){
        curr = curr->next;
        idx++;
      }

      node->prev = curr->prev;
      curr->prev->next = node;
      curr->prev = node;
      node->next = curr;
    }

    //Removes front node
    T removeFront(){
      ListNode<T> *tempNode = front;

      if(front->next == NULL){
        //There is only one node in the List
        back = NULL;
      } else{
        //More than one node in the List
        front->next->prev = NULL;
      }

      front = front->next;
      tempNode->next = NULL;
      T temp = tempNode->data;
      delete tempNode;
      size--;

      return temp;
    }

    //Removes back node
    T removeBack(){
      ListNode<T> *tempNode = back;
      if(back->prev == NULL){
        front = NULL;
      } else{
        back->prev->next = NULL;
      }

      back = back->prev;
      tempNode->prev = NULL;
      T temp = tempNode->data;
      delete tempNode;
      size--;

      return temp;
    }

    //Searches list until value is found and removes the node
    T remove(T val){
      ListNode<T> *curr = front;

      while(curr->data !=val){
        curr = curr->next;
        if(curr == NULL)
          return -1; //if it doesn't find it in list
      }

      if(curr == front){
        front = curr ->next;
      }
      else{
        curr->prev->next = curr->next;
      }

      if(curr == back){
        back = curr->prev;
      }else{
        curr->next->prev = curr->prev;
      }

      curr->next = NULL;
      curr->prev = NULL;
      T temp = curr->data;
      size--;
      delete curr;

      return temp;
    }

    //Removes node at specified position
    T removeAtPos(int pos){
      if(isEmpty()){
        cout << "Error: list is empty" << endl;
        return NULL;
      } else if(pos >= size){
        cout << "Error: Position " << pos << " exceeds list size of " << size << endl;
        return NULL;
      }

      int idx = 0;
      ListNode<T> *curr = front;
      ListNode<T> *prev = front;

      while(idx != pos){
        prev = curr;
        curr = curr->next;
        idx++;
      }

      if(curr == front){
        front = curr->next;
      }
      else{
        curr->prev->next = curr->next;
      }

      if(curr == back){
        back = curr->prev;
      }else{
        curr->next->prev = curr->prev;
      }

      curr->next = NULL;
      curr->prev = NULL;
      T temp = curr->data;
      size--;
      delete curr;

      return temp;
    }

    //Searches list until node is found and returns position
    int search(T val){
      int pos = -1;
      ListNode<T> *curr = front;

      while(curr != NULL){
        ++pos;
        if(curr->data == val){
          break;
        }
        else{
          curr = curr->next;
        }
      }

      if(curr == NULL){
        pos =-1;
      }

      return pos;
    }

    //Returns first node
    T getFront(){
        return front->data;
    }

    //Searches a position of the list and then returns the value at that position
    T getData(int pos){
      int idx = 0;
      ListNode<T> *curr = front;

      while(idx != pos){
        curr = curr->next;
        idx++;
      }

      return curr->data;
    }

    //returns size of doubly linked list
    unsigned int getSize(){
      return size;
    }

    //Returns whether doubly linked list is empty or not
    bool isEmpty(){
      return (size == 0);
    }

    //function to print out the list
    void printList(){
      ListNode<T> *curr = front;

      while(curr != NULL){
        cout << curr->data<< endl;
        curr = curr ->next;
      }
    }
};

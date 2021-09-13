//HW1 Andrew Boyce
//SU Net ID: 209721818 (amboyce)

//CIS554 HW1  Due: March 1 (Monday) at 11:59pm.
//All operations have to be directly performed on the DoublyLinkedList.
//You are not allowed to copy the node values to external structures, perform operations
//on the external structures, and copy the results back to the DoublyLinedList.

/*
Assignment completed by Andrew Boyce (amboyce)
*/

#include <iostream>
using namespace std;

class node{
public:
 int value;
 node *next;
 node *previous;

 node(int i){
  value = i;
  next = previous = nullptr;
 }
 node() { next = previous = nullptr; }
};

class DoublyLinkedList{
public:
 node *head;
 node *tail;
 //constructor
 DoublyLinkedList() { head = tail = nullptr; }
 DoublyLinkedList(int n, int m);
 void print_f();
 void print_r();
 DoublyLinkedList(const initializer_list<int> &I);
 void reverse();
 void sort();   
 void remove_all(int k); 
};

/*
    This function removes all nodes with k as a value.
    
    Case 1: If the head has a value of k, then the head is assigned to the next 
    node. Then the pointer to the head's previous reference is assigned to 
    nullptr.
    
    Case 2: This function finds the node to remove, modifies pointers to the 
    node before and after itself to change references. The pointer before the 
    node will point two nodes ahead of itself (next next). Then the node after 
    the node that we will be removing will have its previous reference changed
    to two nodes previous (previous previous).
    
    Case 3: If the node is the tail, then the previous node is assigned as tail,
    Then the tails next refernce will point to nullptr.
*/
void DoublyLinkedList::remove_all(int k){ 
 if (!head) return;
 node* p1{ head };
 if (head->value == k) { 
  head = head->next; 
  head->previous = nullptr; 
  }
 node* p2 = head->next;
 while (p2) {
  if(p2->next == nullptr && p2->value == k){
   tail = tail->previous;
   tail->next = nullptr;
   return;
  }
  else if (p2->value == k) {
   p2->next->previous = p1;
   p1->next = p2->next;
  }
  p1 = p2;
  p2 = p2->next;
 }
}

/*
    This function sorts the DoublyLinkedList in ascending order and
    then the head and tail are reset at the end of the function.
*/
void DoublyLinkedList::sort(){
 if (!head || !head->next) return;
 node* p1{ head };
 while (p1) {
  node* p2{ p1->next };
  node* pmin{ p1 };
  int min{ p1->value };
  while (p2) {
   if (p2->value < min) {
    min = p2->value;
    pmin = p2;
   }
   p2 = p2->next;
  }
  
  if (p1->next == pmin){
   p1->next = pmin->next;
   pmin->previous = p1->previous;

   if (p1->next != nullptr)
    p1->next->previous = p1;
   if (pmin->previous != nullptr)
    pmin->previous->next = pmin;

   pmin->next = p1;
   p1->previous = pmin;
  }
  else{
   node* pminp = pmin->previous;
   node* pminn = pmin->next;

   pmin->previous = p1->previous;
   pmin->next = p1->next;
   p1->previous = pminp;
   p1->next = pminn;

   if (pmin->next != nullptr)
    pmin->next->previous = pmin;
   if (pmin->previous != nullptr)
    pmin->previous->next = pmin;

   if (p1->next != nullptr)
    p1->next->previous = p1;
   if (p1->previous != nullptr)
    p1->previous->next = p1;
  }

  p1 = pmin;
  p1 = p1->next;
 }
 
 //This is where the tail is reset after the sort.
 node* temp {head};
 while(temp->next != nullptr) 
     temp = temp->next;
 tail = temp;
 
 //This resets the head after the sort.
 node* temp2 {tail};
 while(temp2->previous != nullptr) 
     temp2 = temp2->previous;
 head = temp2;
}

/*
    This function reverses the DoublyLinkedList. 
    This function starts from the head and swaps each node to reverse 
    the order. This uses two pointers and swaps the two nodes until it 
    reaches the end of iteration.
*/
void DoublyLinkedList::reverse(){
 node *p1 = head;
 while (p1 != NULL) {
     node *p2 = p1->next;
     p1->next = p1->previous;
     p1->previous = p2;
     if (p2 == NULL) {
         tail = head;
         head = p1;
     }
     p1 = p2;
 }
}

/*
    This function is a constructor for a DoublyLinkedList.
    This constructor takes in an int n, being the size of the node,
    and an int m, which is used to detemine a value for a node, being a random
    int from 1...m using the rand() function and modding it with m.
*/
DoublyLinkedList::DoublyLinkedList(int n, int m){
 head = tail = nullptr;
 for (int i = 0; i < n; ++i) {
  node* p1 = new node(rand() % m);
  if (i==0) 
   head = tail = p1;
  else{
   head->previous = p1;
   p1->next = head;
   head = p1;
  }
 }
}

/*
    This is another constructor for a DoublyLinkedList.
    This constructor takes in an initializer_list of int's and creates
    a DoublyLinkedList out of the values.
*/
DoublyLinkedList::DoublyLinkedList(const initializer_list<int> &I) : DoublyLinkedList(){
 auto p1{ I.end() - 1 };
 for (size_t i = 0; i < I.size(); ++i) {
  node* p2 = new node(*p1);
  if (i==0) 
   head = tail = p2;
  else{
   p2->next = head;
   head->previous = p2;
   p2->next = head;
   head = p2;
  }
  p1--;
 }
}

/*
    This function prints a DoublyLinkedList forward. 
    Starting at the head, each node's value is printed one at a time by 
    iterating forward.
*/
void DoublyLinkedList::print_f(){ 
 if (!head && !tail)
  cout << "This node is empty." << "";
 else if (!head->next)
  cout << head->value << "";
 else{
  node *p {head};
  cout << p->value << " ";
  while(p=p->next)
   cout << p->value << " ";
 }
 cout << endl;
}

/*
    This function prints a DoublyLinkedList in reverse. 
    Starting at the tail, each node's value is printed one at a time by 
    iterating backwards through the DoublyLinkedList.
*/
void DoublyLinkedList::print_r(){
 if (!head && !tail)
  cout << "This node is empty" << "";
 else if (head == tail)
  cout << head->value << "";
 else{
  node *p {tail};
  cout << p->value << " ";
  while(p=p->previous)
   cout << p->value << " ";
 }
 cout << endl;
}

int main() {
 DoublyLinkedList L1(20, 10);
 L1.print_f();
 L1.print_r();
 L1.reverse();
 L1.print_f();
 L1.print_r();
 L1.remove_all(7);
 L1.print_f();
 L1.print_r();
 L1.sort();
 L1.print_f();
 L1.print_r();

 DoublyLinkedList L2{ 4,5,6,7,8 };//Declare and call initializer_list
 L2.print_f();//4 5 6 7 8
 L2.print_r();

 return 0;
}

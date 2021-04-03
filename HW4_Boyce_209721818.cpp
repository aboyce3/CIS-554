#include <iostream>
#include <vector>
//#include <list>
//#include <string>

using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() :ht(0), wid(0), dep(0) {}
	ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
	T getVol() const { return ht * wid * dep; }
	bool operator==(const ThreeD<T>& t) { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
	T value;
	node<T>* next;
	node<T>* previous;
	node<T>() { next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
	bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <class T> class linked_list {
public:
	node<T>* head;
	node<T>* tail;
	linked_list() { head = tail = nullptr; }
	linked_list(const initializer_list<T>& V);
	void push_front(T t);
	void push_back(T t);
	bool operator==(const linked_list<T>& L) const;

	linked_list(const linked_list<T>& L); //copy constructor
	linked_list(linked_list<T>&& L); //move constructor
	~linked_list();//destructor
	void operator=(const linked_list<T>& L);//L-value operator=; copy assignment
	void operator=(linked_list<T>&& L);//R-value operator= ; move assignment
	template <class T> friend ostream& operator<<(ostream& str, const linked_list<T>& L);
};

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L);

template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
	for(int i = 0; i < V.size; ++i){
        if(i == 0){
            head = tail = new node();
        }
    }
	cout << "initializer_list LL" << endl;
}

template <class T> linked_list<T>::~linked_list() {  //destructor										
	node* current = head;
    node* next;

    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
	cout << "Destructor LL" << endl;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
	//Your code
	cout << "Copy Constructor LL" << endl;
}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
	//Your code
	cout << "Move Constructor LL" << endl;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //Lvalue operator=
//Your code
	cout << "Copy Assignment LL" << endl;

}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
	//Your code
	cout << "Move Assignment LL" << endl;
}


template <class T> void linked_list<T>::push_front(T t) {
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }
	else {
		p->next = head;
		head->previous = p;
		head = p;
	}
}

template <class T> void linked_list<T>::push_back(T t)
{
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }

	else {
		p->previous = tail;
		tail->next = p;
		tail = p;
	}
}

template <class T> bool linked_list<T>::operator==(const linked_list<T>& L) const {
//Your code
}

template <class X> class NODE {
public:
	X value;
	NODE<X>* l_child;
	NODE<X>* r_child;
	NODE<X>* next;
	NODE<X>() : l_child(nullptr), r_child(nullptr), next(nullptr) {}
	NODE<X>(X t) : l_child(nullptr), r_child(nullptr), next(nullptr), value(t) {}
};

template <class X> class Triangle {
public:
	NODE<X>* head;
	Triangle() : head(nullptr) {};
	Triangle(const initializer_list<initializer_list<X>>& I);//initializer_list
	~Triangle();// {};//destructor
	Triangle(const Triangle<X>& T); //copy constructor
	void operator=(const Triangle<X>& T); //copy assignment (Lvalue assignment)
	Triangle<X> ThreeTimes(); //ThreeTimes
	Triangle(Triangle<X>&& T);//move constructor
	void operator=(Triangle<X>&& T);//move assignment (Rvalue assignment)
	bool operator==(const Triangle<X>& T);
};

template <class X> bool Triangle<X>::operator==(const Triangle<X>& T) {
	//Your code

}


template <class X> void Triangle<X>::operator=(Triangle<X>&& T) {//Move assignment (Rvalue assignment)
	//Your code

	cout << "Move Assignment Triangle" << endl;
}

template <class X> Triangle<X>::Triangle(Triangle<X>&& T) {//move constructor
	//Your code
	cout << "Move Constructor Triangle" << endl;

}

template <class X> Triangle<X> Triangle<X>::ThreeTimes() {//ThreeTimes
	//Your code
	cout << "ThreeTimes Triangle" << endl;

}

template <class X> Triangle<X>::~Triangle() {// {};//destructor
	//Your code

	cout << "Destructor Triangle" << endl;

}
template <class X> void Triangle<X>::operator=(const Triangle<X>& T) {//copy assignment
	//Your code
	cout << "Copy Constructor Triangle" << endl;

}

template <class X> Triangle<X>::Triangle(const initializer_list<initializer_list<X>>& I) {
	//Your code
	cout << "initializer_list Triangle" << endl;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);


template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L);



template <class X> ostream& operator<<(ostream& str, const Triangle<X>& T);

int main() {


	Triangle<int> T1{ {1},  {2,3},  {4, 5, 6}, {7,8, 9, 10} };//initializer_list
	cout << T1 << endl;
	Triangle<int> T2{ T1 };
	cout << T2 << endl;

	Triangle<int> T3;
	T3 = T1;
	cout << T3 << endl;

	Triangle<int> T4;
	T4 = T1.ThreeTimes();
	cout << T4 << endl;

	Triangle<linked_list<ThreeD<int>>> T5{ {{{3,4,5},{7,1,4},{6,7,3}}}, {{ {5,4,8 },{4,2,16  }, {7, 8, 4} } ,{ { {8,2,4},{8,4,4}}} } };

	////};
	cout << T5 << endl;

	Triangle<linked_list<ThreeD<int>>>  T6{ {{{3,5,4},{7,2,2},{6,7,3}}}, {{ {5,2,16 },{4,1,32  }, {7, 8, 4} } ,{ { {4,4,4},{4,8,4}}} } };

	cout << T6 << endl;

	if (T5 == T6) cout << "EQUAL" << endl;
	else cout << "NOT EQUQL" << endl;

	Triangle<linked_list<ThreeD<int>>>* p1 = new Triangle<linked_list<ThreeD<int>>>
	{ {{{3,4,5},{7,1,4},{6,7,3}}}, {{ {5,4,8 },{4,2,16  }, {7, 8, 4} } ,{ { {8,2,4},{8,4,4}}} } };
	cout << *p1 << endl;
	delete p1;
	return 0;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
//Your code
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
	//Your code
}


template <class X> ostream& operator<<(ostream& str, const Triangle<X>& T) {
	//Your code


}


//HW5 Due: April 21 (Wednesday) at 11:59PM
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class node {
public:
	shared_ptr<node> east;
	weak_ptr<node> south;
	int value;
	node() {}
	node(int i) { value = i; }
};

class ring {
public:
	//Implement all functions described below

	shared_ptr<node> head;
	int num_rows;
	int num_cols;
	ring(){}
	ring(int r, int c, int k);//constructor
					   //i rows and j cols
					   //values randomly in 0 ..k-1


	~ring();//destructor; do as little work as possible
	ring(const ring &r); //copy constructor
	ring(ring &&r); //move constructor
	void operator=(ring &&r);//Rvalue operator= , i.e., Move Assignment
	void operator=(const ring &r); //Lvalue operator= , i.e., Copy Assignment
	ring(const initializer_list< initializer_list<int>> &V);
	void DelCol(int i);//delete col i of *this ; col number starts at 0
	void DelRow(int i); //delete rowl i of *this  ; row number starts at 0
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.

};

//Constructor for a ring using an initilizer list with a vector containing the first node of each row.
ring::ring(const initializer_list< initializer_list<int>> &V){
	vector<shared_ptr<node>> vi;
	num_cols = V.begin()->size();
	num_rows = V.size();
	int counter = 0;

	//initialize the vector of nodes and set the head
	for(auto & i : V)
		vi.push_back(*new shared_ptr<node>(new node));
	head = vi[0];

	//Configure all of the east pointers
	for(auto & i : V){
		auto p1 = vi[counter];
		int innerCount = 0;
		for(auto & j : i){
			p1->value = j;
			if(innerCount < num_cols-1) {
				p1->east = *new shared_ptr<node>(new node);
				p1 = p1->east;
			}else{
				if(counter == num_rows-1) p1->east = vi[0];
				else p1->east = vi[counter+1];
				p1 = p1->east;
			}
			++innerCount;
		}
		++counter;
	}

	//Configure the south pointers.
	for(int i = 0; i < num_rows; ++i){
		shared_ptr<node> wp1 = vi[i];
		shared_ptr<node> wp2;
		if(i == num_rows-1) wp2 = vi[0]->east;
		else wp2 =  vi[i+1];
		for(int j = 0; j < num_cols; ++j){
			if(j == num_cols-1 && i == num_rows-1){
				wp1->south = head;
			} else{
				wp1->south = wp2;
				wp1 = wp1->east;
				wp2 = wp2->east;
			}
		}
	}
}

ring ring::Threetimes(){
	ring r = *this;
	auto p1 = r.head;
	do{
		p1->value = p1->value * 3;
		p1 = p1->east;
	}while(p1 != r.head);
	cout << "TheeTimes" << endl;
	return r;
}

//Copy Assignment with vector of first element in each row.
void ring::operator=(const ring &r){
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	shared_ptr<node> p1;
	auto p2 = r.head;
	vector<shared_ptr<node>> vi;
	for(int i = 0; i < num_rows; ++i)
		vi.push_back(*new shared_ptr<node>(new node));
	head = vi[0];
	for(int i = 0; i < num_rows; ++i){
		p1 = vi[i];
		for(int j = 0; j < num_cols; ++j){
			if(j != num_cols-1){
				p1->value = p2->value;
				p1->east = *new shared_ptr<node>(new node);
				p1 = p1->east;
				p2 = p2->east;
			} else if(i == num_rows-1 && j == num_cols-1){
				p1->value = p2->value;
				p1->east = vi[0];
				p2 = p2->east;
			} else{
				p1->value = p2->value;
				p1->east = vi[i+1];
				p2 = p2->east;
			}
		}
	}

	//This is where I set the south (weak pointers) of each node
	for(int i = 0; i < num_rows; ++i){
		shared_ptr<node> wp1 = vi[i];
		shared_ptr<node> wp2;
		if(i == num_rows-1) wp2 = vi[0]->east;
		else wp2 =  vi[i+1];
		for(int j = 0; j < num_cols; ++j){
			if(j == num_cols-1 && i == num_rows-1){
				wp1->south = head;
			} else{
				wp1->south = wp2;
				wp1 = wp1->east;
				wp2 = wp2->east;
			}
		}
	}
	cout << "Copy Assignment" << endl ;
}

//Copy constructor
ring::ring(const ring &r){
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	shared_ptr<node> p1;
	auto p2 = r.head;
	vector<shared_ptr<node>> vi;
	for(int i = 0; i < num_rows; ++i)
		vi.push_back(*new shared_ptr<node>(new node));
	head = vi[0];
	for(int i = 0; i < num_rows; ++i){
		p1 = vi[i];
		for(int j = 0; j < num_cols; ++j){
			if(j != num_cols-1){
				p1->value = p2->value;
				p1->east = *new shared_ptr<node>(new node);
				p1 = p1->east;
				p2 = p2->east;
			} else if(i == num_rows-1 && j == num_cols-1){
				p1->value = p2->value;
				p1->east = vi[0];
				p2 = p2->east;
			} else{
				p1->value = p2->value;
				p1->east = vi[i+1];
				p2 = p2->east;
			}
		}
	}

	//This is where I set the south (weak pointers) of each node
	for(int i = 0; i < num_rows; ++i){
		shared_ptr<node> wp1 = vi[i];
		shared_ptr<node> wp2;
		if(i == num_rows-1) wp2 = vi[0]->east;
		else wp2 =  vi[i+1];
		for(int j = 0; j < num_cols; ++j){
			if(j == num_cols-1 && i == num_rows-1){
				wp1->south = head;
			} else{
				wp1->south = wp2;
				wp1 = wp1->east;
				wp2 = wp2->east;
			}
		}
	}
	cout << "Copy Constructor" << endl;
}

/*
In this function I used a vector for the starting node of each row. 
For example in the case of:

1 2 3 
4 5 6
7 8 9

The node with the value of 1 is the head and the nodes being stored in the vector are 1, 4, and 7.
*/
ring::ring(int r, int c, int k){
	if(r == 1 && c == 1){
		num_cols = c;
		num_rows = r;
		head = *new shared_ptr<node>(new node(rand() % k));
		head->east = head;
		head->south = head;
		return;
	} else if((r == 1 && c > 1) || (c == 1 & r > 1)){
		num_cols = c;
		num_rows = r;
		head = *new shared_ptr<node>(new node(rand() % k));
		shared_ptr<node> p1 = head;
		for(int i = 0; i < num_cols; ++i){
			if(i != num_cols-1){
				p1->east = *new shared_ptr<node>(new node(rand() % k));
				p1->south = p1->east;
			}else{
				p1->south = head;
				p1->east = head;
			}
		}
		return;
	}
    head = *new shared_ptr<node>(new node(rand() % k));
    num_cols = c;
    num_rows = r;
  	vector<shared_ptr<node>> startPositions;
	startPositions.push_back(head);
	for(int i = 0; i < num_rows-1; ++i){
		shared_ptr<node> p1 = *new shared_ptr<node>(new node(rand() % k));
		startPositions.push_back(p1);
	}
	shared_ptr<node> p1;
	for(int i = 0; i < num_rows; i++){
		for(int j = 0; j < num_cols; ++j){
			if(j == 0){
				if(i == 0) p1 = startPositions[i];
				p1->east = *new shared_ptr<node>(new node(rand() % k));
				p1 = p1->east;
			} else if(j != num_cols -1){
				p1->east = *new shared_ptr<node>(new node(rand() % k));
				p1 = p1->east;
			} else if(i == num_rows -1 && j == num_cols-1){
				p1->east = head;
			} else{
				p1->east = startPositions[i+1];
				p1 = p1->east;
			}
		}
	}

	//This is where I set the south (weak pointers) of each node
	for(int i = 0; i < num_rows; ++i){
		shared_ptr<node> wp1 = startPositions[i];
		shared_ptr<node> wp2;
		if(i == num_rows-1) wp2 = startPositions[0]->east;
		else wp2 =  startPositions[i+1];
		for(int j = 0; j < num_cols; ++j){
			if(j == num_cols-1 && i == num_rows-1){
				wp1->south = head;
			} else{
				wp1->south = wp2;
				wp1 = wp1->east;
				wp2 = wp2->east;
			}
		}
	}
}

/*
Delete a column and use a vector to keep track of the first node in each row. This also takes into account the base case of:

0 . . . n
.
.
.
n

The extra smart pointers are then deleted. A vector is also used to keep track of the first element of each row.
We also lock() the weak pointer that points to a new column so that we don't mistakingly delete nodes that shouldn't 
be deleted.
*/
void ring::DelCol(int i){
	//Base Case
	if(i >= num_cols || i < 0) return;
	if(!head) return;
	if(num_cols == 1){
		this->~ring();
		num_cols -= 1;
		return;
	} else if(num_rows == 1 && num_cols > 1 && i == 0){
		auto p1 = head;
		for(int k = 0; k < num_cols; ++k){
			p1 = p1->east;
		}
		head = head->east;
		p1->south = head;
		p1->east = head;
		num_cols -= 1;
		return;
	} else if(num_rows == 1 && num_cols > 1){
		auto p1 = head;
		for(int j = 0; j < i; ++j){
			p1 = p1->east;
		}
		p1->east = p1->east->east;
		p1->south = p1->east;
		num_cols -= 1;
		return;
	}
	//End base cases, begin adding first value of each row to vector.
	vector<shared_ptr<node>> vi;
	auto p1 = head;
	vi.push_back(p1);
	for(int j = 0; j < num_rows-1; ++j){
			p1 = p1->south.lock();
			vi.push_back(p1);
	}	
	//If we are deleteing a column which involves the head then we manipulate the pointers to isolate the column.
	if(i == 0){
		for(int k = 0; k < num_rows; ++k){
			auto p2 = vi[k];
			for(int j = 0; j < num_cols; ++j){
				if(k == num_rows-1 && j == num_cols-1){
					head = head->east;
					p2->east = head;
					p2->south = head;
				} else if(j == num_cols-1)
					p2->east = p2->east->east;
				p2 = p2->east;
			}
		}
		num_cols -= 1;

	//If we are deleting a column that doesn't involve the head being deleted.
	} else {
		for(int k = 0; k < num_rows; ++k){
			auto p2 = vi[k];
			for(int j = 0; j < i; ++j){
				if(j == i-1 && k == num_rows-1){
					p2->east = p2->east->east;
					p2->south = p2->south.lock()->east;
				}else if(j == i-1) 
					p2->east = p2->east->east;
				p2 = p2->east;
			}
		}
		num_cols -= 1;
	}
}

//Delete a row and use a vector to keep track of the first node in each row.
void ring::DelRow(int i){
	if(i >= num_rows || i < 0) return;
	if(!head) return;
	if(num_rows == 1){
		this->~ring();
		num_rows -= 1;
		return;
	} else if(num_rows > 1 && num_cols == 1 && i == 0){
		auto p1 = head;
		while(p1->east != head)
			p1 = p1->east;
		p1->east = p1->east->east;
		p1->south = p1->east;
		head = head->east;
		num_rows-=1;
		return;
	} else if(num_rows > 1 && num_cols == 1){
		auto p1 = head;
		for(int j = 0; j < i-1; ++j)
			p1 = p1->east;
		p1->east = p1->east->east;
		p1->south = p1->east;
		num_rows -= 1;
		return;
	}
	//End base cases and create vector of the first node for each row.
	vector<shared_ptr<node>> vi;
	auto p1 = head;
	vi.push_back(p1);
	for(int j = 0; j < num_rows-1; ++j){
		for(int k = 0; k < num_cols; ++k){
			p1 = p1->south.lock();
			vi.push_back(p1);
		}
	}
	//If i is the head.
	if(i == 0){
		auto p2 = vi[num_rows-1];
		auto p3 = vi[1]->east;
		for(int j = 0; j < num_cols; ++j){
			if(j == num_cols-1){
				p2->south = vi[1];
				p2->east = vi[1];
				head = vi[1];
			}else{
				p2->south = p3;
				p2 = p2->east;
				p3 = p3->east;
			}
		}
		num_rows -= 1;
	//If i isn't the head.
	} else {
			auto p2 = vi[i-1];
			auto p3 = vi[i];
			for(int j = 0; j < num_cols; ++j
			){
				if(j == num_cols-1){
					p2->south = p3->south;
					p2->east = p3->east;
				}else {
					p2->south = p3->south;
					p3 = p3->east;
					p2 = p2->east;
				}
			}
		num_rows -= 1;
	}
}

/*
Destructor resets the east and south smart pointers and then resets itself.
*/
ring::~ring(){
    if(head){
		head->east.reset();
		head->south.reset();
		head.reset(); 
	}

	cout << "Destructor" << endl;
} 

//Move constructor for ring. 
ring::ring(ring &&r){
    head = r.head;
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    r.head.reset();
	cout << "Move Constructor" << endl;
}

void ring::operator=(ring &&r){
    head = r.head;
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    r.head.reset();
	cout << "Move Assignment" << endl;
}

ostream& operator<<(ostream& os, const ring& r){
	auto p1 = r.head;
	os << endl;
	for(int i = 0; i < r.num_rows; ++i){
		for(int j = 0; j < r.num_cols; ++j){
			if(p1->value >= 10) os << p1->value << " ";
			else os <<  p1->value << "  ";
			p1 = p1->east;
		}
		os << endl;
	}
    return os;
}


int main() {

	ring R1(4, 6, 20);
	cout << R1 << endl;
	R1.DelCol(3);
	cout << R1 << endl;
	R1.DelCol(4);
	cout << R1 << endl;
	R1.DelCol(0);
	cout << R1 << endl;

	ring R2(5, 7, 20);
	cout << R2 << endl;
	R2.DelRow(3);
	cout << R2 << endl;
	R2.DelRow(3);
	cout << R2 << endl;
	R2.DelRow(0);
	cout << R2 << endl;

	shared_ptr<ring> p1 = make_shared<ring>(3, 5, 10);
	cout << *p1 << endl;
	p1.reset();

	ring R3 = { {10,20,30,40,50} , {100, 200, 300, 400, 500}, {1000, 2000, 3000, 4000, 5000} };//
	cout << R3 << endl;
	ring R4(R3);
	cout << R4 << endl;
	ring R5;
	R5 = R3;
	cout << R5 << endl;
	ring R6;
	R6 = R5.Threetimes();
	cout << R6 << endl;

	return 0;
}
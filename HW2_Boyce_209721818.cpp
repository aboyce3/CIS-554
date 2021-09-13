//HW1 by Andrew Boyce
//SUID: 209721818

//HW2 Due: March 11, Thursday, at 11:59pm
//Implement three member functions of class Tree: 
//mirrorCopy, minHeap, and sort.

#include <iostream>
#include <string>
#include <list>
using namespace std;
//int m = 50;
class Node {
public:
	int value;
	Node* l_child;
	Node* r_child;
	Node() : l_child(nullptr), r_child(nullptr) {}
	Node(int i) :value(i), l_child(nullptr), r_child(nullptr) {}

};



class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
	Node* root;
	Tree() : root(nullptr) {}
	Node* makeTree(int n, int m);
	void printTree1(Node* p); //in-order printing
	void printTree2(Node* p); //pre-order printing
	void printTree3(Node* p); //post-order printing
	void mirror(Node* p);
	int sum(Node* p);

	/*
	HW2: Implement the following three member functions.
	*/

	Node* mirrorCopy(Node* p);//5 points
	//Create an external mirror copy of a tree rooted at a node pointed by p
	//and return a pointer pointing to the root of this external tree.
	//Note that the function will not change the original tree.
	//You are required to implement this function with recursion.


	void minHeap(Node* p);//8 points
	//Recall that in a Min Heap, at all nodes, 
	//value(parent)<= value(l_child) and value(parent) <= value(r_child).
	//This function re-structures the tree, whose root is pointed by p, into a Min Heap.
	//You are required to use recursion.

	pair<Node*, Node* >  sort(Node* p);//22 points
	//sorting such that
	//ascending sequence in pre-order traversal
	//This function returns a pair of pointers,  which point to the node with the smallest
	//value and the node with the largest values in the tree rooted at node pointed by p.
	//printTree2 will give a sorted sequence.
	//You are required to use recursion, but additional while loop is allowed.

	Node* Tree_initalizer(const initializer_list<int> &I);
	
	Tree(const initializer_list<int> &L);

	bool checkHeap(Node *p);
};

Tree::Tree(const initializer_list<int> &L) {
	root = Tree_initalizer(L);
}

Node* Tree::Tree_initalizer(const initializer_list<int> &I) {
	list<Node*> v{};
	auto p{ I.begin() };
	Node* head = new Node(*p); p++;
	v.push_back(head);
	while (p != I.end()) {
		size_t size{ v.size() };
		for (int i = 0; i < size; i++) {
			Node* tmp = v.front();
			v.pop_front();
			tmp->l_child = new Node(*p); p++;
			tmp->r_child = new Node(*p); p++;
			v.push_back(tmp->l_child);
			v.push_back(tmp->r_child);
		}
	}
	return head;
}

bool Tree::checkHeap(Node *p) {
    if(!p || (!p->l_child && !p->r_child)){
        return true;
    }
    bool r = (p->value <= p->l_child->value) && (p->value <= p->r_child->value);
    bool lr = checkHeap(p->l_child);
    bool rr = checkHeap(p->r_child);
    return r && lr && rr;
}



Node* Tree::mirrorCopy(Node* p) {
	Node* mirrorCopyNode = new Node(p->value);
	if(p->l_child != nullptr)
		mirrorCopyNode->l_child = mirrorCopy(p->l_child);
	if(p->r_child != nullptr)
	    mirrorCopyNode->r_child = mirrorCopy(p->r_child);
	return mirrorCopyNode;
}

void Tree::minHeap(Node* p) {
	if (p == nullptr) return;
	minHeap(p->l_child);
	minHeap(p->r_child);
	if(p->l_child != nullptr && p->value > p->l_child->value){
		int temp{p->value};
        p->value = p->l_child->value;
        p->l_child->value = temp;
    }
	if(p->r_child != nullptr && p->value > p->r_child->value){
        int temp{p->value};
        p->value = p->r_child->value;
        p->r_child->value = temp;
    }
}


pair<Node*, Node*>  Tree::sort(Node* p) {
	//Out of bounds check
    if (p == nullptr) return make_pair(nullptr, nullptr);

	//Recursive Step
	pair<Node*, Node*> l = sort(p->l_child);
	pair<Node*, Node*> r = sort(p->r_child);

	//Bottom Leaf (nullptr, nullptr)
	if(!(l.first && l.second))
		return make_pair(p,p);
	if(!(r.first && r.second))
		return make_pair(p,p);
	
	//Middle Nodes (val, val)
	if(p != root){
		if(p->l_child != nullptr && p->value > p->l_child->value){
			int temp{p->value};
        	p->value = p->l_child->value;
        	p->l_child->value = temp;
    	}
		if(p->r_child != nullptr && p->value > p->r_child->value){
        	int temp{p->value};
        	p->value = p->r_child->value;
       	 	p->r_child->value = temp;
    	}
		if(p->r_child != nullptr && p->l_child != nullptr && p->l_child->value > p->r_child->value){
        	int temp{p->l_child->value};
        	p->l_child->value = p->r_child->value;
       	 	p->r_child->value = temp;
    	}
		if(l.second->value > r.first->value){
			int temp{l.second->value};
        	l.second->value = p->r_child->value;
        	p->r_child->value = temp;
			pair<Node*, Node*> l = sort(p);
		}

		int smallest = min(min(l.first->value, l.second->value), min(r.first->value,r.second->value));
		smallest = min(smallest, p->value);
		int largest = max(max(l.first->value, l.second->value), max(r.first->value,r.second->value));
		largest = max(largest, p->value);

		Node * largestNode, * smallestNode;

		if(p->value == smallest)
			smallestNode = p;
		if(l.first->value == smallest)
			smallestNode = l.first;
		if(l.second->value == smallest)
			smallestNode = l.second;
		if(r.first->value == smallest)
			smallestNode = r.first;
		if(r.second->value == smallest)
			smallestNode = r.second;
		if(p->value == largest)
			largestNode = p;
		if(l.first->value == largest)
			largestNode = l.first;
		if(l.second->value == largest)
			largestNode = l.second;
		if(r.first->value == largest)
			largestNode = r.first;
		if(r.second->value == largest)
			largestNode = r.second;

		return make_pair(smallestNode,largestNode);
	}
	//Root node check and possible recursive step again.
	else{
		if(l.second->value > r.first->value){
			int temp{l.second->value};
        	l.second->value = p->r_child->value;
        	p->r_child->value = temp;
			minHeap(p);
			pair<Node*, Node*> l = sort(p);
		}
		if(p->l_child != nullptr && p->value > p->l_child->value){
			int temp{p->value};
        	p->value = p->l_child->value;
        	p->l_child->value = temp;
    	}
		if(p->r_child != nullptr && p->value > p->r_child->value){
        	int temp{p->value};
        	p->value = p->r_child->value;
       	 	p->r_child->value = temp;
    	}
		if(p->r_child != nullptr && p->l_child != nullptr && p->l_child->value > p->r_child->value){
        	int temp{p->l_child->value};
        	p->l_child->value = p->r_child->value;
       	 	p->r_child->value = temp;
    	}
		if(l.second->value > r.first->value){
			int temp{l.second->value};
        	l.second->value = p->r_child->value;
        	p->r_child->value = temp;
			pair<Node*, Node*> l = sort(p);
		}
		Node * max = root->r_child;
    	while(max->r_child != nullptr)
      		max = max->r_child;
    	return make_pair(p,max); 
		} 
}


int Tree::sum(Node* p) {
	if (!p) return 0;
	if (!p->l_child) return p->value;
	return p->value + sum(p->l_child) + sum(p->r_child);
}

void Tree::mirror(Node* p) {
	if (!p || !p->l_child) return;
	mirror(p->l_child);
	mirror(p->r_child);
	swap(p->l_child, p->r_child);
}


Node* Tree::makeTree(int n, int m) { 
	Node* p = new Node(rand() % m);
	if (n == 1) return p;
	p->l_child = makeTree(n - 1, m);
	p->r_child = makeTree(n - 1, m);
	return p;
}

void Tree::printTree1(Node* p) { //in-order printing
	if (p == nullptr) return;
	printTree1(p->l_child);
	cout << p->value << " ";
	printTree1(p->r_child);
}

void Tree::printTree2(Node* p) { //pre-order printing
	if (p == nullptr) return;
	cout << p->value << " ";
	printTree2(p->l_child);
	printTree2(p->r_child);
}

void Tree::printTree3(Node* p) { //post-order printing
	if (p == nullptr) return;
	printTree3(p->l_child);
	printTree3(p->r_child);
	cout << p->value << " ";
}


int main() {
	Tree T1;
	T1.root = T1.Tree_initalizer({100,20,30,5,16,7,12});
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	Tree T2;
	T2.root = T1.mirrorCopy(T1.root);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;
	
	T2.minHeap(T2.root);
	cout << T2.checkHeap(T2.root) << endl;
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;


	
	Tree T3;
	T3.root = T3.makeTree(5, 20);
	T3.sort(T3.root);
	
	T3.printTree1(T3.root);
	cout << endl;
	T3.printTree2(T3.root);
	cout << endl;
	T3.printTree3(T3.root);
	cout << endl;

	return 0;
}
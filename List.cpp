/*Adds functionality to a list
 * List.cpp
 * Lorrayya Williams
 *  Created on: Oct 9, 2018 for CS 112
 *      Author: llw5
 */

#include "List.h"
#include <fstream>
#include <stdexcept>

using namespace std;
List::List(){
	mySize = 0;
	myFirst = NULL;
	myLast = NULL;
}
List::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

List::Node::Node(Item it, Node*next){
	myItem = it;
	myNext = next;

}

//Accessor for Size
unsigned List::getSize() const{
	return mySize;
}

//Accessor for myFirst
Item List::getFirst() const{
	if(mySize < 0 || myFirst == NULL){
		throw underflow_error("There is no First Node!");
	}
	else{
	return myFirst->myItem;
	}
}

//Accessor for myLast
Item List::getLast() const{
	if(mySize < 0 || myFirst == NULL){
			throw underflow_error("There is no First Node!");
		}
		else{
		return myLast->myItem;
		}
}

void List::append(const Item& it){
	 Node *nodePtr= new Node(it, NULL);
	if(myFirst == NULL){
		myFirst = nodePtr;

	}
	else{
		myLast->myNext = nodePtr;
	}
	myLast = nodePtr;
	mySize += 1;
}

List::~List() {
   delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
   myFirst = myLast = NULL; // clear myFirst and myLast (optional)
   mySize = 0;              // clear mySize (optional)
}

List::Node::~Node() {
//	cout << "~Node() is deallocating the node containing item "
//	             << myItem << endl;
    delete myNext;       // delete the next node, invoking ~Node() in it
                      // (does nothing if myNext == NULL)
 }
List::List(const List& original) {
     myFirst = myLast = NULL;       //  set pointers
     mySize = 0;                    //   and size to 'empty' values
     Node* oPtr = original.myFirst; //  start at the first node
     while (oPtr != NULL) {         //  while there are nodes to copy:
        append(oPtr->myItem);       //   append the item in that node
        oPtr = oPtr->myNext;        //   advance to next node
     }
  }
List& List::operator=(const List& original){
if (myFirst != original.myFirst){
	myFirst = myLast = NULL;       //  set pointers
	delete myFirst;
	mySize = 0;                    //   and size to 'empty' values
	     Node* nPtr = original.myFirst; //  start at the first node
	     while (nPtr != NULL) {         //  while there are nodes to copy:
	        append(nPtr->myItem);       //   append the item in that node
	        nPtr = nPtr->myNext;        //   advance to next node
	     }
}
	return *this;
}

bool List::operator!=(const List& original){
	if(mySize == original.mySize){
		return false;
	}

	if(myFirst == original.myFirst) {
		if(myLast == original.myLast){
			Node* nPtr = myFirst;
			Node* nPtr2 = original.myFirst;
			while(nPtr != NULL){
				nPtr->myItem == nPtr2->myItem;
				nPtr = nPtr->myNext;

			}
		}

	}

	else {
		return true;
	}
}

Item List::writeTo(ostream& out, string sep){
	Node *nPtr = myFirst;
	for(unsigned i= 0; i< mySize; i++){
		out << nPtr->myItem
				<< sep;
		nPtr= nPtr->myNext;
	}
	out <<endl;
}

void List::readFrom(const string& fileName) {
	ifstream in(fileName.c_str());
	assert(in.is_open());
	Item it;
	while(!in.eof()){
		in >> it;
		append(it);
	}
	in.close();

}

unsigned List::getIndexOf(unsigned value){
	Node* nPtr = myFirst;
	unsigned index = 0;
	while(nPtr != NULL){
		if(nPtr->myItem == value){
			return index;
		}
		nPtr = nPtr->myNext;
		index += 1;
	}

	throw invalid_argument("That number is not in the list!");


}

Item List::remove(int index) {
	//removes a value from a list at index
	if (mySize == 0) {
		throw range_error("list is empty");
	}

	int intmySize;
	intmySize = mySize; //to get rid of compilation warnings
	Node *bremPtr = myFirst; //before remove
	Node *remPtr = myFirst; //remove
	Item val;

	if (index <= 0) {
		myFirst = remPtr->myNext;
		val = remPtr->myItem;
		mySize -= 1; //decrement size
		remPtr = NULL;
		delete remPtr; //delete node
		return val; //return val at index
	}

	if (index+1 >= intmySize) {
		remPtr = remPtr->myNext; //first increment of remPtr
		for (unsigned i=0; i != mySize-1; ++i) {
			remPtr = remPtr->myNext;
			bremPtr = bremPtr->myNext;
		}
		myLast = bremPtr;
		bremPtr->myNext = remPtr->myNext;
		//updates my last to the ptr before remove
		myLast->myItem = bremPtr->myItem;
		val = remPtr->myItem;
		remPtr = NULL;
		delete remPtr;
		mySize -= 1;
		return val;

	}
	else {
		remPtr = remPtr->myNext; //first increment of remPtr
		for (int i=0; i <= index; i++) {
			if (i == index-1) {
				//before rem idx to ptr after rem idx
				bremPtr->myNext = remPtr->myNext;
				val = remPtr->myItem;
				remPtr = NULL;
				delete remPtr;
				mySize -= 1;
				return val;
			}

			//increment each idx
			remPtr = remPtr->myNext;
			bremPtr = bremPtr->myNext;
		}
	}

	return myFirst->myItem; //returns myFirst if all else fails
}

/*
 * Written by Andrew Baker
 * Tests equality between to lists, returns true or false
 * Param: second List
 * Return: boolean
 */
bool List::operator==(const List& next){
	if (mySize != next.mySize){
		return false;
	}
	Node* oPtr = myFirst;
	Node* nPtr = next.myFirst;
	while(nPtr){
		if(oPtr->myItem != nPtr->myItem){
			return false;
		}
		oPtr = oPtr->myNext;
		nPtr = nPtr->myNext;
	}
	return true;
}

/*
 * Written by Andrew Baker
 * Reads from stream, returns void
 * Param: stream type
 * Return: Void
 */
void List::readFrom(istream& in) {
	Item it;
	while(in.peek() != '\n'){
		in >> it;
		append(it);

	}
}

/*
 * Written by Andrew Baker
 * Writes the contents of a list in to a file, separated by a chosen value
 * Param: String
 * Return: void
 */
void List::writeTo(const string& fileName, char sep) const{
	ofstream fout(fileName.c_str());
	assert(fout.is_open());
	Node* ptr = myFirst;
	while(ptr){
		fout << sep << ptr->myItem;
		ptr = ptr->myNext;
	}
	fout << endl;
	fout.close();
}

/*
 * Written by Andrew Baker
 * adds node with item to the beginning of the list
 * Param: Item
 * Return: void
 */
void List::prepend(const Item& pre){
	if (mySize == 0){
		append(pre);
	}
	else{
		myFirst = new Node(pre, myFirst);
		mySize++;
	}

}

/*
 * Written by Andrew Baker
 * Inserts Node with item at chosen index, if <0 prepends, if >mySize appends
 * Param: Item, unsigned
 * Return: void
 */
void List::insert(const Item& add, unsigned index) {
	if (index >= mySize) {
		append(add);
	} else if (index <= 0) {
		prepend(add);
	} else {
		List::Node* nPtr = myFirst;
		for (unsigned u = 0; u < index - 1; u++) {
			nPtr = nPtr->myNext;
		}
		nPtr->myNext = new Node(add, nPtr->myNext);
		mySize++;
	}
}




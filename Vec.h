/* Vec.h provides a simple vector class named Vec.
 * Student Name:Lorrayya Williams
 * Date: October 1, 2018
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
using namespace std;

template<class Item>
class Vec {
public:
	Vec();
	Vec(unsigned size);
	Vec(const Vec& original);
	~Vec();
	Vec<Item>& operator=(const Vec<Item>& original);
	unsigned getSize() const;
	void setItem(unsigned index, const Item& it);
	Item getItem( unsigned index) const;
	void setSize(unsigned newSize);
	bool operator==(const Vec<Item>& v2) const;
	void writeTo(ostream& out) const;
	void readFrom(istream& in);
	void readFrom(string filename);
	void writeTo(const string& fileName) const;
	Item& operator[](unsigned index);
	const Item& operator[](unsigned index) const;
	bool operator!=(const Vec<Item>& v2);
	Vec<Item> operator+(const Vec<Item>& v2);
	Vec<Item> operator-(const Vec<Item>& v2);
	double operator*(const Vec<Item>& other) const;

private:
	unsigned mySize;
	Item * myArray;
	friend class VecTester;
};

 //Intializes Array with Null values
template<class Item>
Vec<Item>::Vec() {
	myArray = NULL;
	mySize = 0;
}


////Intializes Array with an inputed value
template<class Item>
Vec<Item>::Vec(unsigned size) {
		mySize = size;
	if (size> 0){
		myArray = new Item[mySize];
	}
	else{
		myArray = NULL;
	}
	for(unsigned i=0; i < size; ++i){
		myArray[i]=0;
	}
}


////Changes the size of an array
template<class Item>
Vec<Item>::Vec(const Vec<Item>& original) {
	mySize = original.mySize;
	if (original.mySize > 0){
		myArray = new Item[mySize];
		for (unsigned i = 0; i< mySize; ++i) {
			myArray[i] = original.myArray[i];
		}
	}
	else {
		mySize = 0;
		myArray = NULL;
	}
   }

////Destroys Array
template<class Item>
Vec<Item>::~Vec() {
	delete []myArray;
	mySize = 0;
	myArray = NULL;
}

////Allows operator to compare te size of vectors
template<class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {
	if (this != &original) {
		if (mySize != original.mySize) {
			if (mySize > 0) {
				delete []myArray;
				myArray = NULL;
			}
			if (original.mySize > 0) {
				myArray = new Item[original.mySize];
			}
			mySize = original.mySize;
		}
		for (unsigned i = 0; i < mySize; ++i) {
			myArray[i] = original.myArray[i];
		}
	}
	return *this;
}

////Accessor for Vector Size
template<class Item>
unsigned Vec<Item>::getSize() const {
	return mySize;
}


//
template<class Item>
void Vec<Item>::setItem(unsigned index, const Item& it){
	if (myArray == NULL){
		throw range_error("myArray is empty");
	}
	if(index > mySize - 1){
		throw range_error("Index Out of Bounds");
	}
	else{
		myArray[index] = it;
	}
}

//Accessor for Item
template<class Item>
Item Vec<Item>::getItem(unsigned index) const {
	if (myArray == NULL){
		throw range_error("myArray is empty");
	}
	if(index > mySize - 1){
		throw range_error("Index Out of Bounds");
	}
	else{
		return myArray[index];
	}
}


////Sets the Sixe of the Vector
template<class Item>
void Vec<Item>::setSize(unsigned newSize){
	if (mySize != newSize){
		if (newSize == 0){
			delete []myArray;
			myArray = NULL;
			mySize = 0;
		}
		else{
			Item* newArray = new Item[newSize];
			if (mySize < newSize){
				for(unsigned i= 0; i < mySize; ++i){
					newArray[i] = myArray[i];
				}
				for(unsigned i =mySize; i < newSize; ++i) {
					newArray[i]= 0;
				}
			}
			else{
				for(unsigned i = 0; i < newSize ; ++i){
					newArray[i]= myArray[i];
				}
			}
			mySize = newSize;
			delete []myArray;
			myArray = newArray;
		}

	}
}

//Allows for expression to compare the size of vectors
template<class Item>
bool Vec<Item>::operator==(const Vec<Item>& v2)const{
	if (mySize != v2.mySize){
		return false;
	}
	for(unsigned i =0; i < mySize; ++i){
		if(myArray[i] != v2.myArray[i]){
			return false;
		}
	}
	return true;

}

//Writes Value to a Vector
template<class Item>
void Vec<Item>::writeTo(ostream& out)const{
	for(unsigned i; i < mySize; ++i){
		out << myArray[i] << '\t';
	}


}

//Reads Values in a Vector
template<class Item>
void Vec<Item>::readFrom(istream& in){
	for(unsigned i = 0; i < mySize; i++){
			in >> myArray[i];
	}
}

//reads vectors stored in a file
template<class Item>
void Vec<Item>::readFrom(string filename) {
	ifstream fin(filename.c_str());
	assert(fin.is_open());
	delete[] myArray;
	fin >> mySize;
	myArray = new Item[mySize];
	for(unsigned i = 0; i < mySize; i++){
		fin >> myArray[i];
	}
	fin.close();
}

//Writes vectors to a File
template<class Item>
void Vec<Item>::writeTo(const string& fileName)const{
		ofstream myFile;
		myFile.open(fileName.c_str());

		double numValues = mySize;
		myFile << numValues << endl;

		for(unsigned i = 0; i < mySize; ++i){
			myFile << myArray[i] << endl;

		}
		myFile.close();
}

/* Subscript operator (read version)
 * Gets the value at a given index in myArray
 * @param: index, an unsigned
 * Return: myArray[index], an Item (aka double)
 * Written by: Zachary Chin
 */
template<class Item>
const Item& Vec<Item>::operator[](unsigned index) const{
	if (index >= mySize) {
		throw range_error("index out of bounds of array's size");
	} else {
		return myArray[index];
	}
}

//Allows for the operator to be used for writing to a Vector
template<class Item>
Item& Vec<Item>::operator[](unsigned index) {
	if(index >= mySize){
		throw range_error("The Index is too high!");
	}
	else{
		return myArray[index];
	}
}

/* Inequality operator
 * Compares two Vec objects to see if they are equal
 * @param: v2, a Vec object
 * Return: true if the two Vec objects have the same size and the
 * 		   same values in corresponding indexes; return false otherwise.
 * Written by: Zachary Chin
 */
template<class Item>
bool Vec<Item>::operator!=(const Vec<Item>& v2){
	if (mySize != v2.mySize) {
		return true;
	} else {
		for (unsigned i = 0; i < mySize; i++) {
			if (myArray[i] != v2.myArray[i]) {
				return true;
			}
		}
	}
	return false;
}


//Allows for vectors to be added
template<class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& other){
	if(mySize == other.mySize){
		Vec<Item> vec3(mySize);
		for (unsigned i= 0; i < mySize; i++){
			vec3.setItem(i, myArray[i] + other.myArray[i]);
		}
		return vec3;
	} else {
		throw invalid_argument("size is unequal");
	}



}

/* Subtraction operator
 * Subtracts the values in the array of the current Vec object by the
 *    values in the corresponding indexes in the Vec object passed
 * @param: v2, a Vec object
 * Return: v3, a Vec object, which contains the differences of values
 * 		   between the current Vec object and v2
 * Written by: Zachary Chin
 */
template<class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& v2){
	if(mySize != v2.mySize){
		throw invalid_argument("Arrays are not of equal size");
	}
	else{
		Vec<Item> v3(v2.getSize());
		for(unsigned i = 0; i < mySize; i++){
			v3[i] = myArray[i] - v2[i];
		}

		return v3;
	}
}

//Allows for vectors t be multiplied
template<class Item>
double Vec<Item>::operator*(const Vec<Item>& other) const{
	if (mySize == other.mySize){
		Vec<Item> vec3(mySize);
		for (unsigned i=0; i < mySize; ++i){
			vec3.setItem(i, myArray[i] * other.myArray[i]);
		}
		double product = 0;
		for(unsigned i=0; i < vec3.mySize; ++i) {
			product += vec3.myArray[i];
		}
		return product;
	}else {
		throw invalid_argument("size is unequal");
	}
}







#endif /*VEC_H_*/

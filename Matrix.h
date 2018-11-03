/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name: Lorrayya Williams
 * Date: October 3, 2018
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vec.h"
#include <iostream>
#include <fstream>
using namespace std;

template<class Item>
class Matrix {
public:
	Matrix();
	const unsigned getRows() const;
	const unsigned getColumns() const;
	Matrix(unsigned rows, unsigned columns );
	const Vec<Item>& operator[](unsigned index) const;
	Vec<Item>& operator[](unsigned index);
	bool operator==(const Matrix<Item>& m2) const;
	bool operator!=(const Matrix<Item>& m2) const;
	void readFrom(istream& in);
	Vec<Item>& writeTo(ostream& out);
	void readFrom(string fileName);
	void writeTo(string filename);
	Matrix<Item> operator+(const Matrix<Item>& m2) const;
	Matrix<Item> operator-(const Matrix<Item>& m2);
	Matrix<Item> getTranspose()const;

private:
	unsigned         myRows;
	unsigned         myColumns;
	Vec< Vec<Item> > myVec;
	friend class MatrixTester;
;

};


// Default Constructor by Lorrayya Williams
template<class Item>
Matrix<Item>::Matrix() {
	myRows = myColumns = 0;
}

//Accessor for Rows by Lorrayya Williams
template<class Item>
const unsigned Matrix<Item>::getRows() const{
	return myRows;
}


//Accessor for Columns by Lorrayya Williams
template<class Item>
const unsigned Matrix<Item>::getColumns() const{
	return myColumns;
}

// Explicit Constructor by Lorrayya Williams
template<class Item>
Matrix<Item>::Matrix(unsigned rows, unsigned columns) {
            myRows = rows;
            myColumns = columns;
            myVec.setSize(rows);
            for (unsigned i = 0; i < rows; i++) {
                myVec[i].setSize(columns);
                for(unsigned a = 0; a < columns; a++){
                	myVec[i][a];
                }
            }

}


//read [] operator by Lorrayya Williams
template<class Item>
const Vec<Item>& Matrix<Item>::operator[](unsigned index) const{
	if(index >= myRows){
		throw range_error("The index number  is too large");

	}

	else{
		return myVec[index];
	}

}

//write [] operator by Lorrayya Williams
template<class Item>
Vec<Item>& Matrix<Item>::operator[](unsigned index){
	if(index >= myRows){
			throw range_error("The index number is too large");
		}

		else{
			return myVec[index];
		}



}

//boolean operator for Matrix by Lorrayya Williams
template<class Item>
bool Matrix<Item>::operator==(const Matrix<Item>& m2) const {
   if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
        return false;
   } else {
        return myVec == m2.myVec;
   }
}

template<class Item>
//inequality operator for Matrix - Jessica Hewitt
bool Matrix<Item>::operator!=(const Matrix<Item>& m2) const {
	if ( myRows == m2.getRows() || myColumns == m2.getColumns()) {
		for (unsigned i = 0; i < myRows; i++) {
		for(unsigned a = 0; a < myColumns; a++){
			if(myVec[i][a] == m2.myVec[i][a]){
				return false;
			}
		}
	}
	}
	else {
		return true;
	}
}


template<class Item>
//read from stream by Jessica Hewitt
void Matrix<Item>::readFrom(istream& in) {

	myVec.setSize(myRows);
	for (unsigned i = 0; i < myRows; i++) {
		 myVec[i].setSize(myColumns);
			for(unsigned a = 0; a < myColumns; a++){
				in >> myVec[i][a];
			}
		}
		}

template<class Item>
//Writes to a stream by Lorrayya Williams
Vec<Item>& Matrix<Item>::writeTo(ostream& out){
	for (unsigned i = 0; i < myRows; i++) {
		for(unsigned a = 0; a < myColumns; a++){
			out << myVec[i][a] << '\t';
		}
	}
}
template<class Item>
//Reads from a File by Lorrayya Williams
void Matrix<Item>::readFrom(string fileName){
	ifstream in(fileName.c_str());
	in >> myRows >> myColumns;
	myVec.setSize(myRows);
	for (unsigned i=0 ; i < myRows; i++){
		myVec[i].setSize(myColumns);
	}

	for(unsigned row=0; row<myRows; row++){
		for(unsigned column =0; column <myColumns; column++){
			in >> myVec[row][column];
		}
	}
}


template<class Item>
//writes to a file by Jessica Hewitt
void Matrix<Item>::writeTo(const string fileName){
	ifstream in(fileName.c_str());
	in >> myRows >> myColumns;
	myVec.setSize(myRows);
	for (unsigned i=0 ; i < myRows; i++){
		myVec[i].setSize(myColumns);
	}
	for(unsigned row=0; row<myRows; row++){
			for(unsigned column =0; column <myColumns; column++){
				cout << myVec[row][column] << '\t';
			}
	}
}
template<class Item>
//Addition operator by Lorrayya Williams
Matrix<Item> Matrix<Item>::operator+(const Matrix<Item>& m2) const{
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
	        throw invalid_argument("Matrixes not same size");
	   }
	Matrix<Item> m1(myRows, myColumns);
	for(unsigned row=0; row< myRows; row++){
		for(unsigned column=0; column < myColumns; column++){
			m1[row][column] = myVec[row][column] + m2[row][column];
		}
	}
	return m1;
}


//Equality Operator
template<class Item>
//Subtraction operator by Lorrayya Williams
Matrix<Item> Matrix<Item>::operator-(const Matrix<Item>& m2){
	if(myRows != m2.myRows ||myColumns != m2.myColumns){
		throw invalid_argument("Arguments are not of equal size.");
		}
	else {
		Matrix<Item> m3(m2.getRows(), m2.getColumns());
		for(unsigned i = 0; i < myRows; i++){
			for(unsigned a = 0; a < myColumns; a++){
				m3[i][a] = myVec[i][a] - m2[i][a];

			}

				}
		return m3;
	}
}

// Transpose creator and accessor by Lorrayya Williams
template<class Item>
Matrix<Item> Matrix<Item>::getTranspose() const{
	Matrix<Item> m1 (myColumns, myRows);
	for(unsigned i = 0; i < myRows; i++) {
		for(unsigned a = 0; a < myColumns; a++){
			m1[a][i] = myVec[i][a];
		}
	}
	return m1;
}

#endif

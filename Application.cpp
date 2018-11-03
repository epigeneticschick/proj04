/*
 * Application.cpp
 * Lorrayya Williams
 *
 *  Created on: Oct 8, 2018 for CS 112
 *      Author: llw5
 */

#include "Application.h"

using namespace std;
Application::Application(){

}

bool Application::Interface(){
	int input;
	string file;
	string file2;

	//Prints Options
	cout << "1. Addition \n" << "2. Subtraction \n" << "3.Transpose \n" << "0. To exit\n" << endl;

	//Prompts user to enter choice
	cout << "Enter Your Choice:" << endl;
	cin >> input;

	//Prompts user to enter a file name
	cout << "Enter File Name: " << endl;
	cin >> file;

	//Makes file into a Matrix
	Matrix<double> m;
	m.readFrom(file);


	while (input != 0){
		//Implements choice 1
		if (input==1){
			cout << "Enter Another File Name: " << endl;
			cin >> file2;
			Matrix<double> m2;
			m2.readFrom(file2);
			Matrix<double> m3;
			m3 = m + m2;
			for (unsigned i = 0; i < m3.getRows(); i++){
				for(unsigned a = 0; a < m3.getColumns(); a++){
					cout << m3[i][a] << ", ";
				}
				cout << "\n";
			}
			cout << "1. Addition \n" << "2. Subtraction \n" << "3.Transpose \n" << "0. To exit\n" << endl;
			cout << "Enter Your Choice:" << endl;
			cin >> input;

		}
		//Implements Choice 2
		if (input == 2){
			cout << "Enter Another File Name: " << endl;
			cin >> file2;
			Matrix<double> m2;
			m2.readFrom(file2);
			Matrix<double> m3;
			m3 = m - m2;
			for (unsigned i = 0; i < m3.getRows(); i++){
				for(unsigned a = 0; a < m3.getColumns(); a++){
					cout << m3[i][a] << ", ";
				}
				cout << "\n";

			}
			cout << "1. Addition \n" << "2. Subtraction \n" << "3.Transpose \n" << "0. To exit\n" << endl;
			cout << "Enter Your Choice:" << endl;
			cin >> input;
		}

		//Implements Choice 3
		if (input == 3){
			Matrix<double> m2;
			m2 = m.getTranspose();
			for (unsigned i = 0; i < m2.getRows(); i++){
				for(unsigned a = 0; a < m2.getColumns(); a++){
					cout << m2[i][a] << ", ";
				}
				cout << "\n";
			}
			cout <<  "1. Addition \n" << "2. Subtraction \n" << "3.Transpose \n" << "0. To exit\n" << endl;
			cout << "Enter Your Choice:" << endl;
			cin >> input;
		}
	}
}


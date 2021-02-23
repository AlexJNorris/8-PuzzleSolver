// 8-PuzzleSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>
#include <queue>

using namespace std;


int minIndex(queue<int>& q, int sortedIndex) //borrowed from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/ 
{
	int min_index = -1;
	int min_val = INT_MAX;
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		int curr = q.front();
		q.pop();  // This is dequeue() in C++ STL 

		// we add the condition i <= sortedIndex 
		// because we don't want to traverse 
		// on the sorted part of the queue, 
		// which is the right part. 
		if (curr <= min_val && i <= sortedIndex)
		{
			min_index = i;
			min_val = curr;
		}
		q.push(curr);  // This is enqueue() in  
					   // C++ STL 
	}
	return min_index;
}

// Moves given minimum element to rear of  
// queue 
void insertMinToRear(queue<int>& q, int min_index) //borrowed from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
{
	int min_val;
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		int curr = q.front();
		q.pop();
		if (i != min_index)
			q.push(curr);
		else
			min_val = curr;
	}
	q.push(min_val);
}
void insertMinToRear(queue<string>& q, int min_index) //borrowed from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
{
	string min_val;
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		string curr = q.front();
		q.pop();
		if (i != min_index)
			q.push(curr);
		else
			min_val = curr;
	}
	q.push(min_val);
}

void sortQueue(queue<int>& q, queue<string>& str) //borrowed from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
{
	for (int i = 1; i < q.size()+1; i++)
	{
		int min_index = minIndex(q, q.size() - i);
		insertMinToRear(q, min_index);
		insertMinToRear(str, min_index);
	}
}

bool testIfVisitedState(vector<string> testVec, string test) {

	

	if (find(testVec.begin(), testVec.end(), test) != testVec.end()) {
		//cout << " = visited ";
		return true;
		
	}

	return false;
}

void printArray(char arr[3][3]) {
	for (int i = 0; i < 3; i++) { //For testing input file
		if (i == 0) { 
			cout << endl << endl;
		}
		for (int j = 0; j < 3; j++) {
			if (j == 0) { 
				cout << "{";
			}
				cout << arr[i][j];
			if (j == 2) { 
				cout << "}" << endl; 
			}
			else {
				cout << ", "; 
			}
		}
		if (i == 2) { 
			cout << endl; 
		}
	}

}

int manhattan_distance(char p[3][3], char g[3][3]) {

	int totalCost = 0;
	int x1, x2, y1, y2;
	char px[3], py[3], gx[3], gy[3];
	

	for (int k = 1; k < 9; k++) {
		char c = to_string(k)[0];
		//cout << c;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				px[j] = p[i][j];
				//cout << p[i][j] << " ";
			}
			x1 = distance(px, find(px, px + 3, c));
			if (x1 < 3) {

				//cout << x1;
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				gx[j] = g[i][j];
				//cout << g[i][j] << "-";
			}

			x2 = distance(gx, find(gx, gx + 3, c));
			if (x2 < 3) {

				//cout << x2;
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				py[j] = p[j][i];
				//cout << p[j][i] << " ";
			}

			y1 = distance(py, find(py, py + 3, c));
			if (y1 < 3) {
				//cout << y1;
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				gy[j] = g[j][i];
			}

			y2 = distance(gy, find(gy, gy + 3, c));
			if (y2 < 3) {
				//cout << y2;
				break;
			}
		}

		int x_dif, y_dif;

		x_dif = x2 - x1;
		y_dif = y2 - y1;
		if (x_dif < 0)
			x_dif = -x_dif;
		if (y_dif < 0)
			y_dif = -y_dif;
		totalCost += x_dif + y_dif;
		//cout << x_dif + y_dif;
	}
	//cout << totalCost;
	return totalCost;
}

void swap(char p[3][3],string xy_of_e, string xy_swap) {
	int xe, ye, x, y;

	xe = stoi(xy_of_e.substr(0, 1));
	ye = stoi(xy_of_e.substr(1, 1));
	//cout << xy_swap;
	x = stoi(xy_swap.substr(0, 1));
	y = stoi(xy_swap.substr(1, 1));


	char temp = p[x][y];
	p[x][y] = p[xe][ye];
	p[xe][ye] = temp;
}

int findy_of_e(char arr[3][3]) {
	char arrx[3];
	int x;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arrx[j] = arr[i][j];
			//cout << arr[i][j] << " ";
		}
		x = distance(arrx, find(arrx, arrx + 3, 'E'));
		if (x < 3) {

			//cout << x;
			break;
		}
	}
	return x;

}

int findx_of_e(char arr[3][3]) {
	char arry[3];
	int y;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arry[j] = arr[j][i];
			//cout << arr[j][i] << " ";
		}
		y = distance(arry, find(arry, arry + 3, 'E'));
		if (y < 3) {

			//cout << y;
			break;
		}
	}
	return y;

}

string xy_to_string(int x, int y) {
	string compiled;
	compiled = to_string(x) + to_string(y);
	return compiled;
}

string matrix_toString(char p[3][3]) {
	string str;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			str += p[i][j];
		}
	}
	return str;
}
void  string_toMatrix(char p[3][3], string str) {
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				p[i][j] = str[j];
			} else if (i == 1) {
				p[i][j] = str[j+3];
			} else if (i == 2) {
				p[i][j] = str[j+6];
			}
		}
	}
}

int valid_key_index(string valid[9][5], string xy) {  //find row of valid moves
	string validy[9];
	int y = -1;

	for (int j = 0; j < 9; j++) {
		validy[j] = valid[j][0];
		//cout << valid[j][0] << " ";
	}
	y = distance(validy, find(validy, validy + 9, xy));
	if (y < 9) {

		//cout << y;
		return y;
	}
	return -1;
}

void copy_matrix(char p[3][3], char copy[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			copy[i][j] = p[i][j];
		}
	}
}


int test_move(char test[3][3],char t[3][3], char g[3][3], string xy_of_e, string xy) {
	//cout << xy;
	copy_matrix(test, t);
	swap(t, xy_of_e, xy);
	//printArray(t);
	return manhattan_distance(t, g);


}


int getInvCount(int arr[]) // borrowed from https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
{
	int inv_count = 0;
	for (int i = 0; i < 9 - 1; i++)
		for (int j = i + 1; j < 9; j++)
			// Value 0 is used for empty space
			if (arr[j] && arr[i] && arr[i] > arr[j])
				inv_count++;
	return inv_count;
}

// This function returns true if given 8 puzzle is solvable.
bool isSolvable(char puzzle[3][3]) // borrowed from https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
{
	int copy[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (puzzle[i][j] == 'E') {
				copy[i][j] = 0;
			}
			else {
				copy[i][j] = puzzle[i][j] - '0';
			}
			
		}
	}
	// Count inversions in given 8 puzzle
	int invCount = getInvCount((int*)copy);

	// return true if inversion count is even.
	return (invCount % 2 == 0);
}

vector<string> a_star(char p[3][3], char g[3][3]) {
	int states = 0;
	string wins;
	int winCnt = 0;
	int x, y; //x and y of 'E'
	int validKey;
	//bool solved = false;
	char test[3][3];
	char t[3][3];

	vector<string> testVec;
	queue<string> q;
	vector<string> path;
	queue<int> qMan;

	string testWin;
	int testValue;
	int bestTest;
	string gee;
	string goal = matrix_toString(g);
	//cout << goal;

	string validMoves[9][5]{
		{"00","01","10","no","no"},
		{"01","00","11","02","no"},
		{"02","01","12","no","no"},
		{"10","00","11","20","no"},
		{"11","01","10","12","21"},
		{"12","11","02","22","no"},
		{"20","10","21","no","no"},
		{"21","20","11","22","no"},
		{"22","21","12","no","no"}};

	x = findx_of_e(p);
	y = findy_of_e(p);
	states++;
	printArray(p);
	

	q.push(matrix_toString(p));
	qMan.push(manhattan_distance(p, g));
	path.push_back(matrix_toString(p));
	testVec.push_back(matrix_toString(p));
	//int i = 9;


	while(!q.empty()) {//while loop to end all while loops
		sortQueue(qMan, q);
		gee = q.front();
		q.pop();
		qMan.pop();
		


		bestTest = -1;
		testWin = "";
		winCnt = 0;

		//printArray(p);
		string_toMatrix(test,gee);
		if (!testIfVisitedState(testVec, matrix_toString(test))) {
			path.push_back(matrix_toString(test));
			testVec.push_back(matrix_toString(test));

		}

		x = findx_of_e(test);
		y = findy_of_e(test);
		//printArray(test);
		


		
		states++;
		

		if (gee == goal) {
			cout << "SOLVED IN : " << states << " states" << endl
			<< "FINAL STATE:";
			printArray(test);
			return path;
		}
		else {
			validKey = valid_key_index(validMoves, xy_to_string(x, y));
			//cout << endl << "------------------------------------------------" << endl;
			for (int i = 1; i < 5; i++) {

				if (validMoves[validKey][i] == "no") { //If possible routes exhausted
					if (testWin == "") {
						path.pop_back();
						q.push(path[path.size()-1]);
						string_toMatrix(t, path[path.size()-1]);
						qMan.push(manhattan_distance(t, g));
						//cout << path[path.size()-1];
						break; }
					if (winCnt == 1) {
						testValue = states + test_move(test, t, g, xy_to_string(x, y), testWin);
						q.push(matrix_toString(t));
						qMan.push(testValue);
						break;
					}
					if (winCnt > 1) {
						for (int i = 0; i < winCnt; i++) {
							testWin = wins.substr((i/.5),2);
							testValue = states + test_move(test, t, g, xy_to_string(x, y), testWin);
							q.push(matrix_toString(t));
							qMan.push(testValue);
							break;
						}
					}
					break;
				}


				if (validMoves[validKey][i] != "no") {
					testValue = states + test_move(test, t, g, xy_to_string(x, y), validMoves[validKey][i]); // f(n) = h(n) + g(n)
				}
				//printArray(test);
				//cout << " " << testValue;

				if (!testIfVisitedState(testVec, matrix_toString(t))) {
					if (testValue < bestTest || bestTest == -1) {
						bestTest = testValue;
						testWin = validMoves[validKey][i];
						wins = testWin;
						winCnt = 1;
						//cout << endl << matrix_toString(t);

					}
					if (testValue == bestTest) {
						winCnt++;
						testWin = validMoves[validKey][i];
						wins += testWin;
					}
					//cout << testWin;
				}

				if (i == 4 && testWin != "") { //If possible routes exhausted
					if (winCnt == 1) {
						testValue = states + test_move(test, t, g, xy_to_string(x, y), testWin);
						q.push(matrix_toString(t));
						qMan.push(testValue);
						break;
					}
					if (winCnt > 1) {
						for (int i = 0; i < winCnt; i++) {
							testWin = wins.substr((i / .5), 2);
							testValue = states + test_move(test, t, g, xy_to_string(x, y), testWin);
							q.push(matrix_toString(t));
							qMan.push(testValue);
							break;
						}
					}
					else {
						path.pop_back();
						q.push(path[path.size()-1]);
						string_toMatrix(t, path[path.size()-1]);
						qMan.push(manhattan_distance(t, g));
						//cout << path[path.size()-1];
						break;
					}
				}

			}
			

			
			//i--;
		}

	}
	cout << endl << " FAILURE AFTER : " << states << " STATES "<< endl
		<< "FINAL STATE:";
	printArray(test);
	return path;
}

int main() {
	char puzzle[3][3];
	char goal[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','E'}};
	
	ifstream inFile;
	inFile.open("prog1_input.txt");


	if (!inFile) {
		cout << "File read error!" << endl; 
		return -1;
	}

	int iterations;
	inFile >> iterations;
	//cout << iterations;

	
	for (int i = 0; i < iterations; i++) {
		cout << endl << " PUZZLE #" << i + 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				char c;
				inFile >> c;
				puzzle[i][j] = c;
			}
		}
		if (isSolvable(puzzle)) {
		//	if (i == 2) {
				a_star(puzzle, goal);
		//	}
		}
		else {
			cout << endl << " NOT SOLVABLE " << endl;
		}
		cout << "---------------------------";
	}

	cout << endl << endl;
	system("pause");
	return 0;

}

/*Stupid extra code just in case:

visited.push_back(matrix_toString(p));
		bestTest = 2000;
		testValue = 0;
		if ((manhattan_distance(p, g) == 0)) {
			printArray(p);
			cout << endl << "Total states of: " << states;
			solved = true;
			break;
		}
		x = findx_of_e(p);
		y = findy_of_e(p);

		if (valid_key_index(validMoves, xy_to_string(x, y)) == -1) {
			cout << "valid key error" << endl;
			break;
		}

		validKey = valid_key_index(validMoves, xy_to_string(x, y));

		for (int i = 1; i < 5; i++) {
			if (validMoves[validKey][i] == "no") { break; } // initialize test


			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {

					test[i][j] = p[i][j];
				}
			}


			testValue = test_move(p, g, test, xy_to_string(x, y), validMoves[validKey][i]) + visited.size(); // call test function;
			//cout << testValue;



			if (testIfVisitedState(visited, matrix_toString(test))) {
				testValue += 100;
			}
			cout << testValue;
			states += 1;

			if (testValue < bestTest) {
				cout << "**"<< testValue;
				bestTest = testValue;
				testWin = validMoves[validKey][i];
			}
		}

		swap(p, xy_to_string(x, y), testWin);
		printArray(p);*/
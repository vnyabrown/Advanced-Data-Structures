/************************************************************************************************************
** CS232 Prof. MacKay Lab 2
** File name:	lab2_driver.cpp
**
** This program...Will read in data from a file (lab2 Data.txt) and insert the
** data into a Priority_Queue. It will then display all the elements of the priority_queue from ‘top’
** down
**
**
** Programmer:	Naya Brown
** Date created:	9/20/22
** Date revised:	9/21/22
************************************************************************************************************/

#include<iostream>
#include<fstream>
#include<queue>
#include<string>
using namespace std;

// struct for data
struct members
{
	string firstName;
	string lastName;
	int rank; 
	int id; 
};

// overload input for members
istream& operator>>(istream& in, members mem)
{
	in >> mem.firstName; 
	in >> mem.lastName; 
	in >> mem.rank; 

	return in;
}

// overload output for members
ostream& operator<<(ostream& out, members mem)
{
	out << mem.firstName << ' ';
	out << mem.lastName << ' ';
	out << mem.rank << endl;

	return out;
}

// overload less than comparison for members
bool operator<(members mem_l, members mem_r)
{
	if (mem_l.rank < mem_r.rank)
		return true;
	if (mem_l.rank > mem_r.rank)
		return false;
	if (mem_l.rank == mem_r.rank)
	{
		if (mem_l.id < mem_r.id)
			return false;
	}
}

int main()
{
	int mem_num = 0;
	string fileName; 
	ifstream inFile; 
	members one_member; 
	priority_queue<members> team; // create a priority queue for members
	int id_count = 0;

	// Get file from user
	cout << "Enter file directory: ";
	getline(std::cin, fileName);
	fileName.c_str();
	inFile.open(fileName);

	while (inFile.fail()) // error check file and get new file directory
	{
		fileName.clear();
		cout << "Error opening file, enter file directory: ";
		getline(std::cin, fileName);
		fileName.c_str();
		inFile.open(fileName);
	} // end of while

	// Read Data from file into members and add to priority queue
	while (!inFile.eof()) // edit this
	{
		inFile >> one_member.firstName >> one_member.lastName >> one_member.rank; // must overload input 
		one_member.id = id_count; 
		id_count++;
		team.push(one_member); 
		mem_num++; 
	} // end of while

	// Display data in order
	while (!team.empty())
	{
		cout << team.top(); // must overload output
		team.pop();
	} // end of while

	return 0;
} // end of main




#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include<list>
#include<iomanip>
#include<algorithm>

using namespace std;
struct currDistance
{
	string vName;
	int current = INT_MAX;
};

struct matrixData
{
	bool edge = false;
	double weight = 0;
};

//prototype for Dijkstra up here
void Dijkstra(string v, vector<currDistance> &distances, matrixData** vertmatrix);

int main()
{
	ifstream data("DGraphData.txt");
	int numVertices = 0;
	string tempS, vertChoice, checkS;
	char again;
	vector<currDistance> distances;
	currDistance tempV;

	if (!data)
	{
		cout << "Couldn't open file\n";
		return 0;
	}

	//counting vertices AND populating 'distances'
	while (data >> tempV.vName)
	{
		distances.push_back(tempV);
		numVertices++;
		getline(data, tempS);
	}
	data.clear();
	data.seekg(0);

	// setting up 'empty' adjacency matrix
	matrixData** vertices = new matrixData* [numVertices];
	for (int posi = 0; posi < numVertices; posi++)
		vertices[posi] = new matrixData[numVertices];
	
	//Output data in matrix 
	cout << "Empty Graph Matrix: " << endl; 
	for (int row = 0; row < numVertices; row++)
	{
		cout << distances[row].vName;
		for (int col = 0; col < numVertices; col++)
		{
			cout << setw(2) << vertices[row][col].edge;
		}
		cout << endl;
	}
	cout << endl;

	//populating adjacency matrix-- yay it works!
	// YOU need to do this
		// Starting from first vertex
		for (int i = 0; i < numVertices; i++) // for all vertices
		{
			data >> tempS; // discard starting vertex

			//data >> tempS; // discard current vertex edge
			while (data.peek() != '\n') // if we aren't at the newline character aka the current vertex has edges/connections
			{
				
				data >> checkS; //Get current Vertex
				for (int j = 0; j < numVertices; j++) 
				{
					if (checkS == distances[j].vName) // find proper position of connected vertex in matrix
					{
						// create edge with weight
						vertices[i][j].edge = true;
						data >> vertices[i][j].weight; // add weight of vertex
					}
				}
			}
		}

	// clearing data stream
	data.clear();
	data.seekg(0);

	//Output data in matrix 
	cout << "Filled Graph Matrix: " << endl;
	for (int row = 0; row < numVertices; row++)
	{
		cout << distances[row].vName; 
		for (int col = 0; col < numVertices; col++)
		{
			cout << setw(2) << vertices[row][col].edge;
		}
		cout << endl;
	}
	cout << endl;

	do
	{
		vector<currDistance> temp = distances; //don't change distances, in case they want to run more than once
		cout << "Which vertex to start? ";
		cin >> vertChoice;
		
		Dijkstra(vertChoice, temp, vertices);

		//output the values of temp
		cout << "Shortest paths from vertex " << vertChoice << ": " << endl;
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i].vName == vertChoice)
				cout << temp[i].vName << " No path to start." << " ";
			else if (temp[i].current == INT_MAX)
				cout << temp[i].vName << ":N/A ";
			else
				cout << temp[i].vName << ":" << temp[i].current << " ";
		}
		cout << endl << endl; 


		cout << "Another run(Y/N)? ";
		cin >> again;
	} while (again == 'Y' || again =='y');


	return 0;
}

// define the function Dijkstra down here
void Dijkstra(string v, vector<currDistance> &distances, matrixData** vertmatrix)
{
	// Program Dijkstra's algo for graphs!
	list<string> tobechecked, visited; // keep track of vertexes to check, and visited vertexes
	string u;
	int iterate = 0, tempdist, onvert = 0;
	bool v_start = false, foundsame = false;
	
	// set distance of chosen starting vertex to 0
	while (v_start == false)
	{
		if (distances[iterate].vName == v)
		{
			distances[iterate].current = 0;
			tempdist = distances[iterate].current;
			onvert = iterate;
			v_start = true;
		}
		iterate++;
	}
	iterate = 0; //reset value of iteration

	//Set vertices to be checked
	for (int i = 0; i < distances.size(); i++)
	{
		tobechecked.push_back(distances[i].vName);
	}
	cout << endl;
	
	while (!tobechecked.empty())// While there are still vertices to be checked
	{

		// v = a vertex in tobechecked with smallest distance
		for (int i = 0; i < distances.size(); i++)
		{
			if (iterate != 0) // if we aren't on the first iteration, if we are we will use that
			{
				if (std::find(tobechecked.begin(), tobechecked.end(), distances[i].vName) != tobechecked.end()) // if the element is in to be checked
				{
					//set current smallest to first value in tobechecked
					tempdist = distances[i].current;
					if (distances[i].current < tempdist) // if the element is smaller and in tobechecked
					{
						v = distances[i].vName;
						onvert = i; // set current vertex to know position in matrix
						tempdist = distances[i].current; // set new smallest distance
					} // end if
					else if (distances[i].current <= tempdist)
					{
						// if we've already chosen a vertex with the same value, we just need the next closest one...
						if (foundsame != true)
						{
							v = distances[i].vName;
							onvert = i; // set current vertex to know position in matrix
							tempdist = distances[i].current; // set new smallest distance
							foundsame = true;
						} // end if
					} // end else if
				} // end if
				else // if vertex is not in tobechecked
				{

					if ((i + 1) < distances.size())
					{
						tempdist = distances[i + 1].current; // set new smallest value to any next value
					} // end if
				} // end else
			} //end if
		} // end for
			
		visited.push_back(v); // mark v visited
		tobechecked.remove(v); // remove v from tobechecked
		foundsame = false;

		if (!tobechecked.empty())
		{
			// error here, we're not checking adjacent vertexes properly, because we go through the whole matrix instead of checking the ones next to our current
			// for all vertices u adjacent to v && in tobechecked
			for (int j = 0; j < distances.size(); j++)
			{
				//use adjacency matrix-- what edges does the vertex we're on have?
				if (vertmatrix[onvert][j].edge == true) // if there is an edge
				{
					u = distances[j].vName; // set adjacent vertex u
					//Check weights to set weight!
					if (distances[j].current > ((distances[onvert].current) + vertmatrix[onvert][j].weight)) // if distances of current vertex v is greater than distances of adjacent vertex u + weight between them
						distances[j].current = ((distances[onvert].current) + vertmatrix[onvert][j].weight); // set current distance of adjacent u = u + weight between uv
				} // end if

				iterate++; // keeping track of how many times we've been looping

			} // end for
		} // end if

	} // end while tobechecked

	cout << "Order checked: ";
	for (int i = 0; i < distances.size(); i++)
	{
		cout << visited.front() << " ";
		visited.pop_front();
	}
	cout << endl;

}

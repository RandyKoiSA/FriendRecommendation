#include <fstream>
#include <iostream>
#include <sstream>  // for std::istringstream
#include "Graph.h"
#include <algorithm>

// TO DO
// initialize an undirected graph that can store at most n vertices
Graph::Graph(int n) {
	cap = n; 
	adj.resize(cap);
	for (int i = 0; i < cap; i++) {
		adj[i].resize(cap);
		for (int j = 0; j < cap; j++) {
			adj[j].resize(cap);
			adj[i][j] = 0;
		} //setting the 2d vector to false
	}

	
}

// TO DO
// return the maximum number of vertices
int Graph::size() {
	return cap;
}

// TO DO
// give a string label to vertex
void Graph::addLabel(Vertex i, string s) {
	intToLabels[i] = s;
	labelsToInt[s] = i;
}

// TO DO
// add an edge between vertices i and j
void Graph::addEdge(Vertex i, Vertex j) {
	adj[i][j] = true;
}

// TO DO
// return a vector of vertices adjacent to vertex n
vector<Vertex> Graph::getAdjacentVertices(Vertex n) {
	vector<Vertex> x;
	x.resize(cap);
	int y = 0; //increments
	for (int j = 0; j < cap; j++) {
		if (adj[n][j] == true) {
			x[y] = j; 
			y++;
		}
	}
	x.resize(y);
	return x;
}

Vertex Graph::getVertex(string label) {
	return labelsToInt.at(label);
}

string Graph::getLabel(Vertex n) {
	return intToLabels.at(n);
}

// TO DO
// return a list of names that contain friends of friends of person
// names should not be repeated
vector<string> recommendFriends(Graph &graph, const string &person) {
	Vertex nameID = graph.getVertex(person); //gets persons ID using their name
	vector<Vertex> friends = graph.getAdjacentVertices(nameID); //uses their ID to grab their friends
	vector<string> friends2; //Person's friends of friends (string)

	for (int i = 0; i < friends.size(); i++) {
		vector<Vertex> temp = graph.getAdjacentVertices(friends[i]); //grabs the friends of each friend of person as it loops through the loop

		//loops through to check 3 different conditions that the friend of a friend can be 1. yourself 2. already your friend 3. repated friend in final answer
		for (int j = 0; j < temp.size(); j++){
			string nameofFOF = graph.getLabel(temp[j]);  //start              end         look for this...if the friend of a friend is not already a friend, it will hit the end of the iterator
			vector<Vertex>::iterator checkfriends= find(friends.begin(), friends.end(), temp[j]); // which means checkfriends will = end()
			vector<string>::iterator checkfriends2 = find(friends2.begin(), friends2.end(), nameofFOF); //checks to see if we havce already added the friend to the final vector

			if (checkfriends == friends.end() && checkfriends2 == friends2.end() && nameofFOF != person) {
				friends2.push_back(nameofFOF);
			}
		}
	}	
 
	return friends2;
}


// COMPLETED
// read from a text file, the labels (names) to be associate with each vertex (int)
void readNamesFromFile(Graph &graph, const string& filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile)
		throw invalid_argument("Unable to open file " + filename);
	string s;
	int i;
	while (!inputFile.eof()) {
		inputFile >> i >> s;
		// cout << "adding label " << i << ": " << s << endl;
		graph.addLabel(i, s);
	}
}

// COMPLETED
// read from a text file, the list of friends for each vertex (int)
void readFriendsFromFile(Graph &graph, const string& filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile)
		throw invalid_argument("Unable to open file " + filename);

	for (string line; getline(inputFile, line); ) {
		istringstream iss(line);
		int i;
		iss >> i;
		int j;
		while (!iss.eof()) {
			iss >> j;
			cout << "adding edge " << i << " to " << j << endl;
			graph.addEdge(i, j);
		}
	}
}

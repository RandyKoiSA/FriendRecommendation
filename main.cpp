#include <iostream> //..
#include <vector>
#include "Graph.h"

using namespace std;

template <typename E>
bool checkIfEqual(vector<E> actual, vector<E> correct);

int main() {

	try {
		{
			// test basic graph operations
			const int N = 3;
			Graph g(N);
			if (g.size() == N)
				cout << "Number of vertices test passed" << endl;
			else
				cout << "Number of vertices test failed" << endl;
			g.addEdge(0, 1);
			g.addEdge(0, 2);
			g.addEdge(1, 0);
			g.addEdge(2, 0);
			vector<Vertex> v = g.getAdjacentVertices(0);
			if (checkIfEqual<Vertex>(v, { 1, 2 }))
				cout << "Test Adjacent Vertices passed" << endl;
			else
				cout << "Test Adjacent Vertices failed" << endl;
			v = g.getAdjacentVertices(1);
			if (checkIfEqual<Vertex>(v, { 0}))
				cout << "Test Adjacent Vertices passed" << endl;
			else
				cout << "Test Adjacent Vertices failed" << endl;
			v = g.getAdjacentVertices(2);
			if (checkIfEqual<Vertex>(v, { 0}))
				cout << "Test Adjacent Vertices passed" << endl;
			else
				cout << "Test Adjacent Vertices failed" << endl;
		}
		{
			Graph g(10); // build a social network graph
			readFriendsFromFile(g, "friends10.txt");
			readNamesFromFile(g, "names10.txt");
			string name = "Jonathan";
			cout << "\tFriend recommendations for " << name << ":" << endl;
			vector<string> persons = recommendFriends(g, name);
			for (unsigned i = 0; i < persons.size(); i++)
				cout << "\t" << persons[i] << endl;
			if (checkIfEqual<string>(persons, { "Youngeun", "Alfredo"}))
				cout << "Recommendation test passed" << endl;
			else
				cout << "Recommendation test failed" << endl;
		}
		{// A larger example
			Graph g(150); // build a social network graph
			readFriendsFromFile(g, "friends140.txt");
			readNamesFromFile(g, "names143.txt");
			string name = "Jonathan";
			cout << "\tFriend recommendations for " << name << ":" << endl;
			vector<string> persons = recommendFriends(g, name);
			for (unsigned i = 0; i < persons.size(); i++)
				cout << "\t" << persons[i] << endl;
			if (checkIfEqual<string>(persons, { "Alfredo", "Rakan", "Derek", "Julian", "Jackie", "Samrah", "Ryan", "Khadijah", "Alexandra", "Qiyuan", "Andrea", "Christopher" }))
				cout << "Recommendation test (large graph) passed" << endl;
			else
				cout << "Recommendation test (large graph) failed" << endl;
		}

	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	system("pause");
}

template <typename E>
bool checkIfEqual(vector<E> actual, vector<E> correct) {
	if (actual.size() != correct.size())
		return false;
	for (unsigned i = 0; i < actual.size(); i++) {
		bool found = false;
		for (unsigned j = 0; j < correct.size(); j++)
			if (actual[i] == correct[j]) {
				found = true;
				break;
			}
		if (!found) return false;
	}
	return true;
}

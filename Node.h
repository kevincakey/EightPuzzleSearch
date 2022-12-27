#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node{
	public:
		vector<vector<int>> state;
		Node* parentNode;
		double cost;
		int misplacedBy;
		int blankRowIndex;
		int blankColIndex;
		double getCost();
		void setCost(double cost);
		Node(vector<vector<int>>, Node*, double);
		void move(int, int, int, int);
		void printNode();
};

#endif
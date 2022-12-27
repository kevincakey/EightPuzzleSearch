#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "Priority.h"

using namespace std;

class Problem {
 	private:
		Node* initial_state;
		Node* goal_state;
		int expandedCount = 0;
		int queueMaxCount = 0;
		int goalDepth = -1;
		vector<Node*> visited;
	public:
		Problem(Node*);
		bool isGoalState(Node*);
		void uniformCostSearch();
		void AStarMisplacedTiles();
		void AStarEuclidean();
		int getExpandedCount();
		int getQueueMaxCount();
		int getGoalDepth();
		void setGoalState(vector<vector<int>>);
		Node* getGoalState();
		int countMisplacedTiles(Node*, Node*);
		double calculateEuclideanDistance(Node*, Node*);
		vector<int> findNumIndexes(Node*, int);
	private:
		void incrementExpanded();
		void incrementGoalDepth();
		void setQueueMaxCount(int);
		void pushIntoVisited(Node*);
		bool nodeAlreadyVisited(Node*);
		Node* leftNode(Node*);
		Node* rightNode(Node*);
		Node* topNode(Node*);
		Node* bottomNode(Node*);
};

#endif

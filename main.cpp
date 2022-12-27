#include "Problem.h"
#include "Node.h"
#include <string>
#include <time.h>

using namespace std;

int main(){
	int userInput;
	cout << "Welcome to the 862138776 8 puzzle solver.\nType \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
	cin >> userInput;
	vector<vector<int>> v;

	if(userInput == 1){
		v = {{1,2,3},{4,5,6},{7,8,0}};
		cout << "Using default puzzle" << endl;
	}
	else if(userInput == 2){
		vector<int> firstRow;
		vector<int> secondRow;
		vector<int> thirdRow;
		int rowInput;

		cout << "Enter your puzzle, use a zero to represent the blank \nEnter the first row, use space or tabs between numbers" << endl;
		for(int i = 0; i<3; i++){
			cin >> rowInput;
			firstRow.push_back(rowInput);
		}

		cout << "Enter the second row, use space or tabs between numbers" << endl;
		for(int i = 0; i<3; i++){
			cin >> rowInput;
			secondRow.push_back(rowInput);
		}
		cout << "Enter the third row, use space or tabs between numbers" << endl;
		for(int i = 0; i<3; i++){
			cin >> rowInput;
			thirdRow.push_back(rowInput);
		}
		v.push_back(firstRow);
		v.push_back(secondRow);
		v.push_back(thirdRow);
		cout << "Created Initial State:" <<endl;
	}
	else{
		cout << "bad input, try again" << endl;
	}

	Node *node = new Node(v, nullptr, 0);
	Problem *problem = new Problem(node);
	node->printNode();
	vector<vector<int>> goal = {{8,7,1},{6,0,2},{5,4,3}};
	cout << "Goal state is:" << endl;
	problem->setGoalState(goal);
	problem->getGoalState()->printNode();

	cout << "Enter your choice of algorithm: \n 1. Uniform Cost Search \n 2. A* with the Misplaced Tile heuristic \n 3. A* with the Euclidean distance heuristic" << endl;
	

	int algorithmChoice;
	cin >> algorithmChoice;

	clock_t start = clock();

	if(algorithmChoice == 1){
		//call uniform cost search
		problem->uniformCostSearch();
	}
	else if(algorithmChoice == 2){
		//call A* w misplaced tile
		problem->AStarMisplacedTiles();
	}
	else if(algorithmChoice == 3){
		//call A* w Euclidean
		problem->AStarEuclidean();
	}

	cout << "To solve this problem the search algorithm expanded a total of " <<  problem->getExpandedCount() << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time: " << problem->getQueueMaxCount() << "." << endl;
	cout << "The depth of the goal node was " << problem->getGoalDepth() << "." << endl;
	clock_t end = clock();
	cout << "Runtime: " << end - start << endl;
}

//discussed with Partner Jordan Sam for overall code structure
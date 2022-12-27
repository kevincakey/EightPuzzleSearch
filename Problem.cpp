#include "Problem.h"
#include <queue>
#include <cmath>

using namespace	std;

Problem::Problem(Node* n) {
	this->initial_state = n;
}

Node* Problem::getGoalState(){
	return goal_state;
}

void Problem::setGoalState(vector<vector<int>> v){
	this->goal_state = new Node(v, nullptr, 0);
}

bool Problem::isGoalState(Node* n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n -> state.at(i).at(j) != getGoalState() -> state.at(i).at(j)) {
				return false;
			}
		}
	}
	return true;
}

void Problem::incrementExpanded(){
	expandedCount++;
}

int Problem::getExpandedCount(){
	return expandedCount;
}

int Problem::getQueueMaxCount(){
	return queueMaxCount;
}

void Problem::setQueueMaxCount(int c){
	queueMaxCount = c;
}

void Problem::incrementGoalDepth(){
	goalDepth++;
}

int Problem::getGoalDepth(){
	return goalDepth;
}

void Problem::pushIntoVisited(Node* n){
	visited.push_back(n);
}

bool Problem::nodeAlreadyVisited(Node* n){
	for(int i = 0; i < visited.size(); i++){
		int visits = 0;
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				if (n->state.at(j).at(k) == visited.at(i)->state.at(j).at(k))
				{
					visits++;
				}
			}
		}
		if(visits == 8){
			return true;
		}
		visits = 0;
	}
	return false;
}

Node* Problem::leftNode(Node* n){
	if(n->blankColIndex == 0){
		return nullptr;
	}
	Node* newBranch = new Node(n->state, n, n->cost+1);
	newBranch->move(n->blankRowIndex, n->blankColIndex, n->blankRowIndex, n->blankColIndex - 1);
	newBranch->blankColIndex--;

	return newBranch;
}

Node* Problem::rightNode(Node* n){
	if(n->blankColIndex == 2){
		return nullptr;
	}
	Node* newBranch = new Node(n->state, n, n->cost+1);
	newBranch->move(n->blankRowIndex, n->blankColIndex, n->blankRowIndex, n->blankColIndex + 1);
	newBranch->blankColIndex++;

	return newBranch;
}

Node* Problem::topNode(Node* n){
	if(n->blankRowIndex == 0){
		return nullptr;
	}
	Node* newBranch = new Node(n->state, n, n->cost+1);
	newBranch->move(n->blankRowIndex, n->blankColIndex, n->blankRowIndex - 1, n->blankColIndex);
	newBranch->blankRowIndex--;

	return newBranch;
}

Node* Problem::bottomNode(Node* n){
	if(n->blankRowIndex == 2){
		return nullptr;
	}
	Node* newBranch = new Node(n->state, n, n->cost+1);
	newBranch->move(n->blankRowIndex, n->blankColIndex, n->blankRowIndex + 1, n->blankColIndex);
	newBranch->blankRowIndex++;

	return newBranch;
}

void Problem::uniformCostSearch(){
	//cout << "ucs" << endl;
	priority_queue<Node*, vector<Node*>, compare> q;
	//cout << "intial state: " << endl;
	this->initial_state->printNode();
	q.push(this->initial_state);
	if(!q.empty()){
		if(q.size() > getQueueMaxCount()){
			setQueueMaxCount(q.size());
		}
	}
	//cout << "starting while loop" << endl;

	while(!q.empty()){
		//qmax? 37
		if(!q.empty()){
			if(q.size() > getQueueMaxCount()){
				setQueueMaxCount(q.size());
			}
		}
		Node* currNode = q.top();
		q.pop();
		cout << "The best state to expand with is" << endl;
		currNode->printNode();
		if(isGoalState(currNode)){
			cout << endl;
			cout << "GOAL!!!" << endl;
			//print result path
			Node* printPathTmp = currNode;
			while(printPathTmp != nullptr){
				printPathTmp->printNode();
				cout << endl;
				incrementGoalDepth();
				printPathTmp = printPathTmp->parentNode;
			}
			return;
		}
		incrementExpanded();
		cout << "Expanding this node..." << endl << endl;
		//cout << "node not visited" << endl;
		if(!nodeAlreadyVisited(currNode)){
			pushIntoVisited(currNode);
			//cout << "visited" << endl;
			//visited.at(0)->printNode();

			//cout << "making nodes" << endl;

			Node* l = leftNode(currNode);
			//cout << "l node" << endl;
			//l->printNode();
			Node* r = rightNode(currNode);
			//cout << "r node" << endl;
		//r->printNode();
			Node* t = topNode(currNode);
			//cout << "t node" << endl;
			//t->printNode();
			Node* b = bottomNode(currNode);
			//cout << "b node" << endl;
			//b->printNode();
			//cout << "made nodes" << endl;
			if((l != nullptr) && (!nodeAlreadyVisited(l))){
				//cout << "in l" << endl;
				q.push(l);
				//l->printNode();
			}
			if((r != nullptr) && (!nodeAlreadyVisited(r))){
				//cout << "in r" << endl;
				q.push(r);
				//r->printNode();
			}
			if((t != nullptr) && (!nodeAlreadyVisited(t))){
				//cout << "in t" << endl;
				q.push(t);
				//t->printNode();
			}
			if((b != nullptr) && (!nodeAlreadyVisited(b))){
				//cout << "in b" << endl;
				q.push(b);
				//b->printNode();
			}
		}
		//cout << "q.size: " << q.size() << endl;
	}
}

void Problem::AStarMisplacedTiles(){
	//cout << "ucs" << endl;
	priority_queue<Node*, vector<Node*>, compare> q;
	//cout << "intial state: " << endl;
	this->initial_state->printNode();
	q.push(this->initial_state);
	if(!q.empty()){
		if(q.size() > getQueueMaxCount()){
			setQueueMaxCount(q.size());
		}
	}
	//cout << "starting while loop" << endl;

	while(!q.empty()){
		//qmax? 37
		if(!q.empty()){
			if(q.size() > getQueueMaxCount()){
				setQueueMaxCount(q.size());
			}
		}
		Node* currNode = q.top();
		q.pop();
		cout << "The best state to expand with is" << endl;
		currNode->printNode();
		if(isGoalState(currNode)){
			cout << endl;
			cout << "GOAL!!!" << endl;
			//print result path
			Node* printPathTmp = currNode;
			while(printPathTmp != nullptr){
				printPathTmp->printNode();
				cout << endl;
				//cout << "Cost: " << printPathTmp->getCost() << endl;
				incrementGoalDepth();
				printPathTmp = printPathTmp->parentNode;
			}
			return;
		}
		incrementExpanded();
		cout << "Expanding this node..." << endl;
		//cout << "node not visited" << endl;
		if(!nodeAlreadyVisited(currNode)){
			pushIntoVisited(currNode);
			//cout << "visited" << endl;
			//visited.at(0)->printNode();

			//cout << "making nodes" << endl;

			Node* l = leftNode(currNode);
			if(l != nullptr){
				int lTileCount = countMisplacedTiles(l, getGoalState());
				l->setCost(lTileCount);
				//cout << "l node" << endl;
				//l->printNode();
			}
			Node* r = rightNode(currNode);
			if(r != nullptr){
				int rTileCount = countMisplacedTiles(r, getGoalState());
				r->setCost(rTileCount);
				//cout << "r node" << endl;
				//r->printNode();
			}
			Node* t = topNode(currNode);
			if(t != nullptr){
				int tTileCount = countMisplacedTiles(t, getGoalState());
				t->setCost(tTileCount);
				//cout << "t node" << endl;
				//t->printNode();
			}
			Node* b = bottomNode(currNode);
			if(b != nullptr){
				int bTileCount = countMisplacedTiles(b, getGoalState());
				b->setCost(bTileCount);
				//cout << "b node" << endl;
				//b->printNode();
			}
			//cout << "made nodes" << endl;
			if((l != nullptr) && (!nodeAlreadyVisited(l))){
				//cout << "in l" << endl;
				q.push(l);
				//l->printNode();
			}
			if((r != nullptr) && (!nodeAlreadyVisited(r))){
				//cout << "in r" << endl;
				q.push(r);
				//r->printNode();
			}
			if((t != nullptr) && (!nodeAlreadyVisited(t))){
				//cout << "in t" << endl;
				q.push(t);
				//t->printNode();
			}
			if((b != nullptr) && (!nodeAlreadyVisited(b))){
				//cout << "in b" << endl;
				q.push(b);
				//b->printNode();
			}
		}
		//cout << "q.size: " << q.size() << endl;
	}
}

int Problem::countMisplacedTiles(Node* n1, Node* n2){
	int misplacedTileCount = 0;
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			if(n1->state[i][j] != n2->state[i][j]){
				misplacedTileCount++;
			}
		}
	}
	return misplacedTileCount;
}

void Problem::AStarEuclidean(){
	//cout << "ucs" << endl;
	priority_queue<Node*, vector<Node*>, compare> q;
	//cout << "intial state: " << endl;
	this->initial_state->printNode();
	q.push(this->initial_state);
	if(!q.empty()){
		if(q.size() > getQueueMaxCount()){
			setQueueMaxCount(q.size());
		}
	}
	//cout << "starting while loop" << endl;

	while(!q.empty()){
		//qmax? 37
		if(!q.empty()){
			if(q.size() > getQueueMaxCount()){
				setQueueMaxCount(q.size());
			}
		}
		Node* currNode = q.top();
		q.pop();
		cout << "The best state to expand with is" << endl;
		currNode->printNode();
		if(isGoalState(currNode)){
			cout << endl;
			cout << "GOAL!!!" << endl;
			//print result path
			Node* printPathTmp = currNode;
			while(printPathTmp != nullptr){
				printPathTmp->printNode();
				cout << endl;
				//cout << "Cost: " << printPathTmp->getCost() << endl;
				incrementGoalDepth();
				printPathTmp = printPathTmp->parentNode;
			}
			return;
		}
		incrementExpanded();
		cout << "Expanding this node..." << endl;
		//cout << "node not visited" << endl;
		if(!nodeAlreadyVisited(currNode)){
			pushIntoVisited(currNode);
			//cout << "visited" << endl;
			//visited.at(0)->printNode();

			//cout << "making nodes" << endl;

			Node* l = leftNode(currNode);
			if(l != nullptr){
				double lTileCount = calculateEuclideanDistance(l, getGoalState());
				l->setCost(lTileCount);
				//cout << "l node" << endl;
				//cout << "Cost: " << l->getCost() << endl;
				//l->printNode();
			}
			Node* r = rightNode(currNode);
			if(r != nullptr){
				double rTileCount = calculateEuclideanDistance(r, getGoalState());
				r->setCost(rTileCount);
				//cout << "r node" << endl;
				//cout << "Cost: " << r->getCost() << endl;
				//r->printNode();
			}
			Node* t = topNode(currNode);
			if(t != nullptr){
				double tTileCount = calculateEuclideanDistance(t, getGoalState());
				t->setCost(tTileCount);
				//cout << "t node" << endl;
				//cout << "Cost: " << t->getCost() << endl;
				//t->printNode();
			}
			Node* b = bottomNode(currNode);
			if(b != nullptr){
				double bTileCount = calculateEuclideanDistance(b, getGoalState());
				b->setCost(bTileCount);
				//cout << "b node" << endl;
				//cout << "Cost: " << b->getCost() << endl;
				//b->printNode();
			}
			//cout << "made nodes" << endl;
			if((l != nullptr) && (!nodeAlreadyVisited(l))){
				//cout << "in l" << endl;
				q.push(l);
				//l->printNode();
			}
			if((r != nullptr) && (!nodeAlreadyVisited(r))){
				//cout << "in r" << endl;
				q.push(r);
				//r->printNode();
			}
			if((t != nullptr) && (!nodeAlreadyVisited(t))){
				//cout << "in t" << endl;
				q.push(t);
				//t->printNode();
			}
			if((b != nullptr) && (!nodeAlreadyVisited(b))){
				//cout << "in b" << endl;
				q.push(b);
				//b->printNode();
			}
		}
		//cout << "q.size: " << q.size() << endl;
	}
}

double Problem::calculateEuclideanDistance(Node* goalState, Node* n1){ //calculate distance between all elements of states and total them up with the intent to sum with the cost of  a move?
	double totalEuclideanDistance = 0;
	double x;
	double y;
	double hypotenuse;
	vector<int> goalStateIndexes;
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			if(n1->state[i][j] != goalState->state[i][j]){
				goalStateIndexes = findNumIndexes(goalState, n1->state[i][j]);
				x = abs(i - goalStateIndexes[0]);
				//cout << "x: " << x << endl;
				y = abs(j - goalStateIndexes[1]);
				//cout << "y: " << y << endl;
				hypotenuse = sqrt(pow(x, 2) + pow(y, 2));
				//cout << "hypotenuse: " << hypotenuse << endl;
				totalEuclideanDistance += hypotenuse;
			}
		}
	}
	//cout << "Total EuclideanL " << totalEuclideanDistance << endl;
	return totalEuclideanDistance;
}

vector<int> Problem::findNumIndexes(Node* goalState, int num){
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			if(goalState->state[i][j] == num){
				return {i,j};
			}
		}
	}
	return {-10,-10};
}

//discussed with partner Jordan Sam
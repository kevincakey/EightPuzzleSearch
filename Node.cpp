#include "Node.h"

using namespace std;

Node::Node(vector<vector<int>> s, Node* parent, double c){
	this->state = s;
	this->parentNode = parent;
	this->cost = c;
	for (int i = 0; i < state.size(); i++) 
	{
        for (int j = 0; j < state.at(i).size(); j++) 
		{
            if(state.at(i).at(j) == 0) 
			{
                blankRowIndex = i;
				blankColIndex = j;
            }
        }
    }
}

double Node::getCost(){
	return cost;
}

void Node::setCost(double cost){
    this->cost += cost;
}

void Node::move(int r, int c, int r2, int c2){
	int tmp = this->state.at(r2).at(c2);
	state.at(r2).at(c2) = state.at(r).at(c);
	state.at(r).at(c) = tmp;
}

void Node::printNode(){
	for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.at(i).size(); j++) {
            cout << state[i][j];
            if (j != state[i].size() - 1){
                cout << " ";
            }
        }
        cout << endl;
    }
}
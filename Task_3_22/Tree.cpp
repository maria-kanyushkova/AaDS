#include "enum/ETypeNode.h"
#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(string fileContent, size_t& pointer, int initialStarsCount) {
	this->initialize();

	int currentPointer = (int)pointer;
	int fileLength = fileContent.length();

	while (currentPointer <= fileLength) {
		bool conditionFileFirst = fileContent[currentPointer] == '\n';
		bool conditionFileSecond = currentPointer == fileLength;
		if (conditionFileFirst || conditionFileSecond) {
			int tempPointer = currentPointer;
			if (this->type == ETypeNode::LEAF) {
				this->minWeight = stoi(this->weightStr);
				this->weight = stoi(this->weightStr);
				this->maxWeight = stoi(this->weightStr);
			}
			else {
				this->couldHaveWeight = false;
			}
			currentPointer++;
			if (currentPointer > fileLength) {
				break;
			}
			int currStarCount = 0;
			while (fileContent[currentPointer] == '*') {
				currStarCount++;
				currentPointer++;
			}
			if (currentPointer > fileLength) {
				break;
			}
			if (initialStarsCount < currStarCount) {
				if (initialStarsCount == currStarCount - 1) {
					size_t nextpointer = (unsigned int)currentPointer;
					Tree child(fileContent, nextpointer, currStarCount);
					this->childNodes.push_back(child);
				}
			}
			else {
				currentPointer = tempPointer -1;
				break;
			}
		}
		if (fileContent[currentPointer] == ' ') {
			this->didGetName = true;
			currentPointer++;
			continue;
		}
		if (!this->didGetName) {
			this->name += fileContent[currentPointer];
		}
		else {
			bool readConditionFirst = fileContent[currentPointer] == '&';
			bool readConditionSecond = fileContent[currentPointer] == '|';
			if (readConditionFirst || readConditionSecond) {
				if (this->type == ETypeNode::LEAF) {
					this->type = readConditionFirst ? ETypeNode::AND : ETypeNode::OR;
				}
			}
			else if (this->couldHaveWeight) {
				this->weightStr += fileContent[currentPointer];
			}
		}
		currentPointer++;
	}
	pointer = (unsigned int)currentPointer;
}


void Tree::initialize() {
	this->name = "";
	this->weightStr = "";
	this->weight = 0;
	this->maxWeight = 0;
	this->minWeight = 0;
	this->didGetName = false;
	this->couldHaveWeight = true;
	this->type = ETypeNode::LEAF;
}

vector<Tree> Tree::getChildren() { 
	return this->childNodes;
}

const string Tree::toString() {
	string treeString = "";
	treeString += this->name + ' ';

	switch (this->type) {
	case ETypeNode::AND:
		treeString += '&';
		break;
	case ETypeNode::OR:
		treeString += '|';
		break;
	default:
		treeString += to_string(this->weight);
	}
	treeString += '\n';

	return treeString;
};

void Tree::calculateTree() {
	Tree& firstChild = this->childNodes.front();

	int minWeight = 0;
	int maxWeight = 0;
	if (firstChild.type != ETypeNode::LEAF) {
		firstChild.calculateTree();
	}
	minWeight = firstChild.minWeight;
	maxWeight = firstChild.maxWeight;

	for (size_t i = 1; i < this->childNodes.size(); i++) {
		Tree& child = this->childNodes[i];
		if (child.type != ETypeNode::LEAF) {
			child.calculateTree();
		}

		if (this->type == ETypeNode::AND) {
			minWeight += child.minWeight;
			maxWeight += child.maxWeight;
		}
		else {
			if (child.minWeight < minWeight) {
				minWeight = child.minWeight;
			}
			if (child.maxWeight > maxWeight) {
				maxWeight = child.maxWeight;
			}
		}
	}

	this->minWeight = minWeight;
	this->maxWeight = maxWeight;
}

bool Tree::trimTree(const int maxWeight) {
	if (this->minWeight > maxWeight) {
		return false;
	}

	if (this->maxWeight < maxWeight) {
		return true;
	}

	size_t size = this->childNodes.size();
	for (size_t i = 0; i < size; i++) {
		Tree& child = this->childNodes[i];

		int maxWeightForCurrChild = maxWeight;

		if (this->type != ETypeNode::OR) {
			for (size_t j = 0; j < size; j++) {
				if (j == i) continue;

				maxWeightForCurrChild -= this->childNodes[j].minWeight;
			}
		}

		if (child.type != ETypeNode::LEAF) {
			child.trimTree(maxWeightForCurrChild);
		}

		if (child.minWeight > maxWeightForCurrChild&& this->type == ETypeNode::OR && size > 1) {
			this->childNodes.erase(this->childNodes.begin() + i);
			i--;
			size--;
		}
	}

	this->calculateTree();
	return this->minWeight <= maxWeight;
}


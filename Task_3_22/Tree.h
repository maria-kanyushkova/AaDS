#pragma once

#include "enum/ETypeNode.h"
#include <vector>
#include <string>

using namespace std;

class Tree {
private:
    string name;
    string weightStr;

    int weight;
    int maxWeight;
    int minWeight;

    bool didGetName;
    bool couldHaveWeight;

    ETypeNode type;

    vector<Tree> childNodes;

    void initialize();

public:
    Tree(string fileContent, size_t &pointer, int initialStarsCount);

    vector<Tree> getChildren();

    void calculateTree();

    bool trimTree(int maxWeight);

    const string toString();
};

#include "..//Utils.h"

string pad(int len) {
	return move(string(len, '\t'));
} 

// вершина дерева непосредственно в алгоритмах
struct TreeNode {
    Edge *edge;
    TreeNode *parent = nullptr;
    vector<TreeNode *> childs;
    bool leadsToGoal = true; // один из потомков ведет в конечный город, изначально true для печать полного дерева
    bool isFinal = false; // вершина дерева хранит полет, ведущий в конечный город

    TreeNode(Node *from) : edge(new Edge(nullptr, from, string(""))) {}

    TreeNode(Edge *edge) : edge(edge) {}

    // используется для избежания циклических путей
	bool canAddChild(Edge* edge) {
		auto ptr = this;
		while (ptr != nullptr) {
			if (ptr->edge == edge) {
				return false;
			}
			if (ptr->edge->to == edge->to) {
				if (!Utils::getPathIsCyclic()|| ptr->parent != nullptr) {
					return false;
				}
			}
			ptr = ptr->parent;
		}
		return true;
	}

    // пытается добавить потомка в вершину дерева
    TreeNode *addChild(Edge *edge) {
        if (!canAddChild(edge)) {
            return nullptr;
        }

        auto child = new TreeNode(edge);
        childs.push_back(child);
        child->parent = this;
        return child;
    }

    // устанавливает флаг leadsToGoal = true, если вершина прямо или косвенно ведет к конечной точке
    // устанавливает флаг isFinal = true, если вершина ведет к конечной точке
    void updateGoal(Node *goal) {
        leadsToGoal = false;
        if (edge->to == goal) {
            leadsToGoal = true;
            isFinal = true;
        }

        for (auto child : childs) {
            child->updateGoal(goal);
            leadsToGoal = leadsToGoal || child->leadsToGoal;
        }
    }

    void printImpl(ostream &outFile, TreeNode const *newNode, int padding = 0) {
        if (!leadsToGoal) {
            return;
        }

        outFile << (this == newNode ? "+" : "") << edge->to->city << endl;
        for (auto child : childs) {
            if (!child->leadsToGoal) {
                continue;
            }

            outFile << pad(padding + 1) << "->" << child->edge->flight << "->";
            child->printImpl(outFile, newNode, padding + 1);
            outFile << endl;
        }
    }

    void print(ostream &outFile, TreeNode const *newNode = nullptr) {
        printImpl(outFile, newNode);
        outFile << endl;
    }

    // получает путь из вершины дерева
    vector<Edge *> getPath() {
        vector < Edge * > path;

        auto treeNode = this;
        while (treeNode->parent != nullptr) {
            path.push_back(treeNode->edge);
            treeNode = treeNode->parent;
        }
        reverse(path.begin(), path.end());
        return move(path);
    }


    void getPathsImpl(vector <vector<Edge *>> &paths) {
        if (!leadsToGoal) {
            return;
        }

        if (isFinal) {
            paths.push_back(getPath());
        }

        for (auto child : childs) {
            child->getPathsImpl(paths);
        }
    }

    // получает все пути из дерева
    vector <vector<Edge *>> getPaths() {
        vector <vector<Edge *>> paths;
        getPathsImpl(paths);
        return move(paths);
    }
};
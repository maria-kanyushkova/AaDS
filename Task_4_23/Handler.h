#pragma once

#include <fstream>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
#include "struct/Edge.h"
#include "struct/Node.h"
#include "struct/TreeNode.h"
#include "Utils.h"

namespace Handler {
	// вариация поиска в ширину, в очереди хранятся указатели на вершины дерева
	TreeNode* bfs(map<int, Node*>& const nodes, Node* from, ostream& outFile) {
		auto root = new TreeNode(from);
		root->print(outFile, root);

		queue < TreeNode* > q;
		q.push(root);
		while (!q.empty()) {
			auto treeNode = q.front();
			q.pop();

			for (auto edge : treeNode->edge->to->from) {
				auto newTreeNode = treeNode->addChild(edge);
				if (newTreeNode == nullptr) {
					continue;
				}

				root->print(outFile, newTreeNode);
				q.push(newTreeNode);
			}
		}

		return root;
	}

	void printPath(ostream& os, vector<Edge*> const& path) {
		if (path.size() == 0) {
			return;
		}

		for (auto edge : path) {
			os << edge->from->city << " - " << edge->flight << " - ";
		}
		os << path.back()->to->city << endl;
	}

	void printPaths(ostream& outFile, vector <vector<Edge*>> const& paths) {
		for (auto& path : paths) {
			printPath(outFile, path);
		}
	}

	void solve(istream& iCities, istream& in, ostream& out) {
		map<int, Node*> nodes;
		map<Node*, int> rNodes;

		int n;
		iCities >> n;
		for (int i = 0; i < n; i++) {
			int id;
			string city;
			iCities >> id >> city;
			nodes[id] = new Node(id, city);
			rNodes[nodes[id]] = id;
		}

		int from, to;
		in >> n >> from >> to;
		if (from == to) {
			Utils::setPathIsCyclic(true);
		}

		for (int i = 0; i < n; i++) {
			int from, to;
			string flight;
			in >> from >> to >> flight;
			auto edge = new Edge(nodes[from], nodes[to], flight);
			nodes[from]->from.push_back(edge);
			nodes[to]->to.push_back(edge);
		}


		// поиск в ширину
		auto tree = bfs(nodes, nodes[from], out);

		// печатаем дерево без тупиковых путей
		tree->updateGoal(nodes[to]);
		tree->print(out);

		// получаем все пути из дерева, сортируем по длине и печатаем
		auto paths = tree->getPaths();
		sort(paths.begin(), paths.end(), [](vector<Edge*> const& a, vector<Edge*> const& b) {
			return a.size() < b.size();
			});
		printPaths(out, paths);
	}
}
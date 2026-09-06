#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class BTree
{
private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;

		Node(int x) : value(x), left(nullptr), right(nullptr) {}
	};

	void inorder(Node* node)
	{
		if (node == nullptr) return;
		inorder(node->left);
		cout << node->value << " ";
		inorder(node->right);

	}
	Node* OptimalSorted(const vector<int>& arr, int left, int right)
	{
		if (left > right) return nullptr;

		int mid = (left + right) / 2;
		Node* node = new Node(arr[mid]);

		node->left = OptimalSorted(arr, left, mid - 1);
		node->right = OptimalSorted(arr, mid + 1, right);

		return node;
	}
	void clear(Node* node)
	{
		if (node == nullptr) return;
		clear(node->left);
		clear(node->right);
		delete node;
	}

	void rangeSearch(Node* node, int low, int high, vector<int>& res)
	{
		if (node == nullptr) return;

		if (node->value > low) rangeSearch(node->left, low, high, res);
		if (node->value >= low && node->value <= high) res.push_back(node->value);
		if (node->value < high) rangeSearch(node->right, low, high, res);

	}

	void calcLevels(Node* node, int level, int& maxlvl, int& sumlvl, int& count)
	{
		if (node == nullptr) return;
		if (level > maxlvl) maxlvl = level;
		sumlvl += level;
		count++;
		calcLevels(node->left, level + 1, maxlvl, sumlvl, count);
		calcLevels(node->right, level + 1, maxlvl, sumlvl, count);
	}


	Node* root;

public:

	BTree() : root(nullptr) {}

	void add(int x)
	{
		if (root == nullptr)
		{
			root = new Node(x);
			return;
		}

		Node* cur = root;

		while (true)
		{
			if (x < cur->value)
			{
				if (cur->left != nullptr)
				{
					cur = cur->left;
				}
				else
				{
					cur->left = new Node(x);
					return;
				}
			}

			else if (x > cur->value)
			{
				if (cur->right != nullptr)
				{
					cur = cur->right;
				}
				else
				{
					cur->right = new Node(x);
					return;
				}
			}

			else 
			{
					return;
			}
		}

	}

	bool find(int x)
	{
		if (root == nullptr) return false;

		Node* cur = root;

		while (cur != nullptr)
		{
			if (x > cur->value) cur = cur->right;
			else if (x < cur->value) cur = cur->left;
			else return true;
		}

		return false;
	}

	int findlevel(int x)
	{
		if (root == nullptr) return -1;

		Node* cur = root;
		int lvl = 0;

		while (cur != nullptr)
		{
			if (x > cur->value) { cur = cur->right; lvl++;}
			else if (x < cur->value) { cur = cur->left; lvl++; }
			else return lvl;

		}
		return -1;
	}

	void print()
	{
		inorder(root);
		cout << '\n';

	}

	void massTree(const vector<int>& arr)
	{
		for (int x : arr)
		{
			add(x);
		}
	}

	void OptimalTree(vector<int> arr)
	{
		clear(root);
		root = nullptr;

		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());

		root = OptimalSorted(arr, 0, (int)arr.size() - 1);
	}
	
	vector<int> getRes(int low, int high)
	{
		vector<int> res;
		rangeSearch(root, low, high, res);
		return res;
	}
	
	void levels()
	{
		if (root == nullptr)
		{
			cout << "Pusto" << endl;
			return;
		}

		int maxlvl = 0, count = 0, sumlvl = 0;
		calcLevels(root, 0, maxlvl, sumlvl, count);
		double avglvl = double(sumlvl) / count;
		cout << "maxlvl = " << maxlvl << endl;
		cout << "avglvl = " << avglvl << endl;
	}

	~BTree()
	{
		clear(root);
	}
};
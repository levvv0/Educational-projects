#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "BTree.cpp"

using namespace std;

int main()
{
	srand(time(0));
	vector<int> arr;

	for (int i = 0; i < 15; i++)
	{
		arr.push_back(rand() % 50);
	}

	BTree tree;
	BTree opt;
	opt.OptimalTree(arr);
	tree.massTree(arr);
	cout << "mass = ";
	for (int x : arr)
	{
		cout << x << " ";
	}
	cout << endl;
	tree.print();
	tree.levels();
	cout << "opt = ";
	opt.print();
	opt.levels();
}
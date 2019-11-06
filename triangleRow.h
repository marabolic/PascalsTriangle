#pragma once
#include <iostream>
using namespace std;

using ulli = double;
class Row {
	int n;
	int *row;
public:
	Row() { n = 0; row = nullptr; }
	Row(int n) { 
		row = new int[n+1];
	}
	Row(const Row& r) {
		row = new int[n = r.n + 1];
		for (int i = 0; i < n + 1; i++)
		{
			row[i] = r.row[i];
		}
	}
	Row(Row&& r) { 
		row = r.row;
		r.row = nullptr;
		n = r.n;
	}
	~Row() { delete [] row; }

	ulli returnValue(int k, int n) const;
	int interpolSearch(int key, int n, bool &subFun, ulli newHigh) const;
	int ternarySearch(int key, int n, bool &subFun, ulli &firstB) const;
	int hybridSearch(int key, int n) const;
};
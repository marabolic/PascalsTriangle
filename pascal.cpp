#include <iostream>
#include "triangleRow.h"

using namespace std;
using ulli = double;

ulli Row::returnValue(int k, int n) const {
	ulli nFacDiv = 1, kFac = 1;
	int temp = n;
	if (k > n / 2)
		k = n - k;
	for (int i = 1; i <= k; i++)
	{
		nFacDiv *= temp;
		temp--;
	}
	for (int i = 2; i <= k; i++)
	{
		kFac *= i;
	}
	if (k == 0) kFac = 1;
	return nFacDiv / kFac;
}

int Row::interpolSearch(int key, int n, bool &subFun, ulli newHigh) const {
	bool flag = false;
	ulli high = n / 2, low = 0;
	if (subFun) {
		high = newHigh;
	}
	ulli mid = 0;

	int count = 0;
	while (low <= high) {
		mid = low + (high - low)*(key - returnValue(low, n)) / (returnValue(high, n) - returnValue(low, n));
		count++;
		if (returnValue(mid, n) == key) {
			flag = true;
			break;
		}
		else {
			if (returnValue(mid, n) > key) {
				high = mid - 1;
			}
			else 
				low = mid + 1;
		}
		if (returnValue(high, n) != key) 
			high--;
		if (returnValue(low, n) != key) 
			low++;
		
	}
	if (flag) {
		int intMid = static_cast<int> (mid);
		cout << "\npozicija " << intMid;
		return count;
	}
	else {
			cout << "\nneuspesno pretrazivanje\n";
			return 0;
		
		

	}
	
}

int Row::ternarySearch(int key, int n, bool &subFun, ulli &firstB) const {
	int temp = n / 2;
	bool flag = false;
	int firstBorder = temp/3, secondBorder = 2*temp/3;
	int count = 0;
	int index;
	while (firstBorder <= secondBorder && firstBorder >= 0 && secondBorder <= temp) {
		count++;
		if (key <= returnValue(firstBorder,n)){
			if (key == returnValue(firstBorder, n)) {
				index = firstBorder;
				flag = true;
				break;
			}
			temp = firstBorder - 1;
			firstBorder = temp / 3;
			secondBorder = 2 * temp / 3;
			if (subFun) {
				firstB = temp;
				subFun = true;
				break;
			}
		}
		else {
			if (key <= returnValue(secondBorder, n)) {
				if (key == returnValue(secondBorder, n)) {
					index = secondBorder;
					flag = true;
					break;
				}
					
				temp = secondBorder - 1;
				firstBorder = firstBorder + (temp - firstBorder + 1) / 3;
				secondBorder = firstBorder + 2 * (temp - firstBorder + 1)/ 3;
				if (subFun) {
					subFun = false;
					break;
				}
			}
			else {
				if (key <= returnValue(temp, n)) {
					if (key == returnValue(temp, n)) {
						index = temp;
						flag = true;
						break;
					}
					temp = temp - 1;
					firstBorder = secondBorder + (temp - secondBorder + 1) / 3;
					secondBorder = secondBorder + 2 *  (temp - secondBorder + 1)/ 3;
					if (subFun) {
						subFun = false;
						break;
					}
				}
				else break;
			}
		}
			
	}
	if (flag) {
		cout << "\npozicija " << index;
		return count;
	}
	else {
		if (!subFun) {
			//cout << "\n ternarno neuspesno pretrazivanje\n";
			return 0;
		}
		else
			return count;
	}
}

int Row::hybridSearch(int key, int n) const {
	int count = 0;
	bool flag = true;
	ulli newB = 0;
	count = ternarySearch(key, n, flag, newB);
	if (flag) {
		count += interpolSearch(key, n, flag, newB);
	}
	else {
		count = ternarySearch(key, n, flag, newB);
	}
	return count;
}



int main() {
	int rowNumber, key; 
	cout << "unesi red\n";
	cin >> rowNumber;
	Row r = Row(rowNumber);
	
	cout << "unesi kljuc za pretragu\n";
	cin >> key;
	
	bool flag = false;
	ulli newB = 0;
	
	int countTern = r.ternarySearch(key, rowNumber, flag, newB);
	int countInter = r.interpolSearch(key, rowNumber, flag, newB);
	int countHybrid = r.hybridSearch(key, rowNumber);
	cout << "\nbroj pristupa interpol " << countInter << "\nbroj pristupa tern " << countTern << "\nbroj pristupa hibrid " << countHybrid << "\n";
	system("PAUSE");

}

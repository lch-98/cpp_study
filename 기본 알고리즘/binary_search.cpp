#include <iostream>
using namespace std;

int main() {
	int left = 1;
	int right = 10;

	int target = 7;
	while (left <= right) {
		int mid = (left + right) / 2;

		if (mid < target) left = mid + 1;
		else if (mid > target) right = mid - 1;
		else if (mid == target) {
			cout << "answer: " << left << " " << right << " " << mid << "\n";
			break;
		}
		cout << left << " " << right << " " << mid << "\n";
	}
}
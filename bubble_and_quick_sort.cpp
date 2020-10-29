#include<iostream>
#include<fstream>
#include <vector>
#include<chrono>
using namespace std;
using namespace std::chrono;
 
void readFile(vector<int> &numbers_bubble, vector<int>& numbers_quick) {

	int data = 0;
	string filename;

	cout << "enter file name to bubble sort" << endl;
	cin >> filename;
	ifstream file(filename, std::ios_base::in);
	while (file >> data) {

		numbers_bubble.push_back(data);
		}
	file.close();
	cout << "enter file name to quick sort" << endl;
	cin >> filename;
	ifstream file2(filename, std::ios_base::in);
	while (file2 >> data) {

		numbers_quick.push_back(data);
	}
	file2.close();

}

void bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{

				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		// IF no two elements were swapped by inner loop, then break 
		if (swapped == false)
			break;
	}
}
int get_pivot(int* arr, int first, int last) {
	int middle = (last + first) / 2;
	if (((arr[first] >= arr[middle] && arr[first] <= arr[last]))) {
		swap(arr[first], arr[last]);
		swap(arr[first], arr[middle]);
		return arr[last];
	}
	else if ((arr[first] >= arr[last] && arr[first] <= arr[middle])) {
		swap(arr[first], arr[last]);

		return arr[last];
	}
	else if (((arr[middle] >= arr[first] && arr[middle] <= arr[last]))) {
		swap(arr[middle], arr[last]);
		return arr[last];
	}
	else if ((arr[middle] >= arr[last] && arr[middle] <= arr[first])) {
		swap(arr[middle], arr[last]);
		swap(arr[first], arr[middle]);
		return arr[last];

	}
	else {
		if (arr[middle] < arr[first])
			swap(arr[first], arr[middle]);
		return arr[last];

	}
}
int partition(int* arr, int first, int last) {
	int pivot_value = get_pivot(arr, first, last);
	int lastS1 = first;
	int firstUnkown = lastS1;
	while (firstUnkown < last) {
		if (arr[firstUnkown] < pivot_value)
		{
			swap(arr[lastS1++], arr[firstUnkown]);
		}
		firstUnkown++;
	}

	swap(arr[last], arr[lastS1]);
	return lastS1;

}
void quick_sort(int* arr, int first, int last) {

	if (first < last) {
		int pivot = partition(arr, first, last);
		quick_sort(arr, first, pivot);
		quick_sort(arr, pivot + 1, last);
	}
}
int main() {
	vector<int> numbers_quick ;
	vector<int> numbers_bubble ;
	readFile(numbers_bubble, numbers_quick);
	int* arr_quick = &numbers_quick[0];
	int n_quick = numbers_quick.size();
	int* arr_bubble = &numbers_bubble[0];
	int n_bubble = numbers_bubble.size();
	auto start_bubble = high_resolution_clock::now();
	bubbleSort(arr_bubble, n_bubble);
	auto stop_bubble = high_resolution_clock::now();
	cout << "bubblesort running time" << '\n';
//	for (int j = 0; j < n_bubble; j++) {
	//	cout << arr_bubble[j] << '\n';
	//}
	auto duration_bubble = duration_cast<microseconds>(stop_bubble - start_bubble);
	cout << duration_bubble.count() << " microseconds" << endl;
	auto start_quick = high_resolution_clock::now();
	quick_sort(arr_quick, 0, n_quick - 1);
	auto stop_quick = high_resolution_clock::now();
	cout << "quicksort running time" << '\n';
	//for (int j = 0; j < n_quick; j++) {
		//cout << arr_quick[j] << '\n';
	//}
	auto duration_quick = duration_cast<microseconds>(stop_quick - start_quick);
	cout << duration_quick.count()<<" microseconds" << endl;
	bool identical = true;
	if (n_quick != n_bubble)
		identical = false;
	for (int i =0, j = 0; identical == true && i < n_quick && j < n_bubble; i++, j++) {
		if (arr_quick[i] != arr_bubble[j]) {
			identical = false;
		}
	}
	if (identical == true) {
		cout << "Files are identical" << endl;
	}
	else {
		cout << "Files are not identical" << endl;

	}
	return 0;
}
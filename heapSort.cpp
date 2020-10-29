#include<iostream>
#include<fstream>
#include <vector>
#include<chrono>
using namespace std;
using namespace std::chrono;
vector<int> readFile() {

	int data = 0;
	vector<int> numbers;
	string filename;

	cout << "enter file name" << endl;
	cin >> filename;
	ifstream file(filename, std::ios_base::in);
	numbers.push_back(0);
	while (file >> data) {

		numbers.push_back(data);
	}
	file.close();
	return numbers;
}

void max_heapify(int* arr, int i, int n)
{
	//int n = sizeof(arr)/sizeof(int);
	int largest = i;

	int left = 2 * i;
	int right = 2 * i + 1;
	if (left <= n && arr[left] > arr[i])
		largest = left;
	else {
		largest = i;
	}

	if (right <= n && arr[right] > arr[largest])
		largest = right;

	if (largest != i)
	{
		swap(arr[largest], arr[i]);
       max_heapify(arr, largest, n);

	}


}

void constructheap(int* num, int n)
{
	for (int i = (n / 2); i >= 1; i--)
	{
		max_heapify(num, i, n);
	}
}



void HeapSort(int* arr, int n)
{
	constructheap(arr, n);
	for (int i = n; i > 1; i--) {
		swap(arr[i], arr[1]);
		max_heapify(arr, 1, i-1);
	}
	


}


int main() {
	vector<int> numbers1 = readFile();
	int n = numbers1.size();
	int x = n - 1;
	int* arr1 = &numbers1[0];
	std::cout << "heapsort" << '\n';
	auto start_heap = high_resolution_clock::now();
	HeapSort(arr1, x);
	auto stop_heap = high_resolution_clock::now();
	for (int i = 1; i < numbers1.size(); i++) {
		cout << arr1[i] << '\n';
	}
	cout << "heapsort running time" << '\n';
	auto duration_heap = duration_cast<microseconds>(stop_heap - start_heap);
	cout << duration_heap.count() <<" microsecond"<< endl;
return 0;
}
#include <iostream>

using namespace std;

void swap(int *arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

int parent(int i) {
  return i / 2;
}
int left(int i ) {
  return 2 * i;
}

int right(int i) {
  return 2 * i + 1;
}

void Sift_Down(int* arr, int i, int size) {
  int l = left(i);
  int r = right(i);
  int largest;
  if (l <= size && arr[l] > arr[i]) {
    largest = l;

  } else {
    largest = i;
  }
  if (r <= size && arr[r] > arr[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(arr, i, largest);
  }
  if (l < size && r < size && largest != i) {
    Sift_Down(arr, largest, size);
  }
}
//n/2 log(n)
void Build_max_heap(int* arr, int size) {
  for (int i = size / 2; i >= 1; i--) {
    Sift_Down(arr, i, size);
  }
}
//nlog(n), in-place
void HeapSort(int* arr, int size) {
  Build_max_heap(arr, size);
  for (int i = size; i >= 2; i--) {
    swap(arr, 1, i);
    size -= 1;
    Sift_Down(arr, 1, size);
  }
}

int main() {
  int* arr = new int[131072];
  int size;
  cin >> size;
  for (int i = 0; i < size; i++) {
    cin >> arr[i + 1];
  }
  HeapSort(arr, size);
  for (int i = 1; i <= size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  delete[] arr;
  return 0;
}
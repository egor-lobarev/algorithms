#include <iostream>

using namespace std;

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

int parent(int i) { return i / 2; }

int left(int i) { return 2 * i; }

int right(int i) { return 2 * i + 1; }

int Sift_Down(int* arr, int i, int size) {
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
    return Sift_Down(arr, largest, size);
  }
  return i;
}

int SiftUp(int* pyramide, int i) {
  int prnt = parent(i);
  if (prnt >= 1 && pyramide[prnt] < pyramide[i]) {
    swap(pyramide, prnt, i);
    return SiftUp(pyramide, prnt);
  }
  return i;
}

void Insert(int* pyramide, int size, int value) {
  pyramide[size + 1] = value;
  cout << SiftUp(pyramide, size + 1) << endl;
}

void ExtractMax(int* pyramide, int size) {
  if (size == 0) {
    cout << -1 << endl;
    return;
  }
  int max = pyramide[1];
  swap(pyramide, 1, size);
  int index = Sift_Down(pyramide, 1, size - 1);
  if (size == 1) {
    cout << 0 << " " << max << endl;
    return;
  }
  cout << index << " " << max << endl;
}

void Delete(int* arr, int size, int index) {
  if (index > size || index < 1) {
    cout << -1 << endl;
    return;
  }
  cout << arr[index] << endl;
  swap(arr, size, index);
  Sift_Down(arr, index, size - 1);
  SiftUp(arr, index);
}

void Out(int* arr, int size) {
  for (int i = 1; i <= size; i++) {
    cout << arr[i] << " ";
  }
}

int main() {
  int* pyramide = new int[131072];
  int n;
  int capacity;
  int size = 0;
  cin >> capacity >> n;
  for (int i = 0; i < n; i++) {
    int x;
    int value;
    cin >> x;
    if (x == 1) {
      ExtractMax(pyramide, size);
      if (size > 0) {
        size--;
      }
      continue;
    }
    if (x == 2) {
      cin >> value;
      if (size == capacity) {
        cout << -1 << endl;
      } else {
        Insert(pyramide, size, value);
        size++;
      }
      continue;
    }
    if (x == 3) {
      int index;
      cin >> index;
      Delete(pyramide, size, index);
      if (index <= size && index > 0) {
        size--;
      }
    }
  }
  Out(pyramide, size);
  delete[] pyramide;
  return 0;
}
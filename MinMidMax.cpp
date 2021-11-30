#include <iostream>
#include <cstring>

using namespace std;

struct MinMaxHeap {
  int* maxArr = new int[200000];
  int* minArr = new int[200000];
  int size = 0;
};

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

int parent(int i) {
  return i / 2;
}

int right(int i) {
  return 2 * i;
}

int left(int i) {
  return 2 * i + 1;
}

int Partition(int* arr, int first, int last) {
  int pivot_value = arr[(first + last) / 2];
  int i = first - 1;
  int j = last + 1;
  while (true) {
    do {
      j--;
    } while (arr[j] > pivot_value);
    do {
      i++;
    } while (arr[i] < pivot_value);
    if (i < j) {
      swap(arr, i, j);
    } else {
      return j;
    }
  }
}

int find_k_Statistic(int* arr, int size, int k) {
  int left = 0, right = size - 1;
  while (true) {
    int mid = Partition(arr, left, right);
    if (mid == k - 1) {
      return arr[mid];
    }
    if (k - 1 < mid) {
      right = mid;
    } else {
      left = mid;
    }
  }
}

void SiftUpMin(int* arrMin, int i) {
  int prnt = parent(i);
  if (prnt >= 1 && arrMin[prnt] > arrMin[i]) {
    swap(arrMin, prnt, i);
    SiftUpMin(arrMin, prnt);
  }
}

void SiftUpMax(int* arrMax, int i) {
  int prnt = parent(i);
  if (prnt >= 1 && arrMax[prnt] < arrMax[i]) {
    swap(arrMax, prnt, i);
    SiftUpMax(arrMax, prnt);
  }
}

void SiftDownMin(int* arrMin, int i, int size) {
  int l = left(i), r = right(i);
  int smallest = i;
  if (l <= size && arrMin[l] < arrMin[i]) {
    smallest = l;
  }
  if (r <= size && arrMin[r] < arrMin[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    swap(arrMin, smallest, i);
    SiftDownMin(arrMin, smallest, size);
  }
}

void SiftDownMax(int* arrMax, int i, int size) {
  int l = left(i), r = right(i);
  int largest = i;
  if (l <= size && arrMax[l] > arrMax[i]) {
    largest = l;
  }
  if (r <= size && arrMax[r] > arrMax[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(arrMax, largest, i);
    SiftDownMax(arrMax, largest, size);
  }
}

void Insert(MinMaxHeap* heap, int value) {
  int size = ++heap->size;
  heap->maxArr[size] = value;
  heap->minArr[size] = value;
  SiftUpMin(heap->minArr, size);
  SiftUpMax(heap->maxArr, size);
}

int Find(const int* arr, int x, int size) {
  for (int i = 1; i <= size; i++) {
    if (arr[i] == x) {
      return i;
    }
  }
  return -1;
}

void DeleteMin(int* arrMin, int value, int size) {
  int indx = Find(arrMin, value, size);
  swap(arrMin, indx, size);
  SiftDownMin(arrMin, indx, size - 1);
  SiftUpMin(arrMin, indx);
}

void DeleteMax(int* arrMax, int value, int size) {
  int indx = Find(arrMax, value, size);
  swap(arrMax, indx, size);
  SiftDownMax(arrMax, indx, size - 1);
  SiftUpMax(arrMax, indx);
}

void ExtractMin(MinMaxHeap* heap) {
  if (heap->size == 0) {
    return;
  }
  int size = heap->size;
  int value = heap->minArr[1];
  cout << value << endl;
  swap(heap->minArr, 1, size);
  SiftDownMin(heap->minArr, 1, size - 1);
  DeleteMax(heap->maxArr, value, size);
  heap->size--;
}

void ExtractMax(MinMaxHeap* heap) {
  if (heap->size == 0) {
    return;
  }
  int size = heap->size;
  int value = heap->maxArr[1];
  cout << value << endl;
  swap(heap->maxArr, 1, size);
  SiftDownMax(heap->maxArr, 1, size - 1);
  DeleteMin(heap->minArr, value, size);
  heap->size--;
}

void ExtractMid(MinMaxHeap* heap) {
  if (heap->size == 0) {
    return;
  }
  if (heap->size == 1) {
    cout << heap->minArr[1] << endl;
    heap->size--;
    return;
  }
  int ind;
  if (heap->size % 2 == 0) {
    ind = heap->size / 2;
  } else {
    ind = heap->size / 2 + 1;
  }
  int size = heap->size;
  int* copy_min = new int[size];
  for (int i = 1; i <= size; i++) {
    copy_min[i - 1] = heap->minArr[i];
  }
  int mid = find_k_Statistic(copy_min, heap->size, ind);
  int index_min = Find(heap->minArr, mid, size);
  int index_max = Find(heap->maxArr, mid, size);
  swap(heap->minArr, size, index_min);
  SiftDownMin(heap->minArr, index_min, size - 1);
  SiftUpMin(heap->minArr, index_min);
  swap(heap->maxArr, size, index_max);
  SiftDownMax(heap->maxArr, index_max, size - 1);
  SiftUpMax(heap->maxArr, index_max);
  heap->size--;
  cout << mid << endl;
  delete[] copy_min;
}

int main() {
  MinMaxHeap* heap = new MinMaxHeap;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x[16] = {};
    int value;
    cin >> x;
    if (strcmp(x, "add") == 0) {
      cin >> value;
      Insert(heap, value);
      continue;
    }
    if (strcmp(x, "min") == 0) {
      ExtractMin(heap);
    }
    if (strcmp(x, "max") == 0) {
      ExtractMax(heap);
    }
    if (strcmp(x, "mid") == 0) {
      ExtractMid(heap);
    }
  }
  delete[] heap->maxArr;
  delete[] heap->minArr;
  delete heap;
  return 0;
}
#include <iostream>

void Swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int Partition(int* a, int first, int last) {
  int pivot_value = a[(first + last) / 2];
  int i = first - 1;
  int j = last + 1;
  int p = first;
  int q = last;
  while (true) {
    do {
      if ()
      j--;
    } while (a[j] > pivot_value);
    do {
      i++;
    } while (a[i] < pivot_value);
    if (i < j) {
      Swap(a[i], a[j]);
    } else {
      return j;
    }
  }
}

void QuickSort(int* a, int first, int last) {
  if (first >= last) {
    return;
  }
  int pivot_ind = Partition(a, first, last);
  QuickSort(a, first, pivot_ind);
  QuickSort(a, pivot_ind + 1, last);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  QuickSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
  delete[] arr;
  return 0;
}
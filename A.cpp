#include <iostream>

using namespace std;

void Swap(long long& a, long long& b) {
  long long tmp = a;
  a = b;
  b = tmp;
}

int Partition(long long* arr, int first, int last) {
  long long pivot_value = arr[(first + last) / 2];
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
      Swap(arr[i], arr[j]);
    } else {
      return j;
    }
  }
}

long long find_k_Statistic(long long* arr, int size, int k) {
  int left = 0, right = size - 1;
  while (true) {
    int mid = Partition(arr, left, right);
    if (mid == k - 1) {
      return arr[mid];
    }
    if (k - 1 < mid) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
}

int main() {
  long long A_0, A_1;
  int n, k;
  cin >> n >> k >> A_0 >> A_1;
  long long* arr = new long long[n];
  arr[0] = A_0;
  arr[1] = A_1;
  for (int i = 2; i < n; i++) {
    long long tmp = (A_1 * 123 + A_0 * 45) % (10000000 + 4321);
    arr[i] = tmp;
    A_0 = A_1;
    A_1 = tmp;
  }
  cout << find_k_Statistic(arr, n, k) << endl;
  delete[] arr;
}
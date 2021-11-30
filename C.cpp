#include <iostream>

using namespace std;

int* Merge(const int* arr1, int size1, const int* arr2, int size2) {
  int* res = new int[size1 + size2];
  int ind_res = 0;
  int ind1 = 0, ind2 = 0;
  while (ind1 < size1 && ind2 < size2) {
    int a1 = arr1[ind1], a2 = arr2[ind2];
    if (a1 < a2) {
      res[ind_res] = a1;
      ind1++;
      ind_res++;
    } else {
      res[ind_res] = a2;
      ind2++;
      ind_res++;
    }
  }
  while (ind1 < size1) {
    res[ind_res] = arr1[ind1];
    ind_res++;
    ind1++;
  }
  while (ind2 < size2) {
    res[ind_res] = arr2[ind2];
    ind_res++;
    ind2++;
  }
  return res;
}

int main() {
  int K;
  int size, size_res;

  cin >> K;
  cin >> size_res;
  int* res = new int[size_res];
  for (int i = 0; i < size_res; i++) {
    cin >> res[i];
  }

  for (int cnt = 0; cnt < K - 1; cnt++) {
    cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
      cin >> arr[i];
    }
    int* tmp = res;
    res = Merge(arr, size, res, size_res);
    size_res += size;
    delete[] arr;
    delete[] tmp;
  }
  for (int i = 0; i < size_res; i++) {
    cout << res[i] << " ";
  }
  delete[] res;
  return 0;
}
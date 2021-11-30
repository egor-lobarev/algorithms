#include <iostream>
#include <cstring>

using namespace std;

struct Student {
  char* name{};
  char* surname{};
  int Mark = 0;
};

void Merge(const Student* arr1, const Student* arr2, int size_arr1, int size_arr2, Student* result) {
  int i = 0, j = 0, k = 0;
  while (i < size_arr1 && j < size_arr2) {
    if (arr1[i].Mark >= arr2[j].Mark) {
      result[k] = arr1[i++];
    } else {
      result[k] = arr2[j++];
    }
    k++;
  }
  while (i < size_arr1) {
    result[k] = arr1[i++];
    k++;
  }
  while (j < size_arr2) {
    result[k] = arr2[j++];
    k++;
  }
}

void MergeSortR(Student* arr, int n) {
  if (n < 2) {
    return;
  }
  Student* copy_arr = new Student[n];
  for (int i = 0; i < n; i++) {
    copy_arr[i] = arr[i];
  }
  MergeSortR(copy_arr, n / 2);
  MergeSortR(copy_arr + n / 2, n - n / 2);
  Merge(copy_arr, copy_arr + n / 2, n / 2, n - n / 2, arr);
  delete[] copy_arr;
}

void Print(Student* arr, int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i].name << " " << arr[i].surname << endl;
  }
}

void Clear(Student* arr, int size) {
  for (int i = 0; i < size; i++) {
    delete[] arr[i].name;
    delete[] arr[i].surname;
  }
}

int main() {
  int N;
  cin >> N;
  Student* arr = new Student[N];
  for (int i = 0; i < N; i++) {
    char* name = new char[10001];
    char* surname = new char[10001];
    cin >> name >> surname;
    int a, b, c;
    cin >> a >> b >> c;
    arr[i].Mark = a + b + c;
    arr[i].name = name;
    arr[i].surname = surname;
  }
  MergeSortR(arr, N);
  Print(arr, N);
  Clear(arr, N);
  delete[] arr;
  return 0;
}
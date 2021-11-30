#include <iostream>

using namespace std;

struct Student {
  char* name = nullptr;
  char* surname = nullptr;
  int Mark = 0;
  int index = 0;
};

bool operator > (Student a, Student b) {
  return a.Mark > b.Mark;
}

bool operator < (Student a, Student b) {
  return a.Mark < b.Mark || (a.Mark == b.Mark && a.index > b.index);
}

bool operator <= (Student& a, Student& b) {
  return a.Mark < b.Mark || (a.Mark == b.Mark && a.index > b.index);
}

void swap(Student& a, Student& b) {
  Student tmp = a;
  a = b;
  b = tmp;
}

int LowerBound(Student* arr, int begin, int end, Student& x) {
  int mid;
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (x <= arr[mid]) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return begin;
}

void swapEq(Student* arr, int begin1, int begin2, int size) {
  for (int i = 0; i < size; i++) {
    swap(arr[begin1 + i], arr[begin2 + i]);
  }
}

void swapUneq(Student* arr, int l, int mid, int r) {
  while (mid - l > 0 && r - mid > 0) {
    if (mid - l < r - mid) {
      swapEq(arr, l, r - mid + l, mid - l);
      r = r - mid + l;
    } else {
      swapEq(arr, l, mid, r - mid);
      l = r - mid + l;
    }
  }
}
void InPlaceMerge(Student* arr, int l, int mid, int r) {
  if (mid - l < 1 || r - mid < 1) {
    return;
  }
  int x = l + (mid - l) / 2;
  int lb = LowerBound(arr, mid, r, arr[x]);
  swapUneq(arr, x, mid, lb);
  InPlaceMerge(arr, l, x, x + (lb - mid));
  InPlaceMerge(arr, x + (lb - mid) + 1, lb, r);
}

void MergeSort(Student* arr, int l, int r) {
  if (r - l < 2) {
    return;
  }
  int mid = l +  (r - l) / 2;
  MergeSort(arr, l, mid);
  MergeSort(arr, mid, r);
  InPlaceMerge(arr, l, mid, r);
}

void MergeSort(Student* student_array, size_t left, size_t right) {
  if (right - left > 1) {
    size_t mid = left + (right - left) / 2;
    MergeSort(student_array, left, mid);
    MergeSort(student_array, mid, right);
    InPlaceMerge(student_array, left, mid, right);
  }
}

void Clear(Student* array, int size) {
  for (int i = 0; i < size; i++) {
    delete[] array[i].name;
    delete[] array[i].surname;
  }
}

void print(Student* arr, int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i].name << " " << arr[i].surname << endl;
  }
}

int main() {
  int N;
  cin >> N;
  Student* arr = new Student[N];
  for (int i = 0; i < N; i++) {
    char* name = new char[100];
    char* surname = new char[100];
    cin >> name >> surname;
    int a, b, c;
    cin >> a >> b >> c;
    arr[i].Mark = a + b + c;
    arr[i].name = name;
    arr[i].surname = surname;
    arr[i].index = i;
  }
  MergeSort(arr, 0, N);
  print(arr, N);
  Clear(arr, N);
  delete[] arr;
  return 0;
}


#include <iostream>

using namespace std;

struct Student {
  char* name = nullptr;
  char* surname = nullptr;
  int Mark = 0;
};

bool operator>=(Student a, Student b) {
  return a.Mark >= b.Mark;
}

void swap(Student& a, Student& b) {
  Student tmp = a;
  a = b;
  b = tmp;
}

Student* LowerBound(Student* begin, Student* end, Student* x) {
  Student* mid;
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (*x >= *mid) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return begin;
}

void swapEq(Student* begin1, Student* begin2, long long size) {
  for (long long i = 0; i < size; i++) {
    swap(begin1[i], begin2[i]);
  }
}

void swapUneq(Student* l, Student* mid, Student* r) {
  while (mid - l > 0 && r - mid > 0) {
    if (mid - l < r - mid) {
      swapEq(l, r - mid + l, mid - l);
      r = r - mid + l;
    } else {
      swapEq(l, mid, r - mid);
      l = r - mid + l;
    }
  }
}
void InPlaceMerge(Student* l, Student* mid, Student* r) {
  if (mid - l < 1 || r - mid < 1) {
    return;
  }
  Student* x = l + (mid - l) / 2;
  Student* lb = LowerBound(mid, r, x);
  swapUneq(x, mid, lb);
  InPlaceMerge(l, x, x + (lb - mid));
  InPlaceMerge(x + (lb - mid) + 1, lb, r);
}

void MergeSort(Student* l, Student* r) {
  if (r - l < 2) {
    return;
  }
  Student* mid = l + (r - l) / 2;
  MergeSort(l, mid);
  MergeSort(mid, r);
  InPlaceMerge(l, mid, r);
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
    char* name = new char[1000];
    char* surname = new char[1000];
    cin >> name >> surname;
    int a, b, c;
    cin >> a >> b >> c;
    arr[i].Mark = a + b + c;
    arr[i].name = name;
    arr[i].surname = surname;
  }
  MergeSort(arr, arr + N);
  print(arr, N);
  Clear(arr, N);
  delete[] arr;
  return 0;
}
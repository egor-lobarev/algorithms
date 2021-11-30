#include <iostream>
#include <cstring>

using namespace std;

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

void SiftUp(int* pyr, int i, int* znach) {
  int prnt = parent(i);
  if (prnt >= 1 && znach[pyr[prnt]] > znach[pyr[i]]) {
    swap(pyr, prnt, i);
    SiftUp(pyr, prnt, znach);
  }
}

void SiftDown(int* pyr, int i, int size, int* znach) {
  int l = left(i), r = right(i);
  int smallest;
  if (l <= size && znach[pyr[l]] < znach[pyr[i]]) {
    smallest = l;
  } else {
    smallest = i;
  }
  if (r <= size && znach[pyr[r]] < znach[pyr[smallest]]) {
    smallest = r;
  }
  if (smallest != i) {
    swap(pyr, smallest, i);
    SiftDown(pyr, smallest, size, znach);
  }
}
void Insert(int* pyr, int value, int order_number, int size, int* znach) {
  znach[order_number] = value;
  pyr[size + 1] = order_number;
  SiftUp(pyr, size + 1, znach);
}

void ExtractMin(int* pyr, int size, int* znach) {
  if (size == 0) {
    cout << "error" << endl;
    return;
  }
  cout << znach[pyr[1]] << endl;
  swap(pyr, 1, size);
  SiftDown(pyr, 1, size - 1, znach);
}

int Find(const int* pyr, int order_number, int size) {
  for (int i = 1; i <= size; i++) {
    if (pyr[i] == order_number) {
      return i;
    }
  }
  return -1;
}

bool Delete(int* pyr, int size, int order_number, int* znach) {
  int indx = Find(pyr, order_number, size);
  if (indx == -1) {
    cout << "error" << endl;
    return false;
  }
  cout << "ok" << endl;
  swap(pyr, indx, size);
  SiftDown(pyr, indx, size - 1, znach);
  SiftUp(pyr, indx, znach);
  return true;
}

void Change(int* pyr, int size, int order_number, int x, int* znach) {
  int indx = Find(pyr, order_number, size);
  if (indx == -1) {
    cout << "error" << endl;
    return;
  }
  cout << "ok" << endl;
  znach[pyr[indx]] = x;
  SiftUp(pyr, indx, znach);
  SiftDown(pyr, indx, size, znach);
}

void Out(int* pyr, int size, int* znach) {
  for (int i = 1; i <= size; i++) {
    cout << znach[pyr[i]] << "(" << pyr[i] << ") ";
  }
  cout << endl;
}

int main() {
  int* pyr = new int[262144];
  int* znach = new int[262144];
  int n, counter_of_order = 0;
  int size = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x[16] = {};
    int value, order_number;
    cin >> x;
    if (strcmp(x, "insert") == 0) {
      cin >> value;
      Insert(pyr, value, ++counter_of_order, size, znach);
      size++;
      cout << "ok" << endl;
      continue;
    }
    if (strcmp(x, "extract_min") == 0) {
      ExtractMin(pyr, size, znach);
      if (size > 0) {
        size--;
      }
    }
    if (strcmp(x, "get_min") == 0) {
      if (size == 0) {
        cout << "error" << endl;
        continue;
      }
      cout << znach[pyr[1]] << endl;
      continue;
    }
    if (strcmp(x, "size") == 0) {
      cout << size << endl;
      continue;
    }
    if (strcmp(x, "delete") == 0) {
      cin >> order_number;
      if (Delete(pyr, size, order_number, znach)) {
        size--;
      }
      continue;
    }
    if (strcmp(x, "change") == 0) {
      cin >> order_number >> value;
      Change(pyr, size, order_number, value, znach);
      continue;
    }
    if (strcmp(x, "clear") == 0) {
      cout << "ok" << endl;
      size = 0;
    }
  }
  delete[] pyr;
  delete[] znach;
  return 0;
}
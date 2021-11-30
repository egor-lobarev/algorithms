#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

struct Heap {
  int* arr = new int[200000];
  int size = 0;
};

bool IsMinLevel(int i) {
  return (static_cast<int>(log2(static_cast<double>(i))) % 2 == 0);
}

void swap(Heap* heap, int i, int j) {
  int tmp = heap->arr[i];
  heap->arr[i] = heap->arr[j];
  heap->arr[j] = tmp;
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

bool IsGrandChildOf(int i, int j) {
  return (i > right(j));
}

int max(Heap* heap, int i) {
  int largest = i;
  int l = left(i);
  int r = right(i);
  if (l <= heap->size && heap->arr[l] > heap->arr[largest]) {
    largest = l;
  }
  if (r <= heap->size && heap->arr[r] > heap->arr[largest]) {
    largest = r;
  }
  return largest;
}

int MinOfChild(Heap* heap, int i) {
  int smallest = i;
  int l = left(i);
  int r = right(i);
  if (l <= heap->size && heap->arr[l] < heap->arr[i]) {
    smallest = l;
  }
  if (r <= heap->size && heap->arr[r] < heap->arr[smallest]) {
    smallest = r;
  }
  return smallest;
}

int MaxOfChild(Heap* heap, int i) {
  int largest = i;
  int l = left(i);
  int r = right(i);
  if (l <= heap->size && heap->arr[l] > heap->arr[i]) {
    largest = l;
  }
  if (r <= heap->size && heap->arr[r] > heap->arr[largest]) {
    largest = r;
  }
  return largest;
}

int MinOfChildAndGrandChild(Heap* heap, int i) {
  int smallest = i;
  int l = left(i);
  int r = right(i);
  if (l <= heap->size && heap->arr[MinOfChild(heap, l)] < heap->arr[i]) {
    smallest = MinOfChild(heap, l);
  }
  if (r <= heap->size && heap->arr[MinOfChild(heap, r)] < heap->arr[smallest]) {
    smallest = MinOfChild(heap, r);
  }
  return smallest;
}

int MaxOfChildAndGrandChild(Heap* heap, int i) {
  int largest = i;
  int l = left(i);
  int r = right(i);
  if (l <= heap->size && heap->arr[MaxOfChild(heap, l)] > heap->arr[i]) {
    largest = MaxOfChild(heap, l);
  }
  if (r <= heap->size && heap->arr[MaxOfChild(heap, r)] > heap->arr[largest]) {
    largest = MaxOfChild(heap, r);
  }
  return largest;
}

void SiftUpMin(Heap* heap, int i) {
  int grand_parent = parent(parent(i));
  if (grand_parent >= 1 && heap->arr[grand_parent] > heap->arr[i]) {
    swap(heap, grand_parent, i);
    SiftUpMin(heap, grand_parent);
  }
}

void SiftUpMax(Heap* heap, int i) {
  int grand_parent = parent(parent(i));
  if (grand_parent >= 1 && heap->arr[grand_parent] < heap->arr[i]) {
    swap(heap, grand_parent, i);
    SiftUpMax(heap, grand_parent);
  }
}

void SiftUp(Heap* heap, int i) {
  int prnt = parent(i);
  if (i > 1) {
    if (IsMinLevel(i)) {
      if (heap->arr[i] > heap->arr[prnt]) {
        swap(heap, prnt, i);
        SiftUpMax(heap, prnt);
      } else {
        SiftUpMin(heap, i);
      }
    } else {
      if (heap->arr[i] < heap->arr[prnt]) {
        swap(heap, prnt, i);
        SiftUpMin(heap, prnt);
      } else {
        SiftUpMax(heap, i);
      }
    }
  }
}

void SiftDownMin(Heap* heap, int i) {
  int smallest = MinOfChildAndGrandChild(heap, i);
  if (smallest != i) {
    if (IsGrandChildOf(smallest, i)) {
      swap(heap, smallest, i);
      if (heap->arr[smallest] > heap->arr[parent(smallest)]) {
        swap(heap, smallest, parent(smallest));
      }
      SiftDownMin(heap, smallest);
      return;
    }
    swap(heap, smallest, i);
    SiftDownMin(heap, smallest);
  }
}

void SiftDownMax(Heap* heap, int i) {
  int largest = MaxOfChildAndGrandChild(heap, i);
  if (largest != i) {
    if (IsGrandChildOf(largest, i)) {
      swap(heap, largest, i);
      if (heap->arr[largest] < heap->arr[parent(largest)]) {
        swap(heap, largest, parent(largest));
      }
      SiftDownMax(heap, largest);
      return;
    }
    swap(heap, largest, i);
    SiftDownMax(heap, largest);
  }
}

void SiftDown(Heap* heap, int i) {
  bool isOnMinLevel = IsMinLevel(i);
  if (isOnMinLevel) {
    SiftDownMin(heap, i);
  } else {
    SiftDownMax(heap, i);
  }
}

void Insert(Heap* heap, int value) {
  cout << "ok" << endl;
  heap->size++;
  heap->arr[heap->size] = value;
  SiftUp(heap, heap->size);
}

void ExtractMin(Heap* heap) {
  if (heap->size == 0) {
    cout << "error" << endl;
    return;
  }
  cout << heap->arr[1] << endl;
  swap(heap, 1, heap->size);
  heap->size--;
  if (heap->size > 1) {
    SiftDown(heap, 1);
  }
}

void ExtractMax(Heap* heap) {
  if (heap->size == 0) {
    cout << "error" << endl;
    return;
  }
  int max_index = max(heap, 1);
  cout << heap->arr[max_index] << endl;
  swap(heap, max_index, heap->size);
  heap->size--;
  if (heap->size > 1) {
    SiftDown(heap, max_index);
  }
}

void GetMin(Heap* heap) {
  if (heap->size == 0) {
    cout << "error" << endl;
    return;
  }
  cout << heap->arr[1] << endl;
}

void GetMax(Heap* heap) {
  if (heap->size == 0) {
    cout << "error" << endl;
    return;
  }
  cout << heap->arr[max(heap, 1)] << endl;
}

void Out(Heap* heap) {
  for (int i = 1; i <= heap->size; i++) {
    cout << heap->arr[i] << " ";
  }
  cout << endl;
}

int main() {
  Heap* heap = new Heap;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x[16] = {};
    int value;
    cin >> x;
    if (strcmp(x, "insert") == 0) {
      cin >> value;
      Insert(heap, value);
      continue;
    }
    if (strcmp(x, "extract_min") == 0) {
      ExtractMin(heap);
      continue;
    }
    if (strcmp(x, "extract_max") == 0) {
      ExtractMax(heap);
      continue;
    }
    if (strcmp(x, "get_min") == 0) {
      GetMin(heap);
      continue;
    }
    if (strcmp(x, "get_max") == 0) {
      GetMax(heap);
      continue;
    }
    if (strcmp(x, "size") == 0) {
      cout << heap->size << endl;
      continue;
    }
    if (strcmp(x, "out") == 0) {
      Out(heap);
      continue;
    }
    if (strcmp(x, "clear") == 0) {
      cout << "ok" << endl;
      heap->size = 0;
    }
  }
  delete[] heap->arr;
  delete heap;
  return 0;
}
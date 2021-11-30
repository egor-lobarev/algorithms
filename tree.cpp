#include <iostream>
#include <cstring>

using namespace std;

struct Node {
  int key = 0;
  Node* left = nullptr;
  Node* right = nullptr;
};

Node* MinPtr = nullptr;
Node* MaxPtr = nullptr;

Node* add(Node* t, int x) {
  if (t == nullptr) {
    Node* tmp = new Node{x};
    return tmp;
  }
  if (x < t->key) {
    t->left = add(t->left, x);
  } else if (x >= t->key) {
    t->right = add(t->right, x);
  }
  return t;
}

void Delete(Node* t) {
  if (t == nullptr) {
    return;
  }
  Delete(t->right);
  Delete(t->left);
  delete t;
}

Node* MaxPtr(Node* t) {
  if (t == nullptr) {
    return t;
  }
  if (t->right == nullptr) {
    return t;
  }
  return MaxPtr(t->right);
}

Node* MinPtr(Node* t) {
  if (t == nullptr) {
    return t;
  }
  if (t->left == nullptr) {
    return t;
  }
  return MinPtr(t->left);
}

int DeleteMin(Node*& t) {
  if (t == nullptr) {
    return 0;
  }
  if (t->right == nullptr && t->left == nullptr) {
    int key = t->key;
    Node* tmp = t;
    t = nullptr;
    delete tmp;
    return key;
  }
  if (t->left == nullptr) {
    int key = t->key;
    Node* tmp = t;
    t = t->right;
    delete tmp;
    return key;
  }
  Node* tmp = t;
  while (tmp->left->left != nullptr) {
    tmp = tmp->left;
  }
  Node* tmp2 = tmp->left;
  tmp->left = tmp2->right;
  int key = tmp2->key;
  delete tmp2;
  return key;
}

int DeleteMax(Node*& t) {
  if (t == nullptr) {
    return 0;
  }
  if (t->right == nullptr && t->left == nullptr) {
    int key = t->key;
    Node* tmp = t;
    t = nullptr;
    delete tmp;
    return key;
  }
  if (t->right == nullptr) {
    int key = t->key;
    Node* tmp = t;
    t = t->left;
    delete tmp;
    return key;
  }
  Node* tmp = t;
  while (tmp->right->right != nullptr) {
    tmp = tmp->right;
  }
  Node* tmp2 = tmp->right;
  tmp->right = tmp2->left;
  int key = tmp2->key;
  delete tmp2;
  return key;
}

int main() {
  Node* root = nullptr;
  int n;
  int size = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x[16] = {};
    int value;
    cin >> x;
    if (strcmp(x, "insert") == 0) {
      cin >> value;
      root = add(root, value);
      size++;
      cout << "ok" << endl;
      continue;
    }
    if (strcmp(x, "extract_min") == 0) {
      int tmp = DeleteMin(root);
      if (tmp == 0) {
        cout << "error" << endl;
        continue;
      }
      cout << tmp << endl;
      size--;
      continue;
    }
    if (strcmp(x, "get_min") == 0) {
      Node* tmp = MinPtr(root);
      if (tmp == nullptr) {
        cout << "error" << endl;
        continue;
      }
      cout << tmp->key << endl;
      continue;
    }
    if (strcmp(x, "get_max") == 0) {
      Node* tmp = MaxPtr(root);
      if (tmp == nullptr) {
        cout << "error" << endl;
        continue;
      }
      cout << tmp->key << endl;
      continue;
    }
    if (strcmp(x, "extract_max") == 0) {
      int tmp = DeleteMax(root);
      if (tmp == 0) {
        cout << "error" << endl;
        continue;
      }
      cout << tmp << endl;
      size--;
      continue;
    }
    if (strcmp(x, "size") == 0) {
      cout << size << endl;
      continue;
    }
    if (strcmp(x, "clear") == 0) {
      cout << "ok" << endl;
      Delete(root);
      root = nullptr;
      size = 0;
      continue;
    }
  }
  Delete(root);
  return 0;
}
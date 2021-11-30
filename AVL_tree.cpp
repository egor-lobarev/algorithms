#include <iostream>

using namespace std;

struct Node {
  int key = -1;
  Node* right = nullptr;
  Node* left = nullptr;
  int height = 1;
};

int height(Node* tmp) {
  if (tmp == nullptr) {
    return 0;
  }
  return tmp->height;
}

void FixHeight(Node* q) {
  int h_right = height(q->right);
  int h_left = height(q->left);
  q->height = max(h_left, h_right) + 1;
}

Node* LeftRotate(Node* p) {
  Node* q = p->right;
  p->right = q->left;
  q->left = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

Node* RightRotate(Node* p) {
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

int bFactor(Node* p) {
  return height(p->right) - height(p->left);
}

Node* Balance(Node* p) {
  FixHeight(p);
  if (bFactor((p)) == 2) {
    if (bFactor(p->right) < 0) {
      p->right = RightRotate(p->right);
    }
    return LeftRotate(p);
  }
  if (bFactor(p) == -2) {
    if (bFactor(p->left) > 0) {
      p->left = LeftRotate(p->left);
    }
    return RightRotate(p);
  }
  return p;
}

Node* Add(Node* root, int x) {
  if (root == nullptr) {
    return new Node{x};
  }
  if (x < root->key) {
    root->left = Add(root->left, x);
  } else if (x > root->key) {
    root->right = Add(root->right, x);
  }
  return Balance(root);
}

int FindMin(Node* root) {
  if (root->left != nullptr) {
    return FindMin(root->left);
  }
  return root->key;
}

int next(Node* root, int x) {
  int next = -1;
  while (true) {
    if (root == nullptr) {
      break;
    }
    if (root->key > x && root->left != nullptr) {
      next = root->key;
      root = root->left;
      continue;
    }
    if ((root->key > x && root->left == nullptr) || root->key == x) {
      return root->key;
    }
    root = root->right;
  }
  return next;
}

void Clear(Node* root) {
  if (root != nullptr) {
    Clear(root->left);
    Clear(root->right);
    delete root;
  }
}

int main() {
  Node* tree = nullptr;
  int N, last_answer;
  cin >> N;
  char last_command = '0';
  for (; N > 0; N--) {
    int key;
    char command = '0';
    cin >> command >> key;
    if (last_command != '?' && command == '+') {
      tree = Add(tree, key);
    }
    if (command == '?') {
      last_answer = next(tree, key);
      cout << last_answer << endl;
    }
    if (last_command == '?' && command == '+') {
      key = (key + last_answer) % 1000000000;
      tree = Add(tree, key);
    }
    last_command = command;
  }
  Clear(tree);
  return 0;
}
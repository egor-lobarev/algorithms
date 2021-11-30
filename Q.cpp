#include <iostream>

int main() {
  int N;
  std::cin >> N;
  long long S = 0;
  int a, b;
  for (int i = 0; i < N; i++) {
    std::cin >> a >> b;
    if (b > a) {
      std::swap(a, b);
    }
    S += a;
  }
  std::cout << S;
  return 0;
}
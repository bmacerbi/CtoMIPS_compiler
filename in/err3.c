/*variavel global nao foi implementada*/
int global_var = 0;

void foo(int x) {
  int y = 0;
  while (x > 0) {
    y = y + x;
    x = x - 1;
  }
  global_var = y;
}

int bar(int a, int b) {
  foo(a);
  foo(b);
  return global_var;
}

int main() {
  int result = bar(5, 10);
  return 0;
}
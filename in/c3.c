int soma(int a, int b) {
    return a + b;
}

int soma1(int a1, int b1) {
    int a;
    return a + a1 + b1;
}

int soma2(int a2, int b2) {
    int a;
    return a + a2 + b2;
}

int soma3(int a3, int b3) {
    int a;
    return a + a3 + b3;
}

int main() {
    int num1 = 10;
    int num2 = 20;
    int result = soma(num1, num2);
    result = soma1(num1, num2);
    result = soma2(num1, num2);
    result = soma3(num1, num2);
  
    return 0;
}
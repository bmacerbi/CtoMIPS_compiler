int sub(int a, int b) {
    return a - b;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 10;
    int y = 20;
    int z = add(x, y);
    z = sub(x, y);
    return 0;
}
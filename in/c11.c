int count_char(char c, char str[]) {
    int i = 0;
    int count = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char s[50] = "Hello, world!";
    char c = 'l';
    int x = count_char(c, s);
    int y = 1;
    y = x + 2;
    return 0;
}
int main() {
    char str1[10] = "Hello";
    char str2[10] = "world";
    int i = 0;
    int j = 0;
    while (str1[i] != '\0') {
        j = 0;
        while (str2[j] != '\0') {
            j++;
        }
        i++;
    }
    return 0;
}
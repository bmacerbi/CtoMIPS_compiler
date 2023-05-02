void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int soma(int a, int b) { // Função para somar dois números inteiros
    return a + b;
}

int main(){
    float float_var = -12;
    
    if(float_var || 1){
        return 1;
    }
       
    int c = +2;
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    insertionSort(arr, n);

    int num1 = 123;
    int num2 = -45;
    float num3 = +3.14;
    float num4 = -0.5;

    int result = soma(num1, num2);











    return 0;
}
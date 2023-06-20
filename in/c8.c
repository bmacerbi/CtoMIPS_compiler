void insertionSort(int arr[], int n){
    
    int i;
    int key;
    int j;
    while(i < n) {
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
        i++;
    }
}


int main(){
    float float_var = -12;
    int result;
    int c = +2;
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = 5;
    
    insertionSort(arr, n);

    return 0;
}
#include <stdio.h>

#include <stdlib.h>

#define INSERT_LIMIT 6

void merge(int arr[], int l, int m, int r) {
  int i, j, ind;
  int n1 = m - l + 1;
  int n2 = r - m;
  int tempE[n1], tempD[n2];

  for (i = 0; i < n1; i++)
    tempE[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    tempD[j] = arr[m + 1 + j];

  i = j = 0;
  ind = l;
  while (i < n1 && j < n2) {
    if (tempE[i] <= tempD[j]) {
      arr[ind] = tempE[i];
      i++;
    } else {
      arr[ind] = tempD[j];
      j++;
    }
    ind++;
  }

  while (i < n1) {
    arr[ind] = tempE[i];
    i++;
    ind++;
  }

  while (j < n2) {
    arr[ind] = tempD[j];
    j++;
    ind++;
  }
}

void insertionSort(int arr[], int p, int q) {
  int i, j, key, cpy;
  for (int i = p; i < q; i++) {
    {
      j = i;
      for (cpy = 1; j >= 0 && arr[j - 1] > arr[j]; cpy++) {
        key = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = key;
        j--;
      }
    }
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l - r > INSERT_LIMIT) {
    if (l < r) {
      int m = l + (r - l) / 2;
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);
      if (arr[m] <= arr[m + 1]) return;
      merge(arr, l, m, r);
    }
  } else {
    insertionSort(arr, l, r);
  }

}

void impressao(int A[], int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", A[i]);
  printf("\n");
}

int main() {
  int arr[1000], i;
  for (i = 0; i < 1000; i++)
    arr[i] = rand() % 1000;

  int tam_array = sizeof(arr) / sizeof(arr[0]);
  printf("Array aleatorio gerado:\n");
  impressao(arr, tam_array);

  mergeSort(arr, 0, tam_array);

  printf("\nO array ordenado por mergesort:\n");
  impressao(arr, tam_array);
  return 0;
}

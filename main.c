#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

static int cmp_cnt, swp_cnt;


/**
 * Compares the absolute values of two double numbers and increases cmp_cnt.
 *
 * @param a The first number to compare.
 * @param b The second number to compare.
 * @return 1 if |a| > |b|,
 *         0 if |a| = |b|,
 *        -1 if |a| < |b|.
 */
int compare(double a, double b) {
    cmp_cnt++;

    a = fabs(a);
    b = fabs(b);

    if (a > b)
        return 1;

    if (a == b)
        return 0;

    return -1;
}

/**
 * Swaps the values of two variables and increases swp_cnt.
 *
 * @param a
 * @param b
 */
void swap(double *a, double *b) {
    swp_cnt++;

    double tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Prints elements of given array.
 *
 * @param arr Pointer to an array to be printed.
 * @param size The number of elements to print.
 */
void print_arr(double* arr, int size) {
    for(int i = 0; i < size; i++)
        printf("%.0lf ", arr[i]);
    printf("\n");
}


/**
 * Generates an array of doubles based on a specified mode.
 *
 * @param arr Pointer to the array to be filled.
 * @param size The number of elements to generate.
 * @param mode The mode of generation:
 *             0 for ascending order,
 *             1 for descending order,
 *             2 for random values.
 */
void gen_arr(double* arr, int size, int mode) {
    switch (mode) {
        case 0: {
            for (int i = 0; i < size; i++) {
                arr[i] = (double) i;
            }

            return;
        }
        case 1: {
            for (int i = size - 1; i >= 0; i--) {
                arr[i] = (double) i;
            }

            return;
        }
        case 2: {
            srand(time(NULL));
            for (int i = 0; i < size; i++) {
                arr[i] = (double) (rand() % 20);
            }
            return;
        }
        default: {
            printf("Error: wrong mode for array generation: %d", mode);
            exit(1);
        }
    }

}


void quick_sort_rec(double *arr, int size) {
    if (size <= 1)
        return;

    double pivot = arr[rand() % size];
    int left_side = 0;
    int right_side = size - 1;

    while (1) {
        while (left_side < size - 1 && compare(arr[left_side], pivot) < 0) {
            left_side++;
        }
        while (right_side > 0 && compare(arr[right_side], pivot) > 0) {
            right_side--;
        }

        if (right_side < left_side)
            break;

        swap(arr + left_side, arr + right_side);
        left_side++;
        right_side--;
    }

    quick_sort_rec(arr, right_side + 1);
    quick_sort_rec(arr + left_side, size - left_side);
}


void quick_sort(double *arr, int size) {
    srand(time(NULL));
    quick_sort_rec(arr, size);

}

void shell_sort(double  *arr, int size) {
    for (int h = size / 2; h > 0; h /= 2) {
        for (int i = 0; i < h; i++) {
            double previous = arr[i];
            for (int j = i; j < size; j += h) {

            }

        }

    }

}

void ShellSort(int data[], int size) {
    for (int interval = size / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < size; i += 1) {
            int temp = data[i];
            int j;
            for (j = i; j >= interval && data[j - interval] > temp; j -= interval) {
                data[j] = data[j - interval];
            }
            data[j] = temp;
        }
    }
}

int main(void) {
    double* array = malloc(10 * sizeof(*array));
    gen_arr(array, 10, 2);
    print_arr(array, 10);
    quick_sort(array, 10);
    print_arr(array, 10);

    printf("cmp = %d swp = %d", cmp_cnt, swp_cnt);

    free(array);
}

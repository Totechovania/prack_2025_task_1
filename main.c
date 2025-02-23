#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

static int cmp_cnt, swp_cnt;


/**
 * Сравнивает два числа типа double и увеличивает счётчик сравнений cmp_cnt.
 *
 * @param a Первое число.
 * @param b Второе число.
 * @return 1 если |a| > |b|,
 *         0 если |a| = |b|,
 *        -1 если |a| < |b|.
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
 * Меняет два значения местами и увеличивает счётчик обменов swp_cnt.
 *
 * @param a Указатель на первое число.
 * @param b Указатель на второе число.
 */
void swap(double *a, double *b) {
    swp_cnt++;

    double tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Печатает элементы данного списка.
 *
 * @param arr Указатель на начало списка.
 * @param size Количество элементов для печати.
 */
void print_arr(double* arr, int size) {
    for(int i = 0; i < size; i++)
        printf("%lf ", arr[i]);
    printf("\n");
}


/**
 * Проверяет, что список отсортирован.
 *
 * @param arr Указатель на начало списка.
 * @param size Количество эдементов списка.
 * @return 1 если список отсортирова,
 *         2 если список не отсортирован
 */
int is_sorted(double *arr, int size) {
    for (int i = 1; i < size; i++){
        if (compare(arr[i], arr[i - 1]) < 0)
            return 0;
    }

    return 1;
}

/**
 * Генерирует псевдослучайное число типа double в диапозоне от -RAND_MAX до RAND_MAX(распределение не равномерное).
 *
 * @return Сгенерированное число.
 */
double random_double() {
    double res = (double) rand() / (double) rand();

    if (rand() % 2)
        res *= -1;

    return res;
}


/**
 * Генерирует список чисел типа double в зависимости от режима.
 *
 * @param size Размер генерируемого списка.
 * @param mode Режим генерации:
 *             0 - по неубыванию,
 *             1 - по невозрастанию,
 *             2 - случайные числа.
 *
 * @return Указатель на сгенерированный список.
 */
double *gen_arr(int size, int mode) {
    double* arr = malloc(size * sizeof(*arr));
    srand(time(NULL));

    switch (mode) {
        case 0: {
            for (int i = 0; i < size; i++) {
                arr[i] = (double) i;

                if (rand() % 2)
                    arr[i] *= -1;
            }

            return arr;
        }
        case 1: {
            for (int i = 0; i < size; i++) {
                arr[i] = (double) (size - i);

                if (rand() % 2)
                    arr[i] *= -1;
            }

            return arr;
        }
        case 2: {
            for (int i = 0; i < size; i++) {
                arr[i] = (double) random_double();
            }
            return arr;
        }
        default: {
            free(arr);

            printf("Error: wrong mode for array generation: %d", mode);
            exit(1);
        }
    }

}


/**
 * Вспомогательная рекурсивная функция для быстрой сортировки без инициализации радномайзера(основная функция quik_sort).
 *
 * @param arr Указатель на начало списка.
 * @param size Количество элементов для сортировки.
 */
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


/**
 * Сортирует список эленментов типа double с помощью алгоритма быстрой сортировки.
 *
 * @param arr Указатель на начало списка.
 * @param size Количество элементов для сортировки.
 */
void quick_sort(double *arr, int size) {
    srand(time(NULL));
    quick_sort_rec(arr, size);
}


void insertion_sort(double *arr, int size, int offset, int step) {
    for (int i = offset + 1; i < size; i += step) {
        for (int j = i; j > 0; j -= step) {
            if (compare(arr[j], arr[j - 1]) >= 0)
                continue;
            swap(arr + j, arr + j -1);
        }
    }
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
    int n = 20;
    double *arr = gen_arr(n, 2);
    print_arr(arr, n);
    insertion_sort(arr, n, 0, 1);
    print_arr(arr, n);
}

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int cmp_cnt, swp_cnt;

/**
 * Обнуляет значения счётчиков cmp_cnt, swp_cnt.
 */
void reset_cnt(){
    cmp_cnt = 0;
    swp_cnt = 0;
}

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

/**
 * Сортирует подсписок данного с помощью сотировки вставкой.
 * Вспомогательная функция для shell_sort.
 *
 * @param arr Указатель на начало списка.
 * @param size Общее число элементов в списке.
 * @param offset Отступ от начала списка.
 * @param step Расстояние на котором расположены элементы подсписка.
 */
void insertion_sort(double *arr, int size, int offset, int step) {
    for (int i = offset + 1; i < size; i += step) {
        for (int j = i; j > 0; j -= step) {
            if (compare(arr[j], arr[j - 1]) >= 0)
                continue;
            swap(arr + j, arr + j - 1);
        }
    }
}


/**
 * Сортирует список эленментов типа double с помощью метода Шелла.
 *
 * @param arr Указатель на начало списка.
 * @param size Количество элементов для сортировки.
 */
void shell_sort(double  *arr, int size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (int offset = 0; offset < step; offset++) {
            insertion_sort(arr, size, offset, step);
        }
    }

}


int main(void) {
    int sizes[] = {10, 100, 1000, 10000};
    char *modes[] = {"ascending", "descending", "random"};



    for (int i = 0; i < 4; i++){
        int size = sizes[i];


        printf("n = %d:\n", size);
        for (int mode = 0; mode < 3; mode++) {
            printf("\t%s:\n", modes[mode]);

            double *qsort_arr = gen_arr(size, mode);
            double *shell_arr = malloc(size * sizeof(*shell_arr));
            memcpy(shell_arr, qsort_arr, size * sizeof(*shell_arr));

            reset_cnt();
            quick_sort(qsort_arr, size);
            printf("\t\t- Быстая сортировка:\n\t\t\tобменов - %d; сравнений - %d\n", swp_cnt, cmp_cnt);
            assert(is_sorted(qsort_arr, size));

            reset_cnt();
            shell_sort(shell_arr, size);
            printf("\t\t- Метод Шелла:\n\t\t\tобменов - %d; сравнений - %d\n", swp_cnt, cmp_cnt);
            assert(is_sorted(shell_arr, size));

            free(shell_arr);
            free(qsort_arr);
        }

    }

}

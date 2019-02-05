/**
 * Идея такая: отсортируем массив по убыванию. Для нахождения 
 * единственного будем идти по массиву "блоками". Вроде:
 * a a a b b c d d
 * ^
 * указываем на начало массива. Сравним со следующим. Если он повторяется,
 *  то идём до тех пор, пока не найдём другой или выйдем за пределы массива.
 * a a a b b c d d
 *  = - он повторяется, идём до 4-ой позиции.
 * a a a b b c d d 
 *       ^
 * a a a b b c d d
 *        = - аналогично.
 * a a a b b c d d
 *           ^
 * Элемент не повторяется. Он первый уникальный элемент. Учитывая, что 
 * массив отсортирован по убыванию, то он же максимальный.
 * Для повторяющегося максимума достаточно найти первый повторяющийся элемент, что мы уже делали.
 */

/* для ввода-вывода */
#include <stdio.h>
/* для функции malloc() - выделение памяти */
#include <stdlib.h>

int main() {
    /* считываем размер массива */
    int n;
    scanf("%d", &n);
    /* выделяем под массив память */
    int *array = (int *)malloc(sizeof(int) * n);
    /* если не удалось выделить память - выходим*/
    if (array == NULL) {
        puts("Error: memory allocation failed");
        return 0;
    }
    /* считываем массив */
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    /* сортируем массив по убыванию (сортировка выбором)*/
    for (int i = 0; i < n; i++) {
        int max_position = i;
        for (int j = i + 1; j < n; j++) {
            if (array[max_position] < array[j]) {
                max_position = j;
            }
        }
        int temp = array[max_position];
        array[max_position] = array[i];
        array[i] = temp;
    }
    /* узнаем найден ли был определённый элемент */
    char only_found = 0;
    char repeating_found = 0;
    /* переменная позиции */
    int pos;
    /* сами значения */
    int only = 0;
    int repeating = 0;
    /* проинициализируем */
    pos = -1;
    /* ищем единственный максимум */
    while (!only_found) {
        /* прибавляем счётчик */
        ++pos;
        /* если выход за пределы массива - выходим из цикла*/
        if (pos >= n) {
            break;
        }
        /* если это последний элемент - то он единственный*/
        if (pos == n - 1) {
            only_found = 1;
            only = array[pos];
        } else {                                /* иначе проверяем повторяется ли он*/
            if (array[pos] == array[pos + 1]) { /* если повторяется - идём до следующего, отличного от этого значения */
                int t = array[pos];
                while (t == array[++pos]) {/* идём либо до другого элемента */
                    if (pos >= n - 1) { /* либо до конца массива */
                        break;
                    }
                }
                --pos;
            } else { /* если он не повторяется - то это единственный максимум */
                only_found = 1;
                only = array[pos];
            }
        }
    }
    /* сбрасываем счётчик */
    pos = -1;
    /* ищём повторяющийся максимум */
    while (!repeating_found) {
        /* прибавляем счётчик */
        ++pos;
        /* если выход за пределы массива - выходим из цикла*/
        if (pos >= n) {
            break;
        }
        
        /* если элемент повторяется, то он - повторяющийся максимум */
        if (pos < n - 1 && array[pos] == array[pos + 1]) {
            repeating_found = 1;
            repeating = array[pos];
        }
    }
    /* вывод результата */
    printf("only maximum = ");
    if (only_found) {
        printf("%d", only);
    } else {
        printf("NOT FOUND");
    }
    printf(", repeating maximum = ");
    if (repeating_found) {
        printf("%d", repeating);
    } else {
        printf("NOT FOUND");
    }
    putchar('\n');
    return 0;
}

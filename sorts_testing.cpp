#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <locale>
#include <thread>
#include <mutex>
#define TEST_LEN1 5000
#define TEST_LEN2 15000
#define TEST_LEN3 30000
#define TEST_LEN4 50000
#define FUNC_COUNT 4
int count_main = 0;
int count_side = 0;
int memory = 0;
using namespace std;
void time_of_execution(void (*f) (int*, int), int* a, int n)
{
    cout << "                                                           обрабатывается потоком " << this_thread::get_id() << endl;
    mutex mute_write;
    auto start_time = chrono::high_resolution_clock::now();
    f(a, n);
    auto end_time = chrono::high_resolution_clock::now();
    mute_write.lock();
    cout << "Amount of memory - " << memory << " bites" << endl;
    cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    mute_write.unlock();
}
void BubbleSort(int* a, int n)
{
    count_side = count_main = 0;
    int i, j, x;
    memory = 3 * sizeof(int);
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
}

void BubbleSort1(int* a, int n)
{
    count_side = count_main = 0;
    int i, j, x, flag = 1;
    memory = 4 * sizeof(int);
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
}

void BubbleSort2(int* a, int n)
{
    count_side = count_main = 0;
    int i = 1, j, x, k; /*i=1 - левая граница сравниваемых элементов*/
    memory = 4 * sizeof(int);
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
}

void ShakerSort(int* a, int n)
{
    count_side = count_main = 0;
    int j, k = n - 1, left = 1, right = n - 1, x;
    memory = 5 * sizeof(int);
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
}

int receive_data(string name_file, int** test, int* length)
{
    char c;
    int flag = 0, number = 0, i = 0, j = 0;
    ifstream in(name_file);
    if (!in.is_open())
    {
        cout << "Ошибка открытия файла\n";
        return 0;
    }
    for (i = 0; i < FUNC_COUNT; i++)
    {
        while ((c = in.get()))
        {
            if ((c >= '0' && c <= '9'))
            {
                flag = 1;
                number *= 10;
                number += c - 48;
            }
            if (flag == 1 && !(c >= '0' && c <= '9'))
            {
                test[i][j++] = number;
                if (j == length[i]) break;
                number = 0;
                flag = 0;
            }
        }
        j = 0;
        number = 0;
    }
    in.close();
    return 1;
}

int receive_repeatkeys(string name_file, int* test, int length, int count_keys)
{
    char c;
    int flag = 0, number = 0, j = 0, temp = 0;
    ifstream in(name_file);
    if (!in.is_open())
    {
        cout << "Ошибка открытия файла\n";
        return 0;
    }

    while ((c = in.get()))
    {
        if ((c >= '0' && c <= '9'))
        {
            flag = 1;
            number *= 10;
            number += c - 48;
        }
        if (flag == 1 && !(c >= '0' && c <= '9'))
        {
            break;
        }
    }
    temp = number;
    count_keys = int(length / count_keys);
    flag = number = 0;
    while ((c = in.get()))
    {
        if ((c >= '0' && c <= '9'))
        {
            flag = 1;
            number *= 10;
            number += c - 48;
        }
        if (flag == 1 && !(c >= '0' && c <= '9'))
        {
            if (j % count_keys == 0)
                test[j++] = temp;
            if (j == length) break;
            test[j++] = number;
            if (j == length) break;
            number = 0;
            flag = 0;
        }
    }
    in.close();
    return 1;
}

int main()
{
    setlocale(0, "rus");
    thread threads[4];
    int count_keys[] = { 10, 100, 500, 1000 };
    void (*sorts[FUNC_COUNT]) (int*, int) = { BubbleSort, BubbleSort1, BubbleSort2, ShakerSort };
    int test_mas_lengths[] = { TEST_LEN1, TEST_LEN2, TEST_LEN3, TEST_LEN4 };
    int i = 0, x, * test[FUNC_COUNT], z = 0;
    string names_test[] = { "Сортировка пузырьком", "Сортировка пузырьком с фиксацией факта обмена",
                        "Сортировка пузырьком с фиксацией места обмена", "Шейкерная сортировка" };
    while (z < FUNC_COUNT)//выделяем память под массив массивов чисел
    {
        test[z] = new(nothrow) int[test_mas_lengths[z]];
        if (test[z] == nullptr)
        {
            for (i = 0; i < z; i++)//если произощла ошибка выделения памяти - освобождаем ранее выделенную память
            {
                delete[] test[i];
            }
            cout << "Ошибка выделения памяти\n";
            return -1;
        }
        z++;
    }
    if (!receive_data("test_numbers.txt", test, test_mas_lengths)) /*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    cout << names_test[0] << endl;
    cout << "       неупорядоченный массив" << endl;
    thread th1(time_of_execution, sorts[0], test[0], test_mas_lengths[0]);
    thread th2(time_of_execution, sorts[0], test[1], test_mas_lengths[1]);
    thread th3(time_of_execution, sorts[0], test[2], test_mas_lengths[2]);
    thread th4(time_of_execution, sorts[0], test[3], test_mas_lengths[3]);
    cout << endl;
    cout << "       упорядоченный массив" << endl;
    thread th5(time_of_execution, sorts[0], test[0], test_mas_lengths[0]);
    thread th6(time_of_execution, sorts[0], test[1], test_mas_lengths[1]);
    thread th7(time_of_execution, sorts[0], test[2], test_mas_lengths[2]);
    thread th8(time_of_execution, sorts[0], test[3], test_mas_lengths[3]);
    cout << endl;
    for (int j{ 0 }; j < FUNC_COUNT; j++)
        for (i = 0; i < test_mas_lengths[j] / 2; i++)
        {
            x = test[j][i];
            test[j][i] = test[j][test_mas_lengths[j] - 1 - i];
            test[j][test_mas_lengths[j] - 1 - i] = x;
        }
    cout << "       обратно упорядоченный массив" << endl;
    thread th9(time_of_execution, sorts[0], test[0], test_mas_lengths[0]);
    thread th10(time_of_execution, sorts[0], test[1], test_mas_lengths[1]);
    thread th11(time_of_execution, sorts[0], test[2], test_mas_lengths[2]);
    thread th12(time_of_execution, sorts[0], test[3], test_mas_lengths[3]);

    

    if (!receive_data("test_numbers.txt", test, test_mas_lengths)) /*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    cout << names_test[1] << endl;
    cout << "       неупорядоченный массив" << endl;
    thread th13(time_of_execution, sorts[1], test[0], test_mas_lengths[0]);
    thread th14(time_of_execution, sorts[1], test[1], test_mas_lengths[1]);
    thread th15(time_of_execution, sorts[1], test[2], test_mas_lengths[2]);
    thread th16(time_of_execution, sorts[1], test[3], test_mas_lengths[3]);
    cout << endl;
    cout << "       упорядоченный массив" << endl;
    thread th17(time_of_execution, sorts[1], test[0], test_mas_lengths[0]);
    thread th18(time_of_execution, sorts[1], test[1], test_mas_lengths[1]);
    thread th19(time_of_execution, sorts[1], test[2], test_mas_lengths[2]);
    thread th20(time_of_execution, sorts[1], test[3], test_mas_lengths[3]);
    cout << endl;
    for (int j{ 0 }; j < FUNC_COUNT; j++)
        for (i = 0; i < test_mas_lengths[j] / 2; i++)
        {
            x = test[j][i];
            test[j][i] = test[j][test_mas_lengths[j] - 1 - i];
            test[j][test_mas_lengths[j] - 1 - i] = x;
        }
    cout << "       обратно упорядоченный массив" << endl;
    thread th21(time_of_execution, sorts[1], test[0], test_mas_lengths[0]);
    thread th22(time_of_execution, sorts[1], test[1], test_mas_lengths[1]);
    thread th23(time_of_execution, sorts[1], test[2], test_mas_lengths[2]);
    thread th24(time_of_execution, sorts[1], test[3], test_mas_lengths[3]);

    

    if (!receive_data("test_numbers.txt", test, test_mas_lengths)) /*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    cout << names_test[2] << endl;
    cout << "       неупорядоченный массив" << endl;
    thread th25(time_of_execution, sorts[2], test[0], test_mas_lengths[0]);
    thread th26(time_of_execution, sorts[2], test[1], test_mas_lengths[1]);
    thread th27(time_of_execution, sorts[2], test[2], test_mas_lengths[2]);
    thread th28(time_of_execution, sorts[2], test[3], test_mas_lengths[3]);
    cout << endl;
    cout << "       упорядоченный массив" << endl;
    thread th29(time_of_execution, sorts[2], test[0], test_mas_lengths[0]);
    thread th30(time_of_execution, sorts[2], test[1], test_mas_lengths[1]);
    thread th31(time_of_execution, sorts[2], test[2], test_mas_lengths[2]);
    thread th32(time_of_execution, sorts[2], test[3], test_mas_lengths[3]);
    cout << endl;
    for (int j{ 0 }; j < FUNC_COUNT; j++)
        for (i = 0; i < test_mas_lengths[j] / 2; i++)
        {
            x = test[j][i];
            test[j][i] = test[j][test_mas_lengths[j] - 1 - i];
            test[j][test_mas_lengths[j] - 1 - i] = x;
        }
    cout << "       обратно упорядоченный массив" << endl;
    thread th33(time_of_execution, sorts[2], test[0], test_mas_lengths[0]);
    thread th34(time_of_execution, sorts[2], test[1], test_mas_lengths[1]);
    thread th35(time_of_execution, sorts[2], test[2], test_mas_lengths[2]);
    thread th36(time_of_execution, sorts[2], test[3], test_mas_lengths[3]);

    

    if (!receive_data("test_numbers.txt", test, test_mas_lengths)) /*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    cout << names_test[3] << endl;
    cout << "       неупорядоченный массив" << endl;
    thread th37(time_of_execution, sorts[3], test[0], test_mas_lengths[0]);
    thread th38(time_of_execution, sorts[3], test[1], test_mas_lengths[1]);
    thread th39(time_of_execution, sorts[3], test[2], test_mas_lengths[2]);
    thread th40(time_of_execution, sorts[3], test[3], test_mas_lengths[3]);
    cout << endl;
    cout << "       упорядоченный массив" << endl;
    thread th41(time_of_execution, sorts[3], test[0], test_mas_lengths[0]);
    thread th42(time_of_execution, sorts[3], test[1], test_mas_lengths[1]);
    thread th43(time_of_execution, sorts[3], test[2], test_mas_lengths[2]);
    thread th44(time_of_execution, sorts[3], test[3], test_mas_lengths[3]);
    cout << endl;
    for (int j{ 0 }; j < FUNC_COUNT; j++)
        for (i = 0; i < test_mas_lengths[j] / 2; i++)
        {
            x = test[j][i];
            test[j][i] = test[j][test_mas_lengths[j] - 1 - i];
            test[j][test_mas_lengths[j] - 1 - i] = x;
        }
    cout << "       обратно упорядоченный массив" << endl;
    thread th45(time_of_execution, sorts[3], test[0], test_mas_lengths[0]);
    thread th46(time_of_execution, sorts[3], test[1], test_mas_lengths[1]);
    thread th47(time_of_execution, sorts[3], test[2], test_mas_lengths[2]);
    thread th48(time_of_execution, sorts[3], test[3], test_mas_lengths[3]);


    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
    th11.join();
    th12.join();
    th13.join();
    th14.join();
    th15.join();
    th16.join();
    th17.join();
    th18.join();
    th19.join();
    th20.join();
    th21.join();
    th22.join();
    th23.join();
    th24.join();
    th25.join();
    th26.join();
    th27.join();
    th28.join();
    th29.join();
    th30.join();
    th31.join();
    th32.join();
    th33.join();
    th34.join();
    th35.join();
    th36.join();
    th37.join();
    th38.join();
    th39.join();
    th40.join();
    th41.join();
    th42.join();
    th43.join();
    th44.join();
    th45.join();
    th46.join();
    th47.join();
    th48.join();



    for (z = 0; z < FUNC_COUNT; z++)//освобождаем память выделенную под тестовый массив массивов
    {
        delete[] test[z];
    }
    return 0;
}

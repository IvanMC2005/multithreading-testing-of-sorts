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
using namespace std;

int* test_mass = new(nothrow) int[50000];


void BubbleSort(int n, int * main_counts, int * side_counts, int * durations, int & memory)
{
    int* A = new(nothrow) int[n];   
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i, j, x;
    memory = 3 * sizeof(int);
    for ( i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];    
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    auto end_time = chrono::high_resolution_clock::now();
    main_counts[0] = count_main;
    side_counts[0] = count_side;
    durations[0] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    main_counts[1] = count_main;
    side_counts[1] = count_side;
    durations[1] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    main_counts[2] = count_main;
    side_counts[2] = count_side;
    durations[2] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();
    delete[] A;
}

void BubbleSort1(int n, int* main_counts, int* side_counts, int* durations, int& memory)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i, j, x, flag = 1;
    memory = 3 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    auto end_time = chrono::high_resolution_clock::now();
    main_counts[0] = count_main;
    side_counts[0] = count_side;
    durations[0] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    main_counts[1] = count_main;
    side_counts[1] = count_side;
    durations[1] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    main_counts[2] = count_main;
    side_counts[2] = count_side;
    durations[2] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();
    delete[] A;
}

void BubbleSort2(int n, int* main_counts, int* side_counts, int* durations, int& memory)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i = 1, j, x, k;
    memory = 3 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    memory = 4 * sizeof(int);
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    auto end_time = chrono::high_resolution_clock::now();
    main_counts[0] = count_main;
    side_counts[0] = count_side;
    durations[0] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();
    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    end_time = chrono::high_resolution_clock::now();
    main_counts[1] = count_main;
    side_counts[1] = count_side;
    durations[1] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    end_time = chrono::high_resolution_clock::now();
    main_counts[2] = count_main;
    side_counts[2] = count_side;
    durations[2] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();
    delete[] A;
}

void ShakerSort(int n, int* main_counts, int* side_counts, int* durations, int& memory)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }

    int count_side = 0, count_main = 0;
    int i = 1, j, x, k, left, right;
    memory = 5 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    auto end_time = chrono::high_resolution_clock::now();
    main_counts[0] = count_main;
    side_counts[0] = count_side;
    durations[0] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    end_time = chrono::high_resolution_clock::now();
    main_counts[1] = count_main;
    side_counts[1] = count_side;
    durations[1] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    end_time = chrono::high_resolution_clock::now();
    main_counts[2] = count_main;
    side_counts[2] = count_side;
    durations[2] = chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count();
    delete[] A;
}

int receive_data(string name_file, int* test, int length)
{
    char c;
    int flag = 0, number = 0, i = 0, j = 0;
    ifstream in(name_file);
    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла\n";
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
            test[j++] = number;
            if (j == length) break;
            number = 0;
            flag = 0;
        }
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
        std::cout << "Ошибка открытия файла\n";
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

    int* main_count[FUNC_COUNT * 4];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        main_count[i] = new int[3];
    int* side_count[FUNC_COUNT * 4];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        side_count[i] = new int[3];
    int* durations[FUNC_COUNT * 4];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        durations[i] = new int[3];
    int memory[FUNC_COUNT];

    if (!test_mass)
    {
        cout << "Ошибка выделения памяти\n";
        return -1;
    }
    if (!receive_data("test_numbers.txt", test_mass, TEST_LEN4))/*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    int count_keys[] = { 10, 100, 500, 1000 };
    void (*sorts[FUNC_COUNT]) (int, int*, int*, int*, int&) = { BubbleSort, BubbleSort1, BubbleSort2, ShakerSort };
    int test_mas_lengths[] = { TEST_LEN1, TEST_LEN2, TEST_LEN3, TEST_LEN4 };
    string orderliness[] = { "Неупорядоченный массив", "Упорядоченный по возрастанию", "Упорядоченный по убьванию" };
    int i = 0, x, * test[FUNC_COUNT], z = 0;
    string names_test[] = { "\n\n               Сортировка пузырьком", "\n\n                Сортировка пузырьком с фиксацией факта обмена",
                        "\n\n               Сортировка пузырьком с фиксацией места обмена", "\n\n               Шейкерная сортировка" };
    
    std::thread th1(sorts[0], test_mas_lengths[0], main_count[0], side_count[0], durations[0], ref(memory[0]));
    std::thread th2(sorts[0], test_mas_lengths[1], main_count[1], side_count[1], durations[1], ref(memory[0]));
    std::thread th3(sorts[0], test_mas_lengths[2], main_count[2], side_count[2], durations[2], ref(memory[0]));
    std::thread th4(sorts[0], test_mas_lengths[3], main_count[3], side_count[3], durations[3], ref(memory[0]));

    std::thread th5(sorts[1], test_mas_lengths[0], main_count[4], side_count[4], durations[4], ref(memory[1]));
    std::thread th6(sorts[1], test_mas_lengths[1], main_count[5], side_count[5], durations[5], ref(memory[1]));
    std::thread th7(sorts[1], test_mas_lengths[2], main_count[6], side_count[6], durations[6], ref(memory[1]));
    std::thread th8(sorts[1], test_mas_lengths[3], main_count[7], side_count[7], durations[7], ref(memory[1]));

    std::thread th9(sorts[2], test_mas_lengths[0], main_count[8], side_count[8], durations[8], ref(memory[2]));
    std::thread th10(sorts[2], test_mas_lengths[1], main_count[9], side_count[9], durations[9], ref(memory[2]));
    std::thread th11(sorts[2], test_mas_lengths[2], main_count[10], side_count[10], durations[10], ref(memory[2]));
    std::thread th12(sorts[2], test_mas_lengths[3], main_count[11], side_count[11], durations[11], ref(memory[2]));

    std::thread th13(sorts[3], test_mas_lengths[0], main_count[12], side_count[12], durations[12], ref(memory[3]));
    std::thread th14(sorts[3], test_mas_lengths[1], main_count[13], side_count[13], durations[13], ref(memory[3]));
    std::thread th15(sorts[3], test_mas_lengths[2], main_count[14], side_count[14], durations[14], ref(memory[3]));
    std::thread th16(sorts[3], test_mas_lengths[3], main_count[15], side_count[15], durations[15], ref(memory[3]));

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

    for (int i = 0; i < FUNC_COUNT; ++i)
    {
        std::cout << names_test[i] << std::endl;
        for (int j = 0; j < FUNC_COUNT; ++j)
        {
            std::cout << std::endl << std::endl << std::endl;
            for (int z = 0; z < 3; ++z)
            {
                std::cout << std::endl;
                std::cout << orderliness[z] << std::endl;
                std::cout << "Amount of memory - " << memory[i] << " bites" << endl;
                std::cout << "execution time in milliseconds " << test_mas_lengths[j] << " elemets: " << durations[i * 4 + j][z] << endl;
                std::cout << "Main operations amount - " << main_count[i * 4 + j][z] << " Side operations amount - " << side_count[i * 4 + j][z] << endl;
            }
        }
    }

    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        delete[] main_count[i];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        delete[] side_count[i];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        delete[] durations[i];
    delete[] test_mass;
    return 0;
}

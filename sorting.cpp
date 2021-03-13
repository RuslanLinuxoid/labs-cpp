#include <iostream>
#include <fstream>
using namespace std;


#define count 1000000


void selectionSort(int *num) {
    int min; // для поиска минимального элемента
    for (int i = 0; i < count - 1; i++) {
        min = i; // запоминаем индекс текущего элемента
        // ищем минимальный элемент чтобы поместить на место i-ого
        for (int j = i + 1; j < count; j++)  // для остальных элементов после i-ого
            if (num[j] < num[min]) // если элемент меньше минимального,
                min = j;       // запоминаем его индекс в min

        swap(num[min], num[i]); // меняем местами i-ый и минимальный элементы
    }
}


void bubleSort(int *num) { // сортировка пузырьком, что тут сказать ¯\_(O_o)_/¯
    for (int i = 0; i < count - 1; i++)                                                 
        for (int j = 0; j < count - i - 1; j++)
            if (num[j] > num[j + 1])
                swap(num[j], num[j + 1]);
}


void insertionSort(int *num) { // сортировка вставками
    int temp, // временная переменная для хранения значения элемента сортируемого массива
        item; // индекс предыдущего элемента

    for (int counter = 1; counter < count; counter++) {
        temp = num[counter]; // инициализируем временную переменную текущим значением элемента массива
        item = counter-1; // запоминаем индекс предыдущего элемента массива

        while(item >= 0 && num[item] > temp) { // пока индекс не равен 0 и предыдущий элемент массива больше текущего
            num[item + 1] = num[item]; // перестановка элементов массива
            num[item] = temp;
            item--;
        }
    }
}


void fillArr(int *num) {
    ifstream in; // создаем объект файла
    in.open("data.txt"); // открываем файл
    for (int i = 0; i < count; ++i) in >> num[i]; // читаем числа из файла в массив
    in.close(); // закрываем файл
}


int main() {
    int arr[count]; // сам массив
    int start_time; // начальное время
    int end_time; // конечное время
    int search_time; // искомое время
    
    fillArr(arr);
    
    start_time =  clock();
    bubleSort(arr);
    end_time = clock(); 
    search_time = (end_time - start_time) / CLOCKS_PER_SEC; 
    cout <<  search_time << " секунд работал пузырек" << endl;
    
    fillArr(arr);

    start_time =  clock(); 
    selectionSort(arr);
    end_time = clock(); 
    search_time = (end_time - start_time) / CLOCKS_PER_SEC; 
    cout <<  search_time << " секунд работал выбор" << endl;
    
    fillArr(arr);

    start_time =  clock(); 
    insertionSort(arr);
    end_time = clock(); 
    search_time = (end_time - start_time) / CLOCKS_PER_SEC;
    cout <<  search_time << " секунд работали вставки" << endl;

    return 0;
}

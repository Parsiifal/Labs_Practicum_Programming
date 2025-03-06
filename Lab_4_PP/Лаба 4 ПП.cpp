#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


int main()
{
    setlocale(LC_ALL, "ru");
    
    cout << "\nСтарый алгоритм: " << endl;

    clock_t timeprosl = 0;
    for (int i = 0; i < 10; i++)
    {
        clock_t timestart = clock();
        ifstream file; // создаем объект класса ifstream
        file.open("C:\\Users\\Artem1\\Desktop\\Файл лаба 4 ПП читаем.txt"); // открываем файл для чтения

        file.seekg(0, ios_base::end);   //становимся в конец файла 
        //cout << "\nРазмер файла (в байтах): " << file.tellg() << endl; // считаем кол во символов

        int n = file.tellg(); // n - кол - во символов в файле  
        file.seekg(0, ios_base::beg);  // возвращаемся в начало файла

        // создаем буффер
        char* buffer = new char[n + 1];
        buffer[n] = 0;
        //читаем в него байты
        file.read(buffer, n);

        //cout << "\nПрочитано из файла: " << buffer << endl;

        file.close();

        for (int i = 0; i < n; i++)  // заменяем все ' ' на *
        {
            if (buffer[i] == ' ')
                buffer[i] = '*';
        }

        vector <char> a;
        for (int i = 0; i < n; i++) // записываем в вектор эл ты буффера
            a.push_back(buffer[i]);

        auto last = unique(a.begin(), a.end()); // удаляем все, кроме первого *, из каждой последовательной группы * в диапазоне вектора
        a.erase(last, a.end()); // уменьшаем вектор до нового размера

        char* buffer2 = new char[a.size() + 1];
        buffer2[a.size()] = 0;

        for (int i = 0; i < a.size(); i++)  // записываем в буфер исправленный вектор
            buffer2[i] = a[i];

        //cout << "\nЗаписано в файл: " << buffer2 << endl;

        ofstream file2; // файловый вывод
        file2.open("C:\\Users\\Artem1\\Desktop\\Файл лаба 4 ПП записываем.txt"); // открываем файл для записи

        file2 << buffer2;
        delete[] buffer;
        delete[] buffer2;
        file2.close();

        clock_t timestop = clock();
        timeprosl += timestop - timestart;
    }

    double timepr = ((double)timeprosl / CLOCKS_PER_SEC) / 10;
    cout << "\nСреднее время работы: " << timepr << " секунд!!!" << endl;


    cout << "\nНовый алгоритм: " << endl;

    clock_t timenew = 0;
    for (int i = 0; i < 10; i++)
    {
        clock_t timestart = clock();
        ifstream file; // создаем объект класса ifstream
        file.open("C:\\Users\\Artem1\\Desktop\\Файл лаба 4 ПП читаем.txt"); // открываем файл для чтения

        string str;
        getline(file, str);

        file.close();
      
        string x = " ", y = "*";
        size_t pos;
        while ((pos = str.find(x)) != string::npos)  // все ' ' заменяем на '*'
        {
            str.replace(pos, 1, y);
        }
        //cout << str << endl;
       
        int h = 0;
        int sim;
        while ((sim = str.find("**")) != -1)  //удаляем все повторяющиеся *
        {
            for (h = str.find("**", h++); h != string::npos; h = str.find("**", h + 1))
            {
                str.erase(h, 1);
            }
            h = 0;
        }

        ofstream file2; // файловый вывод
        file2.open("C:\\Users\\Artem1\\Desktop\\Файл лаба 4 ПП записываем.txt"); // открываем файл для записи

        file2 << str;
        file2.close();

        clock_t timestop = clock();
        timenew += timestop - timestart;        
    }

    double timen = ((double)timenew / CLOCKS_PER_SEC) / 10;
    cout << "\nСреднее время работы: " << timen << " секунд!!!" << endl;

    if (timen < timepr)
        cout << "\nНовый алгоритм быстрее!" << endl;
    else if (timen > timepr)
        cout << "\nСтарый алгоритм быстрее!" << endl;
    else if (timen == timepr)
        cout << "\nОдинаково быстро!" << endl;

}
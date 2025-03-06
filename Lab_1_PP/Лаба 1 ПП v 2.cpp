#include <iostream>
#include <string>
using namespace std;

int check_intsize(int min, string strngln) 
{
	int x;
	cout << strngln << "\n";
	cin >> x; // "23dk 24dklc\n"
	while (cin.fail() || cin.peek() != '\n' || x < min)
	{
		//cin.fail() проверяет состояние failbit и в случае его обнаружения возвращает true
		//cin.peek() возвращает целочисленное представление следующего символа в буфере потока, не прочитав его
		// (cin.peek() != '\n') - символ, следующий за последным прочитанным, не является '\n'(строка не закончилась)
		cout << "\nТакой массив создать невозможно! Введите натуральное число!\n" << endl;
		cin.clear(); //cin.clear() очистит все биты и установит бит по умолчанию (std::ios_base::goodbit), таким образом приведя поток в рабочее состояние.
		cin.ignore(10000, '\n'); // очищаем буфер обмена путем игнорирования большого числа символов
		cin >> x;
	}
	return x;
}


int check_intarr() 
{
	int x;
	cin >> x;
	while (cin.fail() || cin.peek() != '\n')
	{
		cout << "\nВведите целое число!\n" << endl;
		cin.clear(); 
		cin.ignore(10000, '\n');
		cin >> x;
	}
	return x;
}

char check_strret() 
{
	char x;
	cin >> x;
	while (cin.fail() || cin.peek() != '\n' || x != 'y')
	{
		cout << "\nЕсли хотите повторить программу, введите y!\n" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> x;
	}
	return x;
}


int main()
{
	setlocale(LC_ALL, "ru");
	char ans = 'y';
	do
	{
		int size = check_intsize(1, "\nВведите количество элементов массива: \n");  // вводим кол-во элементов массива

		int* numbers = new int[size];  // создаем целочисленный динамический массив

		cout << "\nВведите значения элементов массива: \n";

		// Заполнение массива и вывод значений его элементов
		for (int i = 0; i < size; i++)
		{
			cout << "\nЭлемент " << i + 1 << " имеет значение: ";
			numbers[i] = check_intarr();

		}

		// переставляем элементы целочисленного массива в обратном порядке
		cout << "\nМассив с переставленными в обратном порядке элементами: [ ";
		
		int x;
		for (int i = 0, j = size - 1; i < size / 2; i++, j--) // Пусть размер массива size = 4, тогда j = 3,
		{													 // пока i < size/2 = 2, i увеличивается на 1, j уменьшается на 1;
			x = numbers[i];
			numbers[i] = numbers[j];
			numbers[j] = x;
		}

		for (int i = 0; i < size; i++)
		{
			cout << numbers[i] << " ";
		}
		cout << "]" << endl;

		// повторение программы
		cout << "\nХотите повторить программу? Нажмите y!\n";
		char ans = check_strret();

	} while (ans == 'y');

}
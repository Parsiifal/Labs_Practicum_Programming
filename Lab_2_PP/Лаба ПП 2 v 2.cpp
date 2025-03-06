#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;


float check_floatX(int min, int max, string strngln)
{
	float x;
	cout << strngln << "\n";
	cin >> x;
	while (cin.fail() || cin.peek() != '\n' || x < min || x > max)
	{
		//cin.fail() проверяет состояние failbit и в случае его обнаружения возвращает true;
		//cin.peek() возвращает целочисленное представление следующего символа в буфере потока, не прочитав его;
		// (cin.peek() != '\n') - символ, следующий за последным прочитанным, не является '\n'(строка не закончилась);
		cout << "\nВведите такое значение x, что -1 <= x <= 1 !\n" << endl;
		cin.clear();   // очищает все биты и устанавливает бит по умолчанию (std::ios_base::goodbit), таким образом приведя поток в рабочее состояние;
		cin.ignore(10000, '\n'); // очищаем буфер обмена
		cin >> x;
	}
	return x;
}


double check_doubleA(int min, string strngln)
{
	double x;
	cout << strngln << "\n";
	cin >> x;
	while (cin.fail() || cin.peek() != '\n' || x < min)
	{
		cout << "\nВведите корректное значение!\n" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> x;
	}
	return x;
}

void output(int nn, double An, double Sn, double En) 
{
	std::cout << "\nn: " << nn + 1 << "        ";
	std::cout << "An: " << An << "        ";
	std::cout << "Sn: " << Sn << "        ";
	std::cout << "En: " << En << "        " << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	char ans;
	double x1 = 0.1;
	int a_max = 0;
	
	vector<int> nn;
	vector<double> An;
	vector<double> Sn;
	vector<double> En;

	do		// зацикливаем программу;
	{

		float x = check_floatX(-1, 1, "\nВведите параметр x: ");	// вводим x

		double a = check_doubleA(0, "\nВведите a: ");	// вводим a

	
		if (x1 == x)  // ЕСЛИ Х РАВЕН ПРЕДЫДУЩЕЙ ИТЕРАЦИИ
		{
			if (a == (int)a)  // Если а - число итераций
			{
				a = (int)a;
				double sum = 0;

				if (a > nn.size())
				{
					if (a <= a_max)
					{
						cout << "\nВычислено в прошлой итерации с большей точностью: " << endl;

					}
					else
					{
						cout << "\nВычислено в прошлой итерации: " << endl;
						
					}

					for (int i = 0; i < nn.size(); ++i) {
						output(nn[i], An[i], Sn[i], En[i]);
					}

					// поправка суммы
					for (int n = 0; n < nn.size(); n++)
					{
						double f;
						f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);
						sum = sum + f;
					}

					if (a <= a_max)
						cout << endl;
					else
						cout << "\nНовые вычисления: " << endl;

					for (int n = nn.size(); n < a; n++)		// цикл, выполняющий столько итераций, какое значение принимает а;
					{

						double f;
						f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);

						cout << "\nn: " << n + 1 << "        ";

						cout << "An: " << f << "        ";
					
						sum = sum + f;
						cout << "Sn: " << sum << "        ";

						// Вычисление и вывод точности вычисления;
						int j = n + 1;

						double f1;
						f1 = (pow(-1, j) * pow(x, 2 * j + 1) * (1 + pow(x, 2))) / (2 * j + 1);

						double accuracy;
						accuracy = fabs(f1 / sum);

						cout << "En: " << accuracy << endl;

						nn.push_back(n);
						An.push_back(f);
						Sn.push_back(sum);
						En.push_back(accuracy);

					}
					if (a > a_max)
						a_max = a;					

				}
				else  // если а <= nn.size()
				{

					cout << "\nВычислено в прошлой итерации с большей точностью: " << endl;

					for (int i = 0; i < nn.size(); ++i)
					{
						output(nn[i], An[i], Sn[i], En[i]);
					}
										
				}

				x1 = x;

				cout << "\nЕсли хотите повторить программу, нажмите y! Принажатии другой клавиши программа завершится!\n";
				cin >> ans;

			}
			else  // Если а - точность вычисления
			{
				cout << "\nПараметр a - точность!" << endl;
				double sum = 0;
				
				if (a <= En.back())
				{
					cout << "\nВычислено в прошлой итерации: " << endl;

					for (int i = 0; i < nn.size(); ++i) 
					{
						output(nn[i], An[i], Sn[i], En[i]);
					}

					// поправка суммы
					for (int n = 0; n < nn.size(); n++)
					{
						double f;
						f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);
						sum = sum + f;
					}

					cout << "\nНовые вычисления: " << endl;
					double accuracy;
					int n = nn.size();

					do		// цикл, выполняющийся до достижения определенной точности a;
					{

						double f;
						f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);

						cout << "\nn: " << n + 1 << "        ";

						cout << "An: " << f << "        ";

						sum = sum + f;
						cout << "Sn: " << sum << "        ";

						// Вычисление и вывод точности вычисления;
						int j = n + 1;
						double f1;
						f1 = (pow(-1, j) * pow(x, 2 * j + 1) * (1 + pow(x, 2))) / (2 * j + 1);

						accuracy = fabs(f1 / sum);
						cout << "En: " << accuracy << endl;

						nn.push_back(n);
						An.push_back(f);
						Sn.push_back(sum);
						En.push_back(accuracy);

						n++;

					} while (a < accuracy);					

				}
				else  // если а >= En.back()
				{
					cout << "\nВычислено в прошлой итерации с большей точностью: " << endl;
					for (int i = 0; i < nn.size(); ++i) {
						output(nn[i], An[i], Sn[i], En[i]);
					}

				}
				
				x1 = x;

				cout << "\nЕсли хотите повторить программу, нажмите y! Принажатии другой клавиши программа завершится!\n";
				cin >> ans;

			}

		}
		else  // ЕСЛИ Х ДРУГОЙ И ПЕРВЫЙ ПРОГОН ПРОГРАММЫ
		{

			nn.clear();
			An.clear();
			Sn.clear();
			En.clear();
			a_max = 0;

			if (a == (int)a)
			{
				a = (int)a;
				cout << "\nПараметр a - число итераций!" << endl;
				double sum = 0;

				for (int n = 0; n < a; n++)		// цикл, выполняющий столько итераций, какое значение принимает а;
				{

					double f;
					f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);

					cout << "\nn: " << n + 1 << "        ";

					cout << "An: " << f << "        ";

					sum = sum + f;
					cout << "Sn: " << sum << "        ";

					// Вычисление и вывод точности вычисления;
					int j = n + 1;

					double f1;
					f1 = (pow(-1, j) * pow(x, 2 * j + 1) * (1 + pow(x, 2))) / (2 * j + 1);

					double accuracy;
					accuracy = fabs(f1 / sum);

					cout << "En: " << accuracy << endl;

					nn.push_back(n);
					An.push_back(f);
					Sn.push_back(sum);
					En.push_back(accuracy);
					
				}

				x1 = x;
				
				cout << "\nЕсли хотите повторить программу, нажмите y! Принажатии другой клавиши программа завершится!\n";
				cin >> ans;

			}
			else
			{
				cout << "\nПараметр a - точность!" << endl;;
				double sum = 0;
				double accuracy;
				int n = 0;
				do			// цикл, выполняющийся до достижения определенной точности a;
				{

					double f;
					f = (pow(-1, n) * pow(x, 2 * n + 1) * (1 + pow(x, 2))) / (2 * n + 1);

					cout << "\nn: " << n + 1 << "        ";

					cout << "An: " << f << "        ";

					sum = sum + f;
					cout << "Sn: " << sum << "        ";

					// Вычисление и вывод точности вычисления;
					int j = n + 1;
					double f1;
					f1 = (pow(-1, j) * pow(x, 2 * j + 1) * (1 + pow(x, 2))) / (2 * j + 1);

					accuracy = fabs(f1 / sum);
					cout << "En: " << accuracy << endl;

					nn.push_back(n);
					An.push_back(f);
					Sn.push_back(sum);
					En.push_back(accuracy);

					n++;

				} while (a < accuracy);

				x1 = x;
				
				cout << "\nЕсли хотите повторить программу, нажмите y! Принажатии другой клавиши программа завершится!\n";
				cin >> ans;
			}

		}

	} while (ans == 'y');

}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <typeinfo>
#include <windows.h>
using namespace std;


class TripInfo
{
private:

	string departure_point;
	string departure_time;
	string arrival_point;
	string arrival_time;

public:

	string Get_departure_time()
	{
		return departure_time;
	}

	string Get_arrival_time()
	{
		return arrival_time;
	}

	string Get_departure_point()
	{
		return departure_point;
	}

	string Get_arrival_point()
	{
		return arrival_point;
	}

	friend ostream& operator<<(ostream& os, const  TripInfo& point);
	friend istream& operator>>(istream& is, TripInfo& point);
};

void processingTime(string str, int& hour, int& min, int& time)
{	
	regex regex("\\:");

	vector<string> out(sregex_token_iterator(str.begin(), str.end(), regex, -1), sregex_token_iterator());

	hour = stoi(out[0]);
	min = stoi(out[1]);

	time = hour * 60 + min;

}

class TrainTimetable
{
private:

	string date;
	int number_of_trips;
	vector<TripInfo> tripInfoVec;
	string the_shortest_trip;

public:

	string processing()  //  Поиск пунктов назначения самого короткого рейса за день
	{
		int departure_hour, departure_min, departure_time;
		int arrival_hour, arrival_min, arrival_time;
		vector<int> tripsTime;

		for (int i = 0; i < tripInfoVec.size(); i++)
		{
			processingTime(tripInfoVec[i].Get_departure_time(), departure_hour, departure_min, departure_time);
			processingTime(tripInfoVec[i].Get_arrival_time(), arrival_hour, arrival_min, arrival_time);

			int trip_time = arrival_time - departure_time;
			tripsTime.push_back(trip_time);

		}

		int time_of_shortest_trip = tripsTime[0];
		int number_of_shortest_trip = 0;
		int all_equal = 0;

		for (int i = 0; i < tripsTime.size(); i++)
		{
			if (time_of_shortest_trip == tripsTime[i])
			{
				all_equal++;
			}
			else if (time_of_shortest_trip > tripsTime[i])
			{
				time_of_shortest_trip = tripsTime[i];
				number_of_shortest_trip = i;
			}
		}

		if (all_equal == tripsTime.size() && tripsTime.size() != 1)
		{
			the_shortest_trip = "Рейсы равны!";
		}
		else
		{
			the_shortest_trip = tripInfoVec[number_of_shortest_trip].Get_departure_point() + " - " + tripInfoVec[number_of_shortest_trip].Get_arrival_point() + " ";
		}
		return the_shortest_trip;
	
	}

	string Get_the_shortest_trip()
	{
		return the_shortest_trip;
	}

	friend ostream& operator<<(ostream& os, const  TrainTimetable& point);
	friend istream& operator>>(istream& is, TrainTimetable& point);
};


char check_f_i() // f и i
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);

		if (inp.size() == 1 && (inp[0] == 'f' || inp[0] == 'i'))
		{
			state = false;
		}
		else
			cout << "\nОшибка! Повторите ввод: ";

	}
	return inp[0];
}

// ПРОВЕРКИ:
string check_DateInput()  // Проверка ввода даты
{
	int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	string inp;
	int day;
	int month;
	size_t ptr = 0;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		try
		{
			if (inp.size() != 5 || inp[2] != '.')
				throw runtime_error("\nОшибка!!! Повторите ввод: ");

			double check = stod(inp, &ptr);

			regex regex("\\.");

			vector<string> out(sregex_token_iterator(inp.begin(), inp.end(), regex, -1), sregex_token_iterator());

			day = stoi(out[0]);
			month = stoi(out[1]);

			if ((day > 0 && day <= days[month - 1]) && (month > 0 && month <= 12) && (inp.size() == ptr))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка!!! Повторите ввод: ";
		}

	}
	return inp;
}

int check_NumberOf(string str) // Количество элементов
{
	cout << str;
	int res;
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		try
		{
			res = stoi(inp);
			if (inp.size() == to_string(res).size() && res > 0)
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Повторите ввод: ";
		}
		catch (out_of_range)
		{
			cout << "\nО нет, выход за пределы максимально возможного значения!!! Повторите ввод: ";
		}

	}
	return res;
}

string check_TrainStationInput()  // Проверка ввода станции
{
	string str;
	bool state = true;

	while (state)
	{
		getline(cin, str);
		try
		{
			for (int i = 0; i < str.size(); i++)
			{
				if ((str[i] >= ' ' && str[i] <= '@') || (str[i] >= '[' && str[i] <= '`') || (str[i] >= '{' && str[i] <= '~') || (str[i] == '\t') || (str[i] == '\n'))
					throw runtime_error("\nОшибка! Нет такой станции! Повторите ввод: ");
			}

			if (!str.empty())
			{
				state = false;
			}
			else
				cout << "\nОшибка! Нет такой станции! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Нет такой станции! Повторите ввод: ";
		}

	}
	return str;
}

string check_DepartureTimeInput(string out)  // Проверка ввода времени
{
	cout << out;
	string str;
	int hours;
	int mins;
	bool state = true;

	while (state)
	{
		getline(cin, str);
		try
		{
			if (str.size() != 5 || str[2] != ':')
				throw runtime_error("\nОшибка!!! Повторите ввод: ");

			for (int i = 0; i < str.size(); i++)
			{
				if ((str[i] != ':') && (isdigit(str[i]) == 0))
					throw runtime_error("\nОшибка!!! Повторите ввод: ");
			}

			regex regex("\\:");

			vector<string> out(sregex_token_iterator(str.begin(), str.end(), regex, -1), sregex_token_iterator());

			hours = stoi(out[0]);
			mins = stoi(out[1]);

			if ((hours >= 0 && hours < 24) && (mins >= 0 && mins < 60))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка!!! Повторите ввод: ";
		}

	}
	return str;
}

string check_ArrivalTimeInput(string out, string departure_time)  // Проверка ввода времени
{
	cout << out;
	string str;
	int hours;
	int mins;
	bool state = true;

	while (state)
	{
		getline(cin, str);
		try
		{
			if (str.size() != 5 || str[2] != ':')
				throw runtime_error("\nОшибка!!! Повторите ввод: ");

			for (int i = 0; i < str.size(); i++)
			{
				if ((str[i] != ':') && (isdigit(str[i]) == 0))
					throw runtime_error("\nОшибка!!! Повторите ввод: ");
			}

			regex regex("\\:");

			vector<string> out(sregex_token_iterator(str.begin(), str.end(), regex, -1), sregex_token_iterator());

			hours = stoi(out[0]);
			mins = stoi(out[1]);

			int arrival_time = hours * 60 + mins;

			vector<string> departure(sregex_token_iterator(departure_time.begin(), departure_time.end(), regex, -1), sregex_token_iterator());

			int departure_hours = stoi(departure[0]);
			int departure_mins = stoi(departure[1]);

			int departure_time = departure_hours * 60 + departure_mins;

			if (arrival_time <= departure_time)
				throw runtime_error("\nВремя прибытия не может быть меньше либо равно времени отправки! Повторите ввод: ");

			if ((hours >= 0 && hours < 24) && (mins >= 0 && mins < 60))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка!!! Повторите ввод: ";
		}

	}
	return str;
}


void check_FileDateInput(string& str, string& date)  // Проверка ввода даты
{
	size_t n = str.find(' ');
	date = (n != string::npos) ? str.substr(0, n) : "";

	if (date.size() != 5 || date[2] != '.')
		throw runtime_error("\nНекорректные данные в файле!\n");

	size_t ptr = 0;
	int day;
	int month;
	int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

	double check = stod(date, &ptr);

	regex regex("\\.");

	vector<string> out(sregex_token_iterator(date.begin(), date.end(), regex, -1), sregex_token_iterator());

	day = stoi(out[0]);
	month = stoi(out[1]);

	if ((day <= 0 || day > days[month - 1]) || (month <= 0 || month > 12) || (date.size() != ptr))
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}
	else
		str.erase(0, 6);
}

void check_FileNumberOfTrips(string& str, string number_of_trips) // кол - во рейсов в файле
{
	int res;
	res = stoi(number_of_trips);
	
	if (number_of_trips.size() != to_string(res).size() || res <= 0)
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}
	
	str.erase(0, number_of_trips.size() + 1);

}

void check_FileTrainStationInput(string& str, string departure_point)  // Проверка ввода станции
{
	for (int i = 0; i < departure_point.size(); i++)
	{
		if ((departure_point[i] >= ' ' && departure_point[i] <= '@') || (departure_point[i] >= '[' && departure_point[i] <= '`') || (departure_point[i] >= '{' && departure_point[i] <= '~') || (departure_point[i] == '\t') || (departure_point[i] == '\n'))
			throw runtime_error("\nНекорректные данные в файле!\n");
	}

	if (departure_point.empty())
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}

	str.erase(0, departure_point.size() + 1);

}

void check_FileDepartureTimeInput(string& str, string departure_time)  // Проверка ввода времени
{
	int hours;
	int mins;

	if (departure_time.size() != 5 || departure_time[2] != ':')
		throw runtime_error("\nНекорректные данные в файле!\n");

	for (int i = 0; i < departure_time.size(); i++)
	{
		if ((departure_time[i] != ':') && (isdigit(departure_time[i]) == 0))
			throw runtime_error("\nНекорректные данные в файле!\n");
	}

	regex regex("\\:");

	vector<string> out(sregex_token_iterator(departure_time.begin(), departure_time.end(), regex, -1), sregex_token_iterator());

	hours = stoi(out[0]);
	mins = stoi(out[1]);

	if ((hours < 0 || hours >= 24) || (mins < 0 || mins >= 60))
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}
	
	str.erase(0, departure_time.size() + 1);
}

void check_FileArrivalTimeInput(string& str, string arrival_time, string departure_time)  // Проверка ввода времени
{
	int hours;
	int mins;

	if (arrival_time.size() != 5 || arrival_time[2] != ':')
		throw runtime_error("\nНекорректные данные в файле!\n");

	for (int i = 0; i < arrival_time.size(); i++)
	{
		if ((arrival_time[i] != ':') && (isdigit(arrival_time[i]) == 0))
			throw runtime_error("\nНекорректные данные в файле!\n");
	}

	regex regex("\\:");

	vector<string> out(sregex_token_iterator(arrival_time.begin(), arrival_time.end(), regex, -1), sregex_token_iterator());

	hours = stoi(out[0]);
	mins = stoi(out[1]);

	int arriv_time = hours * 60 + mins;

	vector<string> departure(sregex_token_iterator(departure_time.begin(), departure_time.end(), regex, -1), sregex_token_iterator());

	int departure_hours = stoi(departure[0]);
	int departure_mins = stoi(departure[1]);

	int depart_time = departure_hours * 60 + departure_mins;

	if (arriv_time <= depart_time)
		throw runtime_error("\nНекорректные данные в файле! Время прибытия не может быть меньше либо равно времени отправки!\n");

	if ((hours < 0 || hours >= 24) || (mins < 0 || mins >= 60))
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}

	str.erase(0, arrival_time.size() + 1);
}
//

string str;
istream& operator>>(istream& is, TripInfo& r)  // Перегрузка ввода TripInfo
{
	if (typeid(is) == typeid(cin))
	{
		cout << "\n\nВведите пункт отправления: ";
		r.departure_point = check_TrainStationInput();

		r.departure_time = check_DepartureTimeInput("Введите время отправления: ");

		cout << "Введите пункт прибытия: ";
		r.arrival_point = check_TrainStationInput();

		r.arrival_time = check_ArrivalTimeInput("Введите время прибытия: ", r.departure_time);

	}
	else
	{

		string departure_point;
		size_t a = str.find(' ');
		departure_point = (a != string::npos) ? str.substr(0, a) : "";

		check_FileTrainStationInput(str, departure_point);
		r.departure_point = departure_point;

		string departure_time;
		size_t b = str.find(' ');
		departure_time = (b != string::npos) ? str.substr(0, b) : "";

		check_FileDepartureTimeInput(str, departure_time);
		r.departure_time = departure_time;

		string arrival_point;
		size_t p = str.find(' ');
		arrival_point = (p != string::npos) ? str.substr(0, p) : "";

		check_FileTrainStationInput(str, arrival_point);
		r.arrival_point = arrival_point;

		string arrival_time;
		if (str.size() != 5)
		{
			size_t l = str.find(' ');
			arrival_time = (l != string::npos) ? str.substr(0, l) : "";
		}
		else
			arrival_time = str;

		check_FileArrivalTimeInput(str, arrival_time, r.departure_time);
		r.arrival_time = arrival_time;

	}
	return is;
}

istream& operator>>(istream& is, TrainTimetable& t)  // Перегрузка ввода TrainTimetable
{
	if (typeid(is) == typeid(cin))
	{
		cout << "\nВведите дату: ";
		t.date = check_DateInput();

		t.number_of_trips = check_NumberOf("Введите количество рейсов: ");

		for (int i = 0; i < t.number_of_trips; i++)
		{
			cout << "\nВведите информацию о рейсе " << i + 1 << ": ";
			TripInfo r;
			cin >> r;
			t.tripInfoVec.push_back(r);

		}

		t.processing();

	}
	else
	{
		
		getline(is, str);

		string date;
		check_FileDateInput(str, date);
		t.date = date;

		string number_of_trips;
		size_t n = str.find(' ');
		number_of_trips = (n != string::npos) ? str.substr(0, n) : "";

		check_FileNumberOfTrips(str, number_of_trips);
		t.number_of_trips = stoi(number_of_trips);

		for (int i = 0; i < t.number_of_trips; i++)
		{
			TripInfo r;
			is >> r;
			t.tripInfoVec.push_back(r);
		}

		if (!str.empty())
		{
			throw runtime_error("\nНекорректные данные в файле!\n");
		}

		t.processing();
			
	}
	return is;
}

void consInput(vector<TrainTimetable>& trainTimetableVec)
{
	int number_of_days = check_NumberOf("\nВведите количество дней: ");

	cout << "\nВведите расписание: " << endl;

	for (int i = 0; i < number_of_days; i++)
	{
		cout << "\nДень " << i + 1 << ":" << endl;
		TrainTimetable t;
		cin >> t;	// Перегруженный ввод
		trainTimetableVec.push_back(t);
	}

}

void fInput(vector<TrainTimetable>& trainTimetableVec)  // Чтение из файла
{
	ifstream file;
	file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Лаба 5 ПП читаем.txt");

	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт!" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	bool state = true;

	while (state)
	{
		TrainTimetable t;
		file >> t;  // Перегруженный ввод
		trainTimetableVec.push_back(t);

		if (file.eof())
		{
			state = false;
		}
	}

	file.close();

}


char check_r_c() // r и c
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);

		if (inp.size() == 1 && (inp[0] == 'r' || inp[0] == 'c'))
		{
			state = false;
		}
		else
			cout << "\nОшибка! Повторите ввод: ";

	}
	return inp[0];
}


ostream& operator<<(ostream& os, const TripInfo& r)	 // Перегрузка вывода TripInfo
{
	os << r.departure_point << " " << r.departure_time << " " << r.arrival_point << " " << r.arrival_time << " ";
	return os;
}

ostream& operator<<(ostream& os, const TrainTimetable& t)	 // Перегрузка вывода TrainTimetable
{
	os << t.date << " " << t.number_of_trips << " " ;

	for (int i = 0; i < t.tripInfoVec.size(); i++)
	{
		os << t.tripInfoVec[i];
	}
	return os;
}

void consOutput(vector<TrainTimetable> trainTimetableVec)  // Вывод массивов в консоль
{
	cout << "\nРасписание: [ ";

	for (int i = 0; i < trainTimetableVec.size(); i++)
	{
		cout << trainTimetableVec[i];  // Перегруженный вывод
	}
	cout << "]" << endl;

	cout << "\nСамый/е короткий/е рейс/ы: [ ";

	for (int i = 0; i < trainTimetableVec.size(); i++)
	{
		cout << trainTimetableVec[i].Get_the_shortest_trip();  // Перегруженный вывод
	}
	cout << "]" << endl;

}

void fOutput(vector<TrainTimetable> trainTimetableVec)  // Вывод массивов в файл
{
	ofstream file; // создаем объект класса ofstream
	file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Лаба 5 ПП записываем.txt");

	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт! Записано в файл!" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	file << "\nРасписание: [ ";
	for (int i = 0; i < trainTimetableVec.size(); i++)
	{
		file << trainTimetableVec[i];	 // Прегруженный вывод
	}
	file << "]" << endl;

	file << "\nСамый/е короткий/е рейс/ы: [ ";

	for (int i = 0; i < trainTimetableVec.size(); i++)
	{
		file << trainTimetableVec[i].Get_the_shortest_trip();  // Перегруженный вывод
	}
	file << " ]" << endl;

	file.close();

}


int main()
{
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "eng");

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	vector<TrainTimetable> trainTimetableVec;

	cout << "\nВведите i, если хотите ввести вручную, или f, если хотите прочитать из файла: ";
	char inp = check_f_i();

	try
	{
		if (inp == 'i')  // РУЧНОЙ ВВОД 
		{
			consInput(trainTimetableVec);
		}
		else if (inp == 'f')  // ЧТЕНИЕ ИЗ ФАЙЛА
		{
			fInput(trainTimetableVec);
			
		}


		cout << "\nВведите c, если хотите вывести в консоль, или r, если хотите записать в файл: ";
		char out = check_r_c();

		if (out == 'c')  // ВЫВОД В КОНСОЛЬ 
		{
			consOutput(trainTimetableVec);
		}
		else if (out == 'r')  // ЗАПИСЬ В ФАЙЛ
		{
			fOutput(trainTimetableVec);
		}
	}
	catch (runtime_error& e)
	{
		cout << e.what();
	}
	catch (invalid_argument)
	{
		cout << "\nНекорректные данные в файле!\n";
	}
	catch (out_of_range)
	{
		cout << "\nО нет, выход за пределы максимально возможного значения!!!\n";
	}

}
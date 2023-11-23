#include "Header.h"

void FillDataBaseStudVect(vector<DataBaseStud>& DataBaseStudents) {
	DataBaseStud DB;
	ifstream DataBase;
	DataBase.open("DataBaseStudents.txt");
	if (!DataBase.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!DataBase.eof()) {
		getline(DataBase, DB.FullName);
		if (DB.FullName == "") {
			if (DataBase.eof()) {
				break;
			}
			getline(DataBase, DB.FullName);
			getline(DataBase, DB.FullName);
		}
		DataBase >> DB.DataBaseStudInfo.StudID >> DB.DataBaseStudInfo.Group >> DB.DataBaseStudInfo.GPA >> DB.DataBaseMark;
		DataBaseStudents.push_back(DB);
	}
	DataBase.close();
}

void AddDataBaseStudent(vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	DataBaseStud student;
	bool IsRecorded = false;
	do {
		int x = 45, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
			{
				White();
				system("cls");
				ConsoleCursorVisible(true, 1);
				int x = 40, y = 12;
				for (int i = 0; i < DataBaseStudents.size(); i++) {
					if (Users[ThisUser].FullName == DataBaseStudents[i].FullName) {
						GoToXY(x, y);
						cout << "Вы уже записаны на эту дисциплину!";
						IsRecorded = true;
						DeleteConsole(35, y += 2);
						break;
					}
				}
				if (!IsRecorded) {
					student.FullName = Users[ThisUser].FullName;
					student.DataBaseStudInfo.StudID = Users[ThisUser].UserInfo.StudID;
					student.DataBaseStudInfo.Group = Users[ThisUser].UserInfo.Group;
					student.DataBaseStudInfo.GPA = Users[ThisUser].UserInfo.GPA;
					GoToXY(x, y);
					cout << "Введите вашу оценку по базам данных: ";
					InputMark(student.DataBaseMark);
					DataBaseStudents.push_back(student);
					system("cls");
					GoToXY(40, 12);
					cout << "Поздравляем! Вы успешно подали заявку.";
					DeleteConsole(40, 14);
				}
				isBack = true;
			}
			break;
			case 1:
				White();
				system("cls");
				GoToXY(45, 12);
				isBack = true;
				cout << "Вы отменили действие.";
				DeleteConsole(38, 14);
				break;
			}
			break;
		}
	} while (!isBack);
}

void DeleteDataBaseStudent(vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	DataBaseStud student;
	bool IsRecorded = false;
	int studNumber;
	do {
		int x = 45, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
			{
				White();
				ConsoleCursorVisible(true, 1);
				system("cls");
				int x = 25, y = 10;
				for (int i = 0; i < DataBaseStudents.size(); i++) {
					if (Users[ThisUser].FullName == DataBaseStudents[i].FullName) {
						studNumber = i;
						IsRecorded = true;
						break;
					}
				}
				if (!IsRecorded) {
					GoToXY(x, y);
					cout << "Вы не записаны на данную дисциплину!";
					DeleteConsole(x, y += 2);
				}
				else {
					vector<DataBaseStud>::iterator it = DataBaseStudents.begin();
					DataBaseStudents.erase(it + studNumber);
					GoToXY(x, y);
					cout << "Вы успешно отозвали заявку!";
					DeleteConsole(x, y += 2);
				}
				isBack = true;
			}
			break;
			case 1:
				White();
				system("cls");
				GoToXY(45, 12);
				isBack = true;
				cout << "Вы отменили действие.";
				DeleteConsole(38, 14);
				break;
			}
			break;
		}
	} while (!isBack);
}

void BubbleSortDataBaseStudentsMenu(vector<DataBaseStud>& DataBaseStudents) {
	system("cls");
	string menu[] = { "Отсортировать студентов по алфавиту", "Отсортировать студентов по среднему баллу", "Отсортировать студентов по оценке данного предмета", "Вернуться назад" };
	int active_menu = 0;
	bool isBack = false;
	char ch;
	do {
		int x = 45, y = 10;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
				BubbleSortDataBase(DataBaseStudents, active_menu + 1);
				break;
			case 1:
				BubbleSortDataBase(DataBaseStudents, active_menu + 1);
				break;
			case 2:
				BubbleSortDataBase(DataBaseStudents, active_menu + 1);
				break;
			case 3:
				White();
				system("cls");
				GoToXY(45, 12);
				cout << "Вы вернулись назад.";
				DeleteConsole(38, 14);
				break;
			}
			isBack = true;
			break;
		}
	} while (!isBack);
}

void BubbleSortDataBase(vector<DataBaseStud>& DataBaseStudents, int option) {
	int i, j;
	for (i = 0; i < DataBaseStudents.size(); i++) {
		for (j = DataBaseStudents.size() - 1; j > i; j--) {
			if (option == 1) {
				if (DataBaseStudents[j - 1].FullName > DataBaseStudents[j].FullName) {
					swap(DataBaseStudents[j - 1], DataBaseStudents[j]);
				}
			}
			else if (option == 2) {
				if (DataBaseStudents[j - 1].DataBaseStudInfo.GPA < DataBaseStudents[j].DataBaseStudInfo.GPA) {
					swap(DataBaseStudents[j - 1], DataBaseStudents[j]);
				}
			}
			else {
				if (DataBaseStudents[j - 1].DataBaseMark < DataBaseStudents[j].DataBaseMark) {
					swap(DataBaseStudents[j - 1], DataBaseStudents[j]);
				}
			}
		}
	}
}

void FilteringDataBaseStudentsMenu(vector<DataBaseStud> DataBaseStudents) {
	system("cls");
	string menu[] = { "Отфильтровать студентов по среднему баллу", "Отфильтровать студентов по оценке данного предмета", "Вернуться назад" };
	int active_menu = 0;
	bool isBack = false;
	char ch;
	do {
		int x = 45, y = 10;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
				FilteringByGPADataBase(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				FilteringByDataBaseMark(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				White();
				system("cls");
				GoToXY(45, 12);
				cout << "Вы вернулись назад.";
				DeleteConsole(38, 14);
				break;
			}
			isBack = true;
			break;
		}
	} while (!isBack);
}

void FilteringByGPADataBase(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA_min, GPA_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальный и максимальный средний балл, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputGPA(GPA_min);
	cout << endl << "Верхний порог : ";
	InputGPA(GPA_max);
	for (index = 0; index < DataBaseStudents.size(); index++) {
		if (DataBaseStudents[index].DataBaseStudInfo.GPA >= GPA_min && DataBaseStudents[index].DataBaseStudInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			if (DataBaseStudents[i].DataBaseStudInfo.GPA >= GPA_min && DataBaseStudents[i].DataBaseStudInfo.GPA <= GPA_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
					<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void FilteringByDataBaseMark(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int DataBaseMark_min, DataBaseMark_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальную и максимальную оценку, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputMark(DataBaseMark_min);
	cout << endl << "Верхний порог: ";
	InputMark(DataBaseMark_max);
	for (index = 0; index < DataBaseStudents.size(); index++) {
		if (DataBaseStudents[index].DataBaseMark >= DataBaseMark_min && DataBaseStudents[index].DataBaseMark <= DataBaseMark_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			if (DataBaseStudents[i].DataBaseMark >= DataBaseMark_min && DataBaseStudents[i].DataBaseMark <= DataBaseMark_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
					<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchDataBaseStudentsMenu(vector<DataBaseStud> DataBaseStudents) {
	system("cls");
	string menu[] = { "Произвести поиск студентов по ФИО", "Произвести поиск студентов по номеру группы", "Произвести поиск студентов по среднему баллу",
		"Произвести поиск студентов по оценке по данному предмету", "Вернуться назад" };
	int active_menu = 0;
	bool isBack = false;
	char ch;
	do {
		int x = 30, y = 10;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
				DataBaseSearchByName(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				DataBaseSearchByGroup(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				DataBaseSearchByGPA(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 3:
				DataBaseSearchByMark(DataBaseStudents);
				DeleteConsole(45, 24);
				break;
			case 4:
				White();
				system("cls");
				GoToXY(45, 12);
				cout << "Вы вернулись назад.";
				DeleteConsole(38, 14);
				break;
			}
			isBack = true;
			break;
		}
	} while (!isBack);
}

void DataBaseSearchByName(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	setlocale(LC_ALL, "Rus");
	string FullName;
	string LowerFullName;
	bool isFind = false;
	GoToXY(25, 12);
	cout << "Введите ФИО интересуемого студента: ";
	char tempCh;
	while (true) {
		char ch = _getch();
		tempCh = ch;
		if ((int)ch == 13) {  // Enter key
			break;
		}
		if ((int)ch == 8) {  // Backspace key
			if (!LowerFullName.empty()) {
				LowerFullName.pop_back();
				FullName.pop_back();
				system("cls");
			}
		}
		if ((int)ch != 8) {
			LowerFullName += tolower(ch);
			FullName += ch;
		}
		system("cls");
		isFind = false;
		cout << "Введите ФИО интересуемого студента: " << FullName;
		for (int index = 0; index < DataBaseStudents.size(); index++) {
			string UserName = DataBaseStudents[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
						<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
					cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[index].FullName << setw(12) << "|" << setw(8)
					<< DataBaseStudents[index].DataBaseStudInfo.Group << setw(3) << "|" << setw(10) << DataBaseStudents[index].DataBaseStudInfo.GPA
					<< setw(7) << "|" << setw(15) << DataBaseStudents[index].DataBaseMark << setw(13) << "|" << endl;
				cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Студент с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTableDataBase(DataBaseStudents);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Студент с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void DataBaseSearchByGroup(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < DataBaseStudents.size(); index++) {
		if (GroupNumber == DataBaseStudents[index].DataBaseStudInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			if (GroupNumber == DataBaseStudents[i].DataBaseStudInfo.Group) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
					<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void DataBaseSearchByGPA(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < DataBaseStudents.size(); index++) {
		if (GPA == DataBaseStudents[index].DataBaseStudInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			if (GPA == DataBaseStudents[i].DataBaseStudInfo.GPA) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
					<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void DataBaseSearchByMark(vector<DataBaseStud> DataBaseStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int DataBaseMark;
	bool isFind = false;
	int index = 0;
	cout << "Введите оценку по базам данных: ";
	InputMark(DataBaseMark);
	for (index = 0; index < DataBaseStudents.size(); index++) {
		if (DataBaseMark == DataBaseStudents[index].DataBaseMark) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(базы данных)" << setw(5) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			if (DataBaseMark == DataBaseStudents[i].DataBaseMark) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
					<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PrintBestDataBaseStudents(vector<DataBaseStud> DataBaseStudents) {
	system("cls");
	BubbleSortDataBase(DataBaseStudents, 2);
	GoToXY(35, 2);
	cout << "Таблица студентов, проходящих отбор на базы данных" << endl;
	if (DataBaseStudents.size() > 14) {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(24) << "Отметка(базы данных)" << setw(4) << "|" << endl;
		for (int i = 0; i < 15; i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
				<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 37);
	}
	else {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(24) << "Отметка(базы данных)" << setw(4) << "|" << endl;
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
				<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 7 + DataBaseStudents.size() * 2);
	}
}

void LookListOfDataBaseStudentsMenu(vector<DataBaseStud>& DataBaseStudents) {
	system("cls");
	string menu[] = { "Отсортировать студентов по параметру", "Отфильтровать студентов по параметру", "Поиск студента по параметру", "Вывести 15 лучших студентов", "Вернуться назад" };
	int active_menu = 0;
	bool isBack = false;
	char ch;
	do {
		system("cls");
		int x = 45, y = 2;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		cout << endl;
		PrintTableDataBase(DataBaseStudents);
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			else active_menu = size(menu) - 1;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			else active_menu = 0;
			break;
		case ESC:
			exit(0);
		case ENTER:
			switch (active_menu) {
			case 0:
				BubbleSortDataBaseStudentsMenu(DataBaseStudents);
				break;
			case 1:
				FilteringDataBaseStudentsMenu(DataBaseStudents);
				break;
			case 2:
				SearchDataBaseStudentsMenu(DataBaseStudents);
				break;
			case 3:
				PrintBestDataBaseStudents(DataBaseStudents);
				break;
			case 4:
				White();
				system("cls");
				GoToXY(45, 12);
				isBack = true;
				cout << "Вы вернулись назад.";
				DeleteConsole(38, 14);
				break;
			}
			break;
		}
	} while (!isBack);
}

void PrintTableDataBase(vector<DataBaseStud> DataBaseStudents) {
	White();
	cout << endl << setw(93) << "Таблица с данными о студентах, желающих поступить на базы данных\n" << endl;
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
		<< setw(14) << "Средний балл" << setw(3) << "|" << setw(24) << "Отметка(базы данных)" << setw(4) << "|" << endl;
	for (int i = 0; i < DataBaseStudents.size(); i++) {
		cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
		cout << setw(9) << "|" << setw(34) << DataBaseStudents[i].FullName << setw(12) << "|" << setw(8) << DataBaseStudents[i].DataBaseStudInfo.Group << setw(3) << "|"
			<< setw(10) << DataBaseStudents[i].DataBaseStudInfo.GPA << setw(7) << "|" << setw(15) << DataBaseStudents[i].DataBaseMark << setw(13) << "|" << endl;
	}
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToDataBaseFile(vector<DataBaseStud> DataBaseStudents) {
	ofstream Data;
	Data.open("DataBaseStudents.txt");
	if (!Data.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < DataBaseStudents.size(); i++) {
			Data << DataBaseStudents[i].FullName << endl << DataBaseStudents[i].DataBaseStudInfo.StudID << endl
				<< DataBaseStudents[i].DataBaseStudInfo.Group << endl << DataBaseStudents[i].DataBaseStudInfo.GPA
				<< endl << DataBaseStudents[i].DataBaseMark;
			if (i != DataBaseStudents.size() - 1) {
				Data << endl << endl;
			}
		}
	}
	Data.close();
}
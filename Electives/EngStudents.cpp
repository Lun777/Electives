#include "Header.h"

void FillEngStudVect(vector<EngStud>& EngStudents) {
	EngStud E;
	ifstream Eng;
	Eng.open("EnglishStudents.txt");
	if (!Eng.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!Eng.eof()) {
		getline(Eng, E.FullName);
		if (E.FullName == "") {
			if (Eng.eof()) {
				break;
			}
			getline(Eng, E.FullName);
			getline(Eng, E.FullName);
		}
		Eng >> E.EngStudInfo.StudID >> E.EngStudInfo.Group >> E.EngStudInfo.GPA >> E.EngMark;
		EngStudents.push_back(E);
	}
	Eng.close();
}

void AddEngStudent(vector<EngStud>& EngStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	EngStud student;
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
				for (int i = 0; i < EngStudents.size(); i++) {
					if (Users[ThisUser].FullName == EngStudents[i].FullName) {
						GoToXY(x, y);
						cout << "Вы уже записаны на эту дисциплину!";
						IsRecorded = true;
						DeleteConsole(35, y += 2);
						break;
					}
				}
				if (!IsRecorded) {
					student.FullName = Users[ThisUser].FullName;
					student.EngStudInfo.StudID = Users[ThisUser].UserInfo.StudID;
					student.EngStudInfo.Group = Users[ThisUser].UserInfo.Group;
					student.EngStudInfo.GPA = Users[ThisUser].UserInfo.GPA;
					GoToXY(x, y);
					cout << "Введите вашу оценку по английскому языку: ";
					InputMark(student.EngMark);
					EngStudents.push_back(student);
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

void DeleteEngStudent(vector<EngStud>& EngStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	EngStud student;
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
				for (int i = 0; i < EngStudents.size(); i++) {
					if (Users[ThisUser].FullName == EngStudents[i].FullName) {
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
					vector<EngStud>::iterator it = EngStudents.begin();
					EngStudents.erase(it + studNumber);
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

void BubbleSortEngStudentsMenu(vector<EngStud>& EngStudents) {
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
				BubbleSortEng(EngStudents, active_menu + 1);
				break;
			case 1:
				BubbleSortEng(EngStudents, active_menu + 1);
				break;
			case 2:
				BubbleSortEng(EngStudents, active_menu + 1);
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

void BubbleSortEng(vector<EngStud>& EngStudents, int option) {
	int i, j;
	for (i = 0; i < EngStudents.size(); i++) {
		for (j = EngStudents.size() - 1; j > i; j--) {
			if (option == 1) {
				if (EngStudents[j - 1].FullName > EngStudents[j].FullName) {
					swap(EngStudents[j - 1], EngStudents[j]);
				}
			}
			else if (option == 2) {
				if (EngStudents[j - 1].EngStudInfo.GPA < EngStudents[j].EngStudInfo.GPA) {
					swap(EngStudents[j - 1], EngStudents[j]);
				}
			}
			else {
				if (EngStudents[j - 1].EngMark < EngStudents[j].EngMark) {
					swap(EngStudents[j - 1], EngStudents[j]);
				}
			}
		}
	}
}

void FilteringEngStudentsMenu(vector<EngStud> EngStudents) {
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
				FilteringByGPAEng(EngStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				FilteringByEngMark(EngStudents);
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

void FilteringByGPAEng(vector<EngStud> EngStudents) {
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
	for (index = 0; index < EngStudents.size(); index++) {
		if (EngStudents[index].EngStudInfo.GPA >= GPA_min && EngStudents[index].EngStudInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			if (EngStudents[i].EngStudInfo.GPA >= GPA_min && EngStudents[i].EngStudInfo.GPA <= GPA_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
					<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void FilteringByEngMark(vector<EngStud> EngStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int EngMark_min, EngMark_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальную и максимальную оценку, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputMark(EngMark_min);
	cout << endl << "Верхний порог: ";
	InputMark(EngMark_max);
	for (index = 0; index < EngStudents.size(); index++) {
		if (EngStudents[index].EngMark >= EngMark_min && EngStudents[index].EngMark <= EngMark_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			if (EngStudents[i].EngMark >= EngMark_min && EngStudents[i].EngMark <= EngMark_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
					<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchEngStudentsMenu(vector<EngStud> EngStudents) {
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
				EngSearchByName(EngStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				EngSearchByGroup(EngStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				EngSearchByGPA(EngStudents);
				DeleteConsole(45, 24);
				break;
			case 3:
				EngSearchByMark(EngStudents);
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

void EngSearchByName(vector<EngStud> EngStudents) {
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
		for (int index = 0; index < EngStudents.size(); index++) {
			string UserName = EngStudents[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
						<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
					cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(9) << "|" << setw(34) << EngStudents[index].FullName << setw(12) << "|" << setw(8)
					<< EngStudents[index].EngStudInfo.Group << setw(3) << "|" << setw(10) << EngStudents[index].EngStudInfo.GPA
					<< setw(7) << "|" << setw(15) << EngStudents[index].EngMark << setw(13) << "|" << endl;
				cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Студент с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTableEng(EngStudents);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Студент с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void EngSearchByGroup(vector<EngStud> EngStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < EngStudents.size(); index++) {
		if (GroupNumber == EngStudents[index].EngStudInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			if (GroupNumber == EngStudents[i].EngStudInfo.Group) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
					<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void EngSearchByGPA(vector<EngStud> EngStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < EngStudents.size(); index++) {
		if (GPA == EngStudents[index].EngStudInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			if (GPA == EngStudents[i].EngStudInfo.GPA) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
					<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void EngSearchByMark(vector<EngStud> EngStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int EngMark;
	bool isFind = false;
	int index = 0;
	cout << "Введите оценку по английскому языку: ";
	InputMark(EngMark);
	for (index = 0; index < EngStudents.size(); index++) {
		if (EngMark == EngStudents[index].EngMark) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			if (EngMark == EngStudents[i].EngMark) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
					<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PrintBestEngStudents(vector<EngStud> EngStudents) {
	system("cls");
	BubbleSortEng(EngStudents, 2);
	GoToXY(35, 2);
	cout << "Таблица студентов, проходящих отбор на английский язык" << endl;
	if (EngStudents.size() > 14) {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < 15; i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
				<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 37);
	}
	else {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
		for (int i = 0; i < EngStudents.size(); i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
				<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 7 + EngStudents.size() * 2);
	}
}

void LookListOfEngStudentsMenu(vector<EngStud>& EngStudents) {
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
		PrintTableEng(EngStudents);
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
				BubbleSortEngStudentsMenu(EngStudents);
				break;
			case 1:
				FilteringEngStudentsMenu(EngStudents);
				break;
			case 2:
				SearchEngStudentsMenu(EngStudents);
				break;
			case 3:
				PrintBestEngStudents(EngStudents);
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

void PrintTableEng(vector<EngStud> EngStudents) {
	White();
	cout << endl << setw(95) << "Таблица с данными о студентах, желающих поступить на английский язык\n" << endl;
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
		<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(английский язык)" << setw(2) << "|" << endl;
	for (int i = 0; i < EngStudents.size(); i++) {
		cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
		cout << setw(9) << "|" << setw(34) << EngStudents[i].FullName << setw(12) << "|" << setw(8) << EngStudents[i].EngStudInfo.Group << setw(3) << "|"
			<< setw(10) << EngStudents[i].EngStudInfo.GPA << setw(7) << "|" << setw(15) << EngStudents[i].EngMark << setw(13) << "|" << endl;
	}
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToEngFile(vector<EngStud> EngStudents) {
	ofstream Eng;
	Eng.open("EnglishStudents.txt");
	if (!Eng.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < EngStudents.size(); i++) {
			Eng << EngStudents[i].FullName << endl << EngStudents[i].EngStudInfo.StudID << endl << EngStudents[i].EngStudInfo.Group
				<< endl << EngStudents[i].EngStudInfo.GPA << endl << EngStudents[i].EngMark;
			if (i != EngStudents.size() - 1) {
				Eng << endl << endl;
			}
		}
	}
	Eng.close();
}
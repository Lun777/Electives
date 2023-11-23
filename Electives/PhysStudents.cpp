#include "Header.h"

void FillPhysStudVect(vector<PhysStud>& PhysStudents) {
	PhysStud P;
	ifstream Phys;
	Phys.open("PhysStudents.txt");
	if (!Phys.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!Phys.eof()) {
		getline(Phys, P.FullName);
		if (P.FullName == "") {
			if (Phys.eof()) {
				break;
			}
			getline(Phys, P.FullName);
			getline(Phys, P.FullName);
		}
		Phys >> P.PhysStudInfo.StudID >> P.PhysStudInfo.Group >> P.PhysStudInfo.GPA >> P.PhysMark;
		PhysStudents.push_back(P);
	}
	Phys.close();
}

void AddPhysStudent(vector<PhysStud>& PhysStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	PhysStud student;
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
				for (int i = 0; i < PhysStudents.size(); i++) {
					if (Users[ThisUser].FullName == PhysStudents[i].FullName) {
						GoToXY(x, y);
						cout << "Вы уже записаны на эту дисциплину!";
						IsRecorded = true;
						DeleteConsole(35, y += 2);
						break;
					}
				}
				if (!IsRecorded) {
					student.FullName = Users[ThisUser].FullName;
					student.PhysStudInfo.StudID = Users[ThisUser].UserInfo.StudID;
					student.PhysStudInfo.Group = Users[ThisUser].UserInfo.Group;
					student.PhysStudInfo.GPA = Users[ThisUser].UserInfo.GPA;
					GoToXY(x, y);
					cout << "Введите вашу оценку по физике: ";
					InputMark(student.PhysMark);
					PhysStudents.push_back(student);
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

void DeletePhysStudent(vector<PhysStud>& PhysStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	PhysStud student;
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
				for (int i = 0; i < PhysStudents.size(); i++) {
					if (Users[ThisUser].FullName == PhysStudents[i].FullName) {
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
					vector<PhysStud>::iterator it = PhysStudents.begin();
					PhysStudents.erase(it + studNumber);
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

void BubbleSortPhysStudentsMenu(vector<PhysStud>& PhysStudents) {
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
				BubbleSortPhys(PhysStudents, active_menu + 1);
				break;
			case 1:
				BubbleSortPhys(PhysStudents, active_menu + 1);
				break;
			case 2:
				BubbleSortPhys(PhysStudents, active_menu + 1);
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

void BubbleSortPhys(vector<PhysStud>& PhysStudents, int option) {
	int i, j;
	for (i = 0; i < PhysStudents.size(); i++) {
		for (j = PhysStudents.size() - 1; j > i; j--) {
			if (option == 1) {
				if (PhysStudents[j - 1].FullName > PhysStudents[j].FullName) {
					swap(PhysStudents[j - 1], PhysStudents[j]);
				}
			}
			else if (option == 2) {
				if (PhysStudents[j - 1].PhysStudInfo.GPA < PhysStudents[j].PhysStudInfo.GPA) {
					swap(PhysStudents[j - 1], PhysStudents[j]);
				}
			}
			else {
				if (PhysStudents[j - 1].PhysMark < PhysStudents[j].PhysMark) {
					swap(PhysStudents[j - 1], PhysStudents[j]);
				}
			}
		}
	}
}

void FilteringPhysStudentsMenu(vector<PhysStud> PhysStudents) {
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
				FilteringByGPAPhys(PhysStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				FilteringByPhysMark(PhysStudents);
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

void FilteringByGPAPhys(vector<PhysStud> PhysStudents) {
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
	for (index = 0; index < PhysStudents.size(); index++) {
		if (PhysStudents[index].PhysStudInfo.GPA >= GPA_min && PhysStudents[index].PhysStudInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			if (PhysStudents[i].PhysStudInfo.GPA >= GPA_min && PhysStudents[i].PhysStudInfo.GPA <= GPA_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
					<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void FilteringByPhysMark(vector<PhysStud> PhysStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int PhysMark_min, PhysMark_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальную и максимальную оценку, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputMark(PhysMark_min);
	cout << endl << "Верхний порог: ";
	InputMark(PhysMark_max);
	for (index = 0; index < PhysStudents.size(); index++) {
		if (PhysStudents[index].PhysMark >= PhysMark_min && PhysStudents[index].PhysMark <= PhysMark_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			if (PhysStudents[i].PhysMark >= PhysMark_min && PhysStudents[i].PhysMark <= PhysMark_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
					<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchPhysStudentsMenu(vector<PhysStud> PhysStudents) {
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
				PhysSearchByName(PhysStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				PhysSearchByGroup(PhysStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				PhysSearchByGPA(PhysStudents);
				DeleteConsole(45, 24);
				break;
			case 3:
				PhysSearchByMark(PhysStudents);
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

void PhysSearchByName(vector<PhysStud> PhysStudents) {
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
		for (int index = 0; index < PhysStudents.size(); index++) {
			string UserName = PhysStudents[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
						<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
					cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(9) << "|" << setw(34) << PhysStudents[index].FullName << setw(12) << "|" << setw(8)
					<< PhysStudents[index].PhysStudInfo.Group << setw(3) << "|" << setw(10) << PhysStudents[index].PhysStudInfo.GPA
					<< setw(7) << "|" << setw(15) << PhysStudents[index].PhysMark << setw(13) << "|" << endl;
				cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Студент с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTablePhys(PhysStudents);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Студент с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void PhysSearchByGroup(vector<PhysStud> PhysStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < PhysStudents.size(); index++) {
		if (GroupNumber == PhysStudents[index].PhysStudInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			if (GroupNumber == PhysStudents[i].PhysStudInfo.Group) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
					<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PhysSearchByGPA(vector<PhysStud> PhysStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < PhysStudents.size(); index++) {
		if (GPA == PhysStudents[index].PhysStudInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			if (GPA == PhysStudents[i].PhysStudInfo.GPA) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
					<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void PhysSearchByMark(vector<PhysStud> PhysStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int PhysMark;
	bool isFind = false;
	int index = 0;
	cout << "Введите оценку по физике: ";
	InputMark(PhysMark);
	for (index = 0; index < PhysStudents.size(); index++) {
		if (PhysMark == PhysStudents[index].PhysMark) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			if (PhysMark == PhysStudents[i].PhysMark) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
					<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PrintBestPhysStudents(vector<PhysStud> PhysStudents) {
	system("cls");
	BubbleSortPhys(PhysStudents, 2);
	GoToXY(35, 2);
	cout << "Таблица студентов, проходящих отбор на физику" << endl;
	if (PhysStudents.size() > 14) {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < 15; i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
				<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 37);
	}
	else {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
		for (int i = 0; i < PhysStudents.size(); i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
				<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 7 + PhysStudents.size() * 2);
	}
}

void LookListOfPhysStudentsMenu(vector<PhysStud>& PhysStudents) {
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
		PrintTablePhys(PhysStudents);
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
				BubbleSortPhysStudentsMenu(PhysStudents);
				break;
			case 1:
				FilteringPhysStudentsMenu(PhysStudents);
				break;
			case 2:
				SearchPhysStudentsMenu(PhysStudents);
				break;
			case 3:
				PrintBestPhysStudents(PhysStudents);
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

void PrintTablePhys(vector<PhysStud> PhysStudents) {
	White();
	cout << endl << setw(90) << "Таблица с данными о студентах, желающих поступить на физику\n" << endl;
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
		<< setw(14) << "Средний балл" << setw(3) << "|" << setw(21) << "Отметка(физика)" << setw(7) << "|" << endl;
	for (int i = 0; i < PhysStudents.size(); i++) {
		cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
		cout << setw(9) << "|" << setw(34) << PhysStudents[i].FullName << setw(12) << "|" << setw(8) << PhysStudents[i].PhysStudInfo.Group << setw(3) << "|"
			<< setw(10) << PhysStudents[i].PhysStudInfo.GPA << setw(7) << "|" << setw(15) << PhysStudents[i].PhysMark << setw(13) << "|" << endl;
	}
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToPhysFile(vector<PhysStud> PhysStudents) {
	ofstream Phys;
	Phys.open("PhysStudents.txt");
	if (!Phys.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < PhysStudents.size(); i++) {
			Phys << PhysStudents[i].FullName << endl << PhysStudents[i].PhysStudInfo.StudID << endl << PhysStudents[i].PhysStudInfo.Group
				<< endl << PhysStudents[i].PhysStudInfo.GPA << endl << PhysStudents[i].PhysMark;
			if (i != PhysStudents.size() - 1) {
				Phys << endl << endl;
			}
		}
	}
	Phys.close();
}
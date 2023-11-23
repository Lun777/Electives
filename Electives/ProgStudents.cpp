#include "Header.h"

void FillProgStudVect(vector<ProgStud>& ProgStudents) {
	ProgStud Ph;
	ifstream Prog;
	Prog.open("ProgStudents.txt");
	if (!Prog.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!Prog.eof()) {
		getline(Prog, Ph.FullName);
		if (Ph.FullName == "") {
			if (Prog.eof()) {
				break;
			}
			getline(Prog, Ph.FullName);
			getline(Prog, Ph.FullName);
		}
		Prog >> Ph.ProgStudInfo.StudID >> Ph.ProgStudInfo.Group >> Ph.ProgStudInfo.GPA >> Ph.ProgMark;
		ProgStudents.push_back(Ph);
	}
	Prog.close();
}

void AddProgStudent(vector<ProgStud>& ProgStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	ProgStud student;
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
				for (int i = 0; i < ProgStudents.size(); i++) {
					if (Users[ThisUser].FullName == ProgStudents[i].FullName) {
						GoToXY(x, y);
						cout << "Вы уже записаны на эту дисциплину!";
						IsRecorded = true;
						DeleteConsole(35, y += 2);
						break;
					}
				}
				if (!IsRecorded) {
					student.FullName = Users[ThisUser].FullName;
					student.ProgStudInfo.StudID = Users[ThisUser].UserInfo.StudID;
					student.ProgStudInfo.Group = Users[ThisUser].UserInfo.Group;
					student.ProgStudInfo.GPA = Users[ThisUser].UserInfo.GPA;
					GoToXY(x, y);
					cout << "Введите вашу оценку по программированию: ";
					InputMark(student.ProgMark);
					ProgStudents.push_back(student);
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

void DeleteProgStudent(vector<ProgStud>& ProgStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	ProgStud student;
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
				for (int i = 0; i < ProgStudents.size(); i++) {
					if (Users[ThisUser].FullName == ProgStudents[i].FullName) {
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
					vector<ProgStud>::iterator it = ProgStudents.begin();
					ProgStudents.erase(it + studNumber);
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

void BubbleSortProgStudentsMenu(vector<ProgStud>& ProgStudents) {
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
				BubbleSortProg(ProgStudents, active_menu + 1);
				break;
			case 1:
				BubbleSortProg(ProgStudents, active_menu + 1);
				break;
			case 2:
				BubbleSortProg(ProgStudents, active_menu + 1);
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

void BubbleSortProg(vector<ProgStud>& ProgStudents, int option) {
	int i, j;
	for (i = 0; i < ProgStudents.size(); i++) {
		for (j = ProgStudents.size() - 1; j > i; j--) {
			if (option == 1) {
				if (ProgStudents[j - 1].FullName > ProgStudents[j].FullName) {
					swap(ProgStudents[j - 1], ProgStudents[j]);
				}
			}
			else if (option == 2) {
				if (ProgStudents[j - 1].ProgStudInfo.GPA < ProgStudents[j].ProgStudInfo.GPA) {
					swap(ProgStudents[j - 1], ProgStudents[j]);
				}
			}
			else {
				if (ProgStudents[j - 1].ProgMark < ProgStudents[j].ProgMark) {
					swap(ProgStudents[j - 1], ProgStudents[j]);
				}
			}
		}
	}
}

void FilteringProgStudentsMenu(vector<ProgStud> ProgStudents) {
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
				FilteringByGPAProg(ProgStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				FilteringByProgMark(ProgStudents);
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

void FilteringByGPAProg(vector<ProgStud> ProgStudents) {
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
	for (index = 0; index < ProgStudents.size(); index++) {
		if (ProgStudents[index].ProgStudInfo.GPA >= GPA_min && ProgStudents[index].ProgStudInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			if (ProgStudents[i].ProgStudInfo.GPA >= GPA_min && ProgStudents[i].ProgStudInfo.GPA <= GPA_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
					<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void FilteringByProgMark(vector<ProgStud> ProgStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int ProgMark_min, ProgMark_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальную и максимальную оценку, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputMark(ProgMark_min);
	cout << endl << "Верхний порог: ";
	InputMark(ProgMark_max);
	for (index = 0; index < ProgStudents.size(); index++) {
		if (ProgStudents[index].ProgMark >= ProgMark_min && ProgStudents[index].ProgMark <= ProgMark_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			if (ProgStudents[i].ProgMark >= ProgMark_min && ProgStudents[i].ProgMark <= ProgMark_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
					<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchProgStudentsMenu(vector<ProgStud> ProgStudents) {
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
				ProgSearchByName(ProgStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				ProgSearchByGroup(ProgStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				ProgSearchByGPA(ProgStudents);
				DeleteConsole(45, 24);
				break;
			case 3:
				ProgSearchByMark(ProgStudents);
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

void ProgSearchByName(vector<ProgStud> ProgStudents) {
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
		for (int index = 0; index < ProgStudents.size(); index++) {
			string UserName = ProgStudents[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
						<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
					cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(9) << "|" << setw(34) << ProgStudents[index].FullName << setw(12) << "|" << setw(8)
					<< ProgStudents[index].ProgStudInfo.Group << setw(3) << "|" << setw(10) << ProgStudents[index].ProgStudInfo.GPA
					<< setw(7) << "|" << setw(15) << ProgStudents[index].ProgMark << setw(13) << "|" << endl;
				cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Студент с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTableProg(ProgStudents);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Студент с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void ProgSearchByGroup(vector<ProgStud> ProgStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < ProgStudents.size(); index++) {
		if (GroupNumber == ProgStudents[index].ProgStudInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			if (GroupNumber == ProgStudents[i].ProgStudInfo.Group) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
					<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void ProgSearchByGPA(vector<ProgStud> ProgStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < ProgStudents.size(); index++) {
		if (GPA == ProgStudents[index].ProgStudInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			if (GPA == ProgStudents[i].ProgStudInfo.GPA) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
					<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void ProgSearchByMark(vector<ProgStud> ProgStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int ProgMark;
	bool isFind = false;
	int index = 0;
	cout << "Введите оценку по программированию: ";
	InputMark(ProgMark);
	for (index = 0; index < ProgStudents.size(); index++) {
		if (ProgMark == ProgStudents[index].ProgMark) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			if (ProgMark == ProgStudents[i].ProgMark) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
					<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PrintBestProgStudents(vector<ProgStud> ProgStudents) {
	system("cls");
	BubbleSortProg(ProgStudents, 2);
	GoToXY(35, 2);
	cout << "Таблица студентов, проходящих отбор на программирование" << endl;
	if (ProgStudents.size() > 14) {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < 15; i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
				<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 37);
	}
	else {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
		for (int i = 0; i < ProgStudents.size(); i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
				<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 7 + ProgStudents.size() * 2);
	}
}

void LookListOfProgStudentsMenu(vector<ProgStud>& ProgStudents) {
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
		PrintTableProg(ProgStudents);
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
				BubbleSortProgStudentsMenu(ProgStudents);
				break;
			case 1:
				FilteringProgStudentsMenu(ProgStudents);
				break;
			case 2:
				SearchProgStudentsMenu(ProgStudents);
				break;
			case 3:
				PrintBestProgStudents(ProgStudents);
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

void PrintTableProg(vector<ProgStud> ProgStudents) {
	White();
	cout << endl << setw(95) << "Таблица с данными о студентах, желающих поступить на программирование\n" << endl;
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
		<< setw(14) << "Средний балл" << setw(3) << "|" << setw(26) << "Отметка(программирование)" << setw(2) << "|" << endl;
	for (int i = 0; i < ProgStudents.size(); i++) {
		cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
		cout << setw(9) << "|" << setw(34) << ProgStudents[i].FullName << setw(12) << "|" << setw(8) << ProgStudents[i].ProgStudInfo.Group << setw(3) << "|"
			<< setw(10) << ProgStudents[i].ProgStudInfo.GPA << setw(7) << "|" << setw(15) << ProgStudents[i].ProgMark << setw(13) << "|" << endl;
	}
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToProgFile(vector<ProgStud> ProgStudents) {
	ofstream Prog;
	Prog.open("ProgStudents.txt");
	if (!Prog.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < ProgStudents.size(); i++) {
			Prog << ProgStudents[i].FullName << endl << ProgStudents[i].ProgStudInfo.StudID << endl << ProgStudents[i].ProgStudInfo.Group
				<< endl << ProgStudents[i].ProgStudInfo.GPA << endl << ProgStudents[i].ProgMark;
			if (i != ProgStudents.size() - 1) {
				Prog << endl << endl;
			}
		}
	}
	Prog.close();
}
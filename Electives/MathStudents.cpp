#include "Header.h"

void FillMathStudVect(vector<MathStud>& MathStudents) {
	MathStud M;
	ifstream Math;
	Math.open("MathStudents.txt");
	if (!Math.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!Math.eof()) {
		getline(Math, M.FullName);
		if (M.FullName == "") {
			if (Math.eof()) {
				break;
			}
			getline(Math, M.FullName);
			getline(Math, M.FullName);
		}
		Math >> M.MathStudInfo.StudID >> M.MathStudInfo.Group >> M.MathStudInfo.GPA >> M.MathMark;
		MathStudents.push_back(M);
	}
	Math.close();
}

void AddMathStudent(vector<MathStud>& MathStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	MathStud student;
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
				for (int i = 0; i < MathStudents.size(); i++) {
					if (Users[ThisUser].FullName == MathStudents[i].FullName) {
						GoToXY(x, y);
						cout << "Вы уже записаны на эту дисциплину!";
						IsRecorded = true;
						DeleteConsole(35, y += 2);
						break;
					}
				}
				if (!IsRecorded) {
					student.FullName = Users[ThisUser].FullName;
					student.MathStudInfo.StudID = Users[ThisUser].UserInfo.StudID;
					student.MathStudInfo.Group = Users[ThisUser].UserInfo.Group;
					student.MathStudInfo.GPA = Users[ThisUser].UserInfo.GPA;
					GoToXY(x, y);
					cout << "Введите вашу оценку по математике: ";
					InputMark(student.MathMark);
					MathStudents.push_back(student);
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

void DeleteMathStudent(vector<MathStud>& MathStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
	MathStud student;
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
				for (int i = 0; i < MathStudents.size(); i++) {
					if (Users[ThisUser].FullName == MathStudents[i].FullName) {
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
					vector<MathStud>::iterator it = MathStudents.begin();
					MathStudents.erase(it + studNumber);
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

void BubbleSortMathStudentsMenu(vector<MathStud>& MathStudents) {
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
				BubbleSortMath(MathStudents, active_menu + 1);
				break;
			case 1:
				BubbleSortMath(MathStudents, active_menu + 1);
				break;
			case 2:
				BubbleSortMath(MathStudents, active_menu + 1);
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

void BubbleSortMath(vector<MathStud>& MathStudents, int option) {
	int i, j;
	for (i = 0; i < MathStudents.size(); i++) {
		for (j = MathStudents.size() - 1; j > i; j--) {
			if (option == 1) {
				if (MathStudents[j - 1].FullName > MathStudents[j].FullName) {
					swap(MathStudents[j - 1], MathStudents[j]);
				}
			}
			else if (option == 2) {
				if (MathStudents[j - 1].MathStudInfo.GPA < MathStudents[j].MathStudInfo.GPA) {
					swap(MathStudents[j - 1], MathStudents[j]);
				}
			}
			else {
				if (MathStudents[j - 1].MathMark < MathStudents[j].MathMark) {
					swap(MathStudents[j - 1], MathStudents[j]);
				}
			}
		}
	}
}

void FilteringMathStudentsMenu(vector<MathStud> MathStudents) {
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
				FilteringByGPAMath(MathStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				FilteringByMathMark(MathStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				White();
				system("cls");
				GoToXY(45, 12);
				cout << "Вы вернулись назад.";
				DeleteConsole(38, 24);
				break;
			}
			isBack = true;
			break;
		}
	} while (!isBack);
}

void FilteringByGPAMath(vector<MathStud> MathStudents) {
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
	for (index = 0; index < MathStudents.size(); index++) {
		if (MathStudents[index].MathStudInfo.GPA >= GPA_min && MathStudents[index].MathStudInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			if (MathStudents[i].MathStudInfo.GPA >= GPA_min && MathStudents[i].MathStudInfo.GPA <= GPA_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
					<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void FilteringByMathMark(vector<MathStud> MathStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int MathMark_min, MathMark_max;
	bool isFind = false;
	int index = 0;
	cout << "Введите минимальную и максимальную оценку, в промежутке которого выведутся студенты" << endl;
	cout << endl << "Нижний порог: ";
	InputMark(MathMark_min);
	cout << endl << "Верхний порог: ";
	InputMark(MathMark_max);
	for (index = 0; index < MathStudents.size(); index++) {
		if (MathStudents[index].MathMark >= MathMark_min && MathStudents[index].MathMark <= MathMark_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			if (MathStudents[i].MathMark >= MathMark_min && MathStudents[i].MathMark <= MathMark_max) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
					<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchMathStudentsMenu(vector<MathStud> MathStudents) {
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
				MathSearchByName(MathStudents);
				DeleteConsole(45, 24);
				break;
			case 1:
				MathSearchByGroup(MathStudents);
				DeleteConsole(45, 24);
				break;
			case 2:
				MathSearchByGPA(MathStudents);
				DeleteConsole(45, 24);
				break;
			case 3:
				MathSearchByMark(MathStudents);
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

void MathSearchByName(vector<MathStud> MathStudents) {
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
		for (int index = 0; index < MathStudents.size(); index++) {
			string UserName = MathStudents[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
						<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
					cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(9) << "|" << setw(34) << MathStudents[index].FullName << setw(12) << "|" << setw(8)
					<< MathStudents[index].MathStudInfo.Group << setw(3) << "|" << setw(10) << MathStudents[index].MathStudInfo.GPA
					<< setw(7) << "|" << setw(15) << MathStudents[index].MathMark << setw(13) << "|" << endl;
				cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Студент с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTableMath(MathStudents);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Студент с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void MathSearchByGroup(vector<MathStud> MathStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < MathStudents.size(); index++) {
		if (GroupNumber == MathStudents[index].MathStudInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			if (GroupNumber == MathStudents[i].MathStudInfo.Group) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
					<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void MathSearchByGPA(vector<MathStud> MathStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < MathStudents.size(); index++) {
		if (GPA == MathStudents[index].MathStudInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			if (GPA == MathStudents[i].MathStudInfo.GPA) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
					<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void MathSearchByMark(vector<MathStud> MathStudents) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int MathMark;
	bool isFind = false;
	int index = 0;
	cout << "Введите оценку по математике: ";
	InputMark(MathMark);
	for (index = 0; index < MathStudents.size(); index++) {
		if (MathMark == MathStudents[index].MathMark) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			if (MathMark == MathStudents[i].MathMark) {
				cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
				cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
					<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
			}
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void PrintBestMathStudents(vector<MathStud> MathStudents) {
	system("cls");
	BubbleSortMath(MathStudents, 2);
	GoToXY(35, 2);
	cout << "Таблица студентов, проходящих отбор на математику" << endl;
	if (MathStudents.size() > 14) {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < 15; i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
				<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 37);
	}
	else {
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
			<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
		for (int i = 0; i < MathStudents.size(); i++) {
			cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
			cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
				<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
		}
		cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
		DeleteConsole(35, 7 + MathStudents.size() * 2);
	}
}

void LookListOfMathStudentsMenu(vector<MathStud>& MathStudents) {
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
		PrintTableMath(MathStudents);
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
				BubbleSortMathStudentsMenu(MathStudents);
				break;
			case 1:
				FilteringMathStudentsMenu(MathStudents);
				break;
			case 2:
				SearchMathStudentsMenu(MathStudents);
				break;
			case 3:
				PrintBestMathStudents(MathStudents);
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

void PrintTableMath(vector<MathStud> MathStudents) {
	White();
	cout << endl << setw(92) << "Таблица с данными о студентах, желающих поступить на математику\n" << endl;
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(9) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(8) << "Группа" << setw(3) << "|"
		<< setw(14) << "Средний балл" << setw(3) << "|" << setw(23) << "Отметка(математика)" << setw(5) << "|" << endl;
	for (int i = 0; i < MathStudents.size(); i++) {
		cout << setw(9) << "|" << "---------------------------------------------|----------|----------------|---------------------------|" << endl;
		cout << setw(9) << "|" << setw(34) << MathStudents[i].FullName << setw(12) << "|" << setw(8) << MathStudents[i].MathStudInfo.Group << setw(3) << "|"
			<< setw(10) << MathStudents[i].MathStudInfo.GPA << setw(7) << "|" << setw(15) << MathStudents[i].MathMark << setw(13) << "|" << endl;
	}
	cout << setw(9) << "-" << "------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToMathFile(vector<MathStud> MathStudents) {
	ofstream Math;
	Math.open("MathStudents.txt");
	if (!Math.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < MathStudents.size(); i++) {
			Math << MathStudents[i].FullName << endl << MathStudents[i].MathStudInfo.StudID << endl << MathStudents[i].MathStudInfo.Group
				<< endl << MathStudents[i].MathStudInfo.GPA << endl << MathStudents[i].MathMark;
			if (i != MathStudents.size() - 1) {
				Math << endl << endl;
			}
		}
	}
	Math.close();
}
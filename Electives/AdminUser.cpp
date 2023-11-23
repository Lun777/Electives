#include "Header.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y) {
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость
	structCursorInfo.dwSize = size; // изменяем размер
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Cyan() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void LightCyan() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void White() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void DeleteConsole(int x, int y) {
	GoToXY(x, y);
	cout << "Введите любой символ чтобы продолжить..." << endl;
	cin.get();
	for (int i = 3; i > 0; --i) {
		GoToXY(x + 20, ++y);
		cout << i << "...";

		/*cout <<"Осталось: " << i <<" секунд" << endl;*/
		this_thread::sleep_for(chrono::seconds(1));

	}
	system("cls");
}

void InputMark(int& var) {
	cin >> var;
	while (var < 0 || var > 10 || !cin || (getchar() != '\n')) {
		cout << "\nНекорректный ввод данных! Необходимо ввести целое число от 0 до 10! Повторите ввод:" << endl;		//Проверяем на ввод целого числа
		cin.clear();
		rewind(stdin);
		cin >> var;
	}
}

void InputGPA(float& var) {
	cin >> var;
	while (var < 0 || var > 10 || !cin || (getchar() != '\n')) {
		cout << "\nНекорректный ввод данных! Необходимо ввести дробное число от 0 до 10! Повторите ввод:" << endl;		//Проверяем на ввод дробного числа
		cin.clear();
		rewind(stdin);
		cin >> var;																					//Повторяем ввод если считано не дробное значение
	}
}

void InputStudID(int& var) {
	cin >> var;
	while (!cin || var < 10000000 || var > 99999999 || (getchar() != '\n')) {
		cout << "Некорректный ввод данных! Номер студенческого билета должен состоять из 8 цифр! Повторите ввод:";		//Проверяем на ввод целого числа
		cin.clear();
		rewind(stdin);
		cin >> var;																			//Повторяем ввод если считано не целочисленное значение
	}
}

void InputGroup(int& var) {
	cin >> var;
	while (!cin || var < 100000 || var > 999999 || (getchar() != '\n')) {
		cout << "Некорректный ввод данных! Номер группы должен состоять из 6 цифр! Повторите ввод:";		//Проверяем на ввод целого числа
		cin.clear();
		rewind(stdin);
		cin >> var;																					//Повторяем ввод если считано не целочисленное значение
	}
}

void FillAdminVect(vector<Admin>& Admins) {
	Admin Administrator;
	ifstream fileAdmin;
	fileAdmin.open("AdminData.txt");
	if (!fileAdmin.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!fileAdmin.eof()) {
		fileAdmin >> Administrator.login >> Administrator.password >> Administrator.isBanned;
		Admins.push_back(Administrator);
	}
	fileAdmin.close();
}

void FillUserVect(vector<User>& Users) {
	User student;
	ifstream file;
	file.open("UsersData.txt");
	if (!file.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	while (!file.eof()) {
		getline(file, student.FullName);
		if (student.FullName == "") {
			getline(file, student.FullName);
			getline(file, student.FullName);
		}
		file >> student.password >> student.isBanned >> student.UserInfo.StudID >> student.UserInfo.Group >> student.UserInfo.GPA;
		Users.push_back(student);
	}
	file.close();
}

void MainMenu() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<Admin> Admins;
	FillAdminVect(Admins);
	vector<User> Users;
	FillUserVect(Users);
	vector<MathStud> MathStudents;
	FillMathStudVect(MathStudents);
	vector<PhysStud> PhysStudents;
	FillPhysStudVect(PhysStudents);
	vector<ProgStud> ProgStudents;
	FillProgStudVect(ProgStudents);
	vector<EngStud> EngStudents;
	FillEngStudVect(EngStudents);
	vector<DataBaseStud> DataBaseStudents;
	FillDataBaseStudVect(DataBaseStudents);
	ConsoleCursorVisible(false, 100);
	string menu[] = { "Войти как администратор", "Войти как пользователь", "Завершить работу приложения" };
	int active_menu = 0;
	char ch;
	int ThisUser = 0;
	while (1) {
		bool isLoggedIn = false;
		int x = 45, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) LightCyan();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
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
			switch (active_menu)
			{
			case 0:
				AdminAuthorization(Admins, isLoggedIn);
				if (isLoggedIn) {
					AdminMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents, Users);
				}
				break;
			case 1:
				UserAuthorization(Users, isLoggedIn, ThisUser);
				if (isLoggedIn) {
					UserMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents, Users, ThisUser);
				}
				break;
			case 2:
				WriteToUsersFile(Users);
				WriteToMathFile(MathStudents);
				WriteToPhysFile(PhysStudents);
				WriteToProgFile(ProgStudents);
				WriteToEngFile(EngStudents);
				WriteToDataBaseFile(DataBaseStudents);
				exit(0);
				break;
			default:
				break;
			}
		}
	}
}

void AdminAuthorization(vector<Admin> Admins, bool& isLoggedIn) {
	system("cls");
	ConsoleCursorVisible(true, 1);
	White();
	Admin Administrator;
	isLoggedIn = false;
	int tries = 3;
	while (tries != 0) {
		int x = 45, y = 12;
		GoToXY(x, y++);
		cout << "Введите логин: ";
		getline(cin, Administrator.login);
		GoToXY(x, y++);
		cout << "Введите пароль: ";
		Administrator.password = EnterPassword();
		for (int i = 0; i < Admins.size(); i++) {
			if (Administrator.login == Admins[i].login) {
				if (Administrator.password == Admins[i].password) {
					if (!Admins[i].isBanned) {
						GoToXY(x, ++y);
						cout << "Вы успешно авторизировались!";
						DeleteConsole(40, y += 2);
						isLoggedIn = true;
					}
					else {
						GoToXY(x, ++y);
						cout << "Ваша учётная запись заблокирована. Вход невозможен";
						DeleteConsole(35, y += 2);
					}
					break;
				}
			}
		}
		if (isLoggedIn) {
			break;
		}
		tries--;
		if (tries == 0) {
			system("cls");
			GoToXY(40, y += 2);
			cout << "У вас не осталось попыток";
			DeleteConsole(35, y += 2);
		}
		else {
			system("cls");
			GoToXY(25, 6);
			cout << "Логин или пароль введен неверно. Оставшееся количество попыток: " << tries << endl << endl;
		}
	}
}

void UserAuthorization(vector<User> Users, bool& isLoggedIn, int& ThisUser) {
	system("cls");
	ConsoleCursorVisible(true, 1);
	White();
	if (Users.size() != 0) {
		User student;
		isLoggedIn = false;
		int tries = 3;
		while (tries != 0) {
			int x = 45, y = 12;
			GoToXY(x, y++);
			cout << "Введите ФИО: ";
			getline(cin, student.FullName);
			GoToXY(x, y++);
			cout << "Введите пароль: ";
			student.password = EnterPassword();
			for (int i = 0; i < Users.size(); i++) {
				if (student.FullName == Users[i].FullName) {
					if (student.password == Users[i].password) {
						if (!Users[i].isBanned) {
							GoToXY(x, ++y);
							cout << "Вы успешно авторизировались!";
							ThisUser = i;
							DeleteConsole(40, y += 2);
							isLoggedIn = true;
						}
						else {
							GoToXY(x, ++y);
							cout << "Ваша учётная запись заблокирована. Вход невозможен";
							DeleteConsole(40, y += 2);
						}
						break;
					}
				}
			}
			if (isLoggedIn) {
				break;
			}
			tries--;
			if (tries == 0) {
				system("cls");
				GoToXY(45, y += 2);
				cout << "У вас не осталось попыток";
				DeleteConsole(45, y += 2);
			}
			else {
				system("cls");
				GoToXY(25, 6);
				cout << "Логин или пароль введен неверно. Оставшееся количество попыток: " << tries << endl << endl;
			}
		}
	}
	else {
		GoToXY(15, 12);
		cout << "В программе не существует ни одного пользователя! Функция будет доступна после добавления хотя бы одного пользователя!";
	}
}

string EnterPassword() {
	string password = "";
	char ch;
	bool ctrlPressed = false;
	while (true) {
		ch = _getch();
		if (ch == 13) { // 13 - код клавиши Enter
			break;
		}
		if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
			if (password.length() > 0) {
				password.erase(password.length() - 1);
				cout << "\b \b"; // удаляем последнюю звездочку
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
			if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
					continue; // игнорируем клавиши сочетания
				}
			}
			password += ch;
			cout << '*';
		}
		else if (ch == -32) { // игнорируем коды направлений стрелок
			ch = _getch(); // считываем второй байт кода клавиши
			if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
				continue; // игнорируем стрелки
			}
		}
		else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	return password;
}

void AdminMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User>& Users) {
	string menu[] = { "Добавить пользователя", "Заблокировать пользователя", "Разблокировать пользователя", "Удалить пользователя", "Посмотреть список пользователей",
		"Посмотреть список записавшихся студентов", "Выйти из системы" };
	ConsoleCursorVisible(false, 100);
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
				AddUser(Users);
				break;
			case 1:
				BlockUser(Users);
				break;
			case 2:
				UnblockUser(Users);
				break;
			case 3:
				DeleteUser(Users, MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents);
				break;
			case 4:
				LookListOfUsersMenu(Users);
				break;
			case 5:
				LookListOfStudentsMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents);
				break;
			case 6:
				White();
				system("cls");
				GoToXY(40, 12);
				isBack = true;
				cout << "Вы вышли из своей учётной записи.";
				DeleteConsole(38, 14);
				break;
			}
			break;
		}
	} while (!isBack);
}

void AddUser(vector<User>& Users) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				bool isUserExists = false;
				User student;
				int x = 10, y = 2;
				InputFullName(student);
				for (int i = 0; i < Users.size(); i++) {
					if (student.FullName == Users[i].FullName) {
						isUserExists = true;
						break;
					}
				}
				if (isUserExists) {
					GoToXY(x + 20, y += 2);
					cout << "Пользователь с таким именем уже существует!";
					DeleteConsole(x + 20, y += 2);
					return;
				}
				while (1) {
					GoToXY(x, y += 2);
					cout << "Придумайте пароль: ";
					student.password = EnterPassword();
					if (student.password.size() > 15) {
						cout << endl << "Пароль должен содержать не более 15 символов!";
					}
					else if (student.password.size() == 0) {
						cout << endl << "Пароль не может содержать 0 символов!";
						continue;
					}
					else {
						break;
					}
				}
				GoToXY(x, y += 2);
				while (1) {
					cout << "Введите номер студенческого билета: ";
					bool isStudIDExists = false;
					InputStudID(student.UserInfo.StudID);
					for (int i = 0; i < Users.size(); i++) {
						if (student.UserInfo.StudID == Users[i].UserInfo.StudID) {
							isStudIDExists = true;
							GoToXY(x, y += 2);
							cout << endl << "Введённый номер студенческого билета уже существует. Повторите попытку ещё раз!" << endl << endl;
							break;
						}
					}
					if (!isStudIDExists) {
						break;
					}
				}
				cout << endl << setw(32) << "Введите номер группы: ";
				InputGroup(student.UserInfo.Group);
				cout << endl << setw(32) << "Введите средний балл: ";
				InputGPA(student.UserInfo.GPA);
				student.isBanned = false;
				Users.push_back(student);
				cout << endl << setw(79) << "Пользователь успешно добавлен";
				DeleteConsole(x + 36, 28);
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

void InputFullName(User& student) {
	White();
	ConsoleCursorVisible(true, 1);
	bool isLetter = false;
	string tempStr = "";
	while (!isLetter) {
		isLetter = true;
		system("cls");
		char tempCh;
		GoToXY(10, 2);
		cout << "Введите ФИО пользователя, которого хотите добавить: ";
		while (1) {
			tempCh = _getch();
			if (((int)tempCh > -65) && ((int)tempCh < 0) || ((int)tempCh == -88) || ((int)tempCh == -72) || ((int)tempCh == 32)) {
				tempStr += tempCh;
				cout << tempCh;
			}
			else if ((int)tempCh == 13) {
				if (tempStr.empty()) continue;
				break;
				cout << endl;
			}
			else if ((int)tempCh == 8) {
				if (!tempStr.empty()) {
					cout << "\b \b";
					tempStr.pop_back();
				}
			}
		}
	}
	student.FullName = tempStr;
}

void BlockUser(vector<User>& Users) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				bool isUserExists = false;
				User student;
				GoToXY(x, y);
				cout << "Введите ФИО пользователя, которого хотите заблокировать: ";
				getline(cin, student.FullName);
				for (int i = 0; i < Users.size(); i++) {
					if (student.FullName == Users[i].FullName) {
						isUserExists = true;
						if (Users[i].isBanned) {
							GoToXY(x, y += 3);
							cout << "Ошибка! Пользователь " << Users[i].FullName << " уже заблокирован";
							break;
						}
						else {
							Users[i].isBanned = true;
							GoToXY(x, y += 3);
							cout << "Пользователь " << Users[i].FullName << " успешно заблокирован";
							break;
						}
					}
				}
				if (!isUserExists) {
					GoToXY(x, y += 3);
					cout << "Пользователя с таким ФИО не существует!";
				}
				isBack = true;
				DeleteConsole(45, y += 3);
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

void UnblockUser(vector<User>& Users) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				User student;
				bool isUserExists = false;
				GoToXY(x, y);
				cout << "Введите ФИО пользователя, которого хотите разблокировать: ";
				getline(cin, student.FullName);
				for (int i = 0; i < Users.size(); i++) {
					if (Users[i].FullName == student.FullName) {
						isUserExists = true;
						if (Users[i].isBanned) {
							Users[i].isBanned = false;
							GoToXY(x, y += 3);
							cout << "Пользователь " << Users[i].FullName << " успешно разблокирован";
							break;
						}
						else {
							GoToXY(x, y += 3);
							cout << "Ошибка! Пользователь " << Users[i].FullName << " не был заблокирован";
							break;
						}
					}
				}
				if (!isUserExists) {
					GoToXY(x, y += 3);
					cout << "Пользователя с таким ФИО не существует!";
				}
				isBack = true;
				DeleteConsole(45, y += 3);
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

void DeleteUser(vector<User>& Users, vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents) {
	system("cls");
	string menu[] = { "Подтвердить действие", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				User student;
				bool isUserExists = false;
				GoToXY(x, y);
				cout << "Введите ФИО пользователя, которого хотите удалить: ";
				getline(cin, student.FullName);
				for (int i = 0; i < Users.size(); i++) {
					if (Users[i].FullName == student.FullName) {
						isUserExists = true;
						vector<User>::iterator it = Users.begin();
						for (int j = 0; j < MathStudents.size(); j++) {
							if (Users[i].FullName == MathStudents[j].FullName) {
								vector<MathStud>::iterator it = MathStudents.begin();
								MathStudents.erase(it + j);
								break;
							}
						}
						for (int j = 0; j < PhysStudents.size(); j++) {
							if (Users[i].FullName == PhysStudents[j].FullName) {
								vector<PhysStud>::iterator it = PhysStudents.begin();
								PhysStudents.erase(it + j);
								break;
							}
						}
						for (int j = 0; j < ProgStudents.size(); j++) {
							if (Users[i].FullName == ProgStudents[j].FullName) {
								vector<ProgStud>::iterator it = ProgStudents.begin();
								ProgStudents.erase(it + j);
								break;
							}
						}
						for (int j = 0; j < EngStudents.size(); j++) {
							if (Users[i].FullName == EngStudents[j].FullName) {
								vector<EngStud>::iterator it = EngStudents.begin();
								EngStudents.erase(it + j);
								break;
							}
						}
						for (int j = 0; j < DataBaseStudents.size(); j++) {
							if (Users[i].FullName == DataBaseStudents[j].FullName) {
								vector<DataBaseStud>::iterator it = DataBaseStudents.begin();
								DataBaseStudents.erase(it + j);
								break;
							}
						}
						Users.erase(it + i);
						GoToXY(x, y += 3);
						cout << "Пользователь " << student.FullName << " успешно удалён";
					}
				}
				if (!isUserExists) {
					GoToXY(x, y += 3);
					cout << "Пользователя с таким ФИО не существует!";
				}
				isBack = true;
				DeleteConsole(45, y += 3);
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

void LookListOfUsersMenu(vector<User>& Users) {
	system("cls");
	string menu[] = { "Отсортировать пользователей по параметру", "Отфильтровать пользователей по среднему баллу", "Поиск пользователей по параметру", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
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
		PrintTableUsers(Users);
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
				system("cls");
				BubbleSortUserMenu(Users);
				break;
			case 1:
				system("cls");
				FilteringByGPAUser(Users);
				DeleteConsole(45, 24);
				break;
			case 2:
				system("cls");
				SearchUsersMenu(Users);
				break;
			case 3:
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

void LookListOfStudentsMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents) {
	system("cls");
	string menu[] = { "Математика", "Физика", "Программирование", "Английский язык", "Базы данных", "Вернуться назад" };
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
				LookListOfMathStudentsMenu(MathStudents);
				break;
			case 1:
				LookListOfPhysStudentsMenu(PhysStudents);
				break;
			case 2:
				LookListOfProgStudentsMenu(ProgStudents);
				break;
			case 3:
				LookListOfEngStudentsMenu(EngStudents);
				break;
			case 4:
				LookListOfDataBaseStudentsMenu(DataBaseStudents);
				break;
			case 5:
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

void UserMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser) {
	string menu[] = { "Вывести список студентов дисциплины", "Поступить на факультативную дисциплину", "Отозвать заявку на поступление на дисциплину",
		"Перейти в личный кабинет", "Выйти из системы" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				LookListOfStudentsMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents);
				break;
			case 1:
				ApplyForAdmissionMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents, Users, ThisUser);
				break;
			case 2:
				WithdrawApplicationMenu(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents, Users, ThisUser);
				break;
			case 3:
				GoToPersonalAccount(MathStudents, PhysStudents, ProgStudents, EngStudents, DataBaseStudents, Users, ThisUser);
				break;
			case 4:
				White();
				system("cls");
				GoToXY(40, 12);
				isBack = true;
				cout << "Вы вышли из своей учётной записи.";
				WriteToMathFile(MathStudents);
				WriteToPhysFile(PhysStudents);
				WriteToProgFile(ProgStudents);
				WriteToEngFile(EngStudents);
				WriteToDataBaseFile(DataBaseStudents);
				DeleteConsole(38, 14);
				break;
			}
			break;
		}
	} while (!isBack);
}

void ApplyForAdmissionMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Математика", "Физика", "Программирование", "Английский язык", "Базы данных", "Вернуться назад" };
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
				AddMathStudent(MathStudents, Users, ThisUser);
				break;
			case 1:
				AddPhysStudent(PhysStudents, Users, ThisUser);
				break;
			case 2:
				AddProgStudent(ProgStudents, Users, ThisUser);
				break;
			case 3:
				AddEngStudent(EngStudents, Users, ThisUser);
				break;
			case 4:
				AddDataBaseStudent(DataBaseStudents, Users, ThisUser);
				break;
			case 5:
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

void WithdrawApplicationMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser) {
	system("cls");
	string menu[] = { "Математика", "Физика", "Программирование", "Английский язык", "Базы данных", "Вернуться назад" };
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
				DeleteMathStudent(MathStudents, Users, ThisUser);
				break;
			case 1:
				DeletePhysStudent(PhysStudents, Users, ThisUser);
				break;
			case 2:
				DeleteProgStudent(ProgStudents, Users, ThisUser);
				break;
			case 3:
				DeleteEngStudent(EngStudents, Users, ThisUser);
				break;
			case 4:
				DeleteDataBaseStudent(DataBaseStudents, Users, ThisUser);
				break;
			case 5:
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

void GoToPersonalAccount(vector<MathStud> MathStudents, vector<PhysStud> PhysStudents, vector<ProgStud> ProgStudents, vector<EngStud> EngStudents,
	vector<DataBaseStud> DataBaseStudents, vector<User> Users, int ThisUser) {
	system("cls");
	vector<unsigned long long> SizeOfElective = { MathStudents.size(), PhysStudents.size(), ProgStudents.size(), EngStudents.size(), DataBaseStudents.size() };
	for (int i = 0; i < 5; i++) {
		for (int j = 4; j > i; j--) {
			if (SizeOfElective[j - 1] < SizeOfElective[j]) {
				swap(SizeOfElective[j - 1], SizeOfElective[j]);
			}
		}
	}
	vector<bool> isRecorded = { false, false, false, false, false };
	User student;
	student = Users[ThisUser];
	ConsoleCursorVisible(false, 100);
	White();
	int x = 40, y = 2;
	GoToXY(x, y);
	cout << "ЛИЧНЫЙ КАБИНЕТ ПОЛЬЗОВАТЕЛЯ " << student.FullName;
	GoToXY(x, y += 2);
	cout << "Номер студенческого билета: " << student.UserInfo.StudID;
	GoToXY(x, ++y);
	cout << "Группа: " << student.UserInfo.Group;
	GoToXY(x, ++y);
	cout << "Средний балл: " << student.UserInfo.GPA;
	GoToXY(20, y += 3);
	cout << "СПИСОК ДОСТУПНЫХ ФАКУЛЬТАТИВНЫХ ДИСЦИПЛИН – в скобках указано количество студентов подавших заявки. (*) – выделены дисциплины на которые вы подали заявку";
	for (int i = 0; i < 5; i++) {
		if ((SizeOfElective[i] == MathStudents.size()) && (isRecorded[0] == false)) {
			GoToXY(50, 12 + 2 * i);
			cout << "Математика (" << MathStudents.size() << ")";
			for (int j = 0; j < MathStudents.size(); j++) {
				if (student.FullName == MathStudents[j].FullName) {
					GoToXY(60, 12 + 2 * i);
					cout << "*";
					break;
				}
			}
			isRecorded[0] = true;
			continue;
		}
		if ((SizeOfElective[i] == PhysStudents.size()) && (isRecorded[1] == false)) {
			GoToXY(50, 12 + 2 * i);
			cout << "Физика (" << PhysStudents.size() << ")";
			for (int j = 0; j < PhysStudents.size(); j++) {
				if (student.FullName == PhysStudents[j].FullName) {
					GoToXY(56, 12 + 2 * i);
					cout << "*";
					break;
				}
			}
			isRecorded[1] = true;
			continue;
		}
		if ((SizeOfElective[i] == ProgStudents.size()) && (isRecorded[2] == false)) {
			GoToXY(50, 12 + 2 * i);
			cout << "Программирование (" << ProgStudents.size() << ")";
			for (int j = 0; j < ProgStudents.size(); j++) {
				if (student.FullName == ProgStudents[j].FullName) {
					GoToXY(66, 12 + 2 * i);
					cout << "*";
					break;
				}
			}
			isRecorded[2] = true;
			continue;
		}
		if ((SizeOfElective[i] == EngStudents.size()) && (isRecorded[3] == false)) {
			GoToXY(50, 12 + 2 * i);
			cout << "Английский язык (" << EngStudents.size() << ")";
			for (int j = 0; j < EngStudents.size(); j++) {
				if (student.FullName == EngStudents[j].FullName) {
					GoToXY(65, 12 + 2 * i);
					cout << "*";
					break;
				}
			}
			isRecorded[3] = true;
			continue;
		}
		if ((SizeOfElective[i] == DataBaseStudents.size()) && (isRecorded[4] == false)) {
			GoToXY(50, 12 + 2 * i);
			cout << "Базы данных (" << DataBaseStudents.size() << ")";
			for (int j = 0; j < DataBaseStudents.size(); j++) {
				if (student.FullName == DataBaseStudents[j].FullName) {
					GoToXY(61, 12 + 2 * i);
					cout << "*";
					break;
				}
			}
			isRecorded[4] = true;
		}
	}
	DeleteConsole(40, 22);
}

void BubbleSortUserMenu(vector<User>& Users) {
	string menu[] = { "Отсортировать пользователей по алфавиту", "Отсортировать пользователей по среднему баллу", "Отсортировать пользователей по статусу блокировки", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				BubbleSortUserInfo(Users, active_menu + 1);
				break;
			case 1:
				BubbleSortUserInfo(Users, active_menu + 1);
				break;
			case 2:
				BubbleSortUserInfo(Users, active_menu + 1);
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

void BubbleSortUserInfo(vector<User>& Users, int option) {
	int i, j;
	for (i = 0; i < Users.size(); i++) {
		for (j = Users.size() - 1; j > i; j--) {
			if (option == 1) {
				if (Users[j - 1].FullName > Users[j].FullName) {
					swap(Users[j - 1], Users[j]);
				}
			}
			else if (option == 2) {
				if (Users[j - 1].UserInfo.GPA < Users[j].UserInfo.GPA) {
					swap(Users[j - 1], Users[j]);
				}
			}
			else {
				if (Users[j - 1].isBanned < Users[j].isBanned) {
					swap(Users[j - 1], Users[j]);
				}
			}
		}
	}
}

void FilteringByGPAUser(vector<User> Users) {
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
	for (index = 0; index < Users.size(); index++) {
		if (Users[index].UserInfo.GPA >= GPA_min && Users[index].UserInfo.GPA <= GPA_max) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << endl << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
			<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
			<< "|" << endl;
		for (int i = 0; i < Users.size(); i++) {
			if (Users[i].UserInfo.GPA >= GPA_min && Users[i].UserInfo.GPA <= GPA_max) {
				cout << setw(4) << "|" << "---------------------------------------------|-----------------|-------------|-----------|--------|------------|" << endl;
				cout << setw(4) << "|" << setw(43) << Users[i].FullName << setw(3) << "|" << setw(16) << Users[i].password << setw(2) << "|" << setw(7)
					<< Users[i].isBanned << setw(7) << "|" << setw(10) << Users[i].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[i].UserInfo.Group
					<< setw(2) << "|" << setw(8) << Users[i].UserInfo.GPA << setw(5) << "|" << endl;
			}
		}
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов в данном промежутке балла в списке нет!" << endl << endl;
	}
}

void SearchUsersMenu(vector<User> Users) {
	string menu[] = { "Поиск пользователей по ФИО", "Поиск пользователей по номеру группы", "Поиск пользователей по среднему баллу",
		"Поиск пользователей по студенческому билету", "Вернуться назад" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	bool isBack = false;
	char ch;
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
				UserSearchByName(Users);
				DeleteConsole(x, y += 2);
				break;
			case 1:
				UserSearchByGroup(Users);
				DeleteConsole(x, y += 2);
				break;
			case 2:
				UserSearchByGPA(Users);
				DeleteConsole(x, y += 2);
				break;
			case 3:
				UserSearchByStudID(Users);
				DeleteConsole(x, y += 2);
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

void UserSearchByName(vector<User> Users) {
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
		for (int index = 0; index < Users.size(); index++) {
			string UserName = Users[index].FullName;
			for (char& c : UserName) {
				c = tolower(c);
			}
			if (UserName.find(LowerFullName) == 0) {
				if (!isFind) {
					cout << endl << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
					cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
						<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
						<< "|" << endl;
					cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
					isFind = true;
				}
				cout << setw(4) << "|" << setw(43) << Users[index].FullName << setw(3) << "|" << setw(16) << Users[index].password << setw(2) << "|" << setw(7)
					<< Users[index].isBanned << setw(7) << "|" << setw(10) << Users[index].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[index].UserInfo.Group
					<< setw(2) << "|" << setw(8) << Users[index].UserInfo.GPA << setw(5) << "|" << endl;
				cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		if (!isFind) {
			GoToXY(25, 12);
			cout << "Пользователь с таким именем не найден." << endl;
		}
	}
	if (LowerFullName.empty() && (int)tempCh != 13) {
		PrintTableUsers(Users);
	}
	if (!isFind && !LowerFullName.empty()) {
		GoToXY(25, 12);
		cout << "Пользователь с таким именем не найден." << endl;
	}
	setlocale(LC_ALL, "");
}

void UserSearchByGroup(vector<User> Users) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	int GroupNumber;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер группы: ";
	InputGroup(GroupNumber);
	for (index = 0; index < Users.size(); index++) {
		if (GroupNumber == Users[index].UserInfo.Group) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
			<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
			<< "|" << endl;
		for (int i = 0; i < Users.size(); i++) {
			if (GroupNumber == Users[i].UserInfo.Group) {
				cout << setw(4) << "|" << "---------------------------------------------|-----------------|-------------|-----------|--------|------------|" << endl;
				cout << setw(4) << "|" << setw(43) << Users[i].FullName << setw(3) << "|" << setw(16) << Users[i].password << setw(2) << "|" << setw(7)
					<< Users[i].isBanned << setw(7) << "|" << setw(10) << Users[i].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[i].UserInfo.Group
					<< setw(2) << "|" << setw(8) << Users[i].UserInfo.GPA << setw(5) << "|" << endl;
			}
		}
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов такой группы в списке нет!" << endl << endl;
	}
}

void UserSearchByGPA(vector<User> Users) {
	ConsoleCursorVisible(true, 1);
	White();
	system("cls");
	float GPA;
	bool isFind = false;
	int index = 0;
	cout << "Введите средний балл: ";
	InputGPA(GPA);
	for (index = 0; index < Users.size(); index++) {
		if (GPA == Users[index].UserInfo.GPA) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
			<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
			<< "|" << endl;
		for (int i = 0; i < Users.size(); i++) {
			if (GPA == Users[i].UserInfo.GPA) {
				cout << setw(4) << "|" << "---------------------------------------------|-----------------|-------------|-----------|--------|------------|" << endl;
				cout << setw(4) << "|" << setw(43) << Users[i].FullName << setw(3) << "|" << setw(16) << Users[i].password << setw(2) << "|" << setw(7)
					<< Users[i].isBanned << setw(7) << "|" << setw(10) << Users[i].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[i].UserInfo.Group
					<< setw(2) << "|" << setw(8) << Users[i].UserInfo.GPA << setw(5) << "|" << endl;
			}
		}
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким средним баллом в списке нет!" << endl << endl;
	}
}

void UserSearchByStudID(vector<User> Users) {
	White();
	system("cls");
	int StudID;
	bool isFind = false;
	int index = 0;
	cout << "Введите номер студенческого билета: ";
	InputStudID(StudID);
	for (index = 0; index < Users.size(); index++) {
		if (StudID == Users[index].UserInfo.StudID) {
			isFind = true;
			break;
		}
	}
	if (isFind) {
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
			<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
			<< "|" << endl;
		cout << setw(4) << "|" << "---------------------------------------------|-----------------|-------------|-----------|--------|------------|" << endl;
		cout << setw(4) << "|" << setw(43) << Users[index].FullName << setw(3) << "|" << setw(16) << Users[index].password << setw(2) << "|" << setw(7)
			<< Users[index].isBanned << setw(7) << "|" << setw(10) << Users[index].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[index].UserInfo.Group
			<< setw(2) << "|" << setw(8) << Users[index].UserInfo.GPA << setw(5) << "|" << endl;
		cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "\nСтудентов с таким номером студенческого билета в списке нет!" << endl << endl;
	}
}

void PrintTableUsers(vector<User> Users) {
	White();
	cout << endl << setw(75) << "Таблица с данными о пользователях\n" << endl;
	cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(4) << "|" << setw(24) << "ФИО" << setw(22) << "|" << setw(12) << "Пароль" << setw(6) << "|" << setw(13) << "Заблокирован?"
		<< "|" << setw(11) << "Студ. билет" << "|" << setw(7) << "Группа" << setw(2) << "|" << setw(12) << "Средний балл"
		<< "|" << endl;
	for (int i = 0; i < Users.size(); i++) {
		cout << setw(4) << "|" << "---------------------------------------------|-----------------|-------------|-----------|--------|------------|" << endl;
		cout << setw(4) << "|" << setw(43) << Users[i].FullName << setw(3) << "|" << setw(16) << Users[i].password << setw(2) << "|" << setw(7)
			<< Users[i].isBanned << setw(7) << "|" << setw(10) << Users[i].UserInfo.StudID << setw(2) << "|" << setw(7) << Users[i].UserInfo.Group
			<< setw(2) << "|" << setw(8) << Users[i].UserInfo.GPA << setw(5) << "|" << endl;
	}
	cout << setw(4) << "-" << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void WriteToUsersFile(vector<User> Users) {
	ofstream File;
	File.open("UsersData.txt");
	if (!File.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		exit(0);
	}
	else {
		for (int i = 0; i < Users.size(); i++) {
			File << Users[i].FullName << endl << Users[i].password << endl << Users[i].isBanned << endl << Users[i].UserInfo.StudID
				<< endl << Users[i].UserInfo.Group << endl << Users[i].UserInfo.GPA;
			if (i != Users.size() - 1) {
				File << endl << endl;
			}
		}
	}
	File.close();
}
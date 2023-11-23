#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <locale>

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80

using namespace std;

struct Info {
	int StudID;
	int Group;
	float GPA;
};

struct User {
	string FullName;
	string password;
	bool isBanned;
	Info UserInfo;
};

struct Admin {
	string login;
	string password;
	bool isBanned = false;
};

struct MathStud {
	string FullName;
	Info MathStudInfo;
	int MathMark;
};

struct PhysStud {
	string FullName;
	Info PhysStudInfo;
	int PhysMark;
};

struct ProgStud {
	string FullName;
	Info ProgStudInfo;
	int ProgMark;
};

struct EngStud {
	string FullName;
	Info EngStudInfo;
	int EngMark;
};

struct DataBaseStud {
	string FullName;
	Info DataBaseStudInfo;
	int DataBaseMark;
};

void GoToXY(short x, short y);

void ConsoleCursorVisible(bool show, short size);

void Cyan();

void LightCyan();

void White();

void DeleteConsole(int x, int y);

void InputMark(int& var);

void InputGPA(float& var);

void InputStudID(int& var);

void InputGroup(int& var);

void FillAdminVect(vector<Admin>& Admins);

void FillUserVect(vector<User>& Users);

void FillMathStudVect(vector<MathStud>& MathStudents);

void FillPhysStudVect(vector<PhysStud>& PhysStudents);

void FillProgStudVect(vector<ProgStud>& ProgStudents);

void FillEngStudVect(vector<EngStud>& EngStudents);

void FillDataBaseStudVect(vector<DataBaseStud>& DataBaseStudents);

void MainMenu();

void AdminAuthorization(vector<Admin> Admins, bool& isLoggedIn);

void UserAuthorization(vector<User> Users, bool& isLoggedIn, int& ThisUser);

string EnterPassword();

void AdminMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User>& Users);

void AddUser(vector<User>& Users);

void AddMathStudent(vector<MathStud>& MathStudents, vector<User> Users, int ThisUser);

void AddPhysStudent(vector<PhysStud>& PhysStudents, vector<User> Users, int ThisUser);

void AddProgStudent(vector<ProgStud>& ProgStudents, vector<User> Users, int ThisUser);

void AddEngStudent(vector<EngStud>& EngStudents, vector<User> Users, int ThisUser);

void AddDataBaseStudent(vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser);

void InputFullName(User& student);

void BlockUser(vector<User>& Users);

void UnblockUser(vector<User>& Users);

void DeleteUser(vector<User>& Users, vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents);

void DeleteMathStudent(vector<MathStud>& MathStudents, vector<User> Users, int ThisUser);

void DeletePhysStudent(vector<PhysStud>& PhysStudents, vector<User> Users, int ThisUser);

void DeleteProgStudent(vector<ProgStud>& ProgStudents, vector<User> Users, int ThisUser);

void DeleteEngStudent(vector<EngStud>& EngStudents, vector<User> Users, int ThisUser);

void DeleteDataBaseStudent(vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser);

void LookListOfStudentsMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents);

void LookListOfUsersMenu(vector<User>& Users);

void UserMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser);

void ApplyForAdmissionMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser);

void WithdrawApplicationMenu(vector<MathStud>& MathStudents, vector<PhysStud>& PhysStudents, vector<ProgStud>& ProgStudents, vector<EngStud>& EngStudents,
	vector<DataBaseStud>& DataBaseStudents, vector<User> Users, int ThisUser);

void GoToPersonalAccount(vector<MathStud> MathStudents, vector<PhysStud> PhysStudents, vector<ProgStud> ProgStudents, vector<EngStud> EngStudents,
	vector<DataBaseStud> DataBaseStudents, vector<User> Users, int ThisUser);

void LookListOfMathStudentsMenu(vector<MathStud>& MathStudents);

void LookListOfPhysStudentsMenu(vector<PhysStud>& PhysStudents);

void LookListOfProgStudentsMenu(vector<ProgStud>& ProgStudents);

void LookListOfEngStudentsMenu(vector<EngStud>& EngStudents);

void LookListOfDataBaseStudentsMenu(vector<DataBaseStud>& DataBaseStudents);

void BubbleSortUserMenu(vector<User>& Users);

void BubbleSortMathStudentsMenu(vector<MathStud>& MathStudents);

void BubbleSortPhysStudentsMenu(vector<PhysStud>& PhysStudents);

void BubbleSortProgStudentsMenu(vector<ProgStud>& ProgStudents);

void BubbleSortEngStudentsMenu(vector<EngStud>& EngStudents);

void BubbleSortDataBaseStudentsMenu(vector<DataBaseStud>& DataBaseStudents);

void BubbleSortUserInfo(vector<User>& Users, int option);

void BubbleSortMath(vector<MathStud>& MathStudents, int option);

void BubbleSortPhys(vector<PhysStud>& PhysStudents, int option);

void BubbleSortProg(vector<ProgStud>& ProgStudents, int option);

void BubbleSortEng(vector<EngStud>& EngStudents, int option);

void BubbleSortDataBase(vector<DataBaseStud>& DataBaseStudents, int option);

void FilteringMathStudentsMenu(vector<MathStud> MathStudents);

void FilteringPhysStudentsMenu(vector<PhysStud> PhysStudents);

void FilteringProgStudentsMenu(vector<ProgStud> ProgStudents);

void FilteringEngStudentsMenu(vector<EngStud> EngStudents);

void FilteringDataBaseStudentsMenu(vector<DataBaseStud> DataBaseStudents);

void FilteringByGPAUser(vector<User> Users);

void FilteringByGPAMath(vector<MathStud> MathStudents);

void FilteringByMathMark(vector<MathStud> MathStudents);

void FilteringByGPAPhys(vector<PhysStud> PhysStudents);

void FilteringByPhysMark(vector<PhysStud> PhysStudents);

void FilteringByGPAProg(vector<ProgStud> ProgStudents);

void FilteringByProgMark(vector<ProgStud> ProgStudents);

void FilteringByGPAEng(vector<EngStud> EngStudents);

void FilteringByEngMark(vector<EngStud> EngStudents);

void FilteringByGPADataBase(vector<DataBaseStud> DataBaseStudents);

void FilteringByDataBaseMark(vector<DataBaseStud> DataBaseStudents);

void SearchUsersMenu(vector<User> Users);

void SearchMathStudentsMenu(vector<MathStud> MathStudents);

void SearchPhysStudentsMenu(vector<PhysStud> PhysStudents);

void SearchProgStudentsMenu(vector<ProgStud> ProgStudents);

void SearchEngStudentsMenu(vector<EngStud> EngStudents);

void SearchDataBaseStudentsMenu(vector<DataBaseStud> DataBaseStudents);

void UserSearchByName(vector<User> Users);

void UserSearchByGroup(vector<User> Users);

void UserSearchByGPA(vector<User> Users);

void UserSearchByStudID(vector<User> Users);

void MathSearchByName(vector<MathStud> MathStudents);

void MathSearchByGroup(vector<MathStud> MathStudents);

void MathSearchByGPA(vector<MathStud> MathStudents);

void MathSearchByMark(vector<MathStud> MathStudents);

void PhysSearchByName(vector<PhysStud> PhysStudents);

void PhysSearchByGroup(vector<PhysStud> PhysStudents);

void PhysSearchByGPA(vector<PhysStud> PhysStudents);

void PhysSearchByMark(vector<PhysStud> PhysStudents);

void ProgSearchByName(vector<ProgStud> ProgStudents);

void ProgSearchByGroup(vector<ProgStud> ProgStudents);

void ProgSearchByGPA(vector<ProgStud> ProgStudents);

void ProgSearchByMark(vector<ProgStud> ProgStudents);

void EngSearchByName(vector<EngStud> EngStudents);

void EngSearchByGroup(vector<EngStud> EngStudents);

void EngSearchByGPA(vector<EngStud> EngStudents);

void EngSearchByMark(vector<EngStud> EngStudents);

void DataBaseSearchByName(vector<DataBaseStud> DataBaseStudents);

void DataBaseSearchByGroup(vector<DataBaseStud> DataBaseStudents);

void DataBaseSearchByGPA(vector<DataBaseStud> DataBaseStudents);

void DataBaseSearchByMark(vector<DataBaseStud> DataBaseStudents);

void PrintBestMathStudents(vector<MathStud> MathStudents);

void PrintBestPhysStudents(vector<PhysStud> PhysStudents);

void PrintBestProgStudents(vector<ProgStud> ProgStudents);

void PrintBestEngStudents(vector<EngStud> EngStudents);

void PrintBestDataBaseStudents(vector<DataBaseStud> DataBaseStudents);

void PrintTableUsers(vector<User> Users);

void PrintTableMath(vector<MathStud> MathStudents);

void PrintTablePhys(vector<PhysStud> PhysStudents);

void PrintTableProg(vector<ProgStud> ProgStudents);

void PrintTableEng(vector<EngStud> EngStudents);

void PrintTableDataBase(vector<DataBaseStud> DataBaseStudents);

void WriteToMathFile(vector<MathStud> MathStudents);

void WriteToPhysFile(vector<PhysStud> PhysStudents);

void WriteToProgFile(vector<ProgStud> PhysStudents);

void WriteToEngFile(vector<EngStud> EngStudents);

void WriteToDataBaseFile(vector<DataBaseStud> DataBaseStudents);

void WriteToUsersFile(vector<User> Users);
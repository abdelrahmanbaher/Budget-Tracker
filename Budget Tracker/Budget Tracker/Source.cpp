#include <iostream>
#include <fstream>
#include<windows.h>
#include <ctime>
#include<vector>
#include <conio.h>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

void GoBack() //lets the user go to the previous menu where it waits for the user to press SHIFT+A
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	cout << endl << endl << "SHIFT+A : back"; //setting the text to a certain color and displaying a message to the user informing that he could go to the previous menu by pressing SHIFT+A
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //setting the text color to white again
	while (true)
	{
		switch (_getch())
		{
		case 'A':
			system("cls");
			return;
		}
	}
}

void EditList(int MenuPosition, int ControlsPosition) //the list that appears in the editing , it colors the user's choice
{
	string choice[3];
	choice[0] = "Delete";
	choice[1] = "Edit";
	choice[2] = "Back";
	cout << endl << endl;
	for (int j = 0; j < 3; j++)
	{
		if (j == MenuPosition - 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
			cout << choice[j] << endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << choice[j] << endl;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	COORD controls; //displaying the user's guide
	controls.X = 66;
	controls.Y = ControlsPosition;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls); //changing the curosr's position to make output at a certain position set above
	cout << "W : up        ";
	controls.Y = ControlsPosition + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "S : down      ";
	controls.Y = ControlsPosition + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "ENTER : select";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void ListList(int MenuPosition)//the list that appears in the listing , colors the users choice
{
	string choice[3];
	choice[0] = "Quick List";
	choice[1] = "Detailed List";
	choice[2] = "Back";
	for (int j = 0; j < 3; j++)
	{
		if (j == MenuPosition - 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
			cout << choice[j] << endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << choice[j] << endl;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	COORD controls; //displaying the user's guide
	controls.X = 66;
	controls.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "W : up        ";
	controls.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "S : down      ";
	controls.Y = 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "ENTER : select";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

struct User
{
	//variables declaration
	double incomes[1000], expenses[1000];
	double LastIndexIncomes = -1, LastIndexExpenses = -1, SumOfIncomes = 0, SumOfExpenses = 0;
	string ExpenseType[1000], IncomeType[1000];
	SYSTEMTIME IncomeDate[1000], ExpenseDate[1000];
	struct DATE
	{
		int day, month, year;
	}; //used for the entering of date ranges (the date variable won't be needed in case of a quick list)

	struct MONTH
	{
		double sum = 0;
		int month, year;
	}; //used to save data for a quick review

	void TotalSumIncomes()//calculate the new total sum of incomes
	{
		SumOfIncomes = 0;
		for (int i = 0; i < LastIndexIncomes + 1; i++)
		{
			SumOfIncomes += incomes[i];
		}
	}
	void TotalSumExpenses()//calculate the new total sum of expenses
	{
		SumOfExpenses = 0;
		for (int i = 0; i < LastIndexExpenses + 1; i++)
		{
			SumOfExpenses += expenses[i];
		}
	}

	void NewIncome()//Entering new incomes
	{
		cout << "Income Value" << "\t\t" << "Income Type" << endl
			<< "------------" << "\t\t" << "-----------";
		for (int i = LastIndexIncomes + 1, j = 0;; i++, j++)
		{
			COORD IncomesCursor;
			IncomesCursor.X = 0;
			IncomesCursor.Y = j + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor); //changing the coordinates of the cursor
			cin >> incomes[i];
			cin.ignore();
			LastIndexIncomes = i;
			SumOfIncomes = SumOfIncomes + incomes[i];
			IncomesCursor.X = 24;
			IncomesCursor.Y = j + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
			getline(cin, IncomeType[i]);
			GetSystemTime(&IncomeDate[i]);
			bool WantToBreak = false;
			COORD question;
			question.X = 0;
			question.Y = j + 3;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), question);
			//displaying a continuing question for the user that has no accepted answers other than pressing Y or N on the keyboard meaning yes or no
			cout << "Continue ? (y/n)";
			while (true)
			{
				bool answered = false;
				if (_kbhit())
					switch (_getch())
					{
					case 'y':
					case 'Y':
						answered = true;
						WantToBreak = false;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), question);
						cout << "                                                                                  ";
						break;
					case 'n':
					case 'N':
						answered = true;
						WantToBreak = true;
						break;
					}
				if (answered)
				{
					break;
				}
			}
			if (WantToBreak)
			{
				break;
			}
		}
	}

	void EditIncome()//let the user edit or delete any value in the incomes array
	{
		int MenuPosition = 1, ControlsPosition = 3;
		ListIncomeForEdit(ControlsPosition);
		EditList(MenuPosition, ControlsPosition);
		while (true)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 's':
				case 'S':
					if (MenuPosition >= 3)
					{
						MenuPosition = 0;
					}
					MenuPosition++;
					system("cls");
					ListIncomeForEdit(ControlsPosition);
					EditList(MenuPosition, ControlsPosition);
					break;
				case 'w':
				case 'W':
					if (MenuPosition <= 1)
					{
						MenuPosition = 4;
					}
					MenuPosition--;
					system("cls");
					ListIncomeForEdit(ControlsPosition);
					EditList(MenuPosition, ControlsPosition);
					break;
				case '\r':
					if (MenuPosition == 1 || MenuPosition == 4)
					{
						cout << "\n\nEnter the number of  the income you want to delete : ";
						int IndexDelete;
						cin >> IndexDelete;
						if (IndexDelete - 1 > LastIndexIncomes || IndexDelete < 1)
						{
							system("cls");
							cout << "Income not found" << endl;
							Sleep(1000);
							system("cls");
							ListIncomeForEdit(ControlsPosition);
							EditList(MenuPosition, ControlsPosition);
							break;
						}
						for (int i = IndexDelete - 1; i < LastIndexIncomes; i++)//delete the index the user wanted to remove from incomes
							incomes[i] = incomes[i + 1];
						for (int i = IndexDelete - 1; i < LastIndexIncomes; i++)//delete the index the user wanted to remove from incomes type
							IncomeType[i] = IncomeType[i + 1];
						for (int i = IndexDelete - 1; i < LastIndexIncomes; i++)//delete the index the user wanted to remove from incomes date
							IncomeDate[i] = IncomeDate[i + 1];
						LastIndexIncomes--; //decreasing the index by 1 as the user deleted 1 index
						TotalSumIncomes();
						system("cls");
						cout << "Income deleted" << endl;
						Sleep(1000);
						system("cls");
						ListIncomeForEdit(ControlsPosition);
						EditList(MenuPosition, ControlsPosition);
					}
					else if (MenuPosition == 2)
					{
						cout << "\n\nEnter the income number you want to edit : ";
						int IndexEdit;
						cin >> IndexEdit;
						if (IndexEdit - 1 > LastIndexIncomes || IndexEdit < 1)
						{
							system("cls");
							cout << "Income not found" << endl;
							Sleep(1000);
						}
						else
						{
							cout << "Enter the new income value : ";
							cin >> incomes[IndexEdit - 1];
							cin.ignore();
							cout << "Enter the new income type : ";
							getline(cin, IncomeType[IndexEdit - 1]);
							TotalSumIncomes();
							system("cls");
							cout << "Income value changed" << endl;
							Sleep(1000);
						}
						system("cls");
						ListIncomeForEdit(ControlsPosition);
						EditList(MenuPosition, ControlsPosition);
					}
					else if (MenuPosition == 3 || MenuPosition == 0)
					{
						return;
					}
				}
			}
		}
	}

	void ListIncome()//listing the incomes according to the user's choice by displaying a list of choices
	{
		DATE limit1, limit2;
		int MenuPosition = 1;
		ListList(MenuPosition);
		while (true)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 's':
				case 'S':
					if (MenuPosition >= 3)
					{
						MenuPosition = 0;
					}
					MenuPosition++;
					system("cls");
					ListList(MenuPosition);
					break;
				case 'w':
				case 'W':
					if (MenuPosition <= 1)
					{
						MenuPosition = 4;
					}
					MenuPosition--;
					system("cls");
					ListList(MenuPosition);
					break;
				case '\r':
					MONTH IncomeMonths[1000];
					if (MenuPosition == 1 || MenuPosition == 4)
					{
						system("cls");
						cout << "Specify a date range : " << endl;
						cout << "1st Limit : Month : ";
						cin >> limit1.month;
						cout << "            Year : ";
						cin >> limit1.year;
						cout << "2nd Limit : Month : ";
						cin >> limit2.month;
						cout << "            Year : ";
						cin >> limit2.year;
						system("cls");
						int Times = limit2.year - limit1.year; //the diffirence between the 2 years of the limits is the number of times the next if statement could be used
						IncomeMonths[0].month = limit1.month;
						IncomeMonths[0].year = limit1.year;
						int LastIndexMonths = 0;
						double QuickTotalSumIncomes = 0;
						for (int i = 0, j = 0; i <= LastIndexIncomes; i++)
						{
							if (Times > 0)
							{
								if (((IncomeDate[i].wMonth >= limit1.month && IncomeDate[i].wMonth <= limit2.month) || (IncomeDate[i].wMonth > limit1.month && IncomeDate[i].wMonth > limit2.month) || (IncomeDate[i].wMonth < limit1.month && IncomeDate[i].wMonth < limit2.month)) && IncomeDate[i].wYear >= limit1.year && IncomeDate[i].wYear <= limit2.year)//this if statement is used in case the income date exceeded the month range but is still in the years range
								{
									if (IncomeDate[i].wMonth == IncomeMonths[j].month && IncomeDate[i].wYear == IncomeMonths[j].year)
									{
										IncomeMonths[j].sum += incomes[i];
									}
									else
									{
										j++;
										LastIndexMonths++;
										IncomeMonths[j].month = IncomeDate[i].wMonth;
										IncomeMonths[j].year = IncomeDate[i].wYear;
										IncomeMonths[j].sum += incomes[i];
									}
									QuickTotalSumIncomes += incomes[i];
								}
							}
							else  // this statement is only used in the last year of the incomes range where Times=0 and any income that exceeds the month or years range is not needed
							{
								if (IncomeDate[i].wMonth >= limit1.month && IncomeDate[i].wMonth <= limit2.month && IncomeDate[i].wYear >= limit1.year && IncomeDate[i].wYear <= limit2.year)
								{
									if (IncomeDate[i].wMonth == IncomeMonths[j].month && IncomeDate[i].wYear == IncomeMonths[j].year)
									{
										IncomeMonths[j].sum += incomes[i];
									}
									else
									{
										j++;
										LastIndexMonths++;
										IncomeMonths[j].month = IncomeDate[i].wMonth;
										IncomeMonths[j].year = IncomeDate[i].wYear;
										IncomeMonths[j].sum += incomes[i];
									}
									QuickTotalSumIncomes += incomes[i];
								}
							}
							if (IncomeDate[i].wMonth == limit1.month)
							{
								Times--;
							}
						}
						cout << "No.  Income Value\t\t" << "Date" << endl;
						cout << "---  ------------\t\t" << "----" << endl;
						for (int i = 0; i <= LastIndexMonths; i++)
						{
							COORD IncomesCursor;
							IncomesCursor.X = 0;
							IncomesCursor.Y = i + 2;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
							cout << i + 1;
							IncomesCursor.X = 5;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
							cout << IncomeMonths[i].sum;
							IncomesCursor.X = 32;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
							cout << IncomeMonths[i].month << "/" << IncomeMonths[i].year;
						}
						cout << endl << endl << "total amount of incomes is : " << QuickTotalSumIncomes;
						GoBack();
						ListList(MenuPosition);
					}
					else if (MenuPosition == 2)
					{
						system("cls");
						cout << "Specify a date range : " << endl;
						cout << "1st Limit : Day : ";
						cin >> limit1.day;
						cout << "            Month : ";
						cin >> limit1.month;
						cout << "            Year : ";
						cin >> limit1.year;
						cout << "2nd Limit : Day : ";
						cin >> limit2.day;
						cout << "            Month : ";
						cin >> limit2.month;
						cout << "            Year : ";
						cin >> limit2.year;
						system("cls");
						cout << "No.  Income Value\t\t" << "Income Type\t\t" << "Date" << endl;
						cout << "---  ------------\t\t" << "-----------\t\t" << "----" << endl;
						int DetailedTotalSumIncomes = 0;
						int Times = limit2.year - limit1.year; //the diffirence between the 2 years of the limits is the number of times the next if statement could be used
						for (int i = 0, j = 0; i <= LastIndexIncomes; i++)
						{
							if (Times > 0)
							{
								if (((IncomeDate[i].wDay >= limit1.day && IncomeDate[i].wDay <= limit2.day && IncomeDate[i].wMonth >= limit1.month && IncomeDate[i].wMonth <= limit2.month) || (IncomeDate[i].wDay > limit1.day && IncomeDate[i].wDay > limit2.day && IncomeDate[i].wMonth > limit1.month && IncomeDate[i].wMonth > limit2.month) || (IncomeDate[i].wDay < limit1.day && IncomeDate[i].wDay < limit2.day && IncomeDate[i].wMonth < limit1.month && IncomeDate[i].wMonth < limit2.month) || (IncomeDate[i].wDay < limit1.day && IncomeDate[i].wDay < limit2.day && IncomeDate[i].wMonth > limit1.month && IncomeDate[i].wMonth > limit2.month) || (IncomeDate[i].wDay > limit1.day && IncomeDate[i].wDay > limit2.day && IncomeDate[i].wMonth < limit1.month && IncomeDate[i].wMonth < limit2.month)) && IncomeDate[i].wYear >= limit1.year && IncomeDate[i].wYear <= limit2.year)//this if statement is only used in case the income date exceeded the months or days range but is still in the years range
								{
									COORD IncomesCursor;
									IncomesCursor.X = 0;
									IncomesCursor.Y = j + 2;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << j + 1;
									IncomesCursor.X = 5;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << incomes[i];
									DetailedTotalSumIncomes += incomes[i];
									IncomesCursor.X = 32;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << IncomeType[i];
									IncomesCursor.X = 56;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << IncomeDate[i].wDay << "/" << IncomeDate[i].wMonth << "/" << IncomeDate[i].wYear;
									j++;
								}
							}
							else  //this if statement is only used in the last year of the incomes range where Times=0 so if the expense date exceeds the days or months range this expense will not be displayed
							{
								if (IncomeDate[i].wDay >= limit1.day && IncomeDate[i].wDay <= limit2.day && IncomeDate[i].wMonth >= limit1.month && IncomeDate[i].wMonth <= limit2.month && IncomeDate[i].wYear >= limit1.year && IncomeDate[i].wYear <= limit2.year)
								{
									COORD IncomesCursor;
									IncomesCursor.X = 0;
									IncomesCursor.Y = j + 2;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << j + 1;
									IncomesCursor.X = 5;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << incomes[i];
									DetailedTotalSumIncomes += incomes[i];
									IncomesCursor.X = 32;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << IncomeType[i];
									IncomesCursor.X = 56;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
									cout << IncomeDate[i].wDay << "/" << IncomeDate[i].wMonth << "/" << IncomeDate[i].wYear;
									j++;
								}
							}
							if (IncomeDate[i].wDay == limit1.day && IncomeDate[i].wMonth == limit1.month)
							{
								Times--;
							}
						}
						cout << endl << endl;
						cout << "total amount of incomes is : " << DetailedTotalSumIncomes;
						GoBack();
						ListList(MenuPosition);
					}
					else if (MenuPosition == 3 || MenuPosition == 0)
					{
						return;
					}
					break;
				}
			}
		}
	}

	void ListIncomeForEdit(int &ControlsPosition)//lists all the values of the incomes array (used only in the edit function)
	{
		ControlsPosition = 3;
		cout << "No.  Income Value\t\t" << "Income Type\t\t" << "Date" << endl;
		cout << "---  ------------\t\t" << "-----------\t\t" << "----" << endl;
		for (int i = 0; i <= LastIndexIncomes; i++)
		{
			COORD IncomesCursor;
			IncomesCursor.X = 0;
			IncomesCursor.Y = i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
			cout << i + 1;
			IncomesCursor.X = 5;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
			cout << incomes[i];
			IncomesCursor.X = 32;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
			cout << IncomeType[i];
			IncomesCursor.X = 56;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), IncomesCursor);
			cout << IncomeDate[i].wDay << "/" << IncomeDate[i].wMonth << "/" << IncomeDate[i].wYear;
			ControlsPosition++;
		}
	}

	void NewExpense()
	{
		cout << "Expense Value" << "\t\t" << "Expense Type" << endl
			<< "------------" << "\t\t" << "-----------";
		for (int i = LastIndexExpenses + 1, j = 0;; i++, j++)
		{
			COORD ExpensesCursor;
			ExpensesCursor.X = 0;
			ExpensesCursor.Y = j + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			cin >> expenses[i];
			cin.ignore();
			LastIndexExpenses = i;
			SumOfExpenses = SumOfExpenses + expenses[i];
			ExpensesCursor.X = 24;
			ExpensesCursor.Y = j + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			getline(cin, ExpenseType[i]);
			GetSystemTime(&ExpenseDate[i]);
			bool WantToBreak = false;
			COORD question;
			question.X = 0;
			question.Y = j + 3;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), question);
			//displaying a continuing question for the user which has no accepted answers other than pressing the button Y or the button N on the keyboard meaning yes or no
			cout << "Continue ? (y/n)";
			while (true)
			{
				bool answered = false;
				if (_kbhit())
					switch (_getch())
					{
					case 'y':
					case 'Y':
						answered = true;
						WantToBreak = false;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), question);
						cout << "                                                                                  ";
						break;
					case 'n':
					case 'N':
						answered = true;
						WantToBreak = true;
						break;
					}
				if (answered)
				{
					break;
				}
			}
			if (WantToBreak)
			{
				break;
			}
		}
	}

	void EditExpense()//let the user edit or delete any value in the expenses array
	{
		int MenuPosition = 1, ControlsPosition = 3;
		ListExpenseForEdit(ControlsPosition);
		EditList(MenuPosition, ControlsPosition);
		while (true)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 's':
				case 'S':
					if (MenuPosition >= 3)
					{
						MenuPosition = 0;
					}
					MenuPosition++;
					system("cls");
					ListExpenseForEdit(ControlsPosition);
					EditList(MenuPosition, ControlsPosition);
					break;
				case 'w':
				case 'W':
					if (MenuPosition <= 1)
					{
						MenuPosition = 4;
					}
					MenuPosition--;
					system("cls");
					ListExpenseForEdit(ControlsPosition);
					EditList(MenuPosition, ControlsPosition);
					break;
				case '\r':
					if (MenuPosition == 1 || MenuPosition == 4)
					{
						cout << "\n\nEnter the number of the expense you want to delete : ";
						int IndexDelete;
						cin >> IndexDelete;
						if (IndexDelete - 1 > LastIndexExpenses || IndexDelete < 1)
						{
							cout << "Expense not found" << endl;
							Sleep(1000);
							break;
						}
						for (int i = IndexDelete - 1; i < LastIndexExpenses; i++)//delete the index the user wanted to remove from expesnes
							expenses[i] = expenses[i + 1];
						for (int i = IndexDelete - 1; i < LastIndexExpenses; i++)//delete the index the user wanted to remove from expenses type
							ExpenseType[i] = ExpenseType[i + 1];
						for (int i = IndexDelete - 1; i < LastIndexExpenses; i++)//delete the index the user wanted to remove from expenses date
							ExpenseDate[i] = ExpenseDate[i + 1];
						LastIndexExpenses--; //decreasing the index by 1 as the user deleted 1 index
						TotalSumExpenses();
						system("cls");
						cout << "Expense deleted" << endl;
						Sleep(1000);
						system("cls");
						ListExpenseForEdit(ControlsPosition);
						EditList(MenuPosition, ControlsPosition);
					}
					else if (MenuPosition == 2)
					{
						cout << "\n\nEnter the expense number you want to edit : ";
						int IndexEdit;
						cin >> IndexEdit;
						if (IndexEdit - 1 > LastIndexExpenses || IndexEdit < 1)
						{
							system("cls");
							cout << "Expense not found" << endl;
							Sleep(1000);
						}
						else
						{
							cout << "Enter the new expense value : ";
							cin >> expenses[IndexEdit - 1];
							cin.ignore();
							cout << "Enter the new expense type : ";
							getline(cin, ExpenseType[IndexEdit - 1]);
							TotalSumExpenses();
							system("cls");
							cout << "Expense value changed" << endl;
							Sleep(1000);
						}
						system("cls");
						ListExpenseForEdit(ControlsPosition);
						EditList(MenuPosition, ControlsPosition);
					}
					else if (MenuPosition == 3 || MenuPosition == 0)
					{
						return;
					}
				}
			}
		}
	}

	void ListExpense()//listing the expenses according to the user's choice by displaying a list of choices
	{

		DATE limit1, limit2;
		int MenuPosition = 1;
		ListList(MenuPosition);
		while (true)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 's':
				case 'S':
					if (MenuPosition >= 3)
					{
						MenuPosition = 0;
					}
					MenuPosition++;
					system("cls");
					ListList(MenuPosition);
					break;
				case 'w':
				case 'W':
					if (MenuPosition <= 1)
					{
						MenuPosition = 4;
					}
					MenuPosition--;
					system("cls");
					ListList(MenuPosition);
					break;
				case '\r':
					MONTH ExpenseMonths[1000];
					if (MenuPosition == 1 || MenuPosition == 4)
					{
						system("cls");
						cout << "Specify a date range : " << endl;
						cout << "1st Limit : Month : ";
						cin >> limit1.month;
						cout << "            Year : ";
						cin >> limit1.year;
						cout << "2nd Limit : Month : ";
						cin >> limit2.month;
						cout << "            Year : ";
						cin >> limit2.year;
						system("cls");
						int Times = limit2.year - limit1.year; //the diffirence between the 2 years of the limits is the number of times the next if statement could be used
						ExpenseMonths[0].month = limit1.month;
						ExpenseMonths[0].year = limit1.year;
						int LastIndexMonths = 0;
						double QuickTotalSumExpense = 0;
						for (int i = 0, j = 0; i <= LastIndexExpenses; i++)
						{
							if (Times > 0)
							{
								if (((ExpenseDate[i].wMonth >= limit1.month && ExpenseDate[i].wMonth <= limit2.month) || (ExpenseDate[i].wMonth > limit1.month && ExpenseDate[i].wMonth > limit2.month) || (ExpenseDate[i].wMonth < limit1.month && ExpenseDate[i].wMonth < limit2.month)) && ExpenseDate[i].wYear >= limit1.year && ExpenseDate[i].wYear <= limit2.year)//this if statement is used in case the income date exceeded the month range but is still in the years range
								{
									if (ExpenseDate[i].wMonth == ExpenseMonths[j].month && ExpenseDate[i].wYear == ExpenseMonths[j].year)
									{
										ExpenseMonths[j].sum += expenses[i];
									}
									else
									{
										j++;
										LastIndexMonths++;
										ExpenseMonths[j].month = ExpenseDate[i].wMonth;
										ExpenseMonths[j].year = ExpenseDate[i].wYear;
										ExpenseMonths[j].sum += expenses[i];
									}
									QuickTotalSumExpense += expenses[i];
								}
							}
							else  // this statement is only used in the last year of the incomes range where Times=0 and any income that exceeds the month or years range is not needed
							{
								if (ExpenseDate[i].wMonth >= limit1.month && ExpenseDate[i].wMonth <= limit2.month && ExpenseDate[i].wYear >= limit1.year && ExpenseDate[i].wYear <= limit2.year)
								{
									if (ExpenseDate[i].wMonth == ExpenseMonths[j].month && ExpenseDate[i].wYear == ExpenseMonths[j].year)
									{
										ExpenseMonths[j].sum += expenses[i];
									}
									else
									{
										j++;
										LastIndexMonths++;
										ExpenseMonths[j].month = ExpenseDate[i].wMonth;
										ExpenseMonths[j].year = ExpenseDate[i].wYear;
										ExpenseMonths[j].sum += expenses[i];
									}
									QuickTotalSumExpense += expenses[i];
								}
							}
							if (ExpenseDate[i].wMonth == limit1.month)
							{
								Times--;
							}
						}
						cout << "No.  Income Value\t\t" << "Date" << endl;
						cout << "---  ------------\t\t" << "----" << endl;
						for (int i = 0; i <= LastIndexMonths; i++)
						{
							COORD ExpenseCursor;
							ExpenseCursor.X = 0;
							ExpenseCursor.Y = i + 2;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpenseCursor);
							cout << i + 1;
							ExpenseCursor.X = 5;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpenseCursor);
							cout << ExpenseMonths[i].sum;
							ExpenseCursor.X = 32;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpenseCursor);
							cout << ExpenseMonths[i].month << "/" << ExpenseMonths[i].year;
						}
						cout << endl << endl << "total amount of Expense is : " << QuickTotalSumExpense;
						GoBack();
						ListList(MenuPosition);
					}
					else if (MenuPosition == 2)
					{
						system("cls");
						cout << "Specify a date range : " << endl;
						cout << "1st Limit : Day : ";
						cin >> limit1.day;
						cout << "            Month : ";
						cin >> limit1.month;
						cout << "            Year : ";
						cin >> limit1.year;
						cout << "2nd Limit : Day : ";
						cin >> limit2.day;
						cout << "            Month : ";
						cin >> limit2.month;
						cout << "            Year : ";
						cin >> limit2.year;
						system("cls");
						cout << "No.  Income Value\t\t" << "Income Type\t\t" << "Date" << endl;
						cout << "---  ------------\t\t" << "-----------\t\t" << "----" << endl;
						int DetailedTotalSumExpense = 0;
						int Times = limit2.year - limit1.year; //the diffirence between the 2 years of the limits is the number of times the next if statement could be used
						for (int i = 0, j = 0; i <= LastIndexExpenses; i++)
						{
							if (Times > 0)
							{
								if (((ExpenseDate[i].wDay >= limit1.day && ExpenseDate[i].wDay <= limit2.day && ExpenseDate[i].wMonth >= limit1.month && ExpenseDate[i].wMonth <= limit2.month) || (ExpenseDate[i].wDay > limit1.day && ExpenseDate[i].wDay > limit2.day && ExpenseDate[i].wMonth > limit1.month && ExpenseDate[i].wMonth > limit2.month) || (ExpenseDate[i].wDay < limit1.day && ExpenseDate[i].wDay < limit2.day && ExpenseDate[i].wMonth < limit1.month && ExpenseDate[i].wMonth < limit2.month) || (ExpenseDate[i].wDay < limit1.day && ExpenseDate[i].wDay < limit2.day && ExpenseDate[i].wMonth > limit1.month && ExpenseDate[i].wMonth > limit2.month) || (ExpenseDate[i].wDay > limit1.day && ExpenseDate[i].wDay > limit2.day && ExpenseDate[i].wMonth < limit1.month && ExpenseDate[i].wMonth < limit2.month)) && ExpenseDate[i].wYear >= limit1.year && ExpenseDate[i].wYear <= limit2.year)//this if statement is only used in case the Expense date exceeded the months or days range but is still in the years range
								{
									COORD ExpensesCursor;
									ExpensesCursor.X = 0;
									ExpensesCursor.Y = j + 2;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << j + 1;
									ExpensesCursor.X = 5;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << expenses[i];
									DetailedTotalSumExpense += expenses[i];
									ExpensesCursor.X = 32;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << ExpenseType[i];
									ExpensesCursor.X = 56;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << ExpenseDate[i].wDay << "/" << ExpenseDate[i].wMonth << "/" << ExpenseDate[i].wYear;
									j++;
								}
							}
							else  //this if statement is only used in the last year of the incomes range where Times=0 so if the expense date exceeds the days or months range this expense will not be displayed
							{
								if (ExpenseDate[i].wDay >= limit1.day && ExpenseDate[i].wDay <= limit2.day && ExpenseDate[i].wMonth >= limit1.month && ExpenseDate[i].wMonth <= limit2.month && ExpenseDate[i].wYear >= limit1.year && ExpenseDate[i].wYear <= limit2.year)
								{
									COORD ExpensesCursor;
									ExpensesCursor.X = 0;
									ExpensesCursor.Y = j + 2;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << j + 1;
									ExpensesCursor.X = 5;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << expenses[i];
									DetailedTotalSumExpense += expenses[i];
									ExpensesCursor.X = 32;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << ExpenseType[i];
									ExpensesCursor.X = 56;
									SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
									cout << ExpenseDate[i].wDay << "/" << ExpenseDate[i].wMonth << "/" << ExpenseDate[i].wYear;
									j++;
								}
							}
							if (ExpenseDate[i].wDay == limit1.day && ExpenseDate[i].wMonth == limit1.month)
							{
								Times--;
							}
						}
						cout << endl << endl;
						cout << "total amount of incomes is : " << DetailedTotalSumExpense;
						GoBack();
						ListList(MenuPosition);
					}
					else if (MenuPosition == 3 || MenuPosition == 0)
					{
						return;
					}
					break;
				}
			}
		}
	}

	void ListExpenseForEdit(int &ControlsPosition)//lists all the values in the expenses array (used in the editing function only)
	{
		cout << "No.  Expense Value\t\t" << "Expense Type\t\t" << "Date" << endl;
		cout << "---  -------------\t\t" << "------------\t\t" << "----" << endl;
		ControlsPosition = 3;
		for (int i = 0; i <= LastIndexExpenses; i++)
		{
			COORD ExpensesCursor;
			ExpensesCursor.X = 0;
			ExpensesCursor.Y = i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			cout << i + 1;
			ExpensesCursor.X = 5;
			ExpensesCursor.Y = i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			cout << expenses[i];
			ExpensesCursor.X = 32;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			cout << ExpenseType[i];
			ExpensesCursor.X = 56;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ExpensesCursor);
			cout << ExpenseDate[i].wDay << "/" << ExpenseDate[i].wMonth << "/" << ExpenseDate[i].wYear;
			ControlsPosition++;
		}
	}
	////////////////////////////////////////////Saving Incomes & Reading their data//////////////////////////////////////////////////////////

	void SaveIncomes()//saving user's income in the incomes array
	{
		ofstream outfile;
		outfile.open("income.txt"); //creating a file for saving
		for (int i = 0; i < LastIndexIncomes + 1; i++)
		{
			outfile << incomes[i] << endl;
		}
	}

	void SaveIncomesTypes()//saving user's income type in the incomes type array
	{
		ofstream outfile;
		outfile.open("incomeType.txt");
		for (int i = 0; i < LastIndexIncomes + 1; i++)
		{
			outfile << IncomeType[i] << endl;
		}
	}

	void SaveIncomesDates()//saving the date the user entered each income
	{
		ofstream outfile;
		outfile.open("incomeDate.txt");
		for (int i = 0; i < LastIndexIncomes + 1; i++)
		{
			outfile << IncomeDate[i].wDay << " " << IncomeDate[i].wMonth << " " << IncomeDate[i].wYear << endl;
		}
	}

	void ReadIncomes()//reading user's incomes using incomes.txt and saving it to the array of incomes
	{
		ifstream infile;
		infile.open("income.txt");
		for (int i = 0; infile >> incomes[i]; i++)
		{
			LastIndexIncomes = i; //changing value of last index incomes to the current index value of the incomes
			SumOfIncomes += incomes[i]; //changing value of sum of incomes to the saved values of incomes
		}
	}

	void ReadIncomesTypes()//reading user's incomes using incomes.txt and saving it to the array of incomes
	{
		ifstream infile;
		infile.open("inc]'omeType.txt");
		for (int i = 0; getline(infile, IncomeType[i]); i++)
		{
			LastIndexIncomes = i; //changing value of last index incomes to the current index value of the incomes
		}
	}

	void ReadIncomesDates()
	{
		ifstream infile;
		infile.open("incomeDate.txt");
		for (int i = 0; infile >> IncomeDate[i].wDay >> IncomeDate[i].wMonth >> IncomeDate[i].wYear; i++)
		{
			LastIndexIncomes = i; //changing value of last index incomes to the current index value of the incomes date
		}
	}
	////////////////////////////////////////////Saving Expenses & Reading their data//////////////////////////////////////////////////////////

	void SaveExpenses()//saving user's expenses in the expenses array
	{
		ofstream outfile;
		outfile.open("expenses.txt"); //creating a file for saving
		for (int i = 0; i < LastIndexExpenses + 1; i++)
		{
			outfile << expenses[i] << endl;
		}
	}

	void SaveExpensesTypes()//saving user's Expenses type in the Expenses type array
	{
		ofstream outfile;
		outfile.open("expensesType.txt");
		for (int i = 0; i < LastIndexExpenses + 1; i++)
		{
			outfile << ExpenseType[i] << endl;
		}
	}

	void SaveExpensesDates()//saving the date the user entered each expense
	{
		ofstream outfile;
		outfile.open("expenseDate.txt");
		for (int i = 0; i < LastIndexExpenses + 1; i++)
		{
			outfile << ExpenseDate[i].wDay << " " << ExpenseDate[i].wMonth << " " << ExpenseDate[i].wYear << endl;
		}
	}

	void ReadExpenses()//reading user's Expenses using Expenses.txt and saving it to the array of Expenses
	{
		ifstream infile;
		infile.open("expenses.txt");
		for (int i = 0; infile >> expenses[i]; i++)
		{
			LastIndexExpenses = i; //changing value of last index Expenses to the current index value of the Expenses
			SumOfExpenses += expenses[i]; //changing value of sum of expenses to the saved values of expenses
		}
	}

	void ReadExpensesTypes()//reading user's Expenses using Expenses.txt and saving it to the array of Expenses
	{
		ifstream infile;
		infile.open("expensesType.txt");
		for (int i = 0; getline(infile, ExpenseType[i]); i++)
		{
			LastIndexExpenses = i; //changing value of last index Expenses to the current index value of the Expenses
		}
	}

	void ReadExpensesDates()
	{
		ifstream infile;
		infile.open("expenseDate.txt");
		for (int i = 0; infile >> ExpenseDate[i].wDay >> ExpenseDate[i].wMonth >> ExpenseDate[i].wYear; i++)
		{
			LastIndexExpenses = i; //changing value of last index incomes to the current index value of the expenses date
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

void List(int MenuPosition)//the function that displays the main menu by coloring the user's choice
{
	string choice[8];
	choice[0] = "Enter Incomes";
	choice[1] = "Edit Incomes";
	choice[2] = "List Incomes";
	choice[3] = "Enter Expenses";
	choice[4] = "Edit Expenses";
	choice[5] = "List Expenses";
	choice[6] = "Save";
	choice[7] = "Exit";
	for (int j = 0; j < 8; j++)
	{
		if (j == MenuPosition - 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28); //changing the text color
			cout << choice[j] << endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << choice[j] << endl;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	//displaying the user guide for navigation through the menu
	COORD controls;
	controls.X = 66;
	controls.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls); //changing the cursor position to the x and y values set above
	cout << "W : up        ";
	controls.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "S : down      ";
	controls.Y = 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controls);
	cout << "ENTER : select";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int main()
{
	SetConsoleTitleA("Budget Tracker");
	User newUser;
	//loading the user's saved data
	newUser.ReadIncomes();
	newUser.ReadIncomesTypes();
	newUser.ReadIncomesDates();
	newUser.ReadExpenses();
	newUser.ReadExpensesTypes();
	newUser.ReadExpensesDates();
	bool notSaved = false;
	int MenuPosition = 1; //setting the choice to the first choice at starting the program
	List(MenuPosition); //displaying the main menu
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())//the menu only accepts the buttons S , W and ENTER
			{
			case 's':
			case 'S':
				if (MenuPosition >= 8)
				{
					MenuPosition = 0;
				}
				MenuPosition++;
				system("cls");
				List(MenuPosition);
				break;
			case 'w':
			case 'W':
				if (MenuPosition <= 1)
				{
					MenuPosition = 9;
				}
				MenuPosition--;
				system("cls");
				List(MenuPosition);
				break;
			case '\r':
				system("cls");
				if (MenuPosition == 1 || MenuPosition == 9)
				{
					newUser.NewIncome();
					system("cls");
					List(MenuPosition);
					notSaved = true;
				}
				else if (MenuPosition == 2)
				{
					newUser.EditIncome();
					system("cls");
					List(MenuPosition);
					notSaved = true;
				}
				else if (MenuPosition == 3)
				{
					newUser.ListIncome();
					system("cls");
					List(MenuPosition);
				}
				else if (MenuPosition == 4)
				{
					newUser.NewExpense();
					system("cls");
					List(MenuPosition);
					notSaved = true;
				}
				else if (MenuPosition == 5)
				{
					newUser.EditExpense();
					system("cls");
					List(MenuPosition);
					notSaved = true;
				}
				else if (MenuPosition == 6)
				{
					newUser.ListExpense();
					system("cls");
					List(MenuPosition);
				}
				else if (MenuPosition == 7)
				{
					//saving user's data to files to load them next time the user uses the application
					newUser.SaveIncomes();
					newUser.SaveIncomesTypes();
					newUser.SaveIncomesDates();
					newUser.SaveExpenses();
					newUser.SaveExpensesTypes();
					newUser.SaveExpensesDates();
					notSaved = false;
					cout << "Data Saved" << endl;
					Sleep(1000); //sleep to view data saved message to the user
					system("cls");
					List(MenuPosition);
				}
				else if (MenuPosition == 8 || MenuPosition == 0)
				{
					system("cls");
					if (notSaved)
					{
						while (true)
						{
							cout << "Changes not saved, Are you sure to Exit ?" << endl << endl;
							cout << "1.Exit and save changes" << "\t\t" << "2.Exit discarding changes" << "\t" << endl << endl;
							cout << "Enter your choice : ";
							int choice;
							cin >> choice;
							if (choice == 1)
							{
								newUser.SaveIncomes();
								newUser.SaveIncomesTypes();
								newUser.SaveIncomesDates();
								newUser.SaveExpenses();
								newUser.SaveExpensesTypes();
								newUser.SaveExpensesDates();
								return 0;
							}
							else if (choice == 2)
							{
								return 0;
							}
							else
							{
								system("cls");
								cout << "Wrong Choice, Try again" << endl;
								Sleep(1000);
								system("cls");
								continue;
							}
						}
					}
					return 0;
				}
			}
		}
	}
}

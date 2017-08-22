/***
//// Last Build : 8_19_08
//// Compiler   : VS2005
//// Programmer : TAN Lik Wei
//// Capability : Implementing a variable size record.
//// Function   : add, delete, modify, display records ( hourly or salaried )
***/


/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <string>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
using namespace std;


/////////////     Data types    /////////////

struct Grade_Record // Grade record
{
	int staffID;
	int studentID;
	string password;
	int menuchoice;
	string name;
	string address;
	int IC;
	int passportno;
	int session;
	string modeofstudy;
	int year;
	string school;
	int level;
	string program;
	string major;
	int semester;
	int section;
	int coursecode;
	string description;
	int credithours;
	string grade;
	int gradepoints;
	int creditpoints;
	double GPA;
	double GCPA;
	string awards;
	double quiz;
	int attendance;
	double test;
	double assignment;
	double examination;

	bool deleted;
};


/////////////     Variable Declarations & Constants /////////////

#define GRADE_FILE_NAME "Grades.txt" // name of the database file to store Grades informations

Grade_Record Grade;
char     choice; // for choice in menu
fstream *fs = NULL, *fs1 = NULL;// file streams for files : fs -> 'Grade', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted


						   /////////////     Function Prototypes    /////////////

void closeFile(fstream *); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char *); // check if a file exists


								/////////////     Main    /////////////
int main()
{
	while (true)
	{
		do ////// Menu //////
		{
			system("cls"); // clear screen

			cout << "\n    < Grades Database > \n\n";
			cout << "(1) Add     a new Record \n";
			cout << "(2) Modify an existing Record\n";
			cout << "(3) Delete an existing Record \n";
			cout << "(4) Display Records \n";
			cout << "(5) Exit \n\n";
			cout << " Enter a choice (1-5) : " << flush;
			choice = getch();
		} while (choice < '1' || choice > '5'); // while we have no good(between 1 and 5), show menu again

		system("cls");

		// to modify, delete or display records, database file should exist, then we have some records           
		if (choice == '2' || choice == '3' || choice == '4')
		{
			if (!isFileExist(GRADE_FILE_NAME)) // if database file doesn't exist
			{
				cout << "\n Database file ('" << GRADE_FILE_NAME << "') doesn't exist, then there are no records." << endl;
				system("pause");
				continue; // show the menu again
			}
		}

		switch (choice)
		{
			int recs_num; // number of records before the record for modifying(deletion)
			int id;

		case '1': ////// Add Record //////

			cout << "\n\t\t < Entering a new record > ";
			cout << "\n   Enter the following informations for the new record : ";
		
			cout << "Student ID: ";
			cin >> Grade.studentID;
			cout << "Password: ";
			cin >> Grade.password;
			cout << "Name: ";
			cin >> Grade.name;
			cout << "Address: ";
			cin >> Grade.address;
			cout << "IC: ";
			cin >> Grade.IC;
			cout << "Passport No: ";
			cin >> Grade.passportno;
			cout << "Session: ";
			cin >> Grade.session;
			cout << "Mode of Study: ";
			cin >> Grade.modeofstudy;
			cout << "Year: ";
			cin >> Grade.year;
			cout << "School: ";
			cin >> Grade.school;
			cout << "Level: ";
			cin >> Grade.level;
			cout << "Program: ";
			cin >> Grade.program;
			cout << "Major: ";
			cin >> Grade.major;
			cout << "Semester: ";
			cin >> Grade.semester;
			













			//Dont touch after this line
			Grade.deleted = 0;

			fs = new fstream(GRADE_FILE_NAME, ios::out | ios::app | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << GRADE_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			fs->write((char *)&Grade, sizeof(Grade));

			closeFile(fs);

			cout << "\n Record added." << endl;
			system("pause");

			break;

/*		case '2': ////// Modify Record //////

			cout << "\n Enter Grade ID, that you want modify its informatin : ";
			cin >> id;

			fs = new fstream(GRADE_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << GRADE_FILE_NAME << "' file" << endl;
				system("pause");

				break;
			}

			recs_num = -1;

			while (fs->read((char *)&Grade, sizeof(Grade)))
			{
				recs_num++;

				if (Grade.ID == id && !Grade.deleted)
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Grade doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}


			cout << "\n   Enter new informations for this record : ";
			cout << "\n\n PAY_TYPE ( SALARIED : 0, HOURLY : 1 ) : ";
			cin >> Grade.PAY_TYPE;

			cout << "\n ID : ";
			cin >> Grade.ID;
			cout << "\n AGE : ";
			cin >> Grade.AGE;
			cout << "\n DEPT (one character) : ";
			cin >> Grade.DEPT;

			if (Grade.PAY_TYPE == SALARIED)
			{
				cout << "\n MONTHLY_RATE : ";
				cin >> Grade.MONTHLY_RATE;
				cout << "\n START_DATE : ";
				cin >> Grade.START_DATE;
			}

			if (Grade.PAY_TYPE == HOURLY)
			{
				cout << "\n RATE_PER_HOUR : ";
				cin >> Grade.RATE_PER_HOUR;
				cout << "\n REG_HOURS : ";
				cin >> Grade.REG_HOURS;
				cout << "\n OVERTIME_HOURS : ";
				cin >> Grade.OVERTIME_HOURS;
			}


			fs->seekp(sizeof(Grade) * recs_num, ios::beg); // go to the first of the record to be modified
			fs->write((char *)&Grade, sizeof(Grade));

			closeFile(fs);

			cout << "\n Record is modified." << endl;
			system("pause");

			break;


		case '3': ////// Delete Record //////

			cout << "\n Enter Grade's ID, for deletion : ";
			cin >> id;

			fs = new fstream(GRADE_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << GRADE_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			recs_num = -1;

			while (fs->read((char *)&Grade, sizeof(Grade)))
			{
				recs_num++;

				if (Grade.ID == id && !Grade.deleted) // if user deleted an Grade then added another one with the same ID in the same instance of program runs, deleted Grade is still there, then we should go through all the file
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Grade doesn't exist in database file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}

			Grade.deleted = 1;

			fs->seekp(sizeof(Grade) * recs_num, ios::beg);
			fs->write((char *)&Grade, sizeof(Grade));

			closeFile(fs);

			deletion = true; // we have some deleted records

			cout << "\n Record is deleted." << endl;
			system("pause");

			break;


		case '4': // Display Records

				  ////// Print Salaried records...
			fs = new fstream(GRADE_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << GRADE_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			// display column titles
			cout << "\n\t\t < Salaried >\n\n";
			cout << "ID\tAGE\tDEPT\tMONTHLY_RATE\tSTART_DATE\n"
				<< "-------------------------------------------------- \n";

			while (fs->read((char *)&Grade, sizeof(Grade))) // display records
			{
				if (Grade.PAY_TYPE == SALARIED && !Grade.deleted)
				{
					cout << Grade.ID << '\t';
					cout << Grade.AGE << '\t';
					cout << Grade.DEPT << '\t';
					cout << Grade.MONTHLY_RATE << "\t\t";
					cout << Grade.START_DATE << '\n';
				}
			}

			cout << "\n To see Hourly records, "; system("pause");

			closeFile(fs);

			////// Print Hourly records...                 
			system("cls");

			fs = new fstream(GRADE_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << GRADE_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			cout << "\n\t\t\t < Hourly > \n\n";
			cout << "ID\tAGE\tDEPT\tRATE_PER_HOUR\tREG_HOURS\tOVERTIME_HOURS\n"
				<< "---------------------------------------------------------------------- \n";

			while (fs->read((char *)&Grade, sizeof(Grade_Record)))
			{
				if (Grade.PAY_TYPE == HOURLY && !Grade.deleted)
				{
					cout << Grade.ID << '\t';
					cout << Grade.AGE << '\t';
					cout << Grade.DEPT << '\t';
					cout << Grade.RATE_PER_HOUR << "\t\t";
					cout << Grade.REG_HOURS << "\t\t";
					cout << Grade.OVERTIME_HOURS << '\n';
				}
			}

			cout << "\n To see menu, "; system("pause");

			closeFile(fs);

			break;
*/

		case '5': // Exit

			if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
			{
				cout << "\n Updating '" << GRADE_FILE_NAME << "' File..." << endl;

				fs = new fstream(GRADE_FILE_NAME, ios::in | ios::binary);
				if (!fs)
				{
					cout << "\n Can't open '" << GRADE_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}

				fs1 = new fstream("temp", ios::out | ios::binary);
				if (!fs1)
				{
					cout << "\n Can't create temp file, then Updating is incomplete." << endl;
					system("pause");

					closeFile(fs);
					system("cls");
					return 1;
				}

				// write nondeleted records to the temp file
				while (fs->read((char *)&Grade, sizeof(Grade)))
					if (!Grade.deleted)
						fs1->write((char *)&Grade, sizeof(Grade));

				closeFile(fs);
				closeFile(fs1);

				if (remove(GRADE_FILE_NAME) == -1) // if there is an error
				{
					cout << "\n Can't delete '" << GRADE_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}


				struct stat st; // to check size of the temp file
				int res = stat("temp", &st);

				if (st.st_size == 0) // if all of records are deleted then the temp file size is zero                        
					remove("temp"); // we have no records, then no database file is needed, just delete the temp file
				else
					if (rename("temp", GRADE_FILE_NAME))
					{
						cout << "\n Can't rename temp file, then Updating is incomplete." << endl;
						system("pause");

						system("cls");
						return 1;
					}

				cout << "\n Updating database file completed." << endl;
				system("pause");
			}

			system("cls");
			return 0;

			break;
		} // end 'switch'
	} // end 'while'

	return 0;
} // end 'main()'


  /////////////     Function Definitions    /////////////

void closeFile(fstream *fs)
{
	fs->close(); // close the file
	delete fs;
	fs = NULL;
}


bool isFileExist(const char * file_name)
{
	struct stat st; // to check status of file
	int res = stat(file_name, &st);
	return (res == 0); // if file exists     
}
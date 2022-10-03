#include <iostream>
#include <fstream>


using namespace std;

//global variables
int error;
bool logged_in;
string username[10] = {"admin"};
string password[10] = {"0000"};


//functions to create txt files(3)
void createUsernamePassword();
void createBooksAvailable();
void createCompanyDetails();

//first set of functions as choices (Main Menu before login)
void login(string& user, string& pw);
void viewCompanyDetails();

//second set of functions as choices after user login (Sub Menu after login)
void viewAvailableBooks();
void addBook();
void updateBook();
void deleteBook();
void viewSalesDetails();
void registerNewUser();



int main(int argc, char *argv[]){
	int choice_number;
	string userName, passWord;

	

	cout << "\n\t\tWelcome to GENIUS BOOK!!\nUsing this software you can maintain books in the shop\n";
	cout << "***** **** ******** *** *** ******** ***** ** *** ****" << endl;

	
	do {
		cin.clear();
		cout << "\n\n\tPlease select an option from the given menu below:\n\n";
		cout << "\t\t1. Login\n\t\t2. View Company Details\n\t\t3. Exit\n";	
		do {
			error = 0;
			cout << "\n\tEnter your selection (number): ";
			cin >> choice_number;
			
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input" << endl;
				error = 1;
				cin.clear();
				cin.ignore(50, '\n');
								
			}
		} while (error == 1);

		switch (choice_number){
			case 1:
				cout << "\n\tEnter username (default username: admin): ";
				cin >> userName;
				cout << "\n\tEnter password (default password: 0000): ";
				cin >> passWord;
				login(userName, passWord);							
				break;

			case 2:
				createCompanyDetails();
				viewCompanyDetails();
				break;								

			case 3:
				break;
			
			default:				
				cout << "\n\n\tInvalid input!!";
				cout << "\n*****************************************************"<< endl;				
				break;
		}
	} while (choice_number !=3);

	return 0;
	
}

//create txt file containing username and password
void createUsernamePassword()
{	
	ofstream TempFile_01("username&password.txt");

	//iterating through array to write on txt file
	for (int i=0; i <10; i++)
	{
	TempFile_01 << username[i] << "\t"<< password[i] << "\n";		
	}
	TempFile_01.close();
}


//create txt file containing book details
void createBooksAvailable()
{
	//create a list of books details (maximum 100) with details of 5 books already entered	
	string author[100] = {"N.M.Stevenson", "R. Gregor", "L. Timothy", "G. Laura", "P. Randall"};
	string title[100] = {"Learn C++", "Learn Java", "Learn Python", "Learn HTML", "Learn CSS"};
	string publisher[100] = {"Penguin ", "McMillan", "Hachette", "Schuster", "Collins "};
	float price[100] = {2000,3500,990,5600,4200};
	int stock[100] = {3,5,12,6,20};


	ofstream TempFile_02("bookdetails.txt");
	
	//iterating through arrays to write on txt file
	for (int i=0; i < 100; i++)
	{
		if (stock[i] > 0){
		TempFile_02 << author[i] << "\t\t" << title[i] << "\t\t" << publisher[i] << "\t\t" << price[i] << "\t\t" << stock[i] << "\n";
		}
	
	}
	TempFile_02.close();
}

void viewAvailableBooks(){
		string bookstxt;
		ifstream BookDetails("bookdetails.txt");
		while(getline(BookDetails, bookstxt)){
			cout<< bookstxt << "\n";
		}
		BookDetails.close();
}

//create txt file with company details
void createCompanyDetails(){
		ofstream TempFile_03("companydetails.txt");

		TempFile_03<<"\n\n\t\tCOMPANY DETAILS\n";
		TempFile_03<<"\t\t***************\n";
		TempFile_03<<"\t\tName: GENIUS BOOKS (pvt) Ltd.\n";
		TempFile_03<< "\t\tAddress: 345, Galle Road, Colombo-04\n";
		TempFile_03<< "\t\tOwnership: Subramaniam B\n";
		TempFile_03 << "\t\tREG date: 09.12.2016\n";
		TempFile_03.close();
}

//view companydetails
void viewCompanyDetails(){
		string mytext;
		ifstream CompanyDetail("companydetails.txt");
		while (getline(CompanyDetail, mytext)){
			cout << mytext << "\n";
		}
		CompanyDetail.close();
}

//login function that returns true or false
void login(string& user, string& pw)
{	int choice_number;
	logged_in = false;
	for (int i=0; i < 10; i++)
	{
		if (user == username[i] && pw == password[i]){
			cout << "\n\tSuccessfully logged into your account!!" << endl;
			logged_in = true;
			if(logged_in){
				do {
							cin.clear();
							cout << "\n\n\tPlease select an option from the given menu below:\n\n";
							cout << "\t\t1. View available books\n\t\t2. Add a book\n\t\t3. Update a book details\n\t\t4. Delete a book\n\t\t5. View sales details\n\t\t6. Register a new user\n\t\t7. Logout\n";
							do {
								error = 0;
								cout << "\n\tEnter your selection (number): ";
								cin >> choice_number;
								cout << "\n\tAVAILABLE BOOKS: ";
								cout << "\n\t****************" << endl;
								
								if (cin.fail())
								{
									cout << "\n\tPlease enter a valid input" << endl;
									error = 1;
									cin.clear();
									cin.ignore(50, '\n');													
								}
							} while (error == 1);

							switch (choice_number){
								case 1:
									createBooksAvailable();									
									viewAvailableBooks();							
									break;

								case 2:
									// addBook();
									break;

								case 3:
									//updateBook();

								case 4:
									//deleteBook();

								case 5:
									createCompanyDetails();
									viewCompanyDetails();
									break;									

								case 6:
									// void registerNewUser();

								case 7:
									cout << "\n\tYou have successfully logged_out!!";
									break;
								
								default:				
									cout << "\n\n\tInvalid input!!";
									cout << "\n*****************************************************"<< endl;				
									break;
							}
						} while (choice_number !=7);
			}
			break;
		}
	}
	if (!logged_in){
	cout << "\n\tUsername and password does not match!! Try again." << endl;
	}
}


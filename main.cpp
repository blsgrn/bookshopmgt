#include <iostream>
#include <fstream>


using namespace std;

//global variables
int error;
bool logged_in;
string username[10];
string password[10];
string author_arr[100];
string title_arr[100];
string publisher_arr[100];
float price_arr[100];
int stock_arr[100];



//functions to create txt files(3)
void createUsernamePassword();
void createBooksAvailable();
void createCompanyDetails();

//first set of functions as choices (Main Menu before login)
void login(string& user, string& pw);
void viewCompanyDetails();

//second set of functions as choices after user login (Sub Menu after login)
void viewAvailableBooks();
void addNewBooks(int list_number, string author, string title, string publisher, float price, int stock);
void updateBook(int list_no);
void deleteBook(int list_number);
void createNewUsernamePassword(int position, string newuser, string newpassword);


//manage sales
void manageSales();
void addSales(int booklistno, int count);
void createSalestxt();
void viewSales();

int soldBookListNumber[100];
string soldBookAuthor[100];
string soldBookTitle[100];
int soldBookCount[100];
float soldBookPrice[100];
int sales[100];
int totalSales {0};
int totalSalesAccumulation[100];





int main(int argc, char *argv[]){
	int choice_number;
	string userName, passWord;

	

	cout << "\n\t\tWelcome to GENIUS BOOK!!\nUsing this software you can manage books in your bookshop\n";
	cout << "***** **** ******** *** *** ******** ***** ** *** *******" << endl;

	
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
	ofstream TempFile_01("username_password.txt");

	//iterating through array to write on txt file
	for (int i=0; i <10; i++)
	{
	TempFile_01 << username[i] << "\t"<< password[i] << "\n";		
	}
	TempFile_01.close();
}

void createNewUsernamePassword(int position, string newuser, string newpassword){
		username[position] = newuser;
		password[position] = newpassword;
}

//create txt file containing book details
void createBooksAvailable()
{
	
	ofstream TempFile_02("bookdetails.txt");
	
	//iterating through arrays to write on txt file
	for (int i=0; i < 100; i++)
	{
		if (stock_arr[i] > 0){
		TempFile_02 << i << "\t" << author_arr[i] << "\t\t" << title_arr[i] << "\t\t" << publisher_arr[i] << "\t\t" << price_arr[i] << "\t\t" << stock_arr[i] << "\n";
		}
	
	}
	TempFile_02.close();
}

void addNewBooks(int list_number, string author, string title, string publisher, float price, int stock){
	author_arr[list_number] = author;
	title_arr[list_number] = title;
	publisher_arr[list_number] = publisher;
	price_arr[list_number] = price;
	stock_arr[list_number] = stock;
}

void updateBook(int list_no){
	int entered_number;
	string auth, title, publ;
	float pr;
	int stck;
	do {
		cout << "\n\n\tPlease select an option from given menu below to edit:  \n";
		cout << "\t1. Author\n\t2. Title\n\t3. Publisher\n\t4. Price\n\t5. Stock\n\t6. Exit\n";
		cout << "\n\tEnter number: ";
		cin >> entered_number;

		switch (entered_number)
		{
		case 1:
			cout << "Edit author name: ";
			cin >> auth;
			author_arr[list_no] = auth;
			break;
		
		case 2:
			cout << "Edit book title: ";
			cin >> title;
			title_arr[list_no] = title;
			break;

		case 3:
			cout << "Edit book publisher: ";
			cin >> publ;
			publisher_arr[list_no] = publ;
			break;

		case 4:
			cout << "Edit book price: ";
			cin >> pr;
			price_arr[list_no] = pr;
			break;

		case 5:
			cout << "Edit book available stock: ";
			cin >> stck;
			stock_arr[list_no] = stck;
			break;

		case 6:
			break;

		default:
			cout << "Invalid input!! Please enter a number 1 to 6" << endl;
			break;
		}


	}while (entered_number !=6);

}

void deleteBook(int list_number){

	for (int i=0; i < 99; i++){
		if ( i >= list_number){
			author_arr[i] = author_arr[i+1];
			title_arr[i] = title_arr[i+ 1];
			publisher_arr[i] = publisher_arr[i+ 1];
			price_arr[i] = price_arr[i+ 1];
			stock_arr[i] = stock_arr[i+ 1];
		}

	}
	
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
		TempFile_03<< "\t\tOwnership: Subramaniam B(HDCSE105/53)\n";
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

void addSales(int booklistno, int count){
	soldBookListNumber[booklistno] = booklistno;
	soldBookAuthor[booklistno] = author_arr[booklistno];
	soldBookTitle[booklistno] = title_arr[booklistno];
	soldBookPrice[booklistno] = price_arr[booklistno];
	soldBookCount[booklistno] = count;
	sales[booklistno] = price_arr[booklistno] * count;
	totalSales += sales[booklistno];
	totalSalesAccumulation[booklistno] = totalSales;
}

void createSalestxt(){
	ofstream TempSales("salesdetails.txt");

	for (int i =0; i < 100; i++){
		if(soldBookCount[i] > 0){
			TempSales << "\n"<<soldBookListNumber[i] << "\t"<<soldBookAuthor[i] << "\t" << soldBookTitle[i] << "\tCount: " << soldBookCount[i] << "\tPrice: "<< soldBookPrice[i] <<"\tSales: " << sales[i] << "\tAccu.Sales: " << totalSalesAccumulation[i] << "\n";
		}
	}
	TempSales.close();
}

void viewSales(){
	string salestxt;

	ifstream MySales("salesdetails.txt");

	while (getline(MySales, salestxt)){
		cout << salestxt << "\n";
	}
	MySales.close();
}

void manageSales(){
	int select_no, booklistno, count;
	do {
		cout <<"\n\tPlease select a choice from menu below: ";
		cout << "\n\t\t1. Add a sale\n\t\t2. View sales details\n\t\t3. Back to previous menu\n";
		cout << "\n\t\tEnter a number: ";
		cin >> select_no;

		switch (select_no)
		{
		case 1:
			cout <<"\n\t\tEnter book list number of book sold: ";
			cin >> booklistno;
			cout <<"\n\t\tEnter number of books sold: ";
			cin >> count;
			addSales(booklistno, count);
			cout <<"\n\t\tSuccessfully entered a sale!!";
			cout <<"\n\t\t*****************************" << endl;
			break;

		case 2:
			createSalestxt();
			cout << "\nSALES DETAILS: \n";
			cout << "*************";
			viewSales();
			break;

		case 3:
			break;
		
		default:
			cout << "\n\t\tInvalid input!! Please enter number 1 to 3." << endl;
			break;
		}

	} while (select_no != 3);
}

//login function that returns true or false
void login(string& user, string& pw)
{	int choice_number;
	int position_number;

	string newUserName;
	string newPassWord;

	int newListNo;
	string newAuthor;
	string newTitle;
	string newPublisher;
	float newPrice;
	int newStock;

	int editListNo;
	int deleteListNo;

	createNewUsernamePassword(0, "admin", "0000");
	createUsernamePassword();	

	addNewBooks(1,"N.M.Stevenson","Wild Wild Dreams","Penguin ", 2400, 12);
	addNewBooks(2,"R. Gregor", "How to win friends", "McMillan", 3500, 15);
	addNewBooks(3, "M. Micheal", "Run Far Away From Her", "Mermaidz", 3200, 10);
	addNewBooks(4, "K. Krishna", "Power of Knowledge", "BBC Inc.", 2100, 4);
	addNewBooks(5, "K. Rowland", "Learn C++ the easy way", "Schuster", 5800, 18);
	createBooksAvailable();


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
							cout << "\t\t1. View available books\n\t\t2. Add a book\n\t\t3. Update a book details\n\t\t4. Delete a book\n\t\t5. Manage sales\n\t\t6. Register a new user\n\t\t7. Logout\n";
							do {
								error = 0;
								cout << "\n\tEnter your selection (number): ";
								cin >> choice_number;								
								cout << "\n\t*********************************" << endl;
								
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
									cout << "AVAILABLE BOOKS:- \n";								
									viewAvailableBooks();							
									break;

								case 2:
									cout << "Enter list number (0 to 99): ";
									cin >> newListNo;
									cout << "Enter author of new book: ";
									getline(cin, newAuthor);
									cout << "Enter title of new book: ";
									getline(cin, newTitle);
									cout << "Enter publisher of new book: ";
									getline(cin, newPublisher);
									cout << "Enter price of new book: ";
									cin >> newPrice ;
									cout << "Enter how many copies: ";
									cin >> newStock ;

									addNewBooks(newListNo, newAuthor, newTitle, newPublisher, newPrice, newStock);
									createBooksAvailable();									
									break;

								case 3:
									cout << "Enter the book list number to edit: ";
									cin >> editListNo;
									updateBook(editListNo);
									break;


								case 4:
									cout << "Enter the list number of book to be deleted (1-99): ";
									cin >> deleteListNo;

									deleteBook(deleteListNo);

								case 5:
									manageSales();
									break;									

								case 6:
												
									cout << "Enter position number (maximum 1-9): ";
									cin >> position_number;
									cout << "Enter new user username: ";
									cin>> newUserName;
									cout << "Enter new user password: ";
									cin >> newPassWord;
										
									createNewUsernamePassword(position_number, newUserName, newPassWord);									
									cout << "New user successfully registered" << endl;
									createUsernamePassword();			
									break;

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


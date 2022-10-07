#include <iostream>
#include <fstream>

using namespace std;

//global variables
int error;

//manage logins
bool logged_in;
string username[10];
string password[10];
void login(string& user, string& pw);

//Functions that creates text file and used by view functions
void createUsernamePassword();// text file containing list of users and passwords text file
void createBooksAvailable();// text file containing list of books available text file
void createCompanyDetails();//text file containing company details
void createSalestxt();//text file containing list of sales entered

//view company details function
void viewCompanyDetails();

//arrays containing book details
string author_arr[100];
string title_arr[100];
string publisher_arr[100];
float price_arr[100];
int stock_arr[100];

//View, add, update and delete book functions
void viewAvailableBooks();
void addNewBooks(int bookID, string author, string title, string publisher, float price, int stock);
void updateBook(int bookID);
void deleteBook(int bookID);

//register new user function
void createNewUsernamePassword(int position, string newuser, string newpassword);

//Manage Sales Functions
void manageSales();
void addSales(int bookID, int count);
void viewSales();

//Manage Sales Arrays
int soldBookID[100];
string soldBookAuthor[100];
string soldBookTitle[100];
int soldBookCount[100];
float soldBookPrice[100];
float sales[100];
float totalSalesAccumulation;

//Manage Sales Global Variable
float totalSales {0};

//MAIN FUNCTION
int main(int argc, char *argv[]){
	int choice_number;
	string userName, passWord;	

	cout << "\n\t\tWelcome to GENIUS BOOK!!\nUsing this software you can manage books in your bookshop\n";
	cout << "***** **** ******** *** *** ******** ***** ** *** *******" << endl;
	
	//Once program runs this do..while loop will run until exited.
	do {
		cin.clear();
		cout << "\n\n\tPlease select an option from the given menu below:\n\n";
		cout << "\t\t1. Login\n\t\t2. View Company Details\n\t\t3. Exit\n";	

		//Do..while loop to prevent exit from program if invalid input is given
		do {
			error = 0;
			cout << "\n\tEnter your selection (number): ";
			cin >> choice_number;
			
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input!!" << endl;
				error = 1;
				cin.clear();
				cin.ignore(50, '\n');
								
			}
		} while (error == 1);

		//functions for the choices given in main menu
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
				cout << "\n\tInvalid input!!. Enter number 1, 2 or 3.\n";
				cout << "\n\t***************************************"<< endl;				
				break;
		}
	} while (choice_number !=3);

	return 0;
	
}

//function to create a new username and password
void createNewUsernamePassword(int position, string newuser, string newpassword){
		username[position] = newuser;
		password[position] = newpassword;
}

//function to create text file containing username and password list
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


//function to create text file containing book details
void createBooksAvailable()
{
	
	ofstream TempFile_02("bookdetails.txt");
	
	//iterating through arrays to write on txt file
	for (int i=0; i < 100; i++)
	{
		if (stock_arr[i] > 0){
		TempFile_02 << "BookID: "<< i << "\n\tAuthor: " << author_arr[i] << "\n\tTitle: " << title_arr[i] << "\n\tPublisher: " << publisher_arr[i] << "\n\tPrice: " << price_arr[i] << "\n\tStock Available: " << stock_arr[i] << "\n";
		}
	
	}
	TempFile_02.close();
}


//function to add new book
void addNewBooks(int bookID, string author, string title, string publisher, float price, int stock){
	author_arr[bookID] = author;
	title_arr[bookID] = title;
	publisher_arr[bookID] = publisher;
	price_arr[bookID] = price;
	stock_arr[bookID] = stock;
}

//function to output choices to user to update book
void updateBook(int bookID){
	int entered_number;
	string auth, title, publ;
	float pr;
	int stck;
	do {
		cout << "\n\n\tPlease select an option from given menu below to edit:  \n";
		cout << "\t1. Author\n\t2. Title\n\t3. Publisher\n\t4. Price\n\t5. Stock\n\t6. Back to previous menu\n" << endl;		

			//for invalid input 
			do {
				error = 0;
				cout << "\n\tEnter your selection (number): ";
				cin >> entered_number;
				
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input!!" << endl;
					error = 1;
					cin.clear();
					cin.ignore(50, '\n');
									
				}
			} while (error == 1);


		switch (entered_number)
		{
		case 1:
			cout << "Edit author name: ";
			cin.ignore();
			getline(cin, auth);			
			author_arr[bookID] = auth;
			break;
		
		case 2:
			cout << "Edit book title: ";
			cin.ignore();
			getline(cin, title);	
			title_arr[bookID] = title;
			break;

		case 3:
			cout << "Edit book publisher: ";
			cin.ignore();
			getline(cin, publ);	
			publisher_arr[bookID] = publ;
			break;

		case 4:
			cout << "Edit book price: ";
			cin >> pr;
			price_arr[bookID] = pr;
			break;

		case 5:
			cout << "Edit book available stock: ";
			cin >> stck;
			stock_arr[bookID] = stck;
			break;

		case 6:
			break;

		default:
			cout << "Invalid input!! Please enter a number 1 to 6" << endl;
			break;
		}


	}while (entered_number !=6);

}

//function to delete book using list number of book
void deleteBook(int bookID){

	if (stock_arr[bookID] > 0){
	for (int i=0; i < 99; i++){
		if ( i >= bookID){
			author_arr[i] = author_arr[i+1];
			title_arr[i] = title_arr[i+ 1];
			publisher_arr[i] = publisher_arr[i+ 1];
			price_arr[i] = price_arr[i+ 1];
			stock_arr[i] = stock_arr[i+ 1];
		} 
	}	
	} else {
		cout <<"\nCannot delete!! Book does not exist in system." << endl;
	}
}

//function to view available books based on text file
void viewAvailableBooks(){
		string bookstxt;
		ifstream BookDetails("bookdetails.txt");
		while(getline(BookDetails, bookstxt)){
			cout<< bookstxt << "\n";
		}
		BookDetails.close();
}

//function to create text file containing company details
void createCompanyDetails(){
		ofstream TempFile_03("companydetails.txt");

		TempFile_03<<"\n\n\t\tCOMPANY DETAILS\n";
		TempFile_03<<"\t\t***************\n";
		TempFile_03<<"\t\tName: GENIUS BOOKS (pvt) Ltd.\n";
		TempFile_03<<"\t\tTrade Name: Genius Bookshop.\n";
		TempFile_03<< "\t\tAddress: 34, York Street\n";
		TempFile_03<< "\t\tCity: Colombo - 01\n";
		TempFile_03<< "\t\tTel-no: 078-XXX-XXXX\n";
		TempFile_03<< "\t\tChairman: Subramaniam B(HDCSE105/53)\n";
		TempFile_03 << "\t\tREG date: 09.12.2016\n";
		TempFile_03.close();
}

//function to view companydetails based on text file
void viewCompanyDetails(){
		string mytext;
		ifstream CompanyDetail("companydetails.txt");
		while (getline(CompanyDetail, mytext)){
			cout << mytext << "\n";
		}
		CompanyDetail.close();
}

//function to add sales
void addSales(int bookID, int count){
	soldBookID[bookID] = bookID;
	soldBookAuthor[bookID] = author_arr[bookID];
	soldBookTitle[bookID] = title_arr[bookID];
	soldBookPrice[bookID] = price_arr[bookID];
	soldBookCount[bookID] = count;
	sales[bookID] = price_arr[bookID] * count;
	totalSales += sales[bookID];
	totalSalesAccumulation = totalSales;
	stock_arr[bookID] -= count; 
}

//function to create text file containing the list of sales
void createSalestxt(){
	ofstream TempSales("salesdetails.txt");

	for (int i =0; i < 100; i++){
		if(soldBookCount[i] > 0){
			TempSales << "\nSold BookID: "<<soldBookID[i] << "\n\tAuthor: "<<soldBookAuthor[i] << "\n\tTitle: " << soldBookTitle[i] << "\n\tNumber of book sold: " << soldBookCount[i] << "\n\tPrice per book: "<< soldBookPrice[i] <<"\n\tTotal sales: " << sales[i] << "\n\nAccumulated sales (from all books): " << totalSalesAccumulation << "\n";
		}
	}
	TempSales.close();
}

//function to view sales details based on the text file
void viewSales(){
	string salestxt;

	ifstream MySales("salesdetails.txt");

	while (getline(MySales, salestxt)){
		cout << salestxt << "\n";
	}
	MySales.close();	
}

//function to give choice to users for managing sales
void manageSales(){
	int select_no, bookID, count;
	do {
		cout <<"\n\tPlease select a choice from menu below: ";
		cout << "\n\t\t1. Add a sale\n\t\t2. View sales details\n\t\t3. Back to previous menu\n";
		

		do {
				error = 0;
				cout << "\n\tEnter your selection (number): ";
				cin >> select_no;
				
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input!!" << endl;
					error = 1;
					cin.clear();
					cin.ignore(50, '\n');
									
				}
			} while (error == 1);

		switch (select_no)
		{
		case 1:
			cout <<"\n\t\tEnter BookID number of book sold: ";
			cin >> bookID;
			cout <<"\n\t\tEnter number of books sold: ";
			cin >> count;
			addSales(bookID, count);
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
createBooksAvailable();
}

//login function that logins and displays sub menu with choices to user
void login(string& user, string& pw)
{	int choice_number;
	int number_position;

	string newUserName;
	string newPassWord;

	int newListNo;
	string newAuthor;
	string newTitle;
	string newPublisher;
	float newPrice;
	int newStock;

	int editBookID;
	int deleteBookID;

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
									cout << "Enter a BookID number for new book (0 to 99): ";
									cin >> newListNo;
									cout << "Enter author of new book: ";
									cin.ignore();
									getline(cin, newAuthor);
									cout << "Enter title of new book: ";
									// cin >> newTitle;
									getline(cin, newTitle);
									cout << "Enter publisher of new book: ";
									// cin >> newPublisher;
									getline(cin, newPublisher);
									cout << "Enter price of new book: ";
									cin >> newPrice ;
									cout << "Enter how many copies: ";
									cin >> newStock ;

									addNewBooks(newListNo, newAuthor, newTitle, newPublisher, newPrice, newStock);
									createBooksAvailable();									
									break;

								case 3:
									cout << "Enter BookID number of the book to edit: ";
									cin >> editBookID;
									updateBook(editBookID);
									break;


								case 4:
									cout << "Enter BookID number of the book to delete: ";
									cin >> deleteBookID;
									deleteBook(deleteBookID);
									break;

								case 5:
									manageSales();									
									break;									

								case 6:
												
									cout << "Enter new user position number (between 1-9): ";
									cin >> number_position;
									cout << "Enter new user username: ";
									cin>> newUserName;
									cout << "Enter new user password: ";
									cin >> newPassWord;
										
									createNewUsernamePassword(number_position, newUserName, newPassWord);									
									cout << "New user successfully registered!!" << endl;
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



/* THE COPPPERBELT UNIVERSITY
   INTRODUCTION TO PROGRAMMING FUNDAMENTALS
   ASSIGNMENT 1
   ZIT Primary School Students Information System
   GROUP: 9
   GROUP MEMBERS: CLIVET LUNGU          20153390
				: CLEMENT MALAMA        20150066
				: MOSES KATONGO         20157681
				: ELDRIDGE JEMPA        20157992

   DUE DATE		: 21ST JUNE, 2021

 This program is the ZIT Primary School information system that will keep students records and their credentials and will do the following functions:
   1. Add New Pupil
   2. Delete Pupil
   3. Search for Pupil
   4. Edit Pupil record
   5. Display All Pupils by Grade

 Two teachers will only be able to perform the functions (3) and (5), while the Head-Teacher and the Deputy Head-Teacher will be able to perform all functions.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ncurses.h>


using namespace std;

// Prototypes
void retrieve_data();
void login(bool &, bool &);
int mainmenu();
void add_new_pupil();
void update_file();
void display_student_details();
void search();
void edit();
void delete_students();
void welcome();

// structure for student details
struct student_details
{
    long student_ID;
    string first_name;
    string surname;
    short age;
    short grade;
    string guardians_phone_number;
};

// Student details array
const int SIZE = 20;
student_details students[SIZE];

int rec_count = 0; //keeps track of actual number of records

// Main function
int main()
{
    system("cls");

    retrieve_data(); //get data from file and store in array

    int option;
    bool loged_in_as_admin = false, loged_in = false;

    login(loged_in_as_admin, loged_in); //login function call

    if(loged_in_as_admin == true || loged_in == true)
    {
        system("cls");

        do  // loops through switch statements which confirms the access privallages
        {
            option = mainmenu(); //sets option from the main menu to option
            switch (option)
            {
                case 1:
                if(loged_in_as_admin) // verification if the logged in user is a headteacher
                {
                    add_new_pupil(); // calls add new pupil function
                    system("cls");
                }
                else
                {
                    cout<<"Access denied! Only the Head and Deputy head teacher can add new pupil records\n\n";
                    cout<<"Press any key to go back to the main menu...";
                    getch();
                    system("cls");
                }
                break;

                case 2:
                if(loged_in_as_admin) // verification if the logged in user is a deputy headteacher.
                {
                    system("cls");
                    delete_students();  // calls the delete student function
                    getch();
                    system("cls");
                }
                else
                {
                    cout<<"Access denied! Only the Head and Deputy head teacher can delete pupil records\n\n";
                    cout<<"Press any key to go back to the main menu...";
                    getch();
                    system("cls");
                }

                break;

                case 3:
                search(); // calls search function
                getch();
                break;

                case 4:
                if(loged_in_as_admin)  // verification if the logged in user is a teacher.
                {
                    edit();     //calls the edit function
                    system("cls");
                }
                else
                {
                    cout<<"Access denied! Only the Head and Deputy head teacher can delete pupil records\n\n";
                    cout<<"Press any key to go back to the main menu...";
                    getch();
                    system("cls");
                }
                break;

                case 5:
                display_student_details(); //calls display student details function
                break;

                case 6:
                update_file(); //calls the update file function
                exit(0);
                break;
            }
        } while (option != 6);

    }

    return 0;
}


void login(bool &loged_in_as_admin, bool &loged_in)  //login function
{
    string username, username1, username2, username3, username4;  //string for storing the usernames and password
    string password, password1, password2, password3, password4;

    ifstream credentials("credentials.dat");  //opens file where passwords are stored

    while (credentials>>username1>>password1>>username2>>password2>>username3>>password3>>username4>>password4)  //accessing the usernames and functions

    if(credentials)
    {
        do
        {

            welcome(); //calls a welcome function

            cout<<"Log in with your username and password\n\n";
            cout<<"Enter your username: "; cin>>username;
            cout<<"Enter your password: "; cin>>password;

            // verification if passwords entered are correct
            if ((username == username1 && password == password1) || (username == username2 && password == password2))
            {
                loged_in_as_admin = true;
                return;
            }

            else if ((username == username3 && password == password3) || (username == username4 && password == password4))
            {
                loged_in = true;
                return;
            }

            else
            {
                cout<<"\nAccess denied! incorrect username or password!\n";
                cout<<"\nPress any key to try again";
                getch();
                system("cls");
            }


        } while(loged_in_as_admin == false && loged_in == false);

        credentials.close();
    }

    else
    {
        cout<<"Error opening credentials file!\n\n";
        exit(1);
    }

}


void retrieve_data()  // retrieves data from the file (function) and stores them in the array
{
    int row = rec_count;

    ifstream readfile("studentrecords.dat");

    if(readfile)
    {
        while(readfile>>students[row].student_ID>>students[row].first_name>>students[row].surname>>students[row].age>>students[row].grade>>students[row].guardians_phone_number)
        {
            rec_count++;
            row++;
        }
    }

    else
    {
        cout<<"Error opening student records file!\n\n";
        cout<<"Press any key to exit...";
        getch();
        exit(0);
    }
}


int mainmenu() // displays the main menu (function)
{
    system("cls");

    int option;

    cout << "\n\n\n";

    cout << "\t\t\t\t * * *  **** *      ****  ***   ***   ****    " << endl;

    cout << "\t\t\t\t * * * *     *     *     *   * * * * *        "<< endl;

    cout << "\t\t\t\t * * * ***** *     *     *   * * * * *****    " << endl;

    cout << "\t\t\t\t * * * *     *     *     *   * * * * *        " << endl;

    cout << "\t\t\t\t  ***   **** *****  ****  ***  * * *  ****    " << endl;

    cout<<endl;
    cout<<"\t\t\t\t============================================="<<endl;

    cout<<"\t\t\t\tZIT PRIMARY SCHOOL STUDENT INFORMATION SYSTEM"<<endl;

    cout<<"\t\t\t\t=============================================\n"<<endl;



    cout<< "\t\tMain Menu\n";
    cout<<"Press: \n";
    cout<<"1. To add new pupil\n";
    cout<<"2. To delete pupil\n";
    cout<<"3. To search for pupil\n";
    cout<<"4. To edit pupil record\n";
    cout<<"5. To display all pupils by grade\n";
    cout<<"6. To exit and update file\n";

    cout<<"\nchoice: ";
    cin>>option;

    if(option>6||option<1)
    {
        cout<<"Invalid option\n";
        getch();
        system("cls");
        mainmenu();
    }

    return option;
}


void add_new_pupil()  // allows the head teacher and deputy to add a pupil (function)
{
    char option;
    bool found;
    long ID;

    if(rec_count != SIZE)
    {
        for(int row = rec_count + 1; row < SIZE; row++)
        {
            if(students[row].student_ID != 0)
            {
                continue;
            }

            else
            {
                system("cls");

                do
                {
                    cout<<"Enter pupil ID: "; cin>>ID;

                    if(ID < 1)
                    {
                        continue;
                    }

                    //checking if entered ID already exists
                    for(int rows = 0; rows < SIZE; rows++)
                    {
                        if(ID == students[rows].student_ID)
                        {
                            cout<<"Pupil ID already exists! Please enter another ID\n";
                            found = true;
                            break;
                        }

                        else
                        {
                            found = false;
                        }

                    }

                    if(found == false)
                    {
                        students[row].student_ID = ID;
                        break;
                    }

                } while (found == true);

                //assigns the input to the array

                cout<<"Enter first name: "; cin>>students[row].first_name;
                cout<<"Enter surname: "; cin>>students[row].surname;
                cout<<"Enter age: "; cin>>students[row].age;
                do
                {
                    cout<<"Enter grade: "; cin>>students[row].grade;
                    if (students[row].grade < 1 || students[row].grade>2)
                    {
                        cout << "grade should be 1 or 2 !"<<endl;
                    }

                } while (students[row].grade < 1 || students[row].grade > 2);

                cout<<"Enter guardian's phone number: "; cin>>students[row].guardians_phone_number;

                rec_count++;

                cout<<"\nSuccessfully added new pupil!\n\n";
                cout<<"Press y to continue or any other key to go back to the main menu: "; cin>>option;

                system("cls");

                if(option == 'y' || option == 'Y')
                    continue;
                else
                    break;
            }
        }
    }

    else
    {
        cout<<"Maximum number of pupils reached delete pupil to add a new pupil!";
        getch();
    }
}


void display_student_details() // Displays students the screen
{
    int option;
    char option1;

    if(rec_count > 0)
    {
        do
        {

            do
            {
                system("cls");

                cout<<"Press: \n";
                cout<<"1. To Display student records for all grades \n";
                cout<<"2. To Display grade 1 student records \n";
                cout<<"3. To Display grade 2 student records \n";
                cout<<"4. To Go back to the main menu\n";
                cout<<"\nchoice: ";
                cin>>option;

            } while (option < 1 || option > 4);

            switch(option)
            {
                case 1:  // displays all pupils
                system("cls");
                cout << "===============================================================================================\n";
                cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;
                cout << "===============================================================================================\n";
                for(int row = 0; row < SIZE; row++)
                {
                    if(students[row].student_ID != 0)
                    {
                        cout<<left<<setw(15)<<students[row].student_ID;
                        cout<<left<<setw(15)<<students[row].first_name;
                        cout<<left<<setw(15)<<students[row].surname;
                        cout<<left<<setw(15)<<students[row].age;
                        cout<<left<<setw(15)<<students[row].grade;
                        cout<<left<<setw(15)<<students[row].guardians_phone_number<<endl;
                    }

                    else
                    {
                        continue;
                    }
                }

                case 2:  // displays grade one's
                system("cls");
                cout << "===============================================================================================\n";
                cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;
                cout << "===============================================================================================\n";
                for(int row = 0; row < SIZE; row++)
                {
                    if(students[row].student_ID != 0)
                    {
                        if(students[row].grade == 1)
                        {
                            cout<<left<<setw(15)<<students[row].student_ID;
                            cout<<left<<setw(15)<<students[row].first_name;
                            cout<<left<<setw(15)<<students[row].surname;
                            cout<<left<<setw(15)<<students[row].age;
                            cout<<left<<setw(15)<<students[row].grade;
                            cout<<left<<setw(15)<<students[row].guardians_phone_number<<endl;
                        }

                        else
                        {
                            continue;
                        }

                    }

                    else
                    {
                        continue;
                    }
                }
                break;

                case 3:  // displays grade two's
                system("cls");
                cout << "===============================================================================================\n";
                cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;
                cout << "===============================================================================================\n";
                for(int row = 0; row < SIZE; row++)
                {
                    if(students[row].student_ID != 0)
                    {
                        if(students[row].grade == 2)
                        {
                            cout<<left<<setw(15)<<students[row].student_ID;
                            cout<<left<<setw(15)<<students[row].first_name;
                            cout<<left<<setw(15)<<students[row].surname;
                            cout<<left<<setw(15)<<students[row].age;
                            cout<<left<<setw(15)<<students[row].grade;
                            cout<<left<<setw(15)<<students[row].guardians_phone_number<<endl;
                        }

                        else
                        {
                            continue;
                        }

                    }

                    else
                    {
                        continue;
                    }


                }
                break;

                case 4:
                return;
            }

            cout << "===============================================================================================\n";
            cout<<"\nEnter Y to go back to the previous screen or any key to go back to the main menu: ";
            cin>>option1;

        } while (option1 == 'Y' || option1 == 'y');

    }

    else
    {
        cout<<"No student records found!\n\n";
        cout<<"Press any key to go back to the main menu...";

        return;
    }

}


void update_file() // sends data to the text file from the array
{
    ofstream inputfile;
    inputfile.open("studentrecords.dat");

    if(inputfile)
    {
        for(int row = 0; row < SIZE; row++)
        {
            if(students[row].student_ID != 0)
            {
                inputfile<<left<<setw(15)<<students[row].student_ID;
                inputfile<<left<<setw(15)<<students[row].first_name;
                inputfile<<left<<setw(15)<<students[row].surname;
                inputfile<<left<<setw(15)<<students[row].age;
                inputfile<<left<<setw(15)<<students[row].grade;
                inputfile<<left<<setw(15)<<students[row].guardians_phone_number<<endl;
            }

            else
            {
                continue;
            }

        }
    }

    cout<<"\nSuccessfully updated student records!\n\n";

    inputfile.close();
}

// searches for pupils in the file
void search()
{
    long ID;
    bool found = false;
    char option;

    system("cls");

    cout<<"Enter student ID: "; cin>>ID;

    //linear searching
    for(int row = 0; row < SIZE; row++)
    {
        if(ID == students[row].student_ID)  //checks
        {
            system("cls");

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<students[row].student_ID<<left<<setw(15)<<students[row].first_name<<left<<setw(15)<<students[row].surname<<left<<setw(15)<<students[row].age<<left<<setw(15)<<students[row].grade<<left<<setw(15)<<students[row].guardians_phone_number<<endl;

            cout << "===============================================================================================\n";

            found = true;

            cout<<"Press any key to go back to the main menu...";

            break;

        }
    }

    if(!found)
    {
        cout<<"\nNo student records found!\n\n";
        cout<<"Press y to enter ID again or any other key to go back to the main menu: "; cin>>option;

        if(option == 'y' || option == 'Y')
        {
            search();
        }

        else
        {
            return;
        }
    }


}


void edit ()  // this function edits pupils details only by the head teacher and deputy
{
    long ID;
    bool found = false;
    char option, option3;
    int  option2;
    int counter = 0; //keeps track of index of student to be deleted;

    system("cls");

    cout<<"Enter student ID: "; cin>>ID;

    //linear searching
    for(int row = 0; row < SIZE; row++)
    {
        if(ID == students[row].student_ID)
        {
            system("cls");

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<students[row].student_ID<<left<<setw(15)<<students[row].first_name<<left<<setw(15)<<students[row].surname<<left<<setw(15)<<students[row].age<<left<<setw(15)<<students[row].grade<<left<<setw(15)<<students[row].guardians_phone_number<<endl;

            cout << "===============================================================================================\n";

            found = true;

            break;

        }

        else
        {
            counter ++;
        }
    }

    if(!found)
    {
        cout<<"\nNo student records found!\n\n";
        cout<<"Press y to enter ID again or any other key to go back to the main menu: "; cin>>option;

        if(option == 'y' || option == 'Y')
        {
            search();
        }

        else
        {
            return;
        }
    }

    else
    {

        do
        {
            // asks the user which  detail they want to edit
            do
            {
                cout << "\nPress: \n";
                cout << "1. To edit ID Number"<< endl;
                cout << "2. To edit First name"<< endl;
                cout << "3. To edit Surname"<< endl;
                cout << "4. To edit age "<< endl;
                cout << "5. To edit grade"<< endl;
                cout << "6. To edit guardian's phone number"<< endl;
                cout << "7. To return to the main menu"<<endl<<endl;
                cout << "choice: "; cin>>option2;

                if(option2 < 1 || option2 > 7)
                {
                    cout<<"\nInvalid input! Please enter a valid option\n";
                    getch();
                    system("cls");
                }

            } while (option2 < 1 || option2 > 7);

            system("cls");

            switch(option2)  // edits old details and updates them to the new details
            {
                case 1:
                cout<<"Enter new ID: ";
                cin>>students[counter].student_ID;
                break;

                case 2:
                cout<<"Enter new first name: ";
                cin>>students[counter].first_name;
                break;

                case 3:
                cout<<"Enter new surname: ";
                cin>>students[counter].surname;
                break;

                case 4:
                cout<<"Enter new age: ";
                cin>>students[counter].age;
                break;

                case 5:
                cout<<"Enter new grade: ";
                cin>>students[counter].grade;
                break;

                case 6:
                cout<<"Enter new guardian's phone number: ";
                cin>>students[counter].guardians_phone_number;
                break;

                case 7:
                return;

            }

            cout<<"\nEnter Y to continue editing or any key to go back to the main menu... "; cin>>option3;

            system("cls");


        } while (option != 'y' && option != 'Y');

    }

}


void delete_students()  // deletes students from the file
{
    long ID;
    bool found = false;
    int option;
    int counter = 0;

    system("cls");

    cout<<"Enter student ID: "; cin>>ID;

    //linear searching
    for(int row = 0; row < SIZE; row++)
    {
        if(ID == students[row].student_ID)
        {
            system("cls");

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<"Pupil ID"<<left<<setw(15)<<"First name"<<left<<setw(15)<<"surname"<<left<<setw(15)<<"Age"<<left<<setw(15)<<"Grade"<<left<<setw(15)<<"Guardians cell number"<<endl;

            cout << "===============================================================================================\n";

            cout<<left<<setw(15)<<students[row].student_ID<<left<<setw(15)<<students[row].first_name<<left<<setw(15)<<students[row].surname<<left<<setw(15)<<students[row].age<<left<<setw(15)<<students[row].grade<<left<<setw(15)<<students[row].guardians_phone_number<<endl;

            cout << "===============================================================================================\n";

            found = true;

            break;

        }

        else
        {
            counter++;
        }
    }

    if(!found)
    {
        cout<<"\nNo student records found!\n\n";
        cout<<"Press y to enter ID again or any other key to go back to the main menu: "; cin>>option;

        if(option == 'y' || option == 'Y')
        {
            delete_students();  //calls delete function
        }

        else
        {
            return;
        }
    }

    else
    {
        cout<<"Press 1. to confirm deletion and 2. to cancel: "; cin>>option;

        switch(option)
        {
            case 1:
            students[counter].student_ID = 0;
            break;

            case 2:
            return;

        }

        cout<<"\nSuccessfully deleted student record!\n\n";
        cout<<"Press any key to go back to the main menu";

        return;
    }


}

void welcome()  // displays a welcome message
{
    cout << "\n\n\n";

  			cout << "\t===============================================================================================" << endl;

 			cout << "\t**** * *****   ****  ****   *  *        *     *     *****  *     *    ****    ***** *      *    " << endl;

 			cout << "\t  *  *   *     *   * *   *  *  * *    * *    * *    *    *  *   *    *      *       *      *    "<< endl;

			cout << "\t *   *   *     ****  ****   *  *  *  *  *   * * *   ****      *       ****  *       ********    " << endl;

 			cout << "\t*    *   *     *     *  *   *  *   *    *  *     *  *  *      *           * *       *      *    " << endl;

 			cout << "\t**** *   *     *     *    * *  *        * *       * *    *    *       ****    ***** *      *    " << endl;

 			cout << "\t===============================================================================================\n\n" << endl;

}




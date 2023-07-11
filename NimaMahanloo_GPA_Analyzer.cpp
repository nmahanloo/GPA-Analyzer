// NimaMahanloo_GPA_Analyzer.CPP
// Nima Mahanloo - CISP 400
// 02/06/2018
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <windows.h>
using namespace std;

// The program main class
class grade
{
    // Public members
    public:
        // Default constructor
        grade();
        // Destructor
        ~grade();
        // Char function which provide program's main greeting
        char mainMenu(bool);
        // Void function to add new node to list for new course
        void addCourse (grade* (&curr));
        // Void function as mutator to set object's (course) private members score and unit number
        void setScore();
        // Integer function to access course unit number value as private member
        int getUnitNo();
        // Void function to display and save all data in output text file
        void printGrade(grade* head);
        // Void function to display help
        void help();
        // Void function to delete linked list and free heap and memory spaces
        void delList(grade* (&head));
    // Private members
    private:
        // Declare a double variable for course unit number as private member
        double unitNo;
        // Declare an integer variable for course final score as private member
        int score;
        // Declare a double variable for calculated unit * score value
        double unitScore;
        // Create a pointer object from class for next node address
        grade* next;
};
// Default constructor to initialize class members
grade::grade()
{
    unitNo = 0.0;
    score = -1;
    unitScore = 0.0;
    next = nullptr;
}
// Destructor to delete class pointer member and free memory
grade::~grade()
{
    delete next;
    next = nullptr;
}
// Char function as program greeting and main menu
char grade::mainMenu(bool firstRun)
{
    // Declare and initialize boolean variable as error flag for user input character
    bool inputError = false;
    // Declare and initialize character variable for main menu user input
    char user_menu = '?';
    // A condition to check first moment of program's run
    if (firstRun == true)
    {
        // Display the program title
        cout << "GPA Analyzer" << endl;
    }
    // Display program main menu options
    cout << endl << "1 - help" << endl << "2 - enter grade" << endl << "3 - quit" << endl << "> ";
    while (user_menu != '1' && user_menu != '2' && user_menu != '3')
    {
        // A condition to check user input verification
        if (inputError == true)
        {
            // Display an error message to user about invalid user entered number
            cout << "Invalid number! enter again > ";
        }
        // Get user choice input
        cin >> user_menu;
        // Set error flag
        inputError = true;
    }
    // Check user input value verification
    assert(user_menu != '?');
    // Return user entered character to main menu
    return user_menu;
}
// Void function to add new node (new course) to linked list
void grade::addCourse (grade* (&curr))
{
    // create new node for new course
    curr->next = new grade;
    // change list current pointer to new node
    curr = curr->next;
}
// Void function to set unit number, score and unit * score members
void grade::setScore()
{
    // Declare and initialize a boolean function as invalid input flag
    bool error = false;
    // Prompt a request message to user to enter course units number
    cout << "Please enter unit number > ";
    // A conditional loop to verify user entered number about course units number
    while ((unitNo > 15.0) || (unitNo < 0.5))
    {
        // If error flag is ON show an error message to user about invalid entered number
        if (error == true)
        {
            cout << "Invalid number! Enter again > ";
        }
        // Get course units number in
        cin >> unitNo;
        // Set error flag
        error = true;
    }
    // Reset error flag
    error = false;
    // Prompt a request message to user to input course score number
    cout << "Please enter score number > ";
    // A conditional loop to verify user input about course score
    while ((score < 0) || (score > 100))
    {
        //  A condition to check user input error flag status
        if (error == true)
        {
            // Display error message to user about user entered invalid number
            cout << "Invalid number! Enter again > ";
        }
        // Get course final score in
        cin >> score;
        // Set error flag
        error = true;
    }
    // Calculate and set unit * score value
    unitScore = unitNo * score;
}
// Integer function to access and return class private member value to main module
int grade::getUnitNo()
{
    return unitNo;
}
// Void function to show help text about main menu
void grade::help()
{
    cout << endl << "Guide: Please enter your all courses unit numbers and final scores one by one by enter '2'" << endl
    << setw(90) << setfill(' ') << right << "several times as necessary then enter '3' to see results and quit from application." << endl
    << setw(90) << setfill(' ') << right << "All input & output data will save on 'grade.txt' file inside application directory." << endl;
}
// Void function to display and save linked list nodes data (Courses units, scores and total calculated GPA) to output file
void grade::printGrade(grade* head)
{
    // Declare and initialize a double for total GPA
    double GPA = 0.0;
    // Declare and initialize a character variable for GPA grade letter
    char gpaLetter = '?';
    // Declare and initialize integers for courses total units number, total scores sum and display's list row number
    int units = 0, scores = 0, row = 1;
    // Declare an output fstream to write data on output file
    ofstream write("grade.txt");
    // To check output file is open or not
    assert(write.is_open());
    // create a pointer object from class as list current node pointer
    grade* curr = head;
    // A condition to check current node is not empty
    if (curr->unitNo != 0.0)
    {
        // Display list data and Results to user
        cout << endl << "Results >" << endl << endl;
        while (curr != nullptr)
        {
            // Write data to file
            write << curr->unitNo << " " << curr->score << " " << curr->unitScore << endl;
            // To check last writing process on file was successful or not
            assert(write.good());
            // Display current node (course) data
            cout << row << "- Unit : " << curr->unitNo <<  ", Final Score : " << curr->score << ", Units x Score : " << curr->unitScore << endl;
            // Sum courses units
            units += curr->unitNo;
            // Sum Course units * courses
            scores += curr->unitScore;
            // Change list current pointer to next node (course)
            curr = curr->next;
            // Add display row show number
            row ++;
        }
        // Calculate GPA
        GPA = scores / units;
        // Check GPA correctness
        assert(GPA <= 100.00);
        // Convert GPA grade number to letter
        if (GPA >= 90)
        {
            gpaLetter = 'A';
        }
        else if (GPA >= 80)
        {
            gpaLetter = 'B';
        }
        else if (GPA >= 70)
        {
            gpaLetter = 'C';
        }
        else if (GPA >= 60)
        {
            gpaLetter = 'D';
        }
        // Write GPA number as data on output file
        write << GPA;
        // Display calculated GPA
        cout << endl << "GPA is : " << GPA;
        if (GPA < 60)
        {
            cout << " or F and lower"<< endl;
        }
        else
        {
            cout << " or " << gpaLetter << endl;
        }
    }
    // Close output file
    write.close();
}
// Void Function to delete linked list
void grade::delList(grade* (&head))
{
    grade* temp = nullptr;
    while (head != nullptr)
    {
      temp = head;
      head = head->next;
      delete temp;
      temp = nullptr;
      assert(temp == nullptr);
    }
}

int main()
{
    // Change system consul back and font colors
    system ("color 17");
    // Declare and initial boolean variable for program running first moment
    bool firstRun = true;
    // Declare and initial a character variable for main menu (program greeting) user input
    char user_menu = '?';
    // Create the class pointer object as courses linked list
    grade* firstScore = new grade;
    // Create the class pointer object as list current pointer
    grade* currScore = firstScore;
    // A conditional loop until user quit
    while (user_menu != 'q')
    {
        // Show main menu to user and get user input character
        user_menu = currScore->mainMenu(firstRun);
        // To check user input value
        assert (user_menu == '1' || user_menu == '2' || user_menu == '3');
        // Switch for main menu user input value
        switch (user_menu)
        {
            // For value '1' as help
            case '1':
                {
                    // Show help text to user
                    currScore->help();
                    break;
                }
            // For value '2' to add new course (node) to list
            case '2':
                {
                    // If current node is not empty
                    if (currScore->getUnitNo() > 0)
                    {
                        // Add new node to list
                        currScore->addCourse(currScore);
                    }
                    // Set new course data
                    currScore->setScore();
                    // Check to verify new course assigning process
                    assert(currScore->getUnitNo() > 0);
                    break;
                }
            case '3':
                {
                    // Display and write courses data on file
                    currScore->printGrade(firstScore);
                    // Delete list and free memory
                    currScore->delList(firstScore);
                    // Check Delete process result
                    assert(firstScore == nullptr);
                    // Set user input variable to quit
                    user_menu = 'q';
                    break;
                }
        }
        // Set first running moment flag OFF
        firstRun = false;
    }
    return 0;
}

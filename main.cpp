/**************************************************************************************
Program:     Math Tutor V6
Section:     4 - 1:00pm
Programmers: Bret (Kirby) Dunker
Date:        11.23.2024
Version:     6
GitHub URL:  https://github.com/KirbyD-YEAH/MathTutorV6.git
Description:  This program is an easy Math Tutor. It is a program that is intended to
            help small children do simple math problems. This program will ask the
            user to enter their name, and then ask them a math question until they
            don't want more. The math program is able to tell if the input is a number
            or not. It does all 4 math operations to help kids in all math aspects.
            This program also levels up every three correct answers and levels down
            every three wrong answers. After every question, the program will
            ask the user if they want to continue. The program will only end when
            the user says that they want to stop. At the end of the program, there's
            a summary of what questions were asked and how many attempts it took to
            answer or if it's incorrect. Also listed will be the total amount of
            questions, correct answers, incorrect answers, and an average of how may
            were correct. In version 5, functions are added to the code to reduce
            redundancy.
**************************************************************************************/

#include <iostream> // This allows the programmer the use of cins and couts
#include <string>   // needed for the user's name
#include <ctime>    // Needed for the rand() commands to work
#include <cstdlib>  // used for the random number generator
#include <vector>   // needed for the use of vectors in the program
#include <iomanip>  // Needed to use the setw

#include "math_tutor.h" // header file with required prototypes

using namespace std;

/*The main program that keeps looping until the user wants to quit*/

int main() {
    //Constant variables
    const int NUM_ATTEMPT = 3; // # of attempts that the user has on a question

    //range of possible numbers for question.
    int questionRange = 10;

    //variable that holds the symbol for the math problem
    char mathSymbol = '?';
    int mathLevel = 1;

    //These are the variables needed for the program to work
    string userName = "?";
    string userInput = " ";
    int leftNum = 0;
    int rightNum = 0;
    
    //Used to determine if user got the question correct
    int correctAns = 0;
    //Used to keep track of total correct and wrong answers the user has gotten
    int correctNum = 0;
    int incorrectNum = 0;

    vector<vector<int>> questions; //Declares the vector for use in the program


    //The srand() and time restart the rand() so the numbers and equation sign are different everytime
    srand(time(NULL));

    DisplayGameIntro(); //This call displays the game intro

    userName = GitUserName(); //This call contains the function to get the user's name

        try {
                mathLevel = LoadPreviousGame(userName, questions);
        } catch (runtime_error &e) {
                cout << endl;
                cout << e.what() << endl;
        }




    /*start of do while for the main part of the code. Also contains the function call to generate a random question
     Also contains the code needed for the GiveThreeAttempts to work correctly */

    do {

        vector<int> row = GenerateRandomQuestion(mathLevel);
        leftNum = row[1];
        mathSymbol = static_cast<char>(row[2]);
        rightNum = row[3];
        correctAns = row[4];

        if (!GiveThreeAttempts(userName, correctAns, leftNum, mathSymbol, rightNum, NUM_ATTEMPT, correctNum, incorrectNum, row)) {
           row.push_back(0);
        }

        questions.push_back(row); //Ends the 2D vector "questions"

        //This call is what helps the leveling up/down logic
        CheckForLevelChange(correctNum, incorrectNum, mathLevel, questionRange);

        getline(cin, userInput); // clearing the newline from the input buffer

        userInput = YesNoQuestion(userName + ", do you want to continue (y=yes | n=no)?"); //Calls the function that asks the user if they'd like to play again

    } while (userInput == "yes" || userInput == "y");

   DisplaySummaryReport(questions, correctNum, incorrectNum); //This call displays the function containing the summary report

    try {
            SaveCurrentGame(userName, questions);
    } catch (runtime_error &e) {
            cout << e.what() << endl;
            cout << "Sorry, unable to save the game." << endl;
    }

    // The end of program message
    // Used the '|' for a border for first and last sections
    cout << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|                                                                      |"
            << endl;
    cout << "|         Thank you for trying out Version 5 of the Math Tutor!        |"
            << endl;
    cout << "|                                                                      |"
            << endl;
    cout << "|                        ------------------                            |"
            << endl;
    cout << "|                        | End of Program |                            |"
            << endl;
    cout << "|                        ------------------                            |"
            << endl;
    cout << "|                                                                      |"
            << endl;
    cout << "------------------------------------------------------------------------"
            << endl;
    cout << "************************************************************************"
            << endl;
    return 0; //ends the program how it should with a 0
}








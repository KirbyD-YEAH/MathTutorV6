/**************************************************************************************
Program:     Math Tutor V6
Section:     4 - 1:00pm
Programmers: Bret (Kirby) Dunker
Date:        11.23.2024
Version:     6
GitHub URL:  https://github.com/KirbyD-YEAH/MathTutorV6.git
Description:  The functions for the math tutor program that matches the prototypes
**************************************************************************************/

#include "math_tutor.h"
#include <iostream> // This allows the programmer the use of cins and couts
#include <string>   // needed for the user's name
#include <cstdlib>  // used for the random number generator
#include <limits>   // used for the numeric_limits
#include <vector>   // needed for the use of vectors in the program
#include <iomanip>  // Needed to use the setw
#include <fstream>  // for reading and writing to a file
#include <stdexcept> // for throwing errors back to main

using namespace std;

const string FILE_NAME = "mathtutor.txt";

/*
 1. Displays the intro to the game, including math facts, the header, and the
 welcome message.
 2. There are no parameters
 3. Doesn't return anything
 4. The function prints the intro for the game containing
*/
void DisplayGameIntro() {
    // The '*' represents the beginning and end of the programs
    // The '-' represents the borders for differnt sections of the program
    cout << "***********************************************************************"
            << endl;
    cout << "-----------------------------------------------------------------------"
            << endl;
    cout << "|           __  __       _   _       _____      _                     |"
            << endl;
    cout << "|          |  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __         |"
            << endl;
    cout << "|          | |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__|        |"
            << endl;
    cout << "|          | |  | | (_| | |_| | | |   | || |_| | || (_) | |           |"
            << endl;
    cout << "|          |_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|           |"
            << endl;
    cout << "|                                                                     |"
            << endl;
    cout << "-----------------------------------------------------------------------"
            << endl;
    cout << "|                    This is the Silly Math Tutor                     |"
            << endl;
    cout << "-----------------------------------------------------------------------"
            << endl;

    //questions go here
    cout << "Fun Math Facts:" << endl;
    cout <<
            " * There is no roman numeral for zero.                                                                                  "
            << endl;
    cout <<
            " * There is an infinite amount of numbers between every number we normally use.                                         "
            << endl;
    cout <<
            " * The symbol for division is also known as Obelus.                                                                     "
            << endl;
    cout <<
            " * 42 is the answer to life, the universe and everything according to Douglas Adam's Hitchhiker's Guide to the Galaxy.  "
            << endl;
    cout <<
            " * Math was invented by John Math in the year 1 when he decided to figure out what came after one.                      "
            << endl;
    cout <<
            " * If you put the numbers 8 and 7 next to each other and turn your head to the left it will make a plague doctor mask.  "
            << endl;
    cout <<
            " * The word 'one' is the only number that is spelled in descending order.                                               "
            << endl;
    cout <<
            " * There are at least two people in the world who knows what 6 + 9 + 6 * 9 equals.                                      "
            << endl;
    cout << endl;
    cout << "------------------------------------------------------------------------" << endl;
    return;
}

/*
 1. Asks for the user's name, stores it, and displays the welcome message
 2. There are no parameters
 3. returns the string userName
 4. This function asks the user for their name, reads the input, and returns the name as a string.
*/
string GitUserName() {
    string userName = "?";
    // Prompt the user for their name
    cout << "What is your name: ";
    getline(cin, userName);
    cout << endl;
    // Welcome the user to the game
    cout << "Welcome " + userName + ", Thank you for trying Math Tutor Version 6.0 !!!" << endl;
    cout << endl;
    return userName;
}

/*
 1. Generates a random math question based on the level they're on.
 2. The mathLevel parameter which is the current difficulty
 3. Returns a vector containing: mathLevel, leftNum, mathSymbol, rightNum, and correctAns
 4. The function randomly selects a math operation and generates a question that corresponds with two random numbers.
*/
vector<int> GenerateRandomQuestion(int mathLevel) {
    enum MathType { MT_ADD, MT_SUB, MT_MUL, MT_DIV };
    MathType mathType;
    char mathSymbol = '?';
    string userInput = "";
    int leftNum = 0;
    int rightNum = 0;
    int questionRange = 10;
    int temp = 0;
    int correctAns = 0;

    //allows to randomize the math type
    mathType = static_cast<MathType>(rand() % 4);
    leftNum = rand() % questionRange + 1;
    rightNum = rand() % questionRange + 1;

    //this is a switch that determines what math equation the user gets
    switch (mathType) {
        case MT_ADD: //Addition
            mathSymbol = '+';
            correctAns = leftNum + rightNum;
            break;
        case MT_SUB: //Subtraction
            if (leftNum < rightNum) {
                temp = leftNum;
                leftNum = rightNum;
                rightNum = temp;
                correctAns = leftNum - rightNum;
            } else {
                correctAns = leftNum - rightNum;
            }
            mathSymbol = '-';
            break;
        case MT_MUL: //Multiplication
            correctAns = leftNum * rightNum;
            mathSymbol = '*';
            break;
        case MT_DIV: //Division
            correctAns = leftNum;
            leftNum *= rightNum;
            mathSymbol = 246; // This number outputs the divide symbol
            break;
        default: // If an error occurs, this lets the user know who to contact
            cout << "Invalid Question Type: " << mathType << endl;
            cout << "Please contact Kirby Dunker. " << endl;
            throw runtime_error("Invalid Math Type: " + mathType);
    } //End of switch

    //Declares and initializes  the vector
    return {mathLevel, leftNum, mathSymbol, rightNum, correctAns};
}

/*
 1. Asks the user for their answer and makes sure their input is valid
 2. No parameters
 3. Returns the users answer
 4. This function repeatedly asks the user for a valid input.
*/
int GetNumericValue() {
    int userAns;
    /* This while statement lets the user know that they didn't type a number
               and asks them to retry the input */
    while (!(cin >> userAns)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!! ";
        cout << "Please enter a number: ";
    }
    return userAns;
}

/*
 1. Gives the user a question as well as three attempts to answer correctly
 2. Parameters include: correctAns, leftNum, mathSymbol, rightNum, NUM_ATTEMPT, correctNum, incorrectNum, and the row.
 3. Returns a bool that is true of the answer was correct along with amount of attempts
 4. This fucntion presents a question and gives the user three attempts. If correct,
 correct amount is incremented and if not, the correct answer is revealed
*/
bool GiveThreeAttempts(string userName, int correctAns, int leftNum, char mathSymbol, int rightNum, int NUM_ATTEMPT,
                       int &correctNum, int &incorrectNum, vector<int> &row) {
    int userAns = 0;
    bool isCorrect = false;
    int mathLevel = 1;
    //These are the variables needed for the program to work


    //Used to change the font color
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string DEFAULT = "\033[0m";
    // display the math question and get the user's guess
    for (int i = 1; i <= NUM_ATTEMPT; i++) {
        cout << "[ Level " << mathLevel << " ] " << userName << ", what is " << leftNum << " " << mathSymbol << " "
                << rightNum << " = ";

        userAns = GetNumericValue();

        /* The if statement is used to determine if the users answer is correct,
           If it is than the output will be displayed in green font */
        if (userAns == correctAns) {
            cout << GREEN;
            cout << "   You got the answer " << userAns << " which is correct!!:)" << DEFAULT << endl << endl;
            correctNum++;
            row.push_back(i);
            break;
        } else {
            /* This states that the user has gotten all of their possible tries incorrect
               and then displays the correct answer to the math question */
            if (userAns != correctAns && i == NUM_ATTEMPT) {
                cout << "    Your answer " << RED << userAns << " is incorrect :(" << endl;
                cout << DEFAULT << "    The correct answer was " << GREEN << correctAns << DEFAULT << endl << endl;
                incorrectNum++;
                i = 0;
                row.push_back(i);
                break;
            }
            /* This states that the user's answer is incorrect and displays it in red font as
               well as stating how many attempts the user has left */
            else {
                cout << "   Your answer " << RED << userAns << " is incorrect :(" << DEFAULT << endl;
                cout << "   You have " << NUM_ATTEMPT - i << " attempts left." << endl;
                cout << endl;
            }
        }
    }
    return isCorrect;
}

/*
 1. This determines if the user should level up or down based on their performance and adjusts the level accordingly
 2. Parameters include correctNum, incorrectNum, mathLevel, and questionRange
 3. Doesn't return anything
 4. This function checks the user's performance. 3 correct answers levels them up and 3 incorrect levels them down. Also
 adjusts the mathLevel and the range of numbers
*/
void CheckForLevelChange(int &correctNum, int &incorrectNum, int &mathLevel, int &questionRange) {
    const int LEVEL_RANGE_CHANGE = 10; // The range in which the range of numbers change when leveling up/down
    if (correctNum == 3) {
        //levels up the user
        mathLevel++;
        correctNum = 0;
        incorrectNum = 0;
        questionRange += LEVEL_RANGE_CHANGE;
        cout << "You leveled up. Yippee!!" << endl;
        cout << "You are on Level: " << mathLevel << endl;
    } else if ((incorrectNum == 3) && (mathLevel != 1)) {
        //levels down the user
        mathLevel--;
        correctNum = 0;
        incorrectNum = 0;
        questionRange -= LEVEL_RANGE_CHANGE;
        cout << "You leveled down. :( " << endl;
        cout << "You are on Level: " << mathLevel << endl;
    }
}

/*
 1. Asks the user if they'd like to continue playing or exit
 2. Parameter userName
 3. Returns a string of the user's choice to continue or not
 4. This function asks the user if they want to play again and accepts responses such as y, yes, n, or no. It only takes
 these listed answers as an answer.
*/
string YesNoQuestion(string question) {
    string userInput = "?";
    // validates y, yes, n, no
    while (true) {
        cout << question << endl;
        getline(cin, userInput);
        cout << endl;


        //to lower case the user's input
        for (int i = 0; i < userInput.size(); i++) {
            userInput.at(i) = tolower(userInput.at(i)); //include ctype library for tolower
        }

        if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no") {
            break;
        } else {
            cout << "Invalid input, please try again... " << endl << endl;
            cout << endl;
        } // end of if (y, yes, n, no)
    } // end of inner while loop to validated y, yes, n, no
    return userInput;
}

/*
 1. Displays a summary of how the user did. Number of correct and incorrect.
 2. Parameters include questions, correctNum, and incorrectNum
 3. Doesn't return anything
 4. This function contains the code needed to display a detailed summary on how the user did including the level of the
 question, the question itself, number of attempts, total correct and incorrect, and the average of how they did.
*/
void DisplaySummaryReport(const vector<vector<int> > &questions, int correctNum, int incorrectNum) {
    int mathLevel = 0;
    int leftNum = 0;
    char mathSymbol = '?';
    int rightNum = 0;
    int correctAns = 0;
    int attempts = 0;
    // Displays the overall summary of how the user did
    cout << "========================================================================" << endl;
    cout << "                           Summary Report           " << endl;
    cout << "========================================================================" << endl;
    cout << "                  Level       Question      Attempts" << endl;
    cout << "                  ----- ------------------- ---------" << endl;
    correctNum = 0;
    incorrectNum = 0;

    //The for loop needed to correctly display the correct information for the summary of the user
    for (int i = 0; i < questions.size(); i++) {
        mathLevel = questions.at(i).at(0);
        leftNum = questions.at(i).at(1);
        mathSymbol = static_cast<char>(questions.at(i).at(2));
        rightNum = questions.at(i).at(3);
        correctAns = questions.at(i).at(4);
        attempts = questions.at(i).at(5);
        cout << "                   " << setw(2) << right << mathLevel << "       "
                << setw(4) << right << leftNum << " " << mathSymbol << " " << setw(4) << left << rightNum;

        if (attempts != 0) {
            cout << "         " << attempts << endl;
            correctNum++; // increments for the total report
        } else {
            cout << "     Incorrect" << endl;
            incorrectNum++; // increments for the total report
        }
    }

    // Outputs the results of all the questions combined
    cout << endl;
    cout << "   Total Questions: " << setw(4) << right << questions.size() << endl;
    cout << "   Total Correct  : " << setw(4) << right << correctNum << endl;
    cout << "   Total Incorrect: " << setw(4) << right << incorrectNum << endl;
    cout << "   Average Correct: " << setw(4) << right << ((correctNum * 100) / questions.size()) << "%" << endl;
}

/*
 1. Prompts users on if they want to save their current game. If the user chooses to do so, the funciton writes data to
 the mathtutor.txt file.
 2. Parameters are userName which is a string and questions which is a 2D vector
 3. Returns the mathLevel
 4. This function prompts for save confirmation, aborts if the user cancels, opens the file for saving, saves game data,
 closes the file, and gives a confirmation message
 */
void SaveCurrentGame(string userName, const vector<vector<int> > &questions) {
    string userInput = "?";
    ofstream outFS;

    userInput = YesNoQuestion(userName + ", do you want save your game? (y=yes | n=no): ");

    if (userInput == "n" || userInput == "no") {
        cout << "Save game cancelled." << endl;
        return;
    }

    cout << "\tPlease wait, saving game..." << endl;

    outFS.open(FILE_NAME);

    if (!outFS.is_open()) {
        throw runtime_error("Unable to open " + FILE_NAME);
    }

    //code for loop
    for (int i = 0; i < questions.size(); i++) {
        outFS << questions.at(i).at(0) << " "
                << questions.at(i).at(1) << " "
                << questions.at(i).at(2) << " "
                << questions.at(i).at(3) << " "
                << questions.at(i).at(4) << " "
                << questions.at(i).at(5) << endl;
        //end of for loop
    }

    outFS.close();

    cout << "Save game completed sucessfully!!";
    cout << "\t" << questions.size() << " saved.";
}

/*
 1. This function attempts to load a previously saved game from a file and then asks the user if they'd like to load any
 saved data.
 2. Parameters include userName and the questions vector.
 3. Returns mathLevel
 4. The function opens the file for reading, promprts for loading the game, aborts the load operation if the user says
 no and loads game data if yes, closes the file, and displays a success message.
 */
int LoadPreviousGame(string userName, vector<vector<int> > &questions) {
    ifstream inFS;
    string userInput = "?";

    int mathLevel = 1;
    int leftNum = 0;
    int rightNum = 0;
    int correctAns = 0;
    int attempts = 0;
    int mathSymbol = 0;

    inFS.open(FILE_NAME);

    if (!inFS.is_open()) {
        cout << "File not found. Good luck with your new game!" << endl;
        return mathLevel;
    }

    userInput = YesNoQuestion("Would you like to load your previous game? (y=yes | n=no): ");

    if (userInput == "n" || userInput == "no") {
        cout << "Game not loaded. Starting a new game." << endl;
        inFS.close();
        return mathLevel;
    }

    cout << "Loading game, please wait..." << endl;


    while (inFS >> mathLevel >> leftNum >> mathSymbol >> rightNum >> correctAns >> attempts) {
        vector<int> question = {mathLevel, leftNum, mathSymbol, rightNum, correctAns, attempts};
        questions.push_back(question);
    }
    cout << "Game loaded successfully!!!!" << endl;
    cout << "Successfully loaded " << questions.size() << " questions from " << FILE_NAME << endl;

    inFS.close();
    return mathLevel;
}

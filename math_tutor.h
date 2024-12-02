/**************************************************************************************
Program:     Math Tutor V6
Section:     4 - 1:00pm
Programmers: Bret (Kirby) Dunker
Date:        11.23.2024
Version:     6
GitHub URL:  https://github.com/KirbyD-YEAH/MathTutorV6.git
Description:  This is the header file that contains the prototypes for the functions.
**************************************************************************************/

//This is the header file that contains all the prototypes for the math tutor functions.

#ifndef MATH_TUTOR_H
#define MATH_TUTOR_H

#include <string>
#include <vector>

using namespace std;

void DisplayGameIntro();
string GitUserName();
vector<int> GenerateRandomQuestion(int mathLevel);
int GetNumericValue();
bool GiveThreeAttempts(int correctAns, int leftNum, char mathSymbol, int rightNum, int NUM_ATTEMPT, int &correctNum, int &incorrectNum, vector<int> &row);
void CheckForLevelChange(int &correctNum, int &incorrectNum, int &mathLevel, int &questionRange);
string YesNoQuestion(string question);
void DisplaySummaryReport(const vector<vector<int>> &questions, int correctNum, int incorrectNum);


#endif //MATH_TUTOR_H

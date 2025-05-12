// Started May 13, 2025

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

// Global Variables used
struct Course{
        string nameCourse; 
        int credit;
        float grade;
    };

struct cumulative{
    float gpa;
    int creditTerm;
};
vector<cumulative> cumulativeData; 

// Functions used
void information_getter();
void compute_gpa(int numberCourse, vector<Course>& course);
string compute_cgpa(vector<cumulative>& cumulativeData);

/* 
Instructions:
1. Number of Courses
2. Grades earned in each one
3. Program can output individual grades of each course
4. Calculate total credit
5. Total grade points 
6. Determine GPA for the semester
*/



// Function that takes in Number of Courses, Name of Course, Credit, and Grade
void information_getter(){
    int numberCourse;

    // Step 1: Ask number of course to make loop for the rest of information
    cout << "For this sememster, how many courses did you take? ";
    cin >> numberCourse;

    vector<Course> course(numberCourse);

    // Step 2: Create loop to store values in course
    for (int i = 0; i < numberCourse; i++){
        cout << "\nCourse Name: ";
        cin >> course[i].nameCourse;
        cout << "Course Credit: ";
        cin >> course[i].credit;
        cout << "Course Grade: ";
        cin >> course[i].grade;
    }

    // Step 3: Send course to compute function
    compute_gpa(numberCourse, course);
}

// Function that computes for GPA
void compute_gpa(int numberCourse, vector<Course>& course){

    // Step 4: Setup loop to compute Grade points
    double gradePoint = 0;
    int totalCredit = 0;


    // Step 5: Computing GPA
    for (int i=0; i<numberCourse; i++){
        gradePoint = (course[i].credit * course[i].grade) + gradePoint;
        totalCredit = totalCredit + course[i].credit;
    }

    double gpa = gradePoint/totalCredit;

    // Step 6: Display GPA
    cout << "\nYour GPA is: " << fixed << setprecision(1) << gpa << endl;

    // Step 7: Store Variables in Cumulative Structure
    cumulative newEntry;
    newEntry.gpa = gpa;
    newEntry.creditTerm = totalCredit;
    cumulativeData.push_back(newEntry);
}

// Function that computes and display for CGPA
string compute_cgpa(vector<cumulative>& cumulativeData){

    // Checks how many number of entries
    if (cumulativeData.empty()){
        return "No Data";
    }

    // Computes 
    double totalGrade = 0;
    int totalCredit = 0;

    for (const auto& entry: cumulativeData){
        totalGrade = totalGrade + (entry.creditTerm * entry.gpa);
        totalCredit = totalCredit + entry.creditTerm;
    }

    double cgpa = totalGrade/totalCredit;

    // Present in table format
    ostringstream table;
    table << "-----------------------------------\n";
    table << "| Term | GPA       | Total Credits |\n";
    table << "-----------------------------------\n";

    for (size_t i = 0; i < cumulativeData.size(); i++) {
        table << "| " << setw(4) << (i + 1) << " | "
              << setw(9) << fixed << setprecision(1) << cumulativeData[i].gpa << " | "
              << setw(13) << cumulativeData[i].creditTerm << " |\n";
    }

    table << "-----------------------------------\n";
    table << "| CGPA: " << fixed << setprecision(1) << cgpa << "                     |\n";
    table << "-----------------------------------";

    return table.str(); 
}


int main(){
    // main menu loop
    bool isActive = true;
    while(isActive){
        // Option 1: Compute GPA
        // Option 2: Compute CGPA
        // Option 3: Exit

        cout << "CGPA Calculator" << endl;
        cout << "Option 1: Compute and Display GPA" << endl;
        cout << "Option 2: Display CGPA" << endl;
        cout << "Option 3: Exit"<<endl;
        int choice;
        cout << "> ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("clear");
            information_getter();
            break;
        case 2:
            system("clear");
            cout << compute_cgpa(cumulativeData) << endl;
            break;
        case 3:
            system("clear");
            isActive = false;
            break;
        default:
            system("clear");
            cout << "Incorrect Input" << endl; 
            break;
        }
    }
    cout << "Thank you for using me : )" << endl;
}
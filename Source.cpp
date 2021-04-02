#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

//Structure to hold student data
struct Student {
	string firstName;
	string lastName;
	double testGrades[4];
	double finalGrade;
	double average;
	char grade;
};
//Function prototypes
void readFile(ifstream& inFile, Student* students);
double average(double testGrades[], double finalGrade);
char findGrade(double average);
void writeFile(Student* students, int size);

int main() {
	string defaultFile = "ClassData1.txt";
	string userFile, line;
	int n = 0;

	cout << "Please enter a file name: ";
	getline(cin, userFile);

	ifstream inFile;
	if (userFile.size() != '0' && userFile != " ")
		defaultFile = userFile;

	inFile.open(defaultFile.c_str());

	if (!inFile)
		cout << "File cannot be opened." << endl;
	else {
		//Finds out number of students in file
		while (getline(inFile, line)  ) {
			n++;
		}
		//Closes the file      
		inFile.close();

		//Re-opens the file
		inFile.open(defaultFile.c_str());

		//Create structure array with 'n' as size
		Student* students = new Student[n];
		//Reads data from the file
		readFile(inFile, students);
		//Writes data to the file
		writeFile(students, n);
	}
	return 0;
}


void readFile(ifstream& inFile, Student* students) {
	int i = 0;
	//Loops till the end of the file
	//Reads first name
	while (inFile >> students[i].firstName) {
		//Reads last name
		inFile >> students[i].lastName;
		//Reads first four test grades
		for (int j = 0; j < 4; j++)
			inFile >> students[i].testGrades[j];
		//Reads final grade
		inFile >> students[i].finalGrade;
		//Finds average of students
		students[i].average = average(students[i].testGrades, students[i].finalGrade);
		//Finds grade of the student
		students[i].grade = findGrade(students[i].average);
		//Increments the value of 'i' by 1
		i++;
	}
	//Closes the input file
	inFile.close();
}


double average(double testGrades[], double finalGrade) {
	//Required variable to hold sum of all grades
	double sum = 0;
	//Sums up all the test grades
	for (int i = 0; i < 4; i++)
		sum += testGrades[i];
	//Adds final grade
	sum += finalGrade;
	//Returns average
	return sum / 5;
}


char findGrade(double average) {
	if (average >= 90)
		return 'A';
	else if (average >= 80)
		return 'B';
	else if (average >= 70)
		return 'C';
	else if (average >= 60)
		return 'D';
	else
		return 'F';
}

void writeFile(Student* students, int size) {
	//?Required variables
	double totalAverage = 0, testAverages[5] = { 0,0,0,0,0 }, maxTestGrade = 0;
	int i = 0;

	//Creates if not exists and opens 'GradeReport.txt' file
	ofstream outFile;
	outFile.open("GradeReport.txt");

	//Prints header to output file
	outFile << left << setw(30) << "Name" << left << setw(15) << "Test Average" << left << setw(15) << "Grade" << endl;

	//Writes name,test average and grade of each student to outut file
	for (int i = 0; i < size; i++) {
		outFile << left << setw(15) << students[i].firstName
			<< left << setw(15) << students[i].lastName
			<< left << setw(15) << fixed << setprecision(2) << students[i].average
			<< left << setw(15) << students[i].grade << endl;
		//Sums up scores of each test for every student
		for (int j = 0; j < 4; j++) {
			testAverages[j] += students[i].testGrades[j];
			if (j == 3)
				testAverages[j + 1] += students[i].finalGrade;
			if (maxTestGrade < students[i].testGrades[j])
				maxTestGrade = students[i].testGrades[j];
			if (maxTestGrade < students[i].finalGrade)
				maxTestGrade = students[i].finalGrade;
		}

	}
	//Finds test averages
	for (int j = 0; j < 5; j++) {
		testAverages[j] = testAverages[j] / size;
		totalAverage += testAverages[j];
	}

	//Total average
	totalAverage = totalAverage / 5;
	outFile << "===========================================================" << endl;
	//Prints test averages for each test , overall average and highest grade
	for (int i = 0; i < 5; i++)
		outFile << "Average of test #" << (i + 1) << " " << testAverages[i] << endl;
	outFile << endl << "Overall test average: " << fixed << setprecision(2) << totalAverage << endl;
	outFile << "Highest test grade: " << maxTestGrade << endl;
	outFile << "Student(s) with highest test grade: " << endl;
	for (int i = 0; i < size; i++) {
		bool found = false;
		for (int j = 0; j < 4; j++)
			if (students[i].testGrades[j] == maxTestGrade) {
				found = true;
				outFile << students[i].firstName << " " << students[i].lastName << endl;
			}
		if (!found)
			if (students[i].finalGrade == maxTestGrade)
				outFile << students[i].firstName << " " << students[i].lastName << endl;
	}
	//Closes the file
	outFile.close();
}
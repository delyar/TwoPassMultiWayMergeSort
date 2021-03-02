#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

using namespace std;

//Each Tuple has two ints and one double and one string --> so each tuple in this relation is 4 + 40 + 4 + 8 = 56 bytes
//We have 22 Blocks of Main memory
//Each Block Contains 1 Tuple --> 56 Bytes
//We have 22 Blocks that each contains 56 Bytes --> We have totally 22 * 56 = 1,232 Bytes
//Our Employee relation in the csv file has 29 tuples
//The total memory usage of the relation Employee is --> 29 * 56 = 1,624 Bytes --> So relation R is too big to fit in main memory
//B(Employee) = 29
//M = 22
//PHASE 1 : Reading Employee relation M blocks by M blocksand sort them --> 1) read the first 22 blocks of the relation and sort them 2) read another 29-22 = 7 blocks and sort them

int sizeOfEachTuple = 56;
int numberOfBlocks = 22;



// Create a Car class with some attributes
class Employee {
	public:
		int eid;
		string ename;
		int age;
		double salary;

		//Default Constructor
		Employee() {

		}
};

bool ValueCmp(Employee const& a, Employee const& b)
{
	return a.eid < b.eid;
}

Employee employees[29];
Employee first22Elements[22];
Employee second7Elements[7];
Employee sortedArray[29];

// Reading Employee.csv
void readEmployeeFileAndGenerateEmployeesArray() {
	std::cout << "readEmployeeFile Starts!" << std::endl;

	ifstream myFile;
	myFile.open("Emp.csv");

	if (!myFile.is_open()) std::cout << "ERROR: File Open" << '\n';

	string eid;
	string ename;
	string age;
	string salary;

	int index = 0;

	while (index < 29) {
		

		getline(myFile, eid, ',');
		getline(myFile, ename, ',');
		getline(myFile, age, ',');
		getline(myFile, salary, '\n');

		std::cout << "ID: " << eid << '\n';
		std::cout << "Name: " << ename << '\n';
		std::cout << "Age: " << age << '\n';
		std::cout << "Salary: " << salary << '\n';
		std::cout << "----------------------------------------------------------------------------" << '\n';

		//Creating Employee Objects From CSV File:
		Employee employee;
		employee.eid = stoi(eid);
		employee.ename = ename;
		employee.age = stoi(age);
		employee.salary = std::stod(salary);

		employees[index] = employee;

		index += 1;
	}

	

	myFile.close();

}

// Read the first M blocks of the relation and sort them and store them
void phase1_firstReadAndSort() {

	//Slicing the first M blocks of relation
	for (int i = 0; i < 22; i++) {
		first22Elements[i] = employees[i];
	}

	//Sorting the first M blocks of relation
	std::sort(first22Elements, first22Elements + 22 , ValueCmp);

}

// Read the second M blocks of the relation and sort them and store them
void phase1_secondReadAndSort() {

	//Slicing the second M blocks of relation --> which here is 7 blocks remaining 29-22 = 7
	int index = 0;
	for (int i = 22; i < 29; i++) {
		second7Elements[index] = employees[i];
		index += 1;
	}

	//Sorting the first M blocks of relation
	std::sort(second7Elements, second7Elements + 7, ValueCmp);
}

// Merge arrays that are already sorted into one sorted array
void merge(Employee a[], Employee b[], int m, int n) {
	
	int i = 0; // index for first array
	int j = 0; // index for second array
	int k = 0; // index for third sorted array

	while (i < m && j< n){
		if (a[i].eid < b[j].eid) {
			sortedArray[k++] = a[i++];
		} else {
			sortedArray[k++] = b[j++];
		}
	}

	for (; i<m ; i++) {
		sortedArray[k++] = a[i];
	}

	for (; j < n; j++) {
		sortedArray[k++] = b[j];
	}
}

void writeArrayToCSVFile(Employee array[]) {

	std::ofstream file;
	file.open("EmpSorted.csv", std::ios_base::app);

	for (int i = 0; i < 29; i++) {
		file << array[i].eid << "," << array[i].ename << "," << array[i].age << "," << array[i].salary << std::endl;
	}

	file.close();
}

int main() {
	std::cout << "Program Starts!" << std::endl;
	
	readEmployeeFileAndGenerateEmployeesArray();

	//PHASE 1: Divide
	//We read the relation M blocks by M blocks and sort them and store them --> Here we have 29 tuples so we have 2 slices of 22 and 7 elements
	phase1_firstReadAndSort(); //Run 1
	phase1_secondReadAndSort(); //Run 2
	//So at this point we have two parts that each part is sorted based in the eid

	//PHASE 2: Conquer (Merge)
	// We read one block of each of the runs at a time and merge them --> we find the first smalles, second smallest, ...till exhausts

	merge(first22Elements, second7Elements, 22, 7);

	//Writing The Result Array On A CSV File
	writeArrayToCSVFile(sortedArray);

	return 0;
}





//for (int i = 22 - 1; i >= 0; i--)
	//	cout << "xxxxxx: " << first22Elements[i].ename << '\n';
#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	string line;
	int startFloor;
	int totalFloors = 0;

	if (argc != 3) {
		cout << "Elevator usage: elevator <inputFile> <mode>" << endl;
		exit(1);
	}
	
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) {
		cout << "Error opening file or invalid filename" << endl;
		exit(1);
	}
	while (getline(inputFile, line)) {
		cout << line << endl;
	}
	

	return 0;
}
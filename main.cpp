#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	string line;	

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
		int startFloor;
		int totalFloors = 0;
		
		startFloor = stoi(line.substr(0, line.find(':')));
		
		cout << startFloor << endl;
	}
	

	return 0;
}
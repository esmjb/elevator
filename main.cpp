#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
#include <vector>

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
		int currentFloor;
		int totalFloors = 0;
		//vector<pair<int, int>> requests;
		vector<int> nums;

		for (int i = 0; i < line.length();) {
			string str = "";
			while (isdigit(line[i])) {				
				str += line[i];
				i++;
			}
			if (str.length() > 0) {
				int num = stoi(str);
				nums.push_back(num);
			}
			else
				i++;
		}
		//currentFloor = stoi(line.substr(0, line.find(':'))); //get starting position of elevator
		//cout << currentFloor << endl;
		for (int i = 0; i < nums.size(); i++)
			cout << nums[i] << " ";
		cout << endl;
	}
	

	return 0;
}
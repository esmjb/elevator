#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
#include <vector>

using namespace std;

void modeA(vector<int> &, int);
void modeB(vector<int> &, int);

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
		currentFloor = nums[0];				
		nums.erase(nums.begin());			//delete first item in vector 
		
		string mode = argv[2];
		if (mode.compare("A") == 0)
			modeA(nums, currentFloor);
		else
			cout << "**" << argv[2] << "**" << endl;
	}
	

	return 0;
}

void modeA(vector<int> &requests, int current) {
	int total = 0;
	vector<int> stops;

	stops.push_back(current);

	for (int i = 0; i < requests.size(); i += 2) {
		if (requests[i] != current) {
			stops.push_back(requests[i]);
			total += abs(current - requests[i]);			
		}
		total += abs(requests[i] - requests[i + 1]);
		stops.push_back(requests[i + 1]);
		current = requests[i + 1];
	}

	for (int i = 0; i < stops.size(); i++)
		cout << stops[i] << " ";
	cout << "(" << total << ")" << endl;
}

void modeB(vector<int> &, int) {

}
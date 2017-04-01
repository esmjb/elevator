#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

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
		currentFloor = nums[0];				//assign starting position to currentFloor then delete from vector
		nums.erase(nums.begin());			
		
		string mode = argv[2];
		if (mode.compare("A") == 0)
			modeA(nums, currentFloor);
		else
			modeB(nums, currentFloor);
	}

	return 0;
}

void modeA(vector<int> &requests, int current) {
	int total = abs(current - requests[0]);				//initialize total to be distance between start position and first ride origin

	cout << current << " ";
	for (int i = 0; i < requests.size(); i++) {			//iterate through list, only print when two consecutive values are unique 
		if(i == 0)
			cout << requests[i] << " ";	
		else if(requests[i] != requests[i -1]){
			total += abs(requests[i] - requests[i - 1]);
			cout << requests[i] << " ";
		}
	}
	cout << "(" << total << ")" << endl;
}

void modeB(vector<int> &requests, int current) {	
	int total = 0;
	vector<int> stops;								//to hold floors stopped at in sequential order
	queue<pair<int, int>> rides;					//to hold each ride request.  first = origin, second = destination

	stops.push_back(current);						//add starting floor to stops

	for (int i = 0; i < requests.size(); i += 2)						//create queue
		rides.push(make_pair(requests[i], requests[i + 1]));

	while (!rides.empty()) {		
		vector<int> temp;							//to hold all origins and destination of consecutive rides going in same direction
		temp.push_back(rides.front().first);
		temp.push_back(rides.front().second);
		rides.pop();								//pop off first ride, add to temp

		if (temp[0] < temp[1]){				//going up			
			while (!rides.empty() && rides.front().first < rides.front().second) {		//look ahead in queue and add to temp if also going up
				temp.push_back(rides.front().first);
				temp.push_back(rides.front().second);
				rides.pop();
			}
			sort(temp.begin(), temp.end());			
		}
		else {								//going down	
			while (!rides.empty() && rides.front().first > rides.front().second) {		//add each consecutive ride that is also going down
				temp.push_back(rides.front().first);
				temp.push_back(rides.front().second);
				rides.pop();
			}
			sort(temp.begin(), temp.end(), [](const int a, const int b) {return a > b; });		//sort in reverse in order to use same logic below	
		}

		if(temp[0] != current)						//only add to stop if elevator currently not at first ride start position
			stops.push_back(temp[0]);
		for (int i = 1; i < temp.size(); i++) {		//add unique floors to stops in current direction
			if (temp[i] != temp[i - 1])
				stops.push_back(temp[i]);
		}
		current = temp[temp.size() - 1];			//update current elevator position to that of last ride destination in current direction
	}
	for (int i = 0; i < stops.size(); i++) {											
		if (i > 0)
			total += abs(stops[i] - stops[i - 1]);
		cout << stops[i] << " ";
	}
	cout << "(" << total << ")" << endl;
}
	

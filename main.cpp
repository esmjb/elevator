#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void parseLine(string &, vector<int> &);
void modeA(vector<int> &);
void modeB(vector<int> &);

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
		vector<int> nums;

		parseLine(line, nums);		
		
		string mode = argv[2];
		if (mode.compare("A") == 0)
			modeA(nums);
		else
			modeB(nums);
	}

	return 0;
}

/*
*Following function takes a string and vector by reference, parses string by selecting only numeric characters
*then converts numeric strings to ints and appends to vector.
*Function returns nothing but modifies vector.
*/
void parseLine(string &line, vector<int> &nums) {
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
}

/*
*Following function outputs total distance travelled and path of elevator that can only take one passenger at a time and must be done in order
*based on time requested (first come, first serve)
*Function returns nothing and modifies nothing.
*/
void modeA(vector<int> &requests) {
	int total = 0;		
	
	for (int i = 0; i < requests.size(); i++) {			//iterate through list, only print when element does not equal prior element, add difference between current and prior element to total
		if(i == 0)
			cout << requests[i] << " ";	
		else if(requests[i] != requests[i -1]){
			total += abs(requests[i] - requests[i - 1]);
			cout << requests[i] << " ";
		}
	}
	cout << "(" << total << ")" << endl;
}

/*Following function outputs total distance travelled and path of elevator that can accomodate several passengers at same time
*as long as they are going the same direction and there are no requests between them from someone going in opposite direction
*Function returns nothing and modifies nothing
*/
void modeB(vector<int> &requests) {	
	int total = 0;
	int current = requests[0];						//initialize current (current floor) to hold value of starting elevator position
	vector<int> stops;								//to hold floors stopped at in sequential order
	queue<pair<int, int>> rides;					//to hold each ride request.  first = origin, second = destination

	stops.push_back(current);						//add starting floor to stops

	for (int i = 1; i < requests.size(); i += 2)					//create queue starting from index 1 of vector since index 0 is starting position
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
	

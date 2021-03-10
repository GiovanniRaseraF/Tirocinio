#include <utility>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

struct PeakData {
	vector<int> pos, peaks;
};

//using PeakData = vector<pair<int, int>>;

char findState(int a, int b) {
	if (a < b)	return 'r';
	if (a == b) return 's';
	if (a > b)	return 'f';
	return 0;
}

PeakData pick_peaks(vector<int> v) {
	//for (int i : v) cout << i << " ";
	if (v.empty()) return {};
	PeakData result;
	int len = v.size();
	/*
	Stati possibili:
	i	:	inizio
	r	:	raising (salita)
	s	:	still	(piano)
	f	:	falling	(in caduta)
	*/
	char state = 'i';
	pair<int, int> pi;

	for (int i = 1; i < len; i++) {
		//Calcolo il nuovo stato
		char new_state = findState(v[i-1], v[i]);

		switch (state) {
		case 'i':
			//Stato di Init
			switch (new_state) {
			case 'i': case 'f': case 's':
				break;
			case 'r':
				//Se sono nello stato di raising mi salvo la posizione
				state = 'r';
				pi = {v[i], i};
				break;
			}
			break;

		case 'r':
			//Stato rising
			switch (new_state) {
			case 'r':
				state = 'r';
				pi = { v[i], i };
				break;
			case 's':
				state = 's';
				//pi = { v[i], i };
				break;
			case 'f':
				state = 'i';
				result.pos.push_back(pi.second);
				result.peaks.push_back(pi.first);
				break;
			}
			break;

		case 's':
			//Stato still
			switch (new_state) {
			case 's':
				state = 's';
				//pi = { v[i], i };
				break;
			case 'r':
				state = 's';
				pi = { v[i], i };
				break;
			case 'f':
				state = 'i';
				result.pos.push_back(pi.second);
				result.peaks.push_back(pi.first);
				break;
			}
			break;
		case 'f':
			break;

		}
	}

	return result;
}

int main() {
	PeakData actual = pick_peaks(vector<int> {1, 2, 2, 2, 1});
	
	cout << endl;
	for(int i : actual.pos){
		cout << i << " ";
	}
	cout << endl;
	for (int i : actual.peaks) {
		cout << i << " ";
	}


	return 0;
}
// project 1 - CAV
// project main
#include <iostream>
#include "fcm.h"
#include <string>
#include <cctype>
using namespace std;

int main() {
		string in;
		int res, i=0;
		FCM f;
		while(1) {
			getline(cin,in);
			while(i<in.size()) {
				cout << in[i];
				cout<<f.charToInteger(in[i++]);
				cout<<"\n";
			}
			i=0;
		}

    return 0;
}

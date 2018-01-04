/*
 * Student.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: Darius San Agustin
 */
#include <cctype>
#include "Student.h"
using namespace std;


Student::Student() {
	ssid = genSSID();
	fname = genName();
	lname = genName();
}

ostream& operator<<(ostream& o, const Student& s) {
		o << "Name: " << s.fname << " " << s.lname << endl;
		o << "SSID: " << s.ssid << endl;
		return o;
}

bool operator<(const Student& lhs, const Student& rhs) {
	return lhs.ssid < rhs.ssid;
}

bool operator==(const Student& lhs, const Student& rhs) {
	bool same_ssid = (lhs.ssid == rhs.ssid);
	bool same_name = (lhs.fname == rhs.fname) && (lhs.lname == rhs.lname);

	return same_ssid && same_name;
}

bool operator!=(const Student& lhs, const Student& rhs) {

	return !(lhs == rhs);
}

bool operator>(const Student& lhs, const Student& rhs) {
	return lhs.ssid > rhs.ssid;
}

bool operator<=(const Student& lhs, const Student& rhs) {
	return lhs < rhs || lhs == rhs;
}

bool operator>=(const Student& lhs, const Student& rhs) {
	return lhs > rhs || lhs == rhs;
}

string Student::genSSID() {
	string s = "";

	for(int i = 0; i < 11; ++i) {
		if(i == 3 || i == 6) {
			s += "-"; continue;
		}

		s += genDigit();
	}

	return s;
}

string Student::genName() {
	string s = ""; s += toupper(genLetter());

	for(int i = 0, postlength = rand() % 12 + 1; i < postlength; ++i)
		s += genLetter();

	return s;
}

char genDigit() { return '0' + (std::rand() % 10); }
// post-condition: generates digit from 0 to 9 of type char

char genLetter() { return 'a' + (std::rand() % 26); }
// post-condition: generates a random lowercase letter from a to z

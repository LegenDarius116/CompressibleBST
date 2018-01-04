/*
 * Student.h
 *
 *  Created on: Sep 28, 2017
 *      Author: Darius San Agustin
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <ostream>
#include <cstdlib>
//-Student-Prototype----------------------------------------------------------
class Student {
	std::string ssid{}, fname{}, lname{};
public:
	Student();
	// post-condition: values of the fields are generated randomly

	friend std::ostream& operator<<(std::ostream& o, const Student& s);
	// post-condition: prints out student's name and SSID

	friend bool operator<(const Student& lhs, const Student& rhs);
	// post-condition: used by sort algorithm to sort students
	// by their SSIDs. String's < operator is used

	friend bool operator>(const Student& lhs, const Student& rhs);
	friend bool operator<=(const Student& lhs, const Student& rhs);
	friend bool operator>=(const Student& lhs, const Student& rhs);

	friend bool operator==(const Student& lhs, const Student& rhs);
	friend bool operator!=(const Student& lhs, const Student& rhs);
private:
	std::string genSSID();
	// post-condition: randomly generate ssid in formt: ddd-dd-dddd
	// uses genDigit() helper function

	std::string genName();
	// post-condition: generates a name
	// Name starts with a random uppercase letter
	// followed by 1-12 random lowercase letters
	// uses genLetter() helper function
};

//-Helper-Functions-----------------------------------------------------------
char genLetter();
char genDigit();

#endif /* STUDENT_H_ */

//============================================================================
// Name        : DStruct_6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Student.h"
#include "Bag.h"
#include "BST.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

vector<unsigned int> get_shuffled_vector(unsigned int upper_bound, unsigned int subset) {
// precondition: 	upperbound determines the range of the scrambled numbers
//					subset determines how many of those numbers will be used
//					subset < upperbound
// postcondition: 	returns a sorted ascending vector of size subset that contains random elements within
//					[0, upper_bound) exclusive

	assert(subset <= upper_bound); // assert the precondition

	vector<unsigned int> v_ind;
	v_ind.reserve(upper_bound);

	for(unsigned int i = 0; i < upper_bound; ++i) v_ind.push_back(i);

	random_shuffle(v_ind.begin(), v_ind.end());

	vector<unsigned int> v_sub;
	v_sub.reserve(subset);

	for(unsigned int i = 0; i < subset; ++i) v_sub.push_back(v_ind.at(i));

	sort(v_sub.begin(), v_sub.end());

	return v_sub;
}

/*	State of Assignment VI as of Nov. 26, 2017
 * 	The iterative insertion works just fine, the bag and the BST are equal.
 *
 * 	But when attempting the randomly remove 100 elements, you'll either get a false positive, or
 * 	the sort() function will throw an error message because the sizes (b/w the new bag and the bst) are unequal
 *		When error message is thrown, the sizes are often 299 (bag) vs 298 (bst)
 *
 * 	Also, when the bag and bst somehow becomes inequal, the destructor will throw this error:
 * 		[Destructor] Error: m_active is not zero! (4294967278)
 * 	Sometimes, it may also throw the same message, but for m_inactive.
 *
 * 	Research: Tested out some small code on cpp.sh. I found that if you have an unsigned int variable at 0, and then you
 * 	decrement it, you get that huge number that you see in the error message
 *
 *  ------------------
 *
 * 	State of Assignment VI as of Dec. 6, 2017
 *
 * 	Compress causes m_active and m_inactive counters to go negative, resulting in an automatic
 * 	internal error in the sort() function due to a mismatch between the size of the bag it's trying to
 * 	return and m_inactive
 */

int main() {
	srand(time(0));

//#if 0
	cout << "Test I." << endl;

	Bag<Student> b1(300);
	BST<Student> t1;

	for(unsigned int i = 0; i < 300; ++i) b1.insert(Student());

	cout << "[Debug] Waypoint flag!\n";

	for(b1.begin(); !b1.end(); b1++)
		t1.insert(b1.get());

	cout << "[After insertion] b1 and t1 are ";
	if(t1 == b1) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

	// remove 100 random elements; this is where it chokes and starts going nuts
	unsigned int b1_size0 = b1.size();
	int t1_size0 = t1.size();

	Bag<Student> blacklist; blacklist.reserve(100);

	for(int i = 0; i < 100; ++i) blacklist.insert(b1.remove_random_element());

	for(blacklist.begin(); !blacklist.end(); blacklist++) {
		t1.remove(blacklist.get());
	}

	//cout << "T1 active: " << t1.size() << ", t1 inactive: " << t1.hidden() << endl; // this checks out

	assert(b1.size() == b1_size0 - 100);
	assert(t1.size() == t1_size0 - 100);

	cout << "[After random 100 removal] b1 and t1 are ";
	if(t1 == b1) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

// ------------------------------------------------------------------------------

	cout << "Test II." << endl;

	Bag<Student> b2(500);
	BST<Student> t2;

	for(unsigned int i = 0; i < 500; ++i) b2.insert(Student());

	// iterative insertion
	for(b2.begin(); !b2.end(); b2++) t2.insert(b2.get());

	// removing 300 elements randomly
	Bag<Student> blacklist2(300);

	for(unsigned int i = 0; i < 300; ++i) blacklist2.insert(b2.remove_random_element());

	for(blacklist2.begin(); !blacklist2.end(); blacklist2++) {
		t2.remove(blacklist2.get());

		if(blacklist2.get_current() % 50 == 0) t2.compress();
	}

	cout << "[After iterative insertion, 300 random removal, and compression] b2 and t2 are ";
	if(t2 == b2) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

//#endif

// work with small values

#if 0
	cout << "[Private, small scale test]\n";

	Bag<int> bn1;
	BST<int> tn1;

	bn1.insert(1);
	bn1.insert(2);
	bn1.insert(3);
	bn1.insert(4);
	bn1.insert(5);

	//				1
	//						5
	//					2
	//						3
	//							4
	tn1.insert(1);
	tn1.insert(5);
	tn1.insert(2);
	tn1.insert(3);
	tn1.insert(4);

	cout << "[Element-wise unordered insertion] bn1 and tn1 are ";
	if(tn1 == bn1) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

	BST<int> tn2;

	cout << "[Iterative insertion]\n";
	for(bn1.begin(); !bn1.end(); bn1++) {
		int s = bn1.get();

		//cout << "Inserting " << s << "...\n";

		tn2.insert(s);
	}

	cout << "[Iterative insertion] bn1 and tn2 are ";
	if(tn2 == bn1) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

	bn1.erase_one(3);
	tn2.remove(3);

	bn1.erase_one(4);
	tn2.remove(4);

	cout << "[3 and 4 removed] bn1 and tn2 are ";
	if(tn2 == bn1) cout << "equivalent" << endl; //tn2 size doesn't decrement
	else cout << "not equivalent" << endl;

	tn2.compress(); // iterative copy, compress, and destructor checks out!!!

	// now try remove randomly

	Bag<int> brand; brand.reserve(50);
	BST<int> trand;

	vector<int> alltags; alltags.reserve(50);

	for(int i = 0; i < 500; ++i) {
		int num = rand() % 500;

		brand.insert(num);
		trand.insert(num);

		alltags.push_back(i);
	}

	cout << "trand size: " << trand.size() << endl;

	random_shuffle(alltags.begin(), alltags.end());

	assert(trand == brand);

	long ts0 = trand.size();

	for(unsigned int i = 0; i < 200; ++i) {
		trand.remove(brand.remove_random_element());

		if(i % 3 == 0)
			trand.compress();
	}

	cout << "[Random removal with periodic compression] brand and trand are ";
	if(trand == brand) cout << "equivalent" << endl;
	else cout << "not equivalent" << endl;

	cout << "trand size difference: " << ts0 <<  " vs. "<< trand.size() << endl;
	// random removal succeeded! but compression chokes at times.

#endif

	return 0;
}

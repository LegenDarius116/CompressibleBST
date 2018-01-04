/*
 * BST.h
 *
 *  Created on: Nov 6, 2017
 *      Author: mener
 */

#ifndef BST_H_
#define BST_H_

#include "Bag.h"

template<class T>
struct Node {
	 Node(const T& v) : m_val(v), m_act(true), m_left(nullptr), m_right(nullptr) {}

	 T		  m_val;
	 bool     m_act;
	 Node<T>* m_left;  // pointer to the left subtree.
	 Node<T>* m_right; // pointer to the right subtree.

	 bool is_leaf() const { return m_left == nullptr && m_right == nullptr; }
};

template<class T>
class BST {
public:
	BST() : m_root(nullptr), m_active(0L), m_inactive(0L) {};
	BST(const BST&);
	void operator=(const BST&);
	~BST();

	bool remove(const T&);
	void insert(const T&);
	bool is_member(const T&) const;
	long size() const { return m_active; }
	long hidden() const { return m_inactive; } // used for test purposes
	void compress();  		// removed all marked nodes.
	Bag<T> sort() const; 	// produce a sorted Bag.

	template<class T1>
	friend std::ostream& operator<<(std::ostream& o, const BST<T1>& bst);
private:
	Node<T>* m_root;				// points to root of binary search tree
	long  m_active;   				// count of active nodes.
	long  m_inactive; 				// count of inactive nodes.

	void tree_clear(Node<T>*& root_ptr);				// accesses root pointer; deletes whole tree
	Node<T>* tree_copy(const Node<T>* root_ptr); 	// copies over other tree's nodes
													// and returns root node of new tree

	void compress_subtree(Node<T>* root_ptr); // changed to &, makes it crash

	Node<T>* find_parent(Node<T>* node_ptr, Node<T>* parent);

	void compress_all(Node<T>* root_ptr);
};

// nonmember functions for the BST class

template<class T>
void insert_bag(Bag<T>& b, const Node<T>* node_ptr);	// deprecated

template<class Process, class T>
void binorder(Process f, Node<T>* node_ptr, bool active = true);

template<class Process, class T>
void preorder(Process f, Node<T>* node_ptr, bool active = true);

template<class Process, class T>
void inorder(Process f, Node<T>* node_ptr, bool active = true);

template<class T>
bool operator==(const BST<T>& bst, const Bag<T>& b);


#include "BST.template"
#endif /* BST_H_ */

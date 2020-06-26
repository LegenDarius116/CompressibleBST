# CompressibleBST
This is an implementation of a Binary Search Tree with a custom delete function. In its delete function, it releases leaf nodes back into the heap while marking nodes with children (also known as internal nodes) as inactive. 

The data structure also comes with a compress function. The compress function actually deletes inactive internal nodes and rebuilds the tree accordingly.

This implementation was done as part of an assignment for CSc 21200 - Data Structures at the City College of New York.

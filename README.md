# CIS-277 Assignment 4: Binary Tree Explorer

## Student
Hana Sapunxhiu

## Design

## How to Compile
Compile the main program or the student test suite from the project root directory using `g++` (C++17 or newer):
# Compile the main program
g++ -std=c++17 -Wall -Wextra TreeExplorer.cpp main.cpp -o tree_explorer
# Compile the student test suite
g++ -std=c++17 -Wall -Wextra TreeExplorer.cpp tests/student_tests.cpp -o run_tests

## How to Run
# Run the main program
./tree_explorer

# Run the student test suite
./run_tests

## Tests and Results

## Analysis Questions
1. Trace the preorder, inorder, and postorder processing steps for the subtree rooted at 30 in Tree A. Explain why the sequences change while the sum does not.
   Preorder: 30, 20, 40
   Inorder: 20, 30, 40
   Postorder: 20, 40, 30
   The sequences change because the different processing steps record the values by different traversal rules.
   Preorder: root->left->right
   Inorder: left->root->right
   Postorder: left->right->root
   The sum won't change because each node is recorded once despite the traversal order.

3. Explain why Tree B is a binary tree but not a BST, using a specific violated ordering relationship. Why is its inorder sequence not sorted?
   It is a binary tree because of its structure. There is a single root and each parent node has no more than two children. It is NOT a BST because a BST requires that every node in the entire left subtree be less than the parent, and every node in the entire right subtree be greater than the parent, while in Tree B that is not the case. The node with value 30, a higher value than its parent 10, is in the left subtree.
   Inorder visits the left subtree first, recursively traversing left->root->right, so that when a tree is a BST, the traversal will always visit the values in order from smallest to greatest. Because Tree B is not a BST, and 30 is in the left subtree despite being greater than its root, the inorder traversal will reutrn 30 before values smaller than it in the right subtree.

4. Give the depth of node 40 in Tree A and distinguish depth in edges from this assignment's height in levels.
   The depth of node 40 is 2. Depth is measured by the number of edges from the root. 40 is two edges from 50: 50--30--40, while 50 itself has a depth of 0. Height in levels, on the other hand, is measured by the reach of the tree by counting the number of nodes along the longest path. The height of Tree A is 3.

5. Explain how the FIFO queue produces level order. Connect this to the queue behavior from earlier work.
   FIFO produces nodes in the order they are added to the queue. Nodes closer to the root are always visited first, from left to right, by level. That is why 70 comes after 30 in level order from Tree A, being the next node closest to 50. Similarly to the text message and dynamic memory assignment, the nodes entered into the queue first were visited first when memory needed to be renewed, because they were the latest entries.

6. For n nodes, height h, and maximum level width w, explain the time and auxiliary space for depth-first traversal, level-order traversal, measurements, and destruction. Discuss the O(n) returned vector separately from the call stack or queue. Compare the height of a balanced tree with a chain. Explain why a normal traversal does not need dynamic-programming tabulation.
   All the operations run in O(n) time because each visits every one of the nodes (n) once and performs O(1) work per node. Recursive depth-first traversals, measurements, and destruction use O(h) auxiliary space for the call stack, whereas level-order traversal uses O(w) auxiliary space to hold up to one full level of nodes in its queue. In the worst case, a degenerate chain has height h = n (giving O(n) stack space), while a balanced binary tree has height h = O(log n) (reducing stack space to O(log n). Finally, a normal tree traversal does not need dynamic-programming tabulation because every node has a single parent and each subtree is disjoint, so it is never visited more than once.

7. Explain why deletion uses postorder and what TreeNode*& changes in the caller. What would go wrong if the parent were deleted before reading its child pointers?
  Deletion uses postorder traversal (left, right, root) so that a node's left and right subtrees are completely freed before the parent node is deallocated. If the parent were deleted before reading its child pointers, accessing the roots would dereference memory already freed. The child nodes become dangling pointers, leaking the subtree. Passing TreeNode*& by reference allows destroyTree to set the pointer variable of the node called directly to nullptr instead of modifying a copy.


## AI Use

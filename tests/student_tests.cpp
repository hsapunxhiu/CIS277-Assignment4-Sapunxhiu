#include "../TreeExplorer.h"
#pragma once
#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void testEmptyTree() {
    std::cout << "Running Test 1: Empty tree and repeated null destruction...\n";
    TreeNode* root = nullptr;

    //checks that every traversal returns an empty vector without crashing on null
    assert(preorder(root).empty());
    assert(inorder(root).empty());
    assert(postorder(root).empty());
    assert(levelOrder(root).empty());

    assert(countNodes(root) == 0);
    assert(countLeaves(root) == 0);
    assert(treeHeight(root) == 0);
    assert(sumValues(root) == 0LL);

    // Repeated destruction of a null root should be safe
    destroyTree(root);
    assert(root == nullptr);
    destroyTree(root);
    assert(root == nullptr);

    std::cout << "  -> Passed.\n";
}

void testSingletonTree() {
    std::cout << "Running Test 2: Singleton tree with value -4...\n";
    TreeNode* root = new TreeNode{-4};

    const std::vector<int> expected = {-4};
    assert(preorder(root) == expected);
    assert(inorder(root) == expected);
    assert(postorder(root) == expected);
    assert(levelOrder(root) == expected);

    assert(countNodes(root) == 1);
    assert(countLeaves(root) == 1);
    assert(treeHeight(root) == 1);
    assert(sumValues(root) == -4LL);

    destroyTree(root);
    assert(root == nullptr);

    std::cout << "  -> Passed.\n";
}

void testDegenerateChains() {
    std::cout << "Running Test 3: Four-node left-only and right-only chains...\n";

    // Left-only chain: 1 -> left(2) -> left(3) -> left(4)
    TreeNode* leftChain = new TreeNode{1,
        new TreeNode{2,
            new TreeNode{3,
                new TreeNode{4}, nullptr}, nullptr}, nullptr};

    assert(countNodes(leftChain) == 4);
    assert(countLeaves(leftChain) == 1);
    assert(treeHeight(leftChain) == 4);
    assert(sumValues(leftChain) == 10LL);

    // For a left-only chain:
    // - Preorder & Level-order visit top-down: {1, 2, 3, 4}
    // - Inorder & Postorder visit bottom-up:  {4, 3, 2, 1}
    assert((preorder(leftChain)   == std::vector<int>{1, 2, 3, 4}));
    assert((levelOrder(leftChain) == std::vector<int>{1, 2, 3, 4}));
    assert((inorder(leftChain)    == std::vector<int>{4, 3, 2, 1}));
    assert((postorder(leftChain)  == std::vector<int>{4, 3, 2, 1}));

    // Right-only chain: 1 -> right(2) -> right(3) -> right(4)
    TreeNode* rightChain = new TreeNode{1, nullptr,
        new TreeNode{2, nullptr,
            new TreeNode{3, nullptr,
                new TreeNode{4}}}};

    assert(countNodes(rightChain) == 4);
    assert(countLeaves(rightChain) == 1);
    assert(treeHeight(rightChain) == 4);
    assert(sumValues(rightChain) == 10LL);

    // For a right-only chain:
    // - Preorder, Inorder, & Level-order all visit top-down: {1, 2, 3, 4}
    // - Only Postorder visits bottom-up:                     {4, 3, 2, 1}
    assert((preorder(rightChain)   == std::vector<int>{1, 2, 3, 4}));
    assert((inorder(rightChain)    == std::vector<int>{1, 2, 3, 4}));
    assert((levelOrder(rightChain) == std::vector<int>{1, 2, 3, 4}));
    assert((postorder(rightChain)  == std::vector<int>{4, 3, 2, 1}));

    destroyTree(leftChain);
    destroyTree(rightChain);
    assert(leftChain == nullptr && rightChain == nullptr);

    std::cout << "  -> Passed.\n";
}

void testDuplicatesZeroAndNegatives() {
    std::cout << "Running Test 4: Duplicates, zero, and negative values...\n";

    /*
     * Exact Tree Shape (7 nodes, 4 leaves, height 3):
     *
     *          0
     *        /   \
     *      -5     0
     *     /  \   / \
     *   -5    2 2  -1
     */
    TreeNode* root = new TreeNode{0,
        new TreeNode{-5,
            new TreeNode{-5},
            new TreeNode{2}
        },
        new TreeNode{0,
            new TreeNode{2},
            new TreeNode{-1}
        }
    };

    // Verify no duplicates (0, -5, 2) or zeros were merged/omitted
    assert(countNodes(root) == 7);
    assert(countLeaves(root) == 4);
    assert(treeHeight(root) == 3);
    // Sum: 0 + (-5) + 0 + (-5) + 2 + 2 + (-1) = -7
    assert(sumValues(root) == -7LL);

    assert((preorder(root)   == std::vector<int>{0, -5, -5, 2, 0, 2, -1}));
    assert((inorder(root)    == std::vector<int>{-5, -5, 2, 0, 2, 0, -1}));
    assert((postorder(root)  == std::vector<int>{-5, 2, -5, 2, -1, 0, 0}));
    assert((levelOrder(root) == std::vector<int>{0, -5, 0, -5, 2, 2, -1}));

    destroyTree(root);
    assert(root == nullptr);

    std::cout << "  -> Passed.\n";
}

void testImmutabilityAndRepeatedCalls() {
    std::cout << "Running Test 5: Repeated calls and mutating returned vector...\n";

    /*
     *       10
     *      /  \
     *     20   30
     */
    TreeNode* root = new TreeNode{10, new TreeNode{20}, new TreeNode{30}};

    // Call inorder twice and mutate the first returned vector
    std::vector<int> firstInorder = inorder(root);
    assert((firstInorder == std::vector<int>{20, 10, 30}));

    firstInorder[0] = 999;
    firstInorder.push_back(888);

    // Subsequent call must still reflect the untouched original tree
    std::vector<int> secondInorder = inorder(root);
    assert((secondInorder == std::vector<int>{20, 10, 30}));

    // Verify underlying tree node values were never altered
    assert(root->value == 10);
    assert(root->left->value == 20);
    assert(root->right->value == 30);

    // Repeat check on levelOrder
    std::vector<int> firstLevel = levelOrder(root);
    firstLevel.clear();
    assert((levelOrder(root) == std::vector<int>{10, 20, 30}));

    destroyTree(root);
    assert(root == nullptr);

    std::cout << "  -> Passed.\n";
}

void testDestroyAndRebuild() {
    std::cout << "Running Test 6: Destruction, rebuilding, and second destruction...\n";

    // Phase 1: Build initial tree
    TreeNode* root = new TreeNode{100, new TreeNode{50}, nullptr};
    assert(countNodes(root) == 2);
    assert(sumValues(root) == 150LL);

    // Destroy and confirm pointer is reset to nullptr
    destroyTree(root);
    assert(root == nullptr);
    assert(countNodes(root) == 0);

    // Phase 2: Rebuild a completely different tree on the same root pointer
    root = new TreeNode{7,
        new TreeNode{8},
        new TreeNode{9, new TreeNode{10}, nullptr}
    };

    assert(countNodes(root) == 4);
    assert(countLeaves(root) == 2);
    assert(treeHeight(root) == 3);
    assert(sumValues(root) == 34LL);
    assert((preorder(root) == std::vector<int>{7, 8, 9, 10}));

    // Second destruction
    destroyTree(root);
    assert(root == nullptr);
    assert(countNodes(root) == 0);

    std::cout << "  -> Passed.\n";
}

int main() {
    testEmptyTree();
    testSingletonTree();
    testDegenerateChains();
    testDuplicatesZeroAndNegatives();
    testImmutabilityAndRepeatedCalls();
    testDestroyAndRebuild();

    std::cout << "\nAll 6 test suites passed successfully!\n";
    return 0;
}

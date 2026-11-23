#include "TreeExplorer.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Helper to format a vector of ints into a space-separated string
std::string vecToString(const std::vector<int>& vec)
{
    std::ostringstream oss;
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            oss << ' ';
        oss << vec[i];
    }
    return oss.str();
}

}

int main()
{
    // Tree A
    TreeNode* root = new TreeNode{50};
    root->left = new TreeNode{30};
    root->right = new TreeNode{70};
    root->left->left = new TreeNode{20};
    root->left->right = new TreeNode{40};
    root->right->left = new TreeNode{60};
    root->right->right = new TreeNode{80};

    // Tree B
    TreeNode* root_sec = new TreeNode{10};
    root_sec->left = new TreeNode{30};
    root_sec->right = new TreeNode{20};
    root_sec->left->right = new TreeNode{5};
    root_sec->right->right = new TreeNode{15};

    // Column widths for clean table alignment
    const int labelWidth = 18;
    const int treeAWidth = 24;

    std::cout << std::left
              << std::setw(labelWidth) << "Result"
              << std::setw(treeAWidth) << "Tree A"
              << "Tree B\n";
    std::cout << std::string(60, '-') << "\n";

    std::cout << std::setw(labelWidth) << "Preorder"
              << std::setw(treeAWidth) << vecToString(preorder(root))
              << vecToString(preorder(root_sec)) << "\n";

    std::cout << std::setw(labelWidth) << "Inorder"
              << std::setw(treeAWidth) << vecToString(inorder(root))
              << vecToString(inorder(root_sec)) << "\n";

    std::cout << std::setw(labelWidth) << "Postorder"
              << std::setw(treeAWidth) << vecToString(postorder(root))
              << vecToString(postorder(root_sec)) << "\n";

    std::cout << std::setw(labelWidth) << "Level order"
              << std::setw(treeAWidth) << vecToString(levelOrder(root))
              << vecToString(levelOrder(root_sec)) << "\n";

    std::cout << std::setw(labelWidth) << "Nodes"
              << std::setw(treeAWidth) << countNodes(root)
              << countNodes(root_sec) << "\n";

    std::cout << std::setw(labelWidth) << "Leaves"
              << std::setw(treeAWidth) << countLeaves(root)
              << countLeaves(root_sec) << "\n";

    std::cout << std::setw(labelWidth) << "Height in levels"
              << std::setw(treeAWidth) << treeHeight(root)
              << treeHeight(root_sec) << "\n";

    std::cout << std::setw(labelWidth) << "Sum"
              << std::setw(treeAWidth) << sumValues(root)
              << sumValues(root_sec) << "\n";

    // Clean up dynamically allocated memory
    destroyTree(root);
    destroyTree(root_sec);

    return 0;
}

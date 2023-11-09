/*
Lang Towl - U0000010840
Major: CE
Course: Data Structures & Algorithims
Professor: Dr. Parisa Darbari 
Latest Update: 8:32 AM 11/9/2023
*/

/* Library Inclusion Start */
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;
/* Library Inclusion End */

/* Global Variables Start */
int tree_root_count;
int object_count;
int query_count;
/* Global Variables End */

/* Item Node Class Declaration Start */
class itemNode {

public:
    char name[50];
    int count;
    itemNode *left, *right;

    itemNode() {
        name[0]='\0';
        count = 0;
        left = NULL;
        right = NULL;
    }

    itemNode(char itemName[], int population) {
        std::strcpy(name, itemName);
        count = population;
        left = NULL;
        right = NULL;
    }
};
/* Item Node Class Declaration End */

/* Tree Name Node Class Declaration Start */
class treeNameNode {
private:

public:
    char treeName[50];
    treeNameNode *left, *right;
    itemNode *theTree;

    treeNameNode() {
        treeName[0]='\0';
        theTree = NULL;
        left = NULL;
        right = NULL;
    }

    treeNameNode(char name[]) {
        std::strcpy(treeName, name);
        theTree = NULL;
        left = NULL;
        right = NULL;
    }
};
/* Tree Name Node Class Declaration End */

/* Root Traversal Functions Start */
void inorder_root_traversal(treeNameNode* root) {
    // Recursive function to output an inorder traversal of the root tree

    if (root != nullptr) {
        inorder_root_traversal(root->left);

        std::cout << root->treeName << " ";
        
        inorder_root_traversal(root->right);
    }
}

void inorder_item_traversal(itemNode* node) {
    // Recursive function to output an inorder traversal of the item tree

    if (node != nullptr) {
        inorder_item_traversal(node->left);

        std::cout << node->name << " ";
        
        inorder_item_traversal(node->right);
    }
}

void complete_tree_traversal(treeNameNode* root) {
    // Recursive function to display completed bst

    if (root != nullptr) {
        complete_tree_traversal(root->left);
        cout << "***" << root->treeName << "***" << endl;
        inorder_item_traversal(root->theTree);

        cout << endl;
        complete_tree_traversal(root->right);

    }
}
/* Root Traversal Functions End */

/* Root Tree Functions Start */
treeNameNode* insert_root_node(treeNameNode* node, char name[20]) {
    // Recursive function to construct BST from root node

    if(node == nullptr){
        return new treeNameNode(name);
    }

    /* Alphabetical comparison start */
    int comparison_result = strcmp(name, node->treeName);

    if (comparison_result < 0) {
        node->left = insert_root_node(node->left, name);
    } else if (comparison_result > 0) {
        node->right = insert_root_node(node->right, name);
    }
    /* Alphabetical comparison start */

    return node;
}

treeNameNode* add_roots_to_tree(ifstream& input) {
    // Standard function to parse txt file to prepare for root insertion

    treeNameNode* node = nullptr;
    char root_name[20];

    for (int i = 0; i < tree_root_count; i++) {
        input >> root_name;
        node = insert_root_node(node, root_name);
    }

    return node;
}
/* Root Tree Functions End */

/* Item Node Functions Start */ 
treeNameNode* locate_root_node(treeNameNode* root_tree, char type[20]) {
    // Recursice function to locate the address of target root

    if (root_tree != nullptr) {
        int comparison = strcmp(root_tree->treeName, type);

        if (comparison == 0) {
            return root_tree;
        } else if (comparison < 0) {
            return locate_root_node(root_tree->right, type);
        } else if (comparison > 0) {
            return locate_root_node(root_tree->left, type);
        } else {
            return nullptr;
        }
    } else {
        cerr << "Error: Target Root [" << type << "] Was Not Found." << endl;
        return nullptr;
    }
}

itemNode* process_insertion_to_root_tree(itemNode* destination, itemNode* node) {
    // Recursive function to locate the correct location for insertion into root tree

    if (destination == nullptr || strcmp(destination->name, node->name) == 0) {
        return node;
    }
    else {
        if (strcmp(destination->name, node->name) > 0) {
            destination->left = process_insertion_to_root_tree(destination->left, node); 
        } else {
            destination->right = process_insertion_to_root_tree(destination->right, node); 
        }

        return destination;
    }
}

void add_item_to_root_tree(ifstream &input, treeNameNode* root_tree) {
    // Void function to parse txt file to prepare for item insertion to root tree

    if (root_tree == nullptr) {
        cerr << "Error: Null Pointer Detected When Constructing Subtree" << endl;
    } 

    char type[20];
    char name[20];
    int data;
    treeNameNode* temp_root = new treeNameNode();

    for (int i = 0; i < object_count; i++) {
        input >> type >> name >> data;
        itemNode* new_item = new itemNode(name, data);

        temp_root = locate_root_node(root_tree, type);
        temp_root->theTree = process_insertion_to_root_tree(temp_root->theTree, new_item);
    }
}
/* Item Node Functions End */ 

int main() {
    /* Code To Access in.txt File Start */
    ifstream input;
    input.open("in.txt");

    // Conditional checks to see if in.txt file is accessible
    if (input.is_open() == true) {
        cout << "in.txt File Opened Succesfully." << endl << endl;
    } else {
        cerr << "Error: in.txt File Failed To Open." << endl;
        return -1;
    }
    /* Code To Access in.txt File End */

    /* Code To Copy Item Quantities To Global Variables Start */
    input >> tree_root_count >> object_count >> query_count;

    cout << tree_root_count << " Roots Detected, " << object_count << " Objects Detected, " << query_count << " Queries Detected." << endl << endl;
    /* Code To Copy Item Quantities To Global Variables End */

    /* Code To Initialize & Construct Root Nodes Start */
    treeNameNode* root_tree = add_roots_to_tree(input);

    cout << "Inorder Traversal Of Root Tree -> ";
    inorder_root_traversal(root_tree);

    cout << endl << endl;
    /* Code To Initialize & Construct Root Nodes End */

    /* Code To Add Itens To Root Tree Start */
    add_item_to_root_tree(input, root_tree);

    complete_tree_traversal(root_tree);
    /* Code To Add Itens To Root Tree End */
    return 0;
}

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
#include <cstdlib>

using namespace std;
/* Library Inclusion End */

/* Global Variables Start */
int tree_root_count;
int object_count;
int query_count;

ofstream output("out.txt");
/* Global Variables End */

/* Item Node Class Declaration Start -> Class Declaration Was Provided */
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

/* Tree Name Node Class Declaration Start -> Class Declaration Was Provided */
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

    if (root != nullptr) {                      // Conditional checks if root is not a nullptr before continuing
        inorder_root_traversal(root->left);     // Traversal of left sub-tree

        std::cout << root->treeName << " ";     // write to command line
        output << root->treeName << " ";        // write to out.txt

        inorder_root_traversal(root->right);    // Traversal of right sub-tree
    }
}

void inorder_item_traversal(itemNode* node) {
    // Recursive function to output an inorder traversal of the item tree

    
    if (node != nullptr) {                      // Conditional checks if root is not a nullptr before continuing
        inorder_item_traversal(node->left);     // Traversal of left sub-tree

        std::cout << node->name << " ";         // write to command line
        output << node->name << " ";            // write to out.txt
        
        inorder_item_traversal(node->right);    // Traversal of right sub-tree
    }
}

void complete_tree_traversal(treeNameNode* root) {
    // Recursive function to display completed bst

    
    if (root != nullptr) {                                                              // Conditional checks if root is not a nullptr before continuing
        complete_tree_traversal(root->left);                                            // completes inorder traversal of left root tree recursivly
        cout << "Inorder Traversal Of [ " << root->treeName << " ] Tree." << endl;      // writes to command line
        output << "***" << root->treeName << "***"<< endl;                              // writes to out.txt
        inorder_item_traversal(root->theTree);                                          // completes inorder traversal of left item tree recursivly

        cout << endl;
        output << endl;

        complete_tree_traversal(root->right);                                           // completes inorder traversal of right root tree recursivly
    }
}
/* Root Traversal Functions End */

/* Root Tree Functions Start */
treeNameNode* insert_root_node(treeNameNode* node, char name[20]) {
    // Recursive function to construct BST from root node

    if(node == nullptr){
        return new treeNameNode(name);
    }

    int comparison_result = strcmp(name, node->treeName);          // alphabetical comparison between target node name and current node name

    if (comparison_result < 0) {                                   // conditional to determine the direction of traversal
        node->left = insert_root_node(node->left, name);           // traversal direction -> left
    } else if (comparison_result > 0) {
        node->right = insert_root_node(node->right, name);         // traversal direction -> right
    }

    return node;
}

treeNameNode* add_roots_to_tree(ifstream& input) {
    // Standard function to parse txt file to prepare for root insertion

    treeNameNode* node = nullptr;
    char root_name[20];

    for (int i = 0; i < tree_root_count; i++) {         // iterates through all tree root names 
        input >> root_name;                             // scans tree root name from in.txt
        node = insert_root_node(node, root_name);       // sets the new node aftering locating the subtree in which it belongs
    }

    return node;
}
/* Root Tree Functions End */

/* Item Node Functions Start */ 
treeNameNode* locate_root_node(treeNameNode* root_tree, char type[20]) {
    // Recursice function to locate the address of target root

    if (root_tree != nullptr) {
        int comparison = strcmp(root_tree->treeName, type);     // alphabetical comparison between target node name and current node name

        if (comparison == 0) {                                  // condition is met when the names match
            return root_tree;       
        } else if (comparison < 0) {                            // conditional to determine direction of traversal
            return locate_root_node(root_tree->right, type);    // traversal direction -> right
        } else if (comparison > 0) {
            return locate_root_node(root_tree->left, type);     // traversal direction -> left
        } else {
            return nullptr;                                     // nullptr returned if none of the conditions are met indicating the root node wasnt found
        }
    } else {
        return nullptr;
    }
}

itemNode* process_insertion_to_root_tree(itemNode* destination, itemNode* node) {
    // Recursive function to locate the correct location for insertion into root tree

    if (destination == nullptr || strcmp(destination->name, node->name) == 0) {                 // conditional checks to see if end of tree is found or if target is foudn
        return node;
    }
    else {
        if (strcmp(destination->name, node->name) > 0) {                                        // conditional to determine the direction of traversal
            destination->left = process_insertion_to_root_tree(destination->left, node);        // traversal direction -> left
        } else {
            destination->right = process_insertion_to_root_tree(destination->right, node);      // traversal direction -> right
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

    for (int i = 0; i < object_count; i++) {                     // iterates through all object items from in.txt
        input >> type >> name >> data;                           // fetches item parameters from in.txt
        itemNode* new_item = new itemNode(name, data);           // constructs object from fercged parameters

        temp_root = locate_root_node(root_tree, type);           // locates subtree for insertion
        temp_root->theTree = process_insertion_to_root_tree(temp_root->theTree, new_item);  // completes insertion process intro subtree
    }
}
/* Item Node Functions End */ 

/* Query Function Start */
int fetch_data(itemNode* sub_tree, char target[20]) {
    // Recursive function to fetch data stored in target item, returns -1 if search fails

    if (sub_tree != nullptr) {
        if (strcmp(sub_tree->name, target) == 0) {          // condition is satisfied when the target item is found
            return sub_tree->count;
        }

        if (strcmp(sub_tree->name, target) < 0) {           // condition to determine the direction of traversal
            return fetch_data(sub_tree->right, target);     // traversal direction -> right
        } else {
            return fetch_data(sub_tree->left, target);      // traversal direction -> left
        }

        return -1;
    }

    return -1;
}

int item_before(itemNode* sub_tree, char target[20]) {
    // Recursive function to determine the amount of items above or before a target item

    if (sub_tree == nullptr) {
        return 0;
    } else {
        if (strcmp(sub_tree->name, target) < 0) {
            return item_before(sub_tree->left, target) + item_before(sub_tree->right, target) + 1;      // aggregates total number of items on the way to locating target node -> direction right
        } else {
            return item_before(sub_tree->left, target) + 0;                                             // aggregates total number of items on the way to locating target node -> direction left
        }
    }
}

int height_balance(itemNode* sub_tree) {
    // Recursive function to compute the subtree height of either the left or right subtree

    if (sub_tree == nullptr) {
        return 0;
    } else {
        int left_height = height_balance(sub_tree->left);       // variables aggregate total number of items in left subtrees
        int right_height = height_balance(sub_tree->right);     // variables aggregate total number of items in right subtrees

        if (right_height < left_height) {   // conditional to determine the direction of traversal
            return left_height + 1;         // +1 for each traversal into a left subtree
        } else {
            return right_height + 1;        // +1 for each traversal into a right subtree
        }
    }
}

int sub_tree_count(itemNode* sub_tree) {
    // Recursive function to compute the sum of each items data nested within a target subtree

    if (sub_tree == nullptr) {
        return 0;
    } else {
        return sub_tree->count + sub_tree_count(sub_tree->left) + sub_tree_count(sub_tree->right);      // traverses in both directiosn starting from target node aggragating the data within each object
    }
}

void execute_queries(treeNameNode* root_tree, ifstream &input) {
    // Function to process and execute queries

    for (int i = 0; i < query_count; i++) {         // iterates through all queries from in.txt
        char query[20];                 
        input >> query;                             // pareses query and stores it

        // Search function implementation start
        if (strcmp(query, "search") == 0) {         // conditional exectues when query is of type "search"
            char type[20];
            char target[20];
            input >> type >> target;                // pareses query and stores it

            treeNameNode* temp_root = locate_root_node(root_tree, type);

            if (temp_root != nullptr) {

                int fetched_data = fetch_data(temp_root->theTree, target);

                if (fetched_data != -1) {                                                               // if the data != -1 that means that it was found in tree
                    cout << fetched_data << " " << target << " found in " << type << "." << endl;
                    output << fetched_data << " " << target << " found in " << type << endl;
                } else {                                                                                // code to run when target is not present in the tree
                    cout << target << " could not be found in data set." << endl;
                    output << target << " not found in " << type << endl;
                }
            } else {                                                                                    // code to run when type is not present in the tree
                cout << type << " does not exist" << endl;
                output << type << " does not exist" << endl;
            }
        }
        // Search function implementation end

        else

        // Item before function call start
        if (strcmp(query, "item_before") == 0) {
            char type[20];
            char target[20];
            input >> type >> target;                                                    // pareses query and stores it

            treeNameNode* temp_root = locate_root_node(root_tree, type);                // locates target node
            int items_before = item_before(temp_root->theTree, target);                 // calls item_before

            if (temp_root != nullptr) {                                                 // checks to make sure that the target was located in the tree
                cout << "Items before " << target << ": " << items_before << endl;
                output << "item before " << target << ": " << items_before << endl;
            } else {                                                                    // code to run if the target was not located in the tree
                cerr << "Error: Failed To Locate Target Node When Calculating Item Befor." << endl;
            }
        }
        // Irem before function call end

        else

        // Height Balance function call start
        if (strcmp(query, "height_balance") == 0) {
            char type[20];
            input >> type;                                                      // pareses query and stores it

            treeNameNode* temp_root = locate_root_node(root_tree, type);        // locates target node
            
            int left_tree_height = height_balance(temp_root->theTree->left);    // couts height of left tree
            int right_tree_height = height_balance(temp_root->theTree->right);  // counts height of right tree
            int difference = abs(right_tree_height - left_tree_height);         // computes the difference of the tree and absolute values it
            string result = (difference > 1) ? "not balanced." : "balanced";    // ternieray opeartor for output

            cout << type << ": left height " << left_tree_height << ", right height " << right_tree_height << ", difference " << difference << ", " << result << endl;
            output << type << ": left height " << left_tree_height << ", right height " << right_tree_height << ", difference " << difference << ", " << result << endl;
        }
        // Height Balance function call end

        else

        // Count function call start
        if (strcmp(query, "count") == 0) {
            char type[20];
            input >> type;                                                  // pareses query and stores it

            treeNameNode* temp_root = locate_root_node(root_tree, type);    // locates target node

            int total = sub_tree_count(temp_root->theTree);                 // computes total count of target subtree
            cout << type << " count " << total << endl;
            output << type << " count " << total << endl;
        }
        // Count function call end

        else {
            break; // breaks out of for loop is command is not recognized
        }

        cout << endl;
    }
}
/* Query Function End */

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
    output << endl;
    /* Code To Initialize & Construct Root Nodes End */

    /* Code To Add Itens To Root Tree Start */
    add_item_to_root_tree(input, root_tree);
    complete_tree_traversal(root_tree);

    cout << endl;
    /* Code To Add Itens To Root Tree End */

    /* Code To Execute BST Queries Start */
    cout << "Results Of Query Executions:" << endl;

    execute_queries(root_tree, input);
    /* Code To Execute BST Queries End */

    return 0;
}
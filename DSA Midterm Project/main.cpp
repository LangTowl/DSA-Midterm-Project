/* Library Inclusion Start */
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;
/* Library Inclusion End */

/* Global Variables Start */
int tree_root_count;
int object_count;
int query_count;
/* Global Variables End */

/* Class Declarations Start */
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
/* Class Declarations End */

/* Traversal functions start */
void inorder_root_traversal(treeNameNode* root) {
    if (root != nullptr) {
        inorder_root_traversal(root->left);

        std::cout << root->treeName << endl;
        
        inorder_root_traversal(root->right);
    }
}
/* Traversal functions end */

/* BST builder functions start */
treeNameNode* insert_root_node(treeNameNode* node, char name[20]) {

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

    treeNameNode* root = nullptr;

    for (int i = 0; i <= tree_root_count; i++) {
        string name;
        char name_char[20];

        getline(input, name, '\n');
        strcpy(name_char, name.c_str());
            
        root = insert_root_node(root, name_char);
    }

    return root;
}

itemNode* insert_item_node(itemNode* node, char name[20], int data) {
    return nullptr;
} 

treeNameNode* locate_root_node(treeNameNode* node, char name[]) {
    if (node == nullptr || strcmp(node->treeName, name) == 0) {
        return node;
    }

    if (strcmp(name, node->treeName) < 0) {
        return locate_root_node(node->left, name);
    } else {
        return locate_root_node(node->right, name);
    }
}

void add_item_to_root(ifstream& input, treeNameNode* root) {
    for (int i = tree_root_count; i < tree_root_count + object_count + 1; i++) {
        if (i > tree_root_count && i < tree_root_count + object_count + 1) {
            string type;
            char type_char[20];
            string name;
            char name_char[20];
            string data;

            getline(input, type, ' ');
            strcpy(type_char, type.c_str());
            getline(input, name, ' ');
            strcpy(name_char, name.c_str());
            getline(input, data, '\n');

            treeNameNode* temp = locate_root_node(root, type_char);

            if (temp != nullptr) {
                cout << temp->treeName << endl;
            } else {
                cout << "Root node [" << type << "] not found" << endl;
            }
        }
    }
}

/* BST builder functions end */

int main() {
    /* in.txt accessor start */
    ifstream input;
    input.open("in.txt");
    input >> tree_root_count >> object_count >> query_count;
    /* in.txt accessor end */

    /* Code to run upon successful file access start */
    if (input.is_open() == true) {
        treeNameNode* root = add_roots_to_tree(input);

        inorder_root_traversal(root);

        if (root == nullptr) {
            cout << "nullptr" << endl;
        } else {
            cout << root->treeName << endl;
        }
    } 
    /* Code to run upon successful file access end */
    else 
    /* Code to run upon failed file access start */
    {
        cerr << "Error: Failed to open [in.txt]" << endl;
    }
    /* Code to run upon failed file access end */

    return 0;
}
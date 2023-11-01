/* Library Inclusion Start */
#include <iostream>
#include <fstream>
#include <string>
/* Library Inclusion End */

/* Class Declaration Start */
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

    itemNode(const char itemName[], const int population) {
        std::strcpy(name, itemName);
        count = population;
        left = NULL;
        right = NULL;
    }
};

class treeNameNode {

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

    treeNameNode(const char name[]) {
        std::strcpy(treeName, name);
        theTree = NULL;
        left = NULL;
        right = NULL;
    }
};
/* Class Declaration End */

/* Build BST Functions Start*/
treeNameNode* add_tree_nodes(int treeNameCount) {
    // in.txt accessor
    std::ifstream in;
    in.open("in.txt");

    treeNameNode* head = nullptr;

    // Checks to see if in.txt open succesfully
    if (in.is_open() == true) {
        // for loop to iterate through contents of in.txt based on item quantities
        for(int i = 0; i <= treeNameCount; i++) {
            /* String collection start */
            std::string txt;
            std::getline(in, txt);

            char buffer[60];
            std::strcpy(buffer, txt.c_str());

            char substring_one[20];
            std::sscanf(buffer, "%s", substring_one);
            /* String collection start */

            treeNameNode* new_node = new treeNameNode(substring_one);

            // Conditional to skip first line of text file
            if (i != 0) {
                if (head == nullptr) {
                    head = new_node;
                } else {
                    
                    treeNameNode* current = head;
                    while (current->left != nullptr) {
                        current = current->left;
                    }
                    current->left = new_node;
                }
            }
        }
    } else {
        // Output errer message should the file fail to open
        std::cerr << "Error: Failed to open in.txt" << std::endl;
    }

    in.close();
    return head;
}

void add_items_to_tree(int treeNameCount, int itemCount, treeNameNode* tree) {
    // in.txt accessor
    std::ifstream in;
    in.open("in.txt");

    // Checks to see if in.txt open succesfully
    if (in.is_open() == true) {
        // for loop to iterate through contents of in.txt based on item quantities
        for(int i = 0; i <= treeNameCount + itemCount + 1; i++) {
            /* String collection start */
            std::string txt;
            std::getline(in, txt);

            char buffer[60];
            std::strcpy(buffer, txt.c_str());

            char substring_one[20];
            char substring_two[20];
            char substring_three[20];
            std::sscanf(buffer, "%s %s %s", substring_one, substring_two, substring_three);
            /* String collection start */

            if (i != 0 && i > treeNameCount + 1 && i < treeNameCount + itemCount + 1) {
                // process_item_addition(tree, substring_one, substring_two, std::stoi(substring_three));
            }
        }
    }

    in.close();
}

void process_item_addition(treeNameNode* tree, std::string type, std::string item, int data) {

}
/* Build BST Functions Start*/

int main() {
    /* Determin Item Quantities Start */
    int treeNameCount = 0;
    int itemCount = 0;
    int queryCount = 0;

    // Update variable quantities
    FILE *collect = fopen("in.txt", "r");
    fscanf(collect, "%d %d %d", &treeNameCount, &itemCount, &queryCount);
    /* Determin Item Quantities End */

    treeNameNode* head = add_tree_nodes(treeNameCount);
    add_items_to_tree(treeNameCount, itemCount, head);

    while (head != nullptr) {
        std::cout << head->treeName << std::endl;
        head = head->left;
    }
    return 0;
}
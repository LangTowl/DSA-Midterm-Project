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
        strcpy(name, itemName);
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
        strcpy(treeName, name);
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
            // Copys in.txt line contents and breaks into substrings
            std::string txt;
            std::getline(in, txt);

            char buffer[60];
            std::strcpy(buffer, txt.c_str());

            char substring_one[20];
            std::sscanf(buffer, "%s", substring_one);

            treeNameNode* new_node = new treeNameNode(substring_one);

            // Conditional to skip first line of text file
            if (i != 0) {
                // Conditional to see if pointer is empty
                if (head == nullptr) {
                    head = new_node;
                } else {
                    head->left = new_node;
                    head = head->left;
                }

                std::cout << head->treeName << std::endl;
            }
        }
    } else {
        // Output errer message should the file fail to open
        std::cerr << "Error: Failed to open in.txt" << std::endl;
    }

    in.close();
    return head;
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

    treeNameNode* test = add_tree_nodes(treeNameCount);

    return 0;
}
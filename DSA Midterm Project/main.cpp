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
treeNameNode* build_bst(int treeNameCount, int itemCount, int queryCount) {

    // in.txt accessor
    std::ifstream in;
    in.open("in.txt");
    
    // Checks to see if in.txt open succesfully
    if (in.is_open() == true) {

        // for loop to iterate through contents of in.txt based on item quantities
        for(int i = 1; i <= (treeNameCount + itemCount + queryCount + 1); i++) {

            // Copys in.txt line contents and breaks into substrings
            std::string txt;
            std::getline(in, txt);

            char buffer[60];
            std::strcpy(buffer, txt.c_str());

            char substring_one[20];
            char substring_two[20];
            char substring_three[20];

            std::sscanf(buffer, "%s %s %s", substring_one, substring_two, substring_three);

            // Code to run for n number of trees
            if (i != 1 && i <= treeNameCount + 1) {
                // std::cout << "NODE -> "<< substring_one << std::endl;
            }

            // Code to run for n number of items
            if (i > treeNameCount + 1 && i <= treeNameCount + itemCount + 1) {
                // std::cout << "OBJ -> "<< substring_one << std::endl;
            }

            // Code to run for n number of queries
            if (i > treeNameCount + itemCount + 1 && i <= treeNameCount + itemCount + queryCount + 1) {
                // std::cout << "QUERY -> "<< substring_one << std::endl;
            }
        }
    } else {
        std::cerr << "Error: Failed To Open in.txt file." << std::endl;
    }

    treeNameNode* test = new treeNameNode("name");

    return test;
}
/* Build BST Functions Start*/

/* BST Addition -> treeNameNode Start */

/* BST Addition -> treeNameNode Start */

int main() {
    /* Determin Item Quantities Start */
    int treeNameCount = 0;
    int itemCount = 0;
    int queryCount = 0;

    // Update variable quantities
    FILE *collect = fopen("in.txt", "r");
    fscanf(collect, "%d %d %d", &treeNameCount, &itemCount, &queryCount);
    /* Determin Item Quantities End */

    treeNameNode* root = build_bst(treeNameCount, itemCount, queryCount);

    std::cout << root->treeName;
    return 69;
}
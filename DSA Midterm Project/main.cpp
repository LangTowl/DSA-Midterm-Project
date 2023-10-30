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

    itemNode(char itemName[], int population) {
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

    treeNameNode(char name[]) {
        strcpy(treeName, name);
        theTree = NULL;
        left = NULL;
        right = NULL;
    }
};
/* Class Declaration End */

int main() {
    // Varaibles to store catagoy quantities
    int treeNameCount = 0;
    int itemCount = 0;
    int queryCount = 0;

    // Update variable quantities
    FILE *collect = fopen("in.txt", "r");
    fscanf(collect, "%d %d %d", &treeNameCount, &itemCount, &queryCount);

    // Output Variable quantities
    // std::cout << treeNameCount << " " << itemCount << " " << queryCount << std::endl;

    // testing
    std::ifstream in;
    
    in.open("in.txt");
    
    if (in.is_open() == true) {
        
        std::string txt;

        for(int i = 1; i <= (treeNameCount + itemCount + queryCount + 1); i++) {
            std::getline(in, txt);
            if (i != 1 && i <= treeNameCount + 1) {
                std::cout << "NODE -> "<< txt << std::endl;
            }

            if (i > treeNameCount + 1 && i <= treeNameCount + itemCount + 1) {
                std::cout << "OBJ -> "<< txt << std::endl;
            }
        }
    }

    return 69;
}
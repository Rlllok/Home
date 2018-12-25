#include "CTreeNode.cpp"
#include "CBinTree.cpp"


#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

int main()
{
    CBinTree trainTree;

    std::ifstream file("trainData.csv");
    if (!file.is_open()) {
        std::cout << "ERROR! File was not opened" << '\n';
    }

    while (file.good()) {
        std::string trainNumStr;
        std::string desStr;
        std::string timeStr;

        getline(file, trainNumStr, ',');
        getline(file, desStr, ',');
        getline(file, timeStr);

        int trainNum = std::atoi(trainNumStr.c_str());
        int time = std::atoi(timeStr.c_str());
        if (trainNum && time){
            Node node(trainNum, desStr, time);
            trainTree.AddLeaf(node);
        }
    }
    file.close();

    trainTree.PrintInNumOrder();

    int input = 0;

    while (input != -1) {
        std::cout << "Delete train number: " << '\n';
        std::cin >> input;
        if (input != -1) {
            trainTree.RemoveNode(input);
            trainTree.PrintInNumOrder();
        }
    }

    return 0;
}

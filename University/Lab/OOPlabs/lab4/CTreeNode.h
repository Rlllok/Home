#pragma once
#include <string>

class Node
{
private:

public:
    int m_TrainNumber;
    std::string m_Destination;
    int m_DepartureTime;
    Node* left;
    Node* right;

    Node();
    Node(int m_TrainNumber, std::string m_Destination, int m_DepartureTime);
    void PrintNode();
    bool operator< (Node node);
    bool operator> (Node node);
    bool operator== (Node node);
    Node& operator= (const Node& node);
};

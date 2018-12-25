#pragma once
#include "CTreeNode.h"

class CBinTree
{
private:
    Node treeNode;
    Node* root;

    Node* CreatLeaf(Node node);
    void AddLeafPrivate(Node node, Node* Ptr);
    void PrintInNumOrderPrivate(Node* Ptr);
    Node* ReturnNode(Node node, Node* Ptr);
    Node FindSmallestNodePrivate(Node* Ptr);
    void RemoveNodePrivate(int m_TrainNumber, Node* parent);
    void RemoveRootMatch();
    void RemoveMatch(Node* parent, Node* mathc, bool left);
    void PrintByDestinationPrivate(std::string m_Destination, Node* Ptr);
public:
    CBinTree();
    void AddLeaf(Node node);
    void PrintInNumOrder();
    void PrintNodeByNum(Node node);
    void PrintNodeByNum(int m_TrainNumber);
    Node FindSmallestNode();
    void RemoveNode(int m_TrainNumber);
    void PrintByDestination(std::string m_Destination);
};

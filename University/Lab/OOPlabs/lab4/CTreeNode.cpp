#include "CTreeNode.h"
#include <string>
#include <iostream>

Node::Node()
{
    m_TrainNumber = 0;
    m_Destination = "\0";
    m_DepartureTime = 0;
    left = NULL;
    right = NULL;
}
Node::Node(int m_TrainNumber, std::string m_Destination, int m_DepartureTime)
{
    this->m_TrainNumber = m_TrainNumber;
    this->m_Destination = m_Destination;
    this->m_DepartureTime = m_DepartureTime;
    this->left = NULL;
    this->right = NULL;
}

void Node::PrintNode()
{
    std::cout << m_TrainNumber << "||";
    std::cout << m_Destination << "||";
    std::cout << m_DepartureTime << "||\n";
}

bool Node::operator< (Node node)
{
    return (this->m_TrainNumber < node.m_TrainNumber) ? true: false;
}

bool Node::operator> (Node node)
{
    return (this->m_TrainNumber > node.m_TrainNumber) ? true: false;
}

bool Node::operator== (Node node)
{
    return (this->m_TrainNumber == node.m_TrainNumber) ? true: false;
}

Node& Node::operator= (const Node& node)
{
    if (this == &node)
    {
        return *this;
    }
    this->m_TrainNumber = node.m_TrainNumber;
    this->m_Destination = node.m_Destination;
    this->m_DepartureTime = node.m_DepartureTime;
    return *this;
}

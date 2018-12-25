#include "CBinTree.h"

#include <iostream>
#include <cstdlib>
#include <string>

CBinTree::CBinTree()
{
    root = NULL;
}

Node* CBinTree::CreatLeaf(Node node)
{
    Node* n = new Node;
    *n = node;

    return n;
}

void CBinTree::AddLeaf(Node node)
{
    AddLeafPrivate(node, root);
}

void CBinTree::AddLeafPrivate(Node node, Node* Ptr)
{
    if (root == NULL) {
        root = CreatLeaf(node);
    } else if (node < *Ptr) {
        if (Ptr->left != NULL) {
            AddLeafPrivate(node, Ptr->left);
        } else {
            Ptr->left = CreatLeaf(node);
        }
    } else if (node > *Ptr) {
        if (Ptr->right != NULL) {
            AddLeafPrivate(node, Ptr->right);
        } else {
            Ptr->right = CreatLeaf(node);
        }
    } else {
        std::cout << "Train number " << node.m_TrainNumber << " has already been added to the tree." << '\n';
    }
}

void CBinTree::PrintInNumOrder()
{
    PrintInNumOrderPrivate(root);
}

void CBinTree::PrintInNumOrderPrivate(Node* Ptr)
{
    if (root != NULL) {
        if (Ptr->left !=NULL) {
            PrintInNumOrderPrivate(Ptr->left);
        }
        Ptr->PrintNode();
        if (Ptr->right != NULL) {
            PrintInNumOrderPrivate(Ptr->right);
        }
    } else {
        std::cout << "The tree is empty!" << '\n';
    }
}

Node* CBinTree::ReturnNode(Node node, Node* Ptr)
{
    if (Ptr != NULL) {
        if (*Ptr == node) {
            return Ptr;
        } else {
            if (node < *Ptr) {
                return ReturnNode(node, Ptr->left);
            } else {
                return ReturnNode(node, Ptr->right);
            }
        }
    } else {
        return NULL;
    }

}

void CBinTree::PrintNodeByNum(Node node)
{
    Node* Ptr = ReturnNode(node, root);

    if (Ptr != NULL) {
        Ptr->PrintNode();
    } else {
        std::cout << "Train number " << node.m_TrainNumber << " is not in the tree." << '\n';
    }
}

void CBinTree::PrintNodeByNum(int m_TrainNumber) {
    Node node;
    node.m_TrainNumber = m_TrainNumber;
    Node* Ptr = ReturnNode(node, root);

    if (Ptr != NULL) {
        Ptr->PrintNode();
    } else {
        std::cout << "Train number " << node.m_TrainNumber << " is not in the tree." << '\n';
    }
}

Node CBinTree::FindSmallestNode()
{
    return FindSmallestNodePrivate(root);
}

Node CBinTree::FindSmallestNodePrivate(Node* Ptr)
{
    if (root == NULL) {
        Node node;
        std::cout << "The tree is empty!" << '\n';
        return node;
    } else {
        if (Ptr->left != NULL) {
            return FindSmallestNodePrivate(Ptr->left);
        } else {
            return *Ptr;
        }
    }
}

void CBinTree::RemoveNode(int m_TrainNumber)
{
    RemoveNodePrivate(m_TrainNumber, root);
}

void CBinTree::RemoveNodePrivate(int m_TrainNumber, Node* parent)
{
    if (root != NULL) {
        if (root->m_TrainNumber == m_TrainNumber) {
            RemoveRootMatch();
        } else {
            if (m_TrainNumber < parent->m_TrainNumber && parent->left != NULL) {
                parent->left->m_TrainNumber == m_TrainNumber ?
                RemoveMatch(parent, parent->left, true) :
                RemoveNodePrivate(m_TrainNumber, parent->right);
            } else if (m_TrainNumber > parent->m_TrainNumber && parent->right != NULL) {
                parent->right->m_TrainNumber == m_TrainNumber ?
                RemoveMatch(parent, parent->right, false) :
                RemoveNodePrivate(m_TrainNumber, parent->right);
            } else {
                std::cout << "The train number " << m_TrainNumber << " was not found." << '\n';
            }
        }
    } else {
        std::cout << "The tree is empty!" << '\n';
    }
}

void CBinTree::RemoveRootMatch()
{
    if (root != NULL) {
        Node* delPtr = root;
        int rootTrainNum = root->m_TrainNumber;
        Node smallestTrainNum;

        //0 children
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
            delete delPtr;
        }
        //1 child
        else if (root->left == NULL && root->right != NULL){
            root = root->right;
            delPtr->right = NULL;
            delete delPtr;
            std::cout << "The root node with train number " << rootTrainNum
            << " was deleted." << "The new root contains train number " << root->m_TrainNumber <<'\n';
        } else if (root->left != NULL && root->right == NULL){
            root = root->left;
            delPtr->left = NULL;
            delete delPtr;
            std::cout << "The root node with train number " << rootTrainNum
            << " was deleted." << "The new root contains train number " << root->m_TrainNumber <<'\n';
        }
        // 2 children
        else {
            smallestTrainNum = FindSmallestNodePrivate(root->right);
            RemoveNodePrivate(smallestTrainNum.m_TrainNumber, root);
            *root = smallestTrainNum;
            std::cout << "The root containing train number " << rootTrainNum <<
            " was overwritten with train number " << root->m_TrainNumber <<'\n';
        }

    } else {
        std::cout << "The tree is empty!" << '\n';
    }
}

void CBinTree::RemoveMatch(Node* parent, Node* match, bool left)
{
    if (root != NULL) {
        Node* delPtr = NULL;
        int matchTrainNum = match->m_TrainNumber;
        Node smallestTrainNum;

        //0 children
        if (match->left == NULL && match->right == NULL) {
            delPtr = match;
            left == true ? parent->left = NULL : parent->right = NULL;
            delete delPtr;
            std::cout << "The node containing train number " << matchTrainNum <<
            " was removed"<< '\n';
        }
        //1 child
        else if (match->left == NULL && match->right != NULL){
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = NULL;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing train number " << matchTrainNum <<
            " was removed"<< '\n';
        } else if (match->left != NULL && match->right == NULL){
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = NULL;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing train number " << matchTrainNum <<
            " was removed"<< '\n';
        }
        // 2 children
        else {
            smallestTrainNum = FindSmallestNodePrivate(match->right);
            RemoveNodePrivate(smallestTrainNum.m_TrainNumber, match);
            *match = smallestTrainNum;
        }
    } else {
        std::cout << "The tree is empty!" << '\n';
    }
}

void CBinTree::PrintByDestination(std::string m_Destination)
{
    PrintByDestinationPrivate(m_Destination, root);
}

void CBinTree::PrintByDestinationPrivate(std::string m_Destination, Node* Ptr)
{
    if (root != NULL) {
        if (Ptr->left != NULL) {
            PrintByDestinationPrivate(m_Destination, Ptr->left);
        }
        if (Ptr->m_Destination == m_Destination) {
            Ptr->PrintNode();
        }
        if (Ptr->right != NULL) {
            PrintByDestinationPrivate(m_Destination, Ptr->right);
        }
    } else {
        std::cout << "The tree is empty" << '\n';
    }
}

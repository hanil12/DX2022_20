#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

void BinarySearchTree::Insert(int key)
{
    Node* newNode = new Node(key);

    if (_root == nullptr)
    {
        _root = newNode;
        return;
    }

    Node* node = _root;
    Node* parent = nullptr;

    while (true)
    {
        if (node == nullptr)
            break;
        parent = node;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    newNode->parent = parent;
    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* node)
{
    // ���� ��ȸ : ��Ʈ ~ ���� ~ ������
    // ���� ��ȸ : ���� ~ ��Ʈ ~ ������
    // ���� ��ȸ : ���� ~ ������ ~ ��Ʈ
    if (node == nullptr)
        return;

    cout << node->key << endl;
    PrintTree(node->left);
    PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
    return nullptr;
}

Node* BinarySearchTree::Min(Node* node)
{
    return nullptr;
}

Node* BinarySearchTree::Max(Node* node)
{
    return nullptr;
}

Node* BinarySearchTree::Previous(Node* node)
{
    return nullptr;
}

Node* BinarySearchTree::Next(Node* node)
{
    return nullptr;
}

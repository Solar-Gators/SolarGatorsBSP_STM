// File Name: Map.hpp
// Description: This is a module that implements an associated AVL tree
// Author: John Carr
// Date Created: 10/27/2021
// Last Modified by:
// Date Last Modified:

//Header Guards
#ifndef SOLARGATORS_BSP_CONTAINERS_INC_MAP_H_
#define SOLARGATORS_BSP_CONTAINERS_INC_MAP_H_

//Include Files
#include <iterator>

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */

//C Public Variables

//C Public Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface

//Class Definitions
namespace SolarGators::Containers
{
  template<typename KEY_T, typename DATA_T, int SIZE>
  class Map
  {
  public:
    Map();
    struct Node
    {
      KEY_T key;
      DATA_T* data;
      Node* left;
      Node* right;
      uint32_t height;
    };
    bool Insert(KEY_T key, DATA_T* new_element);
    DATA_T* Find(KEY_T key);
    static constexpr uint32_t MAX_NODES = SIZE;
    Node array[SIZE];
  private:
    Node* root_;
    Node* AddNode(Node* node, Node* new_node);
    Node* NewNode(KEY_T key, DATA_T* new_element);
    Node* LeftRotate(Node* x);
    Node* RightRotate(Node* y);
    uint32_t current_size_;
    uint32_t Height(Node *N);
    uint32_t GetBalance(Node *N);
    Node* FindNode(Node* node, KEY_T key);
    uint32_t Max(uint32_t a, uint32_t b);
  };

  template<typename KEY_T, typename DATA_T, int SIZE>
  Map<KEY_T, DATA_T, SIZE>::Map():current_size_(0)
  {
    root_ = nullptr;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  bool Map<KEY_T, DATA_T, SIZE>::Insert(KEY_T key, DATA_T* new_element)
  {
    //Only insert a node if there is room
    if(current_size_ < MAX_NODES && new_element != nullptr)
    {
      root_ = AddNode(root_, NewNode(key, new_element));
      return true;
    }
    return false;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  typename Map<KEY_T, DATA_T, SIZE>::Node* Map<KEY_T, DATA_T, SIZE>::NewNode(KEY_T key, DATA_T* new_element)
  {
      Node* node = &array[current_size_++];
      node->data = new_element;
      node->key = key;
      node->left = nullptr;
      node->right = nullptr;
      return node;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  typename Map<KEY_T, DATA_T, SIZE>::Node* Map<KEY_T, DATA_T, SIZE>::AddNode(Node* node, Node* new_node)
  {
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)
      return new_node;

    if (new_node->key < node->key)
        node->left = AddNode(node->left, new_node);
    else if (new_node->key > node->key)
        node->right = AddNode(node->right, new_node);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + Max(Height(node->left),
                        Height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = GetBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && new_node->key < node->left->key)
        return RightRotate(node);

    // Right Right Case
    if (balance < -1 && new_node->key > node->right->key)
        return LeftRotate(node);

    // Left Right Case
    if (balance > 1 && new_node->key > node->left->key)
    {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && new_node->key < node->right->key)
    {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  uint32_t Map<KEY_T, DATA_T, SIZE>::Height(Node *N)
  {
    if (N == nullptr)
      return 0;
    return N->height;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  uint32_t Map<KEY_T, DATA_T, SIZE>::GetBalance(Node *N)
  {
    if (N == nullptr)
      return 0;
    return Height(N->left) - Height(N->right);
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  typename Map<KEY_T, DATA_T, SIZE>::Node* Map<KEY_T, DATA_T, SIZE>::LeftRotate(Node *x)
  {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = Max(Height(x->left),
        Height(x->right)) + 1;
    y->height = Max(Height(y->left),
        Height(y->right)) + 1;

    // Return new root
    return y;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  typename Map<KEY_T, DATA_T, SIZE>::Node* Map<KEY_T, DATA_T, SIZE>::RightRotate(Node *y)
  {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = Max(Height(y->left),
        Height(y->right)) + 1;
    x->height = Max(Height(x->left),
        Height(x->right)) + 1;

    // Return new root
    return x;
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  DATA_T* Map<KEY_T, DATA_T, SIZE>::Find(KEY_T key)
  {
    Node* foundNode = FindNode(root_, key);
    if(foundNode == nullptr)
    {
      return nullptr;
    }
    else
    {
      return foundNode->data;
    }
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  typename Map<KEY_T, DATA_T, SIZE>::Node* Map<KEY_T, DATA_T, SIZE>::FindNode(Node* node, KEY_T key)
  {
    //Can't find node return nullptr
    if(node == nullptr)
    {
      return node;
    }

    if(key < node->key)
    {
      return FindNode(node->left, key);
    }
    else if(key > node->key)
    {
      return FindNode(node->right, key);
    }
    else
    {
      //If key == node_key then return the node
      return node;
    }
  }

  template<typename KEY_T, typename DATA_T, int SIZE>
  uint32_t Map<KEY_T, DATA_T, SIZE>::Max(uint32_t a, uint32_t b)
  {
      return (a > b)? a : b;
  }

}

#endif //End Header Guard

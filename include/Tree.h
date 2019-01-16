#pragma once

#include <memory>
#include <c++/7/utility>
#include "Exception.h"

template <typename KeyType, typename ValueType>
struct Node
{
  struct Data
  {
    KeyType   _key;
    ValueType _value;
  };

  using Ptr     = std::shared_ptr<Node>;

  explicit Node(const KeyType& key_, const ValueType& value_):
  _data(Data{key_, value_}){}

  Data    _data;
  Ptr     _leftPtr  = nullptr;
  Ptr     _rightPtr = nullptr;
};

template <typename KeyType, typename ValueType>
class Tree
{
  using NodePtr       = typename Node<KeyType, ValueType>::Ptr;
  using ItrReturnType = std::pair<NodePtr , bool>;
  
public:
  Tree() = default;

  auto find(const KeyType& key_) const -> NodePtr;
  auto insert(const KeyType &key_, const ValueType &value_) -> ItrReturnType;
  auto size() const -> size_t;

private:
  static auto find(const NodePtr& nodePtr_, const KeyType& key_) -> NodePtr ;
  static auto insert(NodePtr &nodePtr_, const KeyType &key_, const ValueType &value_, bool &inserted) -> NodePtr&;

  NodePtr _rootNodePtr = nullptr;
  size_t  _size = 0;
};

// Implementation of declared functions

template<typename K, typename V>
auto Tree<K, V>::find(const K &key_) const -> Tree::NodePtr
{
  return find(_rootNodePtr, key_);
}

template<typename K, typename V>
auto Tree<K, V>::insert(const K &key_, const V &value_) -> Tree::ItrReturnType
{
  bool inserted = true;
  auto nodePtr = insert(_rootNodePtr, key_, value_, inserted);
  if (inserted) ++_size;

  return Tree::ItrReturnType{nodePtr, inserted};
}

template<typename K, typename V>
auto Tree<K, V>::size() const -> size_t 
{
  return _size;
}

template<typename K, typename V>
auto Tree<K, V>::find(const Tree::NodePtr &nodePtr_, const K &key_) -> Tree::NodePtr
{
  if (!nodePtr_) return nullptr;

  if (key_ <  nodePtr_->_data._key) return find(nodePtr_->_rightPtr, key_);
  if (key_ >  nodePtr_->_data._key) return find(nodePtr_->_leftPtr,  key_);
  if (key_ == nodePtr_->_data._key) return nodePtr_;
}

template<typename K, typename V>
auto Tree<K, V>::insert(NodePtr &nodePtr_, const K &key_, const V &value_, bool &inserted) -> NodePtr&
{
  if (!nodePtr_)
  {
    nodePtr_ = std::make_shared<typename NodePtr::element_type>(key_, value_);
  }

  else if (key_ < nodePtr_->_data._key)
  {
    nodePtr_->_leftPtr = insert(nodePtr_->_leftPtr, key_, value_, inserted);
  }

  else if (key_ > nodePtr_->_data._key)
  {
    nodePtr_->_rightPtr = insert(nodePtr_->_rightPtr, key_, value_, inserted);
  }

  else if (key_ == nodePtr_->_data._key)
  {
    inserted = false;
    // leave the nodePtr untouched
    // nodePtr_->_data._value = value_;
  }

  return nodePtr_;
}
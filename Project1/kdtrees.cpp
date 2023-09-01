#include <tuple>
#include <iostream>
#include "kdtrees.h"

template <typename ...T>
KdNode<T...>::KdNode(T... el) {
    keys = std::make_tuple(el...);
    left = right = nullptr;
}

template <typename... T>
KdNode<T...>::KdNode(std::tuple<T...> keys) {
    this->keys = keys; left = right = nullptr;
}

template<typename... T>
KdTree<T...>::KdTree() { root = 0; }


template<typename... T>
KdTree<T...>::KdTree(KdNode<T...>* root) { this->root = root; }

template<typename... T>
void KdTree<T...>::insert(const std::tuple<T...>& keys) { this->root = insert<0>(this->root, keys); }

template<typename... T>
KdNode<T...>* KdTree<T...>::search(const std::tuple<T...>& keys) { return search<0>(this->root, keys); }

template<typename... T>
void KdTree<T...>::remove(const std::tuple<T...>& keys) { this->root = remove<0>(this->root, keys); }

template<typename... T>
template<std::size_t i>
KdNode<T...>* KdTree<T...>::insert(KdNode<T...>* node, const std::tuple<T...>& el)
{
    if (!node) return new KdNode<T...>(el);

    constexpr int k = (i + 1) % node->size;
    if (std::get<i>(el) < node->template get<i>())
        node->left = insert<k>(node->left, el);
    else if (std::get<i>(el) > node->template get<i>())
        node->right = insert<k>(node->right, el);

    return node;
}

template<typename... T>
template<std::size_t i>
KdNode<T...>* KdTree<T...>::search(KdNode<T...>* node, const std::tuple<T...>& el)
{
    constexpr int k = (i + 1) % node->size;
    if (node->keys == el) 
        return node;
    else if (std::get<i>(el) < node->template get<i>())
        return search<k>(node->left, el);
    else if (std::get<i>(el) > node->template get<i>())
        return search<k>(node->right, el);

    return nullptr;
}


template<typename... T>
template<std::size_t i>
KdNode<T...>* KdTree<T...>::remove(KdNode<T...>* node, const std::tuple<T...>& el)
{
    constexpr int k = (i + 1) % node->size;
    if (node->keys == el)
    {
        if (!node->left && !node->right)
        {
            delete node;
            return nullptr;
        }
        else if (!node->left)
        {

            auto *right_child = node->right;
            delete node;
            return right_child;
        }
        else if (!node->right) {
            auto *left_child = node->left;
            delete node;
            return left_child;
        }
        else {
            auto *rightmost_child = get_inorder_predecessor(node);
            auto *left_child = node->left;
            rightmost_child->right = node->right;

            delete node;
            return left_child;
        }
    }
    else if (std::get<i>(el) < node->template get<i>())
        node->left = remove<k>(node->left, el);
    else if (std::get<i>(el) > node->template get<i>())
        node->right = remove<k>(node->right, el);

    return node;
}

template<typename... T>
KdNode<T...> *get_inorder_predecessor(KdNode<T...> *node) {
    node = node->left;
    while (node->right) node = node->right;
    return node;
}

template class KdNode<int, int>;
template class KdTree<int, int>;
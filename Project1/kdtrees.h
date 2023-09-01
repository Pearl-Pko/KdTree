#ifndef KD_NODE_H
#define KD_NODE_H

#include <tuple>
#include <iostream>

template<typename... T>
class KdNode
{
public:
    KdNode(T... el);

    KdNode(std::tuple<T...> keys);

    template <std::size_t i>
    auto get()
    {
        return std::get<i>(keys);
    }

    KdNode<T...> *left, *right;

    static constexpr std::size_t size = sizeof...(T);

    std::tuple<T...> keys;
};

template<typename... T>
class KdTree
{
public:
    KdTree();
    KdTree(KdNode<T...>* root);

    KdNode<T...>* root;

    void insert(const std::tuple<T...>& keys);

    KdNode<T...> *search(const std::tuple<T...>& keys);

    void remove(const std::tuple<T...>& keys);

private:
    template<std::size_t i>
    KdNode<T...> *search(KdNode<T...>* node,  const std::tuple<T...>& el);

    template<std::size_t i>
    KdNode<T...> *insert(KdNode<T...>* node, const std::tuple<T...>& el);

    template<std::size_t i>
    KdNode<T...> *remove(KdNode<T...>* node, const std::tuple<T...>& el);
};

#endif
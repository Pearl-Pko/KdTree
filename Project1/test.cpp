#include <tuple>
#include "kdtrees.h"

int main()
{
    auto* root = new KdNode<int, int>(40, 60);

    root->left = new KdNode<int, int>(20, 80);

    root->left->left = new KdNode<int, int>(30, 60);

    root->right = new KdNode<int, int>(80, 40);

    root->right->left = new KdNode<int, int>(80, 20);

    root->right->left->left = new KdNode<int, int>(60, 20);

    root->right->right = new KdNode<int, int>(60, 80);

    auto tree = KdTree<int, int>(root);

    //auto tu = std::make_tuple(20, 80);
    auto *value= tree.search(std::make_tuple(20, 80));
    //std::cout << da;

    tree.remove(std::make_tuple(40, 60));

    tree.insert(std::make_tuple(80, 90));
}
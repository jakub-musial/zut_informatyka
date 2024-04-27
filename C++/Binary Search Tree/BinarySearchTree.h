#pragma once
#include <iostream>

template <typename T>
struct Node
{
	T data = NULL;
	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template <typename T>
class BinarySearchTree
{
private:
	Node<T>* root;
	size_t size;

	void display_tree_helper(Node<T>* root, int space);
	Node<T>* find_min(Node<T>* root);
	int height_helper(Node<T>* root);
	int max_value(int a, int b);
	void preorder_helper(Node<T>* root);
	void inorder_helper(Node<T>* root);

public:
	BinarySearchTree();

	void add(T data);
	Node<T>* find(T key);
	void delete_node(Node<T>* node);
	void preorder();
	void inorder();
	Node<T>* postorder(Node<T>* root);
	void clear();
	int height();
	void display_tree();
};


template <typename T> BinarySearchTree<T>::BinarySearchTree() : root(nullptr), size(0) {}

template <typename T> void BinarySearchTree<T>::add(T data)
{
	Node<T>* new_node = new Node<T>;
	new_node->data = data;
	
	if (root == nullptr)
	{
		root = new_node;
		new_node->parent = nullptr;
	}
	else
	{
		Node<T>* parent = nullptr;
		Node<T>* current = root;
		while (current != nullptr)
		{
			parent = current;
			if (data < current->data) current = current->left;
			else                      current = current->right;
		}

		if (data < parent->data)
		{
			parent->left = new_node;
			new_node->parent = parent;
		}
		else
		{
			parent->right = new_node;
			new_node->parent = parent;
		}
	}
	size++;
}

template <typename T> Node<T>* BinarySearchTree<T>::find_min(Node<T>* root)
{
	Node<T>* tmp = root;
	while (tmp->left != nullptr)
		tmp = tmp->left;
	
	return tmp;
}

template <typename T> Node<T>* BinarySearchTree<T>::find(T key)
{
	Node<T>* tmp = root;
	while (tmp != nullptr)
	{
		if (key == tmp->data)     return tmp;
		else if (key < tmp->data) tmp = tmp->left;
		else                      tmp = tmp->right;
	}
	return nullptr;
}

template <typename T> void BinarySearchTree<T>::delete_node(Node<T>* node)
{
	if (node->left == nullptr && node->right == nullptr) // deleting node with no children
	{
		(node->parent->left == node) ? node->parent->left = nullptr : node->parent->right == nullptr;
		size--;
		delete node;
	}
	else if (node->right == nullptr) // deleting node with only left child
	{
		(node->parent->left == node) ? node->parent->left = node->left : node->parent->right = node->left;
		size--;
		delete node;
	}
	else if (node->left == nullptr) // deleting node with only right child
	{
		(node->parent->left == node) ? node->parent->left = node->right : node->parent->right = node->right;
		size--;
		delete node;
	}
	else                            // deleting node with two children
	{
		// merging two branches
		Node<T>* tmp = find_min(node->right);
		tmp->left = node->left; // connecting left branch to right branch
		node->left = nullptr;

		// connecting merged branches to tree
		(node->parent->left == node) ? node->parent->left = node->right : node->parent->right = node->right;
		delete node;
	}
}

template <typename T> void BinarySearchTree<T>::preorder_helper(Node<T>* root) // root left right
{
	if (root == nullptr) return;
	std::cout << root->data << ", ";
	preorder_helper(root->left);
	preorder_helper(root->right);
}

template <typename T> void BinarySearchTree<T>::preorder()
{
	preorder_helper(root);
}

template <typename T> void BinarySearchTree<T>::inorder_helper(Node<T>* root) // left root right
{
	if (root == nullptr) return;
	inorder_helper(root->left);
	std::cout << root->data << ", ";
	inorder_helper(root->right);
}

template <typename T> void BinarySearchTree<T>::inorder()
{
	inorder_helper(root);
}

template <typename T> Node<T>* BinarySearchTree<T>::postorder(Node<T>* root) // left right root
{
	if (root == nullptr) return nullptr;
	postorder(root->left);
	postorder(root->right);
	return root;
}

template <typename T> void BinarySearchTree<T>::clear()
{
	delete postorder(root);
	root = nullptr;
	size = 0;
}

template <typename T> int BinarySearchTree<T>::height()
{
	return height_helper(root);
}

template <typename T> int BinarySearchTree<T>::height_helper(Node<T>* root)
{
	if (root == nullptr)
		return -1;
	
	return max_value(height_helper(root->left), height_helper(root->right)) + 1;
}

template <typename T> int BinarySearchTree<T>::max_value(int a, int b)
{
	if (a < b) return b;
	else if (a > b) return a;
	else return a;
}

template <typename T> void BinarySearchTree<T>::display_tree()
{

	display_tree_helper(root, 0);
}

template <typename T> void BinarySearchTree<T>::display_tree_helper(Node<T>* tmp_root, int space)
{
	if (tmp_root == nullptr)
		return;

	space += 10;

	display_tree_helper(tmp_root->right, space);

	std::cout << std::endl;
	for (int i = 10; i < space; i++)
		std::cout << " ";
	std::cout << tmp_root->data << "  " << tmp_root << " parent: " << tmp_root << "\n";

	display_tree_helper(tmp_root->left, space);
}
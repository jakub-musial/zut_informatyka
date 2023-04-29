#pragma once
#include <iostream>

enum Color { RED, BLACK };


template <typename T>
struct Node
{
	T data = NULL;
	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Color color = RED;
};

template <typename T>
class RedBlackTree
{
private:
	Node<T>* root;
	size_t size;

	void preorder_helper(Node<T>* root);
	void inorder_helper(Node<T>* root);
	int height_helper(Node<T>* root);
	void balance_tree(Node<T>* node);
	void recolor(Node<T>* node);
	void rotate_left(Node<T>* node);
	void rotate_right(Node<T>* node);
	void display_tree_helper(Node<T>* tmp_root, int space);

public:
	RedBlackTree() : size(0), root(nullptr) {};

	void insert(T data);
	Node<T>* find(T key);
	void preorder();
	void inorder();
	Node<T>* postorder(Node<T>* root);
	void clear();
	int height();
	void display_tree();
};


template <typename T> void RedBlackTree<T>::insert(T data)
{
	{
		Node<T>* new_node = new Node<T>;
		new_node->data = data;

		if (root == nullptr)
		{
			root = new_node;
			new_node->parent = nullptr;
			new_node->color = BLACK;
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
			balance_tree(new_node);
		}
		size++;
	}
}

template <typename T> void RedBlackTree<T>::balance_tree(Node<T>* node)
{
	if (node->parent->color == BLACK)
	{
		return;
	}
	else //RED RED conflict
	{
		Node<T>* grandparent = nullptr;
		Node<T>* parent = nullptr;

		while (node != root && node->parent->color == RED && node->color == RED)
		{
			grandparent = node->parent->parent;
			parent = node->parent;

			//CHECKING COLOR OF UNCLE NODE (PARENT'S SIBLING)

			//CASE WHEN UNCLE NODE IS BLACK
			//'parent' is left child of 'grandparent', so its sibling is right child
			if ( (grandparent->left == parent) && (grandparent->right == nullptr || grandparent->right->color == BLACK) )
			{
				grandparent->color = RED;

				//'node' is left child; LEFT LEFT situation
				if (parent->left == node)
				{
					parent->color = BLACK;
					rotate_right(node->parent);
				}
				else //'node' is right child; LEFT RIGHT situation
				{
					node->color = BLACK;
					rotate_left(node);
					rotate_right(node);
				}
			}
			//'parent' is right child of 'grandparent', so its sibling is left child
			else if ( (grandparent->right == parent) && (grandparent->left == nullptr || grandparent->left->color == BLACK ) )
			{
				grandparent->color = RED;

				//'node' is left child; RIGHT LEFT situation
				if (parent->left == node)
				{
					node->color = BLACK;
					rotate_right(node);
					rotate_left(node);
				}
				else //'node' is right child; RIGHT RIGHT situation
				{
					parent->color = BLACK;
					rotate_left(node->parent);
				}
			}
			//CASE WHEN UNCLE NODE IS RED
			else
			{
				//'parent' is left child of 'grandparent', so its sibling is right child
				if (grandparent->left == parent && grandparent->right->color == RED)
				{
					parent->color = BLACK; //!(parent->color);
					grandparent->right->color = BLACK; //!(grandparent->right->color);
				}
				//'parent' is right child of 'grandparent', so its sibling is left child
				else if (grandparent->right == parent && grandparent->left->color == RED)
				{
					parent->color = BLACK; //!(parent->color);
					grandparent->left->color = BLACK; //!(grandparent->right->color);
				}

				if (grandparent != root)
					grandparent->color = RED;

				node = grandparent;
			}
		}
		//root->color = BLACK;
	}
}

template <typename T> void RedBlackTree<T>::recolor(Node<T>* node)
{
	node->parent->color = BLACK; //!(node->parent->color);
	node->parent->parent->color = BLACK; //!(node->parent->parent->color);
}

template <typename T> void RedBlackTree<T>::rotate_left(Node<T>* node)
{
	Node<T>* tmp_parent = node->parent;
	Node<T>* tmp_left = node->left;

	tmp_parent->right = nullptr;
	node->parent = tmp_parent->parent;

	if (tmp_parent->parent != nullptr && tmp_parent->parent->left == tmp_parent)
		tmp_parent->parent->left = node;
	else if (tmp_parent->parent != nullptr && tmp_parent->parent->right == tmp_parent)
		tmp_parent->parent->right = node;

	node->left = tmp_parent;
	tmp_parent->parent = node;
	
	if (tmp_left != nullptr)
	{
		Node<T>* tmp = node->left;
		while (tmp->right != nullptr)
		{
			tmp = tmp->right;
		}
		tmp->right = tmp_left;
	}

	if (root == tmp_parent)
		root = node;
}

template <typename T> void RedBlackTree<T>::rotate_right(Node<T>* node)
{
	Node<T>* tmp_parent = node->parent;
	Node<T>* tmp_right = node->right;

	tmp_parent->left = nullptr;
	node->parent = tmp_parent->parent;

	if (tmp_parent->parent->left == tmp_parent)
		tmp_parent->parent->left = node;
	else if (tmp_parent->parent->right == tmp_parent)
		tmp_parent->parent->right = node;

	node->right = tmp_parent;
	tmp_parent->parent = node;

	if (tmp_right != nullptr)
	{
		Node<T>* tmp = node->right;
		while (tmp->right != nullptr)
		{
			tmp = tmp->left;
		}
		tmp->left = tmp_right;
	}

	if (root == tmp_parent)
		root = node;
}

template <typename T> Node<T>* RedBlackTree<T>::find(T key)
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

template <typename T> void RedBlackTree<T>::preorder_helper(Node<T>* root) // root left right
{
	if (root == nullptr) return;
	std::cout << root->data << ", ";
	preorder_helper(root->left);
	preorder_helper(root->right);
}

template <typename T> void RedBlackTree<T>::preorder()
{
	preorder_helper(root);
}

template <typename T> void RedBlackTree<T>::inorder_helper(Node<T>* root) // left root right
{
	if (root == nullptr) return;
	inorder_helper(root->left);
	std::cout << root->data << ", ";
	inorder_helper(root->right);
}

template <typename T> void RedBlackTree<T>::inorder()
{
	inorder_helper(root);
}

template <typename T> Node<T>* RedBlackTree<T>::postorder(Node<T>* root) // left right root
{
	if (root == nullptr) return nullptr;
	postorder(root->left);
	postorder(root->right);
	return root;
}

template <typename T> void RedBlackTree<T>::clear()
{
	delete postorder(root);
	root = nullptr;
	size = 0;
}

template <typename T> int RedBlackTree<T>::height_helper(Node<T>* root)
{
	if (root == nullptr)
		return -1;

	return std::max(height_helper(root->left), height_helper(root->right)) + 1;
}

template <typename T> int RedBlackTree<T>::height()
{
	return height_helper(root);
}

template <typename T> void RedBlackTree<T>::display_tree()
{
	display_tree_helper(root, 0);
}

template <typename T> void RedBlackTree<T>::display_tree_helper(Node<T>* tmp_root, int space)
{
	if (tmp_root == nullptr)
		return;

	space += 10;

	display_tree_helper(tmp_root->right, space);

	std::cout << std::endl;
	for (int i = 10; i < space; i++)
		std::cout << " ";

	std::cout << tmp_root->data << ", " << tmp_root->color << "\n";

	display_tree_helper(tmp_root->left, space);
}
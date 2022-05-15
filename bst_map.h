#ifndef _BST_MAP_
#define _BST_MAP_

#include <iostream>

using std::cout;
using std::endl;

template<typename Key, typename Value>
class BSTMap {
  struct Node {
    Key key;
    Value value;
    Node *left, *right;

    Node(Key key)
        : key(key), left(nullptr), right(nullptr) {}
  };

  Node *root;

  void print(Node *cur) const {
    if (cur != nullptr) {
      print(cur->left);
      cout << cur->key << ": " << cur->value << endl;
      print(cur->right);
    }
  }

public:
  BSTMap() : root(nullptr) {}

  BSTMap(const BSTMap& other) {
    root = deep_copy(other.root);
  }

  Node* deep_copy(const Node* root) {
    if (root == nullptr) {
      return nullptr;
    }
    Node *copy = new Node(root->key);
    copy->value = root->value;
    copy->left = deep_copy(root->left);
    copy->right = deep_copy(root->right);
    return copy;
  }

	~BSTMap() {
		delete_node(root);
	};

  Value& get_or_insert(const Key& key) {
		return get_or_insert(key, root);	
	}

  Value& get_or_insert(const Key& key, Node *&curr) {
    if (curr == nullptr) {
			curr = new Node(key);
			return curr->value;
		} else if (curr->key == key) {
			return curr->value;
		}

		if (key < curr->key) {
			return get_or_insert(key, curr->left);
		} else { // key > curr->key
			return get_or_insert(key, curr->right);
		}
	}

	void delete_node(Node *&curr) {
		if (curr) {
			delete_node(curr->left);
			delete_node(curr->right);
			delete curr;
		}
	}

  void print() const {
    print(root);
  }
};

#endif // _BST_MAP_
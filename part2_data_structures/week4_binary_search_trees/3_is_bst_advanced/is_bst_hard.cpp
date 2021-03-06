#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool Recurse(const vector<Node>& tree, int node, int last_left_key, int last_right_key) {
  /// XXX: same as is_bst.cpp :) but the >= for the last_left_key :))
  if(last_left_key != -1 && tree[node].key >= last_left_key) {
    return false;
  }
  if(last_right_key != -1 && tree[node].key < last_right_key) {
    return false;
  }
  if(tree[node].left != -1) {
    if(!Recurse(tree,tree[node].left,tree[node].key,last_right_key)) {
      return false;
    }
  }
  if(tree[node].right != -1) {
    if(!Recurse(tree,tree[node].right,last_left_key,tree[node].key)) {
      return false;
    }
  }
  return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if(tree.empty()) {
    return true;
  }
  return Recurse(tree,0,-1,-1);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

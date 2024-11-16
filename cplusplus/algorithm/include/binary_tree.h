#ifndef DATA_STRUCTURE_AND_ALGORITHM_H
#define DATA_STRUCTURE_AND_ALGORITHM_H

template <typename T> class binary_tree {
public:
  /**
   * todo:
   * 1. default ctor
   * 2. copy ctor
   * 3. copy assignment
   * 4. move ctor
   * 5. move assignment
   * 6. dtor
   *
   * 1. preorder traversal
   * 2. inorder traversal
   * 3. postorder traversal
   * 4. dump
   *
   * 1. emplace
   * 2. insert
   *
   * 1. remove
   * 2. clear
   *
   * 1. find
   * 2. count
   */

private:
  struct binary_tree_node {
    T elem;
    T *p_left;
    T *p_right;
  };
};

#endif

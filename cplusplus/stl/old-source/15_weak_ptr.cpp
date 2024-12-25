#include "test.h"

//============================================================
template <typename T> struct Node {
  std::weak_ptr<Node> next;
  T data;

  explicit Node(const T &data) : data(data) {}
};

void test_weak_ptr() {
  using IntNode = Node<int>;
  const auto node1 = std::make_shared<IntNode>(IntNode(1));
  const auto node2 = std::make_shared<IntNode>(IntNode(2));
  out("node1->data = ", node1->data, "; ",
      "node1->use_count = ", node1.use_count());
  out("node2->data = ", node2->data, "; ",
      "node2->use_count = ", node2.use_count());

  out("============================");
  node1->next = node2;
  node2->next = node1;
  out("node1->data = ", node1->data, "; ",
      "node1->use_count = ", node1.use_count());
  out("node2->data = ", node2->data, "; ",
      "node2->use_count = ", node2.use_count());

  out("============================");
  if (const auto lck = node1->next.lock()) {
    out("lck->data = ", lck->data, "; ", "lck->use_count = ", lck.use_count());
    out("node1->data = ", node1->data, "; ",
        "node1->use_count = ", node1.use_count());
  }
  out("node1->data = ", node1->data, "; ",
      "node1->use_count = ", node1.use_count());
}

//============================================================
void test() {
  // todo
  TEST(test_weak_ptr);
}

//============================================================
int main() { test(); }

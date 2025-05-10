#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

template<typename T>
class BTreeNode {
public:
    bool IsLeaf;
    std::vector<T> Keys;
    std::vector<std::shared_ptr<BTreeNode>> Children;

    BTreeNode(bool Leaf) : IsLeaf(Leaf) {}
};

template<typename T>
class BTree {
private:
    const size_t M = 4; // 阶数
    using Node = BTreeNode<T>;
    std::shared_ptr<Node> Root;

public:
    BTree() : Root(std::make_shared<Node>(true)) {}

    void Insert(const T& Key) {
        if (Root->Keys.size() == M - 1) {
            auto NewRoot = std::make_shared<Node>(false);
            NewRoot->Children.push_back(Root);
            SplitChild(NewRoot, 0);
            Root = NewRoot;
        }
        InsertNonFull(Root, Key);
    }

    void PrintTree() const {
        PrintTree(Root, 0);
    }

private:
    void InsertNonFull(std::shared_ptr<Node> NodePtr, const T& Key) {
        int i = NodePtr->Keys.size() - 1;

        if (NodePtr->IsLeaf) {
            NodePtr->Keys.insert(
                std::upper_bound(NodePtr->Keys.begin(), NodePtr->Keys.end(), Key),
                Key);
        } else {
            while (i >= 0 && Key < NodePtr->Keys[i]) i--;
            i++;
            if (NodePtr->Children[i]->Keys.size() == M - 1) {
                SplitChild(NodePtr, i);
                if (Key > NodePtr->Keys[i]) i++;
            }
            InsertNonFull(NodePtr->Children[i], Key);
        }
    }

    void SplitChild(std::shared_ptr<Node> Parent, int Index) {
        auto FullChild = Parent->Children[Index];
        auto NewChild = std::make_shared<Node>(FullChild->IsLeaf);

        size_t Mid = (M - 1) / 2;
        T MiddleKey = FullChild->Keys[Mid];

        NewChild->Keys.assign(FullChild->Keys.begin() + Mid + 1, FullChild->Keys.end());
        FullChild->Keys.resize(Mid);

        if (!FullChild->IsLeaf) {
            NewChild->Children.assign(
                FullChild->Children.begin() + Mid + 1, FullChild->Children.end());
            FullChild->Children.resize(Mid + 1);
        }

        Parent->Keys.insert(Parent->Keys.begin() + Index, MiddleKey);
        Parent->Children.insert(Parent->Children.begin() + Index + 1, NewChild);
    }


void PrintNode(const std::shared_ptr<Node>& N, const std::string& Prefix, bool IsLast) const {
    std::cout << Prefix;

    // 分支符号
    std::cout << (IsLast ? "└── " : "├── ");

    // 打印 Key
    std::cout << "[ ";
    for (size_t i = 0; i < N->Keys.size(); ++i) {
        std::cout << N->Keys[i];
        if (i + 1 != N->Keys.size()) std::cout << " | ";
    }
    std::cout << " ]" << std::endl;

    // 递归打印子节点
    if (!N->IsLeaf) {
        for (size_t i = 0; i < N->Children.size(); ++i) {
            bool ChildIsLast = (i == N->Children.size() - 1);
            PrintNode(N->Children[i], Prefix + (IsLast ? "    " : "│   "), ChildIsLast);
        }
    }
}


};


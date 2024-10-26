#include <iostream>
#include <optional>

class BinaryNode{
     public:
          int value;
          BinaryNode *left, *right;
          BinaryNode(int value): value(value), left(nullptr), right(nullptr){}
};

class BinaryTree{
     private:
          BinaryNode *root;
          int FindLeftMostLeaf(BinaryNode *node){
               // as there was no specification of what to do if the tree is empty
               // I would throw an exception in the public method. Since this is util method
               // I don't see a reason to check if node itself is nullptr and assume the
               // public method will handle that.
               if(not node->left) return node->value;               
               return FindLeftMostLeaf(node->left);
          }
     public:
          int FindLeftMostLeaf(){
               if (not root) throw std::runtime_error("Empty tree");
               return FindLeftMostLeaf(root);
          }
};
int main(){
     
}

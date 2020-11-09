#include "bitree.hpp"
#include <string>
using namespace std;

int main(){
  
  BiNode<string>* root=new BiNode<string>("songjiang");
  BiNode<string>* node1 =new BiNode<string>("wuyong");
  BiNode<string>* node2=new BiNode<string>("lujunyi");
  BiNode<string>* node3=new BiNode<string>("linchong");
  BiNode<string>* node4=new BiNode<string>("likui");
  
  //创建一棵二叉树
  BiTree<string>* bitree=new BiTree(root);
  root->setLeft(node1);
  root->setRight(node2);
  node1->setLeft(node3);
  node1->serRight(node4);

  bitree->PreOrder();
  return 0; 

}

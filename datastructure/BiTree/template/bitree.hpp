#include <iostream>

using namespace std;

template <class T>
struct  BiNode{
  T data;
  BiNode* left;
  BiNode* right;
  //构造函数
  BiNode(T data){
      this->data=data;
      this->left=NULL;
      this->right=NULL;
  }
  //设置左节点
  void setLeft(BiNode<T>* left){
       this->left=left;
  }
  //设置右节点
  void setRight(BiNode<T>* right){
       this->right=right;
  }
};

template <class T>
class BiTree{
    public:
      //构造函数
      BiTree(BiNode<T>* root){
         this->root=root;
      }

      //遍历
      //1.前序遍历
      void PreOrder(){
          cout<<"前序遍历"<<endl;
          PreOrder(root);
          cout<<endl;
      }
    private:
      BiNode<T>* root;//二叉树的根节点
      //二叉树的遍历
      void PreOrder(BiNode<T>*bt);

};

template<class T>
BiTree<T>::PreOrder(BiNode<T>*bt){
       if(bt==NULL){
          return;   //如果为空，那么返回
       }else{
          cout<<bt->data<<" ";
          PreOrder(bt->left);
          PreOrder(bt->right);
       }
}

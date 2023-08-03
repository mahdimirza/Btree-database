#include<iostream>
#include<string>
#include "BTreeNode.h"

using namespace std;

class BTree
{
    private:
        BTreeNode* root;
        
    public:
        int numArgs = 0; 
        BTree(int );
        Node* insert(long long int data);
        Node* Delete(Node* data);
        Node* creatNode(long long int, BTreeNode* );
        void check_smaler(long long int , BTreeNode*, int sotoon, vector<int> &);
        void check_bigger(long long int , BTreeNode* , int sotoon, vector<int> &);
        void check_equal(long long int , BTreeNode* , int sotoon, vector<int> &);
        void getAllIds(BTreeNode* , int sotoon, vector<int> &);
        int get_ID(Node* , int , int);

        BTreeNode* GetRoot();
};
BTree::BTree(int num)
{
    numArgs = num;
    root = new BTreeNode();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
BTreeNode* BTree::GetRoot()
{
    return(root);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
Node* BTree::creatNode(long long int datainput, BTreeNode* xinput)
{
    Node* x = new Node();
    x->data = datainput;
    x->Next = NULL;
    x->Self = xinput;
    return(x);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void BTree::check_equal(long long int input, BTreeNode* bt, int sotoon, vector<int> & res)
{
    int i = 0;
    for(int i = 0; i < bt->num_keys; i++)
    {
        if(!bt->is_leaf)
        {
            check_bigger(input, bt->Children[i], sotoon, res);
        }

        if(bt->keys[i]->data == input)
        {
            res.push_back(get_ID(bt->keys[i], sotoon, numArgs));
        }
    }

    if(!bt->is_leaf)
    {
        check_bigger(input, bt->Children[i + 1], sotoon, res);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void BTree::check_smaler(long long int input, BTreeNode* bt, int sotoon, vector<int> & res)
{
    int i = 0;
    for(int i = 0; i < bt->num_keys; i++)
    {
        if(!bt->is_leaf)
        {
            check_smaler(input, bt->Children[i], sotoon, res);
        }

        if(bt->keys[i]->data < input)
        {
            res.push_back(get_ID(bt->keys[i], sotoon, numArgs));
        }
    }

    if(!bt->is_leaf)
    {
        check_smaler(input, bt->Children[i + 1], sotoon, res);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BTree::check_bigger(long long int input, BTreeNode* bt, int sotoon, vector<int> & res)
{
    int i = 0;
    for(int i = 0; i < bt->num_keys; i++)
    {
        if(bt->keys[i]->data > input)
        {
            res.push_back(get_ID(bt->keys[i], sotoon, numArgs));
        }
        if(!bt->is_leaf)
        {
            check_bigger(input, bt->Children[i], sotoon, res);
        }

    }
    if(!bt->is_leaf)
    {
        check_bigger(input, bt->Children[i + 1], sotoon, res);
    }

    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* BTree::Delete(Node* deleteKey)
{
    if(!root)
    {
        return(NULL);
    }
    else{
        root->Delete(deleteKey);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* BTree::insert(long long int insertKey)
{
    if(root->num_keys == 0)
    {
        root = new BTreeNode();
        Node*x = creatNode(insertKey, root);
        root->keys[0] = x;
        root->num_keys++;
        return(root->keys[0]);
    }
    else{
        Node* x = new Node;
        x->data = insertKey;
        root = root->insert(x, root);
        return(x);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BTree::get_ID(Node* input, int sotoon, int numArgs)
{
    int res = 0;
    Node* ptr = input;
    for(int i = 0; i < numArgs - sotoon; i++)
    {
        ptr = ptr->Next;
    }


    return(ptr->data);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BTree::getAllIds(BTreeNode* bt, int sotoon, vector<int> & res)
{
    int i = 0;
    for(int i = 0; i < bt->num_keys; i++)
    {
        if(!bt->is_leaf)
        {
            getAllIds(bt->Children[i], sotoon, res);
        }

        res.push_back(get_ID(bt->keys[i], sotoon, numArgs));
    }

    if(!bt->is_leaf)
    {
        getAllIds(bt->Children[i + 1], sotoon, res);
    }
}
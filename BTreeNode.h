class BTreeNode;

class Node
{
    public:
        long long int data;
        Node* Next;
        BTreeNode* Self;
        Node();
        Node(long long int);
         
};

Node::Node()
{
    data = 0;
    Next = NULL;
    Self = NULL;
}


class BTreeNode
{

    public:
        int degree = 5;
        bool is_leaf;                           
        long long int num_keys;                          
        int max_child, max_key, min_key; 
        Node** keys;
        BTreeNode** Children;
        BTreeNode();
        BTreeNode* insert(Node* , BTreeNode*);
        void Delete(Node* );
        void split(BTreeNode* , int i);
        void InsertNonFul(BTreeNode* , Node*);
        Node* predeccesor(int );
        Node* succesor(int );
};



/////////////////////////////////////////////////////////////////////////////////////////////////
BTreeNode::BTreeNode()
{
    num_keys = 0;
    max_child = 2 * degree;
    max_key = 2 * degree - 1;
    min_key = degree - 1;

    is_leaf = true;

    keys = new Node*[max_key];
    Children = new BTreeNode* [max_child];

    for(int i = 0; i < max_key; i++)
    {
        keys[i] = NULL;
    }
    for(int i = 0; i < max_child; i++)
    {
        Children[i] = NULL;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void BTreeNode::split(BTreeNode* input, int indx)
{
    BTreeNode* splitChild = input->Children[indx];
    BTreeNode* rightChild = new BTreeNode();
    int cnt = 0;
    for(int i = degree; i < max_key; i++)
    {
        rightChild->keys[cnt] = splitChild->keys[i];
        splitChild->keys[i] = new Node();
        splitChild->num_keys--; 
        rightChild->num_keys++;
        cnt++;
    }
    cnt = 0;
    for(int i = degree; i < max_child; i++)
    {
        rightChild->Children[cnt] = splitChild->Children[i];
        cnt++;
    }
    for(int i = input->num_keys; i >= indx + 1; i--)
    {
        input->keys[i] = input->keys[i - 1];
    }
    input->keys[indx] = splitChild->keys[degree - 1];
    splitChild->keys[degree - 1] = new Node();
    splitChild->num_keys--;
    input->num_keys++;
    for(int i = num_keys; i >= indx + 2; i--)
    {
        input->Children[i] = input->Children[i - 1];
    }
    input->Children[indx + 1] = rightChild;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void BTreeNode::InsertNonFul(BTreeNode* bt, Node* input)
{
    if(bt->is_leaf)
    {
        int i = bt->num_keys - 1;
        while(i >= 0 && input->data < bt->keys[i]->data)
        {
            bt->keys[i + 1] = bt->keys[i];
            i--;
        }
        bt->keys[i + 1] = input;
        bt->num_keys++;
    }
    else
    {
        int i = bt->num_keys - 1;
        while(i >= 0 && input->data < bt->keys[i]->data)
        {
            i--;
        }
        i++;
        if(bt->Children[i]->num_keys == bt->Children[i]->max_key)
        {
            bt->split(bt->Children[i], i);
            if(input->data > bt->keys[i]->data)
            {
                i++;
            }
            InsertNonFul(bt->Children[i], input);
        }
        else
        {
            InsertNonFul(bt->Children[i], input);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
BTreeNode* BTreeNode::insert(Node* input, BTreeNode* bt)
{
    if(bt->num_keys == bt->max_key)
    {
        BTreeNode* x = new BTreeNode();
        BTreeNode* y = new BTreeNode();
        x = bt;
        bt = y;
        bt->is_leaf = false;
        bt->num_keys = 0;
        bt->Children[0] = x;
        split(bt, 0);
        bt->InsertNonFul(bt, input);
        return(bt);
    }
    else
    {
        bt->InsertNonFul(bt, input);
        return(bt);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void BTreeNode::Delete(Node* input)
{
    if(input->Self->is_leaf)
    {
        if(input->Self->num_keys > input->Self->min_key)
        {
            for(int i = 0; i < input->Self->num_keys; i++)
            {
                if(input->Self->keys[i] == input)
                {
                    for(int j = i; j < input->Self->num_keys; j++)
                    {
                        input->Self->keys[j] = input->Self->keys[i + 1];
                    }
                    break;
                }
            }
        }
        else
        {
            
        }
    }
    else
    {

    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
Node* BTreeNode::predeccesor(int input)
{
    BTreeNode* ptr = Children[input];
    while(!ptr->is_leaf)
    {
        ptr = ptr->Children[ptr->num_keys];
    }
    return(ptr->keys[num_keys - 1]);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Node* BTreeNode::succesor(int input)
{
    BTreeNode* ptr = Children[input];
    while(!ptr->is_leaf)
    {
        ptr = ptr->Children[0];
    }
    return(ptr->keys[0]);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

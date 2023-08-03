#include<iostream>
#include<string>
#include<vector>
#include "BTree.h"

using namespace std;



class Table
{
    private:
        
        vector<string> types;
        vector<string> nameofTypes;

    public:
        Node* id_table;
        vector<BTree*> make_table;
        vector<string> gettypes();
        vector<string> getnameoftypes();
        string table_name;
        void set_types(vector<string>);
        void set_nameOfTypes(vector<string>); 
        Table(string table_name);
        string get_name();
        void Making_table(vector<string>);
        int getFreeId();
        void insert(vector<string> );
        void Delete(int );
        void UpdateId(int);
        void Update(int , vector<string> );
        void select(int , vector<int> );
        vector<int> selectForOperatin(string);
        vector<int> set_condition(string data);
};
vector<string> Table::gettypes()
{
    return(types);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> Table::getnameoftypes()
{
    return(nameofTypes);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
Table::Table(string name)
{
    table_name = name;
    id_table = new Node[1000000];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::Making_table(vector<string> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        BTree* x = new BTree(types.size()); 
        make_table.push_back(x);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::set_types(vector<string> typeArgs)
{
    types = typeArgs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::set_nameOfTypes(vector<string> x)
{
    nameofTypes = x;
    Making_table(nameofTypes);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
string Table::get_name()
{
    return(table_name);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::insert(vector<string> input)
{
    vector<Node* > Nodes;
    for(int i = 0; i < types.size(); i++)
    {
        if(types[i] == "int")
        {
            Node* x = make_table[i]->insert(stoll(input[i]));
            Nodes.push_back(x);
        }
        else if(types[i] == "string")
        {
            Node* x = make_table[i]->insert(Hash_name(input[i]));
            Nodes.push_back(x);
        }
        else
        {
            Node* x = make_table[i]->insert(Hash_Time(input[i]));
            Nodes.push_back(x);
        }

    }
    for(int i = 0; i < Nodes.size() - 1; i++)
    {
        Nodes[i]->Next = Nodes[i + 1];
    }
    int Id = getFreeId();
    Nodes[Nodes.size() - 1]->Next = &id_table[Id];
    id_table[Id].Next = Nodes[0];
    id_table[Id].data = Id;


}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Table::getFreeId()
{
    for(int i = 0; i < 1000000; i++)
    {
        if(id_table[i].Next == NULL)
        {
            return(i);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::Delete(int id_Delete)
{
    Node* ptr = id_table[id_Delete].Next;
    for(int i = 0; i < types.size(); i++)
    {
        Node* Nextptr = ptr->Next;
        make_table[i]->Delete(ptr);
        ptr = Nextptr;
    }
    UpdateId(id_Delete);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::UpdateId(int DeleteId)
{
    int i = DeleteId;
    while(id_table[i].Next != NULL)
    {
        id_table[i].Next = id_table[i + 1].Next;
        i++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::Update(int ID, vector<string> tokens)
{
    Node* ptr = id_table[ID].Next;
    for(int i = 0; i < types.size(); i++)
    {
        int data;
        if(types[i] == "int")
        {
            data = stoi(tokens[i]);
        }
        else if(types[i] == "string")
        {
            data = Hash_name(tokens[i]);
        }
        else if(types[i] == "timestamp")
        {
            data = Hash_Time(tokens[i]);
        }
        Node* nxtptr = ptr->Next;
        ptr->data = data;
        ptr = nxtptr;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Table::select(int Id, vector<int> tokens)
{
    Node* ptr = id_table[Id].Next;
    int indx = 0;
    cout << Id << " ";
    for(int i = 0; i < tokens.size(); i++)
    {
        if(indx == tokens[i])
        {
            cout << ptr->data << " ";
        }
        else
        {
            ptr = ptr->Next;
        }
    }
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> Table::selectForOperatin(string condition)
{
    return(set_condition(condition));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> Table::set_condition(string condition)
{
    vector<int> res;
    string arg = "";
    string value = "";
    string operation = "";
    int indx = 0;
    for(int i = 0; i < condition.size(); i++)
    {
        if(condition[i] != '<' && condition[i] != '>' && condition[i] != '=')
        {
            arg += condition[i];
        }
        else
        {
            if(condition[i] == '<')
            {
                operation = '<';
                indx = i + 1;
                break;
            }
            else if(condition[i] == '>')
            {
                operation = '>';
                indx = i + 1;
                break;
            }
            else
            {
                operation = "==";
                indx = i + 2;
                break;
            }
        }
        
    }

    for(int i = indx; i < condition.size(); i++)
    {
        value += condition[i];
    }
    if(arg == "id")
    {
        vector<int> res; 
        make_table[0]->getAllIds(make_table[0]->GetRoot(), 0, res);
        sort(res);
        vector<int> res1;
        for(int i = 0; i < res.size(); i++)
        {
            if(res[i] < stoll(value) - 1)
            {
                res1.push_back(res[i]);
            }
        }
        return(res1);
    }
    else
    {
        for(int i = 0; i < nameofTypes.size(); i++)
        {
            if(nameofTypes[i] == arg)
            {
                if(operation == "==")
                {
                    if(types[i] == "string")
                    {
                        (make_table[i]->check_equal(Hash_name(value), make_table[i]->GetRoot(), i, res));
                    }
                    else if(types[i] == "timestamp")
                    {
                        (make_table[i]->check_equal(Hash_Time(value), make_table[i]->GetRoot(), i, res));
                    }
                    else
                    {
                        (make_table[i]->check_equal(stoll(value), make_table[i]->GetRoot(), i, res));
                    }
                }
                else if(operation == ">")
                {
                    if(types[i] == "string")
                    {
                        (make_table[i]->check_bigger(Hash_name(value), make_table[i]->GetRoot(), i, res));
                    }
                    else if(types[i] == "timestamp")
                    {
                        (make_table[i]->check_bigger(Hash_Time(value), make_table[i]->GetRoot(), i, res));
                    }
                    else
                    {
                        (make_table[i]->check_bigger(stoll(value), make_table[i]->GetRoot(), i, res));
                    }
                }
                else
                {   
                    if(types[i] == "string")
                    {
                        (make_table[i]->check_smaler(Hash_name(value), make_table[i]->GetRoot(), i, res));
                    }
                    else if(types[i] == "timestamp")
                    {
                        (make_table[i]->check_smaler(Hash_Time(value), make_table[i]->GetRoot(), i, res));
                    }
                    else
                    {
                        (make_table[i]->check_smaler(stoll(value), make_table[i]->GetRoot(), i, res));
                    }

                }
            }
        }
    }
    return(res);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

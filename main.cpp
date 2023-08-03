#include<iostream>
#include<string>
#include<vector>
#include "help.h"
#include "Table.h"

using namespace std;
 


int main()
{

    vector<Table*> tables;
    int q;
    cin >> q;
    cin.ignore();
    for(int i = 0; i < q; i++)
    {
        string s;
        getline(cin, s);
        string operation = "";
        for(int j = 0; j < s.size(); j++)
        {
            if(s[j] != ' ')
            {
                operation += s[j];
            }
            else
                break;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////
        if(operation == "CREATE")
        {
            vector<string> typesArgs = getArgs(s);
            vector<string> nameArgs = getNameOfArgs(s);
            Table* x = new Table(setNameOfTable(s));
            x->set_types(typesArgs);
            x->set_nameOfTypes(nameArgs);
            tables.push_back(x);
            
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////
        else if(operation == "INSERT")
        {
            Table* tptr = NULL;
            for(int j = 0;j < tables.size(); j++)
            {
                if(tables[j]->get_name() == setNameOfTable(s))
                {
                    tptr = tables[j];
                    break;
                }
            }
            if(!tptr)
            {
                cout << "Table Not Found!" << endl;
            }
            else
            {
                vector<string> x;
                for(int j = 0; j < split(s).size(); j++)
                {
                    if(split(s)[j] == "VALUES")
                    {
                        for(int k = j + 1; k < split(s).size(); k++)
                        {
                            x.push_back(split(s)[k]);
                        }
                        break;
                    }
                }

                tptr->insert(x);
            }

        }
        /////////////////////////////////////////////////////////////////////////////////////////////////
        else if(operation == "UPDATE")
        {
            Table* tptr = NULL;
            for(int j = 0;j < tables.size(); j++)
            {
                if(tables[j]->get_name() == split(s)[1])
                {
                    tptr = tables[j];
                    break;
                }
            }
            if(!tptr)
            {
                cout << "Table Not Found!" << endl;
            }
            else
            {
                vector<string> tokens = get_tokens(s);
                vector<string>types = tptr->gettypes();
                vector<int> selectID = tptr->selectForOperatin((split(s)[split(s).size() - 1]));

                for(int j = 0; j < selectID.size(); j++)
                {
                    Node* ptr = tptr->id_table[selectID[j]].Next;
                    for(int k = 0; k < tokens.size(); k++)
                    {
                        if(types[k] == "string")
                        {
                            ptr->data = Hash_name(tokens[k]);
                        }
                        else if(types[k] == "timestamp")
                        {
                            ptr->data = Hash_Time(tokens[k]);
                        }
                        else
                        {
                            ptr->data = stoll(tokens[k]);
                        }
                        ptr = ptr->Next;
                    }
                    
                }
                
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////
        else if(operation == "DELETE")
        {
            Table* tptr = NULL;
            for(int j = 0;j < tables.size(); j++)
            {
                if(tables[j]->get_name() == split(s)[2])
                {
                    tptr = tables[j];
                    break;
                }
            }
            if(!tptr)
            {
                cout << "Table Not Found!" << endl;
            }
            else
            {
                /*
                vector<int> deleteId = tptr->selectForOperatin(split(s)[split(s).size() - 1]);
                for(int j = 0; j < deleteId.size(); j++)
                {
                    tptr->Delete(j);
                }*/
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////
        else if(operation == "SELECT")
        {
            Table* tptr = NULL;
            for(int j = 0;j < tables.size(); j++)
            {
                if(tables[j]->get_name() == getNameforselect(s))
                {
                    tptr = tables[j];
                    break;
                }
            }
            if(!tptr)
            {
                cout << "Table Not Found!" << endl;
            }
            else
            {
                vector<int> diplay;
                if(split(s)[1] == "*")
                {
                    for(int j = 0; j < tptr->make_table[0]->numArgs; j++)
                    {
                        diplay.push_back(j);
                    }
                }
                else
                {
                    for(int j = 1; j < split(s).size(); j++)
                    {
                        if(split(s)[j] == "FROM")
                            break;
                        else
                        {
                            for(int k = 0; k < tptr->gettypes().size(); k++)
                            {
                                if(split(s)[j] == tptr->getnameoftypes()[k])
                                {
                                    diplay.push_back(k);
                                    break;
                                }
                            }
                        }
                    }
                }
                string cond = split(s)[split(s).size() - 1];
                string arg = "";
                for(int j = 0; j < cond.size(); j++)
                {
                    if(cond[j] != '<' && cond[j] != '>' && cond[j] != '==')
                        arg += cond[j];
                    else
                        {
                            break;
                        }
                }
                vector<int> res = tptr->selectForOperatin(split(s)[split(s).size() - 1]);
                sort(res);
                for(int j = 0; j < res.size() ; j++)
                {
                    int indx = 0;
                    Node* ptr = tptr->id_table[res[j]].Next;
                    if(arg == "id" || diplay.size() == tptr->gettypes().size())
                        cout << res[j] + 1 << " ";
                    for(int k = 0; k < tptr->gettypes().size(); k++)
                    {
                        if(k == diplay[indx])
                        {
                            if(tptr->gettypes()[diplay[indx]] == "string")
                            {
                                cout << dehash_name(ptr->data) << " ";
                            }
                            else if(tptr->gettypes()[diplay[indx]] == "timestamp")
                                cout << DeHash_Time(ptr->data) << " ";
                            else
                            {
                                cout << ptr->data << " ";
                            }
                            indx++;
                        }
                        ptr = ptr->Next;
                    }
                    cout << endl;
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////
    }

}
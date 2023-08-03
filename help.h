#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

string check_string(string x)
{
    string res = "";
    for(int i = 0; i < x.size(); i++)
    { 
        if(x[i] != '"')
            res+= x[i];
    }

    return(res);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> split(string s)
{
    vector<string> res;
    s = check_string(s);
    string word = "";
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] != ' ' && s[i] != ',' && s[i] != '(' && s[i] != ')'&& s[i] != '"')
        {
            word += s[i];
        }
        
        else
        {

            if(word != " " && word != "")
            {
                res.push_back(word);
                word = "";
            }
        }
    }
    res.push_back(word);
    return(res);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
string getNameforselect(string s)
{
    vector<string> res = split(s);
    string name;
    for(int i = 0; i < res.size(); i++)
    {
        if(res[i] == "FROM")
        {
            name= res[i + 1];
            break;
        }
    }
    return(name);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> get_tokens(string s)       //get tokens for update
{
    vector<string> splitedinput = split(s);
    vector<string> res;
    for(int i = 0; i < splitedinput.size(); i++)
    {
        if(splitedinput[i] == "SET")
        {
            for(int j = i + 1; j < splitedinput.size(); j++)
            {
                if(splitedinput[j] == "WHERE")
                    break;
                else
                {
                    res.push_back(splitedinput[j]);
                }
            }
            break;
        }
    }

    return(res);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
string setNameOfTable(string s)            // get name for creat
{
    return(split(s)[2]);
}   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> getArgs(string s)            //get type of args for create
{
    vector<string>splitedinput = split(s);
    vector<string> res;
    int indx = 3;
    for(int i = indx; i < splitedinput.size(); i++)
    {
        if(i % 2 == 0)
        {
            res.push_back(splitedinput[i]);
        }
    }
    return(res);
}    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> getNameOfArgs(string s)
{
    vector<string>splitedinput = split(s);
    vector<string> res;
    int indx = 3;
    for(int i = indx; i < splitedinput.size(); i++)
    {
        if(i % 2 == 1)
        {
            res.push_back(splitedinput[i]);
        }
    }
    return(res);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> chosenArgs(string s)     // get tokens for select;
{
    vector<int> res;
    vector<string> splitedinput;
    vector<string> args = getNameOfArgs(s);
    if(splitedinput[1] == "*")
    {
        for(int i = 0; i < args.size(); i++)
        {
            res.push_back(i);
        }
        return(res);
    }
    else
    {
        for(int i = 0; i < splitedinput.size(); i++)
        {
            if(splitedinput[i] == "SELECT")
            {
                for(int j = i + 1; j < splitedinput.size() ;j++)
                {
                    if(splitedinput[j] == "FROM")
                    {
                        break;
                    }
                    else
                    {
                        for(int k = 0; k < args.size(); k++)
                        {
                            if(args[k] == splitedinput[j])
                            {
                                res.push_back(k);
                                break;
                            }
                        }
                    }
                }
                break;;
            }

        }
    }
    return(res);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long int Hash_name(string s) 
{
    char alphabet[37] = {'/' ,'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    long long int hashedstring = 0;
    for(int i = 0; i < s.size(); i++)
    {
        int indx = 0;
        for(int j = 0; j < 37; j++)
        {
            if(s[i] == alphabet[j])
            {
                indx = j;
                break;
            }
        }

        hashedstring += indx * pow(37, i);
    }

    return(hashedstring);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long int Hash_Time(string time)
{
    long long int hashedTime = 0;
    vector<int> timevect;
    string word = "";
    for(int i = 0; i < time.size(); i++)
    {
        if(time[i] != '/')
        {
            word += time[i];
        }
        else{
            timevect.push_back(stoi(word));
            word = "";
        }
    }
    timevect.push_back(stoi(word));

    for(int i = 0; i < timevect.size(); i++)
    {
        if(i == 0)
        {
            hashedTime += timevect[i];
        }
        else{
            hashedTime = hashedTime * 100 + timevect[i];
        }
    }

    return(hashedTime);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
string dehash_name(long long int hashedstring)
{
    string res = "";
    char alphabet[37] = {'/','0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    while(hashedstring > 0)
    {
        res += alphabet[hashedstring % 37];
        hashedstring /= 37;
    }

    return(res);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
string DeHash_Time(int time)
{
    string Dehashedtime = "";
    vector<string> tmievect;
    for(int i = 0; i < 3; i++)
    {
        if(i == 0 || i == 1)
        {
            tmievect.push_back(to_string(time % 100));
            time /= 100;
        }
        else{
            tmievect.push_back(to_string(time));
        }
    }

    for(int i = 2; i >= 1; i--)
    {
        Dehashedtime += tmievect[i];
        Dehashedtime += "/";
    }

    Dehashedtime += tmievect[0];

    return(Dehashedtime);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sort(vector<int> &arr)
{
    for(int i = 1; i < arr.size(); i++)
    {
        for(int j = i; j > 0; j--)
        {
            if(arr[j] < arr[j - 1])
            {
                int c = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = c;
            }
        }
    }
}
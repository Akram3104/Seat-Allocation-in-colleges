#include<bits/stdc++.h>
using namespace std;
#include<fstream>

bool compare(pair<string,int>p1,pair<string,int>p2)
{
    return p1.second<p2.second;
}

class applicant
{
    public :
    string user_id="";
    int ctrl_rank;
    int res_rank;
    string cat;
    string choice_1;
    string choice_2;
    string choice_3;
    bool is_allocated=0;
    string allocated_branch;
};
applicant applicants[120];

vector<pair<string,int>>open;
vector<pair<string,int>>oc;
vector<pair<string,int>>ews;
vector<pair<string,int>>sc;
vector<pair<string,int>>st;
vector<pair<string,int>>obc;
void insert(string user_id,string cat,int res_rank,int ctrl_rank)
{
    open.push_back({user_id,ctrl_rank});
    if(cat=="OC")
    {
        oc.push_back({user_id,res_rank,});
    }
    else if(cat=="EWS")
    {
        ews.push_back({user_id,res_rank,});
    }
    else if(cat=="SC")
    {
        sc.push_back({user_id,res_rank,});
    }
    else if(cat=="ST")
    {
        st.push_back({user_id,res_rank,});
    }
    else if(cat=="OBC")
    {
        obc.push_back({user_id,res_rank,});
    }
}
void open_f1(string f1)
{
    ifstream file;
    file.open(f1);
    string line;
    int n=0;
    string user_id="",cat="",ctrl_rank="",res_rank="";

    while(getline(file,user_id))
    {
        getline(file,cat);
        getline(file,ctrl_rank);
        getline(file,res_rank);
        insert(user_id,cat,stoi(res_rank),stoi(ctrl_rank));
        applicants[n].user_id=user_id;
        applicants[n].cat=cat;
        applicants[n].ctrl_rank=stoi(ctrl_rank);
        applicants[n].res_rank=stoi(res_rank);
        user_id="";
        cat="";
        ctrl_rank="";
        res_rank="";
        n++;
    }
}


void open_f2(string f2)
{
    ifstream file;
    file.open(f2);
    string user_id="",choice_1="",choice_2="",choice_3="";
    while(getline(file,user_id))
    {
        getline(file,choice_1);
        getline(file,choice_2);
        getline(file,choice_3);

        for(int i=0;i<100;i++)
        {
            if(applicants[i].user_id==user_id)
            {
                applicants[i].choice_1=choice_1;
                applicants[i].choice_2=choice_2;
                applicants[i].choice_3=choice_3;
                break;
            }
        }

        choice_1="";
        choice_2="";
        choice_3="";
    }
}



int main()
{
    string f1,f2;
    getline(cin,f1);
    getline(cin,f2);
    open_f1(f1);
    open_f2(f2);

}
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


class seat_allocation
{
    private :
    int max_cse=40;
    int max_ece=40;
    int max_mech=40;
    int max_cse_oc=16;
    int max_ece_oc=16;
    int max_mech_oc=16;
    int max_cse_ews=4;
    int max_ece_ews=4;
    int max_mech_ews=4;
    int max_cse_sc=6;
    int max_ece_sc=6;
    int max_mech_sc=6;
    int max_cse_st=3;
    int max_ece_st=3;
    int max_mech_st=3;
    int max_cse_obc=11;
    int max_ece_obc=11;
    int max_mech_obc=11;

    /////////////////////////
    int no_cse_oc=0;
    int no_ece_oc=0;
    int no_mech_oc=0;
    int no_cse_ews=0;
    int no_ece_ews=0;
    int no_mech_ews=0;
    int no_cse_sc=0;
    int no_ece_sc=0;
    int no_mech_sc=0;
    int no_cse_st=0;
    int no_ece_st=0;
    int no_mech_st=0;
    int no_cse_obc=0;
    int no_ece_obc=0;
    int no_mech_obc=0;

    public :
    seat_allocation()
    {
        sort(open.begin(),open.end(),compare);
        sort(oc.begin(),oc.end(),compare);
        sort(obc.begin(),obc.end(),compare);
        sort(sc.begin(),sc.end(),compare);
        sort(st.begin(),st.end(),compare);
        sort(ews.begin(),ews.end(),compare);
    }

    void allocateSeat()
    {
        for(int i=0;i<oc.size();i++)
        {
            for(int j=0;j<100;j++)
            {
                if(oc[i].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].choice_1,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_1,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_2,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_2,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_3,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_3,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int i=0;i<obc.size();i++)
        {
            for(int j=0;j<100;j++)
            {
                if(oc[i].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].choice_1,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_1,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_2,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_2,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_3,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_3,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int i=0;i<ews.size();i++)
        {
            for(int j=0;j<100;j++)
            {
                if(oc[i].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].choice_1,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_1,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_2,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_2,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_3,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_3,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int i=0;i<sc.size();i++)
        {
            for(int j=0;j<100;j++)
            {
                if(oc[i].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].choice_1,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_1,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_2,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_2,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_3,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_3,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int i=0;i<st.size();i++)
        {
            for(int j=0;j<100;j++)
            {
                if(oc[i].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].choice_1,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_1,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_2,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_2,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].choice_3,applicants[i].cat))
                        {
                            give_seat(applicants[i].choice_3,applicants[i].cat);
                            applicants[i].allocated_branch=applicants[i].choice_3;
                            break;
                        }
                    }
                }
            }
        }
    }

    bool checkSeat(string branch,string cat)
    {
        if(branch=="CSE")
        {
            if(cat=="OC") return no_cse_oc<=max_cse_oc;
            else if(cat=="OBC") return no_cse_obc<=max_cse_obc;
            else if(cat=="SC") return no_cse_sc<=max_cse_sc;
            else if(cat=="ST") return no_cse_st<=max_cse_st;
            else if(cat=="EWS") return no_cse_ews<=max_cse_ews;
        }
        else if(branch=="ECE")
        {
            if(cat=="OC") return no_ece_oc<=max_ece_oc;
            else if(cat=="OBC") return no_ece_obc<=max_ece_obc;
            else if(cat=="SC") return no_ece_sc<=max_ece_sc;
            else if(cat=="ST") return no_ece_st<=max_ece_st;
            else if(cat=="EWS") return no_ece_ews<=max_ece_ews;
        }
        else if(branch=="MECH")
        {
            if(cat=="OC") return no_mech_oc<=max_mech_oc;
            else if(cat=="OBC") return no_mech_obc<=max_mech_obc;
            else if(cat=="SC") return no_mech_sc<=max_mech_sc;
            else if(cat=="ST") return no_mech_st<=max_mech_st;
            else if(cat=="EWS") return no_mech_ews<=max_mech_ews;
        }
    }

    void give_seat(string branch,string cat)
    {
        if(branch=="CSE")
        {
            if(cat=="OC") no_cse_oc++;
            else if(cat=="OBC")  no_cse_obc++;
            else if(cat=="SC")  no_cse_sc++;
            else if(cat=="ST")  no_cse_st++;
            else if(cat=="EWS") no_cse_ews++;
        }
        else if(branch=="ECE")
        {
           if(cat=="OC") no_ece_oc++;
            else if(cat=="OBC")  no_ece_obc++;
            else if(cat=="SC")  no_ece_sc++;
            else if(cat=="ST")  no_ece_st++;
            else if(cat=="EWS") no_ece_ews++;
        }
        else if(branch=="MECH")
        {
            if(cat=="OC") no_mech_oc++;
            else if(cat=="OBC")  no_mech_obc++;
            else if(cat=="SC")  no_mech_sc++;
            else if(cat=="ST")  no_mech_st++;
            else if(cat=="EWS") no_mech_ews++;
        }
    }


};


int main()
{
    string f1,f2;
    getline(cin,f1);
    getline(cin,f2);
    open_f1(f1);
    open_f2(f2);

    seat_allocation obj;
    obj.allocateSeat();

}
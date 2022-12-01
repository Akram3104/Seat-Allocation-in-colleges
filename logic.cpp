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
    int open_rank;
    int category_rank;
    string category;
    string college_choice_1;
    string branch_choice_1;
    string college_choice_2;
    string branch_choice_2;
    string college_choice_3;
    string branch_choice_3;
    bool is_allocated=0;
    string allocated_branch;
    string allocated_college;
};
applicant applicants[500];

class SeatAllocater
{
    private :
    // vector stores user id and category rank of different categories
    vector<pair<string,int>>open;
    vector<pair<string,int>>oc;
    vector<pair<string,int>>ews;
    vector<pair<string,int>>sc;
    vector<pair<string,int>>st;
    vector<pair<string,int>>obc;
    // map stores the category and seats left
    map<string,vector<int>>nit_warangal;
    map<string,vector<int>>nit_calicut;
    map<string,vector<int>>iiit_trichy;
    map<string,vector<int>>iiit_ranchi;
    map<string,vector<int>>iit_goa;
   // map stores branch name and students joined in that branch
    map<string,vector<int>> nit_warangal_students_list;
    map<string,vector<int>> nit_calicut_students_list;
    map<string,vector<int>> iit_goa_students_list;
    map<string,vector<int>> iiit_ranchi_students_list;
    map<string,vector<int>> iiit_trichy_students_list;
    

    public :
    SeatAllocater()
    {
        string f1,f2;
        f1="info_category.txt";
        f2="sample_choices.txt";
        openRankFile(f1);
        openChoicesFile(f2);
        sort(open.begin(),open.end(),compare);
        sort(oc.begin(),oc.end(),compare);
        sort(obc.begin(),obc.end(),compare);
        sort(sc.begin(),sc.end(),compare);
        sort(st.begin(),st.end(),compare);
        sort(ews.begin(),ews.end(),compare);
        intialiseCollegeData();
        
    }
    private:
    void intialiseCollegeData()
    {
       // index in the vector    seats for specific caste   no of seats 
        // 0                        OC                          13
        // 1                        OBC                          8
        // 2                        EWS                          3
        // 3                        SC                           4
        // 4                        ST                           2


        
        vector<int>v{13,8,3,4,2};
        nit_warangal.insert({"CSE",v});
        nit_warangal.insert({"ECE",v});
        nit_warangal.insert({"MECH",v});
        nit_calicut.insert({"CSE",v});
        nit_calicut.insert({"ECE",v});
        nit_calicut.insert({"MECH",v});
        iiit_ranchi.insert({"CSE",v});
        iiit_ranchi.insert({"ECE",v});
        iiit_ranchi.insert({"MECH",v});
        iiit_trichy.insert({"CSE",v});
        iiit_trichy.insert({"ECE",v});
        iiit_trichy.insert({"MECH",v});
        iit_goa.insert({"CSE",v});
        iit_goa.insert({"ECE",v});
        iit_goa.insert({"MECH",v});
        
    }
    // functions to store data
    void insert(string user_id,string cat,int res_rank,int ctrl_rank)
    {
        open.push_back({user_id,ctrl_rank});
        if(cat=="OC")
        {
            oc.push_back({user_id,res_rank});
        }
        else if(cat=="EWS")
        {
            ews.push_back({user_id,res_rank});
        }
        else if(cat=="SC")
        {
            sc.push_back({user_id,res_rank});
        }
        else if(cat=="ST")
        {
            st.push_back({user_id,res_rank});
        }
        else if(cat=="OBC")
        {
            obc.push_back({user_id,res_rank});
        }
    }    
    void openRankFile(string f1)
    {
        ifstream file;
        file.open(f1);
        string line;
        int n=0;
        string user_id="",category="",open_rank="",category_rank="";    
        while(getline(file,user_id))
        {
            getline(file,category);
            getline(file,open_rank);
            getline(file,category_rank);
            insert(user_id,category,stoi(category_rank),stoi(open_rank));
            applicants[n].user_id=user_id;
            applicants[n].category=category;
            applicants[n].open_rank=stoi(open_rank);
            applicants[n].category_rank=stoi(category_rank);
            user_id="";
            category="";
            open_rank="";
            category_rank="";
            n++;
        }
    }
    void openChoicesFile(string f2)
    {
        ifstream file;
        file.open(f2);
        string user_id="",branch_choice_1="",branch_choice_2="",branch_choice_3="";
        string college_choice_1="",college_choice_2="",college_choice_3="";
        while(getline(file,user_id))
        {
            getline(file,college_choice_1);
            getline(file,branch_choice_1);
            getline(file,college_choice_2);
            getline(file,branch_choice_2);
            getline(file,college_choice_3);
            getline(file,branch_choice_3);
            for(int i=0;i<500;i++)
            {
                if(applicants[i].user_id==user_id)
                {
                    applicants[i].college_choice_1=college_choice_1;
                    applicants[i].branch_choice_1=branch_choice_1;
                    applicants[i].college_choice_2=college_choice_2;
                    applicants[i].branch_choice_2=branch_choice_2;
                    applicants[i].college_choice_3=college_choice_3;
                    applicants[i].branch_choice_3=branch_choice_3;
                    break;
                }
            }
            branch_choice_1="";
            branch_choice_2="";
            branch_choice_3="";
            college_choice_1="";
            college_choice_2="";    
            college_choice_3="";
        }
    }
    public:
    // function to allocate Seat
    void allocateSeat()
    {
        for(int j=0;j<obc.size();j++)
        {
            for(int i=0;i<500;i++)
            {
                if(obc[j].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category);
                            applicants[i].allocated_college=applicants[i].college_choice_1;
                            applicants[i].allocated_branch=applicants[i].branch_choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category);
                            applicants[i].allocated_college=applicants[i].college_choice_2;
                            applicants[i].allocated_branch=applicants[i].branch_choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category);
                            applicants[i].allocated_college=applicants[i].college_choice_3;
                            applicants[i].allocated_branch=applicants[i].branch_choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int j=0;j<ews.size();j++)
        {
            for(int i=0;i<500;i++)
            {
                if(ews[j].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_1;
                            applicants[i].allocated_college=applicants[i].college_choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_2;
                            applicants[i].allocated_college=applicants[i].college_choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_3;
                            applicants[i].allocated_college=applicants[i].college_choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int j=0;j<sc.size();j++)
        {
            for(int i=0;i<500;i++)
            {
                if(sc[j].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_1;
                            applicants[i].allocated_college=applicants[i].college_choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_2;
                            applicants[i].allocated_college=applicants[i].college_choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_3;
                            applicants[i].allocated_college=applicants[i].college_choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int j=0;j<st.size();j++)
        {
            for(int i=0;i<500;i++)
            {
                if(st[j].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_1;
                            applicants[i].allocated_college=applicants[i].college_choice_1;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_2;
                            applicants[i].allocated_college=applicants[i].college_choice_2;
                            break;
                        }
                        else if(checkSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category))
                        {
                            allocateSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3,applicants[i].category);
                            applicants[i].allocated_branch=applicants[i].branch_choice_3;
                            applicants[i].allocated_college=applicants[i].college_choice_3;
                            break;
                        }
                    }
                }
            }
        }

        for(int j=0;j<open.size();j++)
        {
            for(int i=0;i<500;i++)
            {
                if(open[j].first==applicants[i].user_id)
                {
                    if(applicants[i].is_allocated==false)
                    {
                        if(checkOpenSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1))
                        {
                            allocateOpenSeat(applicants[i].college_choice_1,applicants[i].branch_choice_1);
                            applicants[i].allocated_branch=applicants[i].branch_choice_1;
                            applicants[i].allocated_college=applicants[i].college_choice_1;
                            break;
                        }
                        else if(checkOpenSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2))
                        {
                            allocateOpenSeat(applicants[i].college_choice_2,applicants[i].branch_choice_2);
                            applicants[i].allocated_branch=applicants[i].branch_choice_2;
                            applicants[i].allocated_college=applicants[i].college_choice_2;
                            break;
                        }
                        else if(checkOpenSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3))
                        {
                            allocateOpenSeat(applicants[i].college_choice_3,applicants[i].branch_choice_3);
                            applicants[i].allocated_branch=applicants[i].branch_choice_3;
                            applicants[i].allocated_college=applicants[i].college_choice_3;
                            break;
                        }
                    }
                }
            }
        }

       distributeStudentsToColleges();
       listAllTheStudentsInCollege();
    }
    private:
    // function to check if Seat is available or not
    bool checkSeat(string clg,string branch,string category)
    {
        if(clg=="NIT WARANGAL")
        {
            if(branch=="CSE")
            {
                if(category=="OBC")
                {
                    if(nit_warangal["CSE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_warangal["CSE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_warangal["CSE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_warangal["CSE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="ECE")
            {
                if(category=="OBC")
                {
                    if(nit_warangal["ECE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_warangal["ECE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_warangal["ECE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_warangal["ECE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="MECH")
            {
                if(category=="OBC")
                {
                    if(nit_warangal["MECH"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_warangal["MECH"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_warangal["MECH"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_warangal["MECH"][4])  return true;
                    else return false;
                }
            }
        }

        else if(clg=="NIT CALICUT")
        {
            if(branch=="CSE")
            {
                if(category=="OBC")
                {
                    if(nit_calicut["CSE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_calicut["CSE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_calicut["CSE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_calicut["CSE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="ECE")
            {
                if(category=="OBC")
                {
                    if(nit_calicut["ECE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_calicut["ECE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_calicut["ECE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_calicut["ECE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="MECH")
            {
                if(category=="OBC")
                {
                    if(nit_calicut["MECH"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(nit_calicut["MECH"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(nit_calicut["MECH"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(nit_calicut["MECH"][4])  return true;
                    else return false;
                }
            }
        }
        else if(clg=="IIIT TRICHY")
        {
            if(branch=="CSE")
            {
                if(category=="OBC")
                {
                    if(iiit_trichy["CSE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_trichy["CSE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_trichy["CSE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_trichy["CSE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="ECE")
            {
                if(category=="OBC")
                {
                    if(iiit_trichy["ECE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_trichy["ECE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_trichy["ECE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_trichy["ECE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="MECH")
            {
                if(category=="OBC")
                {
                    if(iiit_trichy["MECH"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_trichy["MECH"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_trichy["MECH"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_trichy["MECH"][4])  return true;
                    else return false;
                }
            }
        }
        else if(clg=="IIIT RANCHI")
        {
            if(branch=="CSE")
            {
                if(category=="OBC")
                {
                    if(iiit_ranchi["CSE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_ranchi["CSE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_ranchi["CSE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_ranchi["CSE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="ECE")
            {
                if(category=="OBC")
                {
                    if(iiit_ranchi["ECE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_ranchi["ECE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_ranchi["ECE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_ranchi["ECE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="MECH")
            {
                if(category=="OBC")
                {
                    if(iiit_ranchi["MECH"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iiit_ranchi["MECH"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iiit_ranchi["MECH"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iiit_ranchi["MECH"][4])  return true;
                    else return false;
                }
            }
        }
        else if(clg=="IIT GOA")
        {
            if(branch=="CSE")
            {
                if(category=="OBC")
                {
                    if(iit_goa["CSE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iit_goa["CSE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iit_goa["CSE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iit_goa["CSE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="ECE")
            {
                if(category=="OBC")
                {
                    if(iit_goa["ECE"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iit_goa["ECE"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iit_goa["ECE"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iit_goa["ECE"][4])  return true;
                    else return false;
                }
            }
            else if(branch=="MECH")
            {
                if(category=="OBC")
                {
                    if(iit_goa["MECH"][1])  return true;
                    else return false;
                }
                else if(category=="EWS")
                {
                    if(iit_goa["MECH"][2])  return true;
                    else return false;
                }
                else if(category=="SC")
                {
                    if(iit_goa["MECH"][3])  return true;
                    else return false;
                }
                else if(category=="ST")
                {
                    if(iit_goa["MECH"][4])  return true;
                    else return false;
                }
            }
        }
        return false;
    }
    // function to check if Open Seat is available or not
    bool checkOpenSeat(string clg,string branch)
    {
        if(clg=="NIT WARANGAL")
            {
                if(branch=="CSE")
                {
                    if(nit_warangal["CSE"][0])  return true;
                    else return false;
                }
                else if(branch=="ECE")
                {
                    if(nit_warangal["ECE"][0])  return true;
                    else return false;
                }
                else if(branch=="MECH")
                {
                    if(nit_warangal["MECH"][0])  return true;
                    else return false;
                }
            }
            else if(clg=="NIT CALICUT")
            {
                if(branch=="CSE")
                {
                    if(nit_calicut["CSE"][0])  return true;
                    else return false; 
                }
                else if(branch=="ECE")
                {
                    if(nit_calicut["ECE"][0])  return true;
                    else return false; 
                }
                else if(branch=="MECH")
                {
                    if(nit_calicut["MECH"][0])  return true;
                    else return false; 
                }
            }
            else if(clg=="IIIT TRICHY")
            {
                if(branch=="CSE")
                {
                    if(iiit_trichy["CSE"][0])  return true;
                    else return false;
                }
                else if(branch=="ECE")
                {
                    if(iiit_trichy["ECE"][0])  return true;
                    else return false;
                }
                else if(branch=="MECH")
                {
                    if(iiit_trichy["MECH"][0])  return true;
                    else return false;
                }
            }
            else if(clg=="IIIT RANCHI")
            {
                if(branch=="CSE")
                {
                    if(iiit_ranchi["CSE"][0])  return true;
                    else return false;
                }
                else if(branch=="ECE")
                {
                    if(iiit_ranchi["ECE"][0])  return true;
                    else return false;
                }
                else if(branch=="MECH")
                {
                   if(iiit_ranchi["MECH"][0])  return true;
                    else return false;
                }
            }
            else if(clg=="IIT GOA")
            {
                if(branch=="CSE")
                {
                    if(iit_goa["CSE"][0])  return true;
                    else return false;
                }
                else if(branch=="ECE")
                {
                    if(iit_goa["ECE"][0])  return true;
                    else return false;
                }
                else if(branch=="MECH")
                {
                    if(iit_goa["MECH"][0])  return true;
                    else return false;
                }
            }
            return false;
    }
    // function to allocate Seat
    void allocateSeat(string clg,string branch,string category)
    {
        if(clg=="NIT WARANGAL")
        {
            if(branch=="CSE")
            {
                if(category=="OBC") nit_warangal["CSE"][1]--;
                else if(category=="EWS") nit_warangal["CSE"][2]--;
                else if(category=="SC") nit_warangal["CSE"][3]--;
                else if(category=="ST")  nit_warangal["CSE"][4]--;
            }
            else if(branch=="ECE")
            {
                if(category=="OBC") nit_warangal["ECE"][1]--;
                else if(category=="EWS") nit_warangal["ECE"][2]--;
                else if(category=="SC") nit_warangal["ECE"][3]--;
                else if(category=="ST")  nit_warangal["ECE"][4]--;
            }
            else if(branch=="MECH")
            {
                if(category=="OBC") nit_warangal["MECH"][1]--;
                else if(category=="EWS") nit_warangal["MECH"][2]--;
                else if(category=="SC") nit_warangal["MECH"][3]--;
                else if(category=="ST")  nit_warangal["MECH"][4]--;
            }
        }
        else if(clg=="NIT CALICUT")
        {
            if(branch=="CSE")
            {
                if(category=="OBC") nit_calicut["CSE"][1]--;
                else if(category=="EWS") nit_calicut["CSE"][2]--;
                else if(category=="SC") nit_calicut["CSE"][3]--;
                else if(category=="ST")  nit_calicut["CSE"][4]--;
            }
            else if(branch=="ECE")
            {
                if(category=="OBC") nit_calicut["ECE"][1]--;
                else if(category=="EWS") nit_calicut["ECE"][2]--;
                else if(category=="SC") nit_calicut["ECE"][3]--;
                else if(category=="ST")  nit_calicut["ECE"][4]--;
            }
            else if(branch=="MECH")
            {
                if(category=="OBC") nit_calicut["MECH"][1]--;
                else if(category=="EWS") nit_calicut["MECH"][2]--;
                else if(category=="SC") nit_calicut["MECH"][3]--;
                else if(category=="ST")  nit_calicut["MECH"][4]--;
            }
        }
        else if(clg=="IIIT TRICHY")
        {
            if(branch=="CSE")
            {
                if(category=="OBC") iiit_trichy["CSE"][1]--;
                else if(category=="EWS") iiit_trichy["CSE"][2]--;
                else if(category=="SC") iiit_trichy["CSE"][3]--;
                else if(category=="ST")  iiit_trichy["CSE"][4]--;
            }
            else if(branch=="ECE")
            {
                if(category=="OBC") iiit_trichy["ECE"][1]--;
                else if(category=="EWS") iiit_trichy["ECE"][2]--;
                else if(category=="SC") iiit_trichy["ECE"][3]--;
                else if(category=="ST")  iiit_trichy["ECE"][4]--;
            }
            else if(branch=="MECH")
            {
                if(category=="OBC") iiit_trichy["MECH"][1]--;
                else if(category=="EWS") iiit_trichy["MECH"][2]--;
                else if(category=="SC") iiit_trichy["MECH"][3]--;
                else if(category=="ST")  iiit_trichy["MECH"][4]--;
            }
        }
        else if(clg=="IIIT RANCHI")
        {
            if(branch=="CSE")
            {
                if(category=="OBC") iiit_ranchi["CSE"][1]--;
                else if(category=="EWS") iiit_ranchi["CSE"][2]--;
                else if(category=="SC") iiit_ranchi["CSE"][3]--;
                else if(category=="ST")  iiit_ranchi["CSE"][4]--;
            }
            else if(branch=="ECE")
            {
                if(category=="OBC") iiit_ranchi["ECE"][1]--;
                else if(category=="EWS") iiit_ranchi["ECE"][2]--;
                else if(category=="SC") iiit_ranchi["ECE"][3]--;
                else if(category=="ST")  iiit_ranchi["ECE"][4]--;
            }
            else if(branch=="MECH")
            {
                if(category=="OBC") iiit_ranchi["MECH"][1]--;
                else if(category=="EWS") iiit_ranchi["MECH"][2]--;
                else if(category=="SC") iiit_ranchi["MECH"][3]--;
                else if(category=="ST")  iiit_ranchi["MECH"][4]--;
            }
        }
        else if(clg=="IIT GOA")
        {
            if(branch=="CSE")
            {
                if(category=="OBC") iit_goa["CSE"][1]--;
                else if(category=="EWS") iit_goa["CSE"][2]--;
                else if(category=="SC") iit_goa["CSE"][3]--;
                else if(category=="ST")  iit_goa["CSE"][4]--;
            }
            else if(branch=="ECE")
            {
                if(category=="OBC") iit_goa["ECE"][1]--;
                else if(category=="EWS") iit_goa["ECE"][2]--;
                else if(category=="SC") iit_goa["ECE"][3]--;
                else if(category=="ST")  iit_goa["ECE"][4]--;
            }
            else if(branch=="MECH")
            {
                if(category=="OBC") iit_goa["MECH"][1]--;
                else if(category=="EWS") iit_goa["MECH"][2]--;
                else if(category=="SC") iit_goa["MECH"][3]--;
                else if(category=="ST")  iit_goa["MECH"][4]--;
            }
        }
    } 
    // function to allocate Open Seat
    void allocateOpenSeat(string clg,string branch)
    {
        if(clg=="NIT WARANGAL")
        {
            if(branch=="CSE")
            {
                nit_warangal["CSE"][0]--;
            }
            else if(branch=="ECE")
            {
                nit_warangal["ECE"][0]--;
            }
            else if(branch=="MECH")
            {
                nit_warangal["MECH"][0]--;
            }
        }
        else if(clg=="NIT CALICUT")
        {
            if(branch=="CSE")
            {
                nit_calicut["CSE"][0]--;
            }
            else if(branch=="ECE")
            {
                nit_calicut["ECE"][0]--;
            }
            else if(branch=="MECH")
            {
                nit_calicut["MECH"][0]--;
            }
        }
        else if(clg=="IIIT TRICHY")
        {
            if(branch=="CSE")
            {
                iiit_trichy["CSE"][0]--;
            }
            else if(branch=="ECE")
            {
                iiit_trichy["ECE"][0]--;
            }
            else if(branch=="MECH")
            {
                iiit_trichy["MECH"][0]--;
            }
        }
        else if(clg=="IIIT RANCHI")
        {
            if(branch=="CSE")
            {
                iiit_ranchi["CSE"][0]--;
            }
            else if(branch=="ECE")
            {
                iiit_ranchi["ECE"][0]--;
            }
            else if(branch=="MECH")
            {
                iiit_ranchi["MECH"][0]--;
            }
        }
        else if(clg=="IIT GOA")
        {
            if(branch=="CSE")
            {
                iit_goa["CSE"][0]--;
            }
            else if(branch=="ECE")
            {
                iit_goa["ECE"][0]--;
            }
            else if(branch=="MECH")
            {
                iit_goa["MECH"][0]--;
            }
        }
    }
    // function to store list of all the students belonging to one college at one place
    void distributeStudentsToColleges()
    {
        for(int i=0;i<500;i++)
        {
            if(applicants[i].allocated_college=="NIT WARANGAL")
            {
                nit_warangal_students_list[applicants[i].allocated_branch].push_back(stoi(applicants[i].user_id));
            }
            else if(applicants[i].allocated_college=="NIT CALICUT")
            {
                nit_calicut_students_list[applicants[i].allocated_branch].push_back(stoi(applicants[i].user_id));
            }
            else if(applicants[i].allocated_college=="IIT GOA")
            {
                iit_goa_students_list[applicants[i].allocated_branch].push_back(stoi(applicants[i].user_id));
            }
            else if(applicants[i].allocated_college=="IIIT RANCHI")
            {
                iiit_ranchi_students_list[applicants[i].allocated_branch].push_back(stoi(applicants[i].user_id));
            }
            else if(applicants[i].allocated_college=="IIIT TRICHY")
            {
                iiit_trichy_students_list[applicants[i].allocated_branch].push_back(stoi(applicants[i].user_id));
            }
        }
    }
    // function to write students of particular college to separate file
    void listAllTheStudentsInCollege()
    {
        ofstream file1;
        file1.open("IIT_GOA_LIST");

        file1<<"STUDENTS IN CSE BRANCH \n";
        for(auto i : iit_goa_students_list["CSE"])
        {
            file1<<i<<"\n";
        }
        file1<<"STUDENTS IN ECE BRANCH \n";
        for(auto i : iit_goa_students_list["ECE"])
        {
            file1<<i<<"\n";
        }
        file1<<"STUDENTS IN MECH BRANCH \n";
        for(auto i : iit_goa_students_list["MECH"])
        {
            file1<<i<<"\n";
        }
        file1.close();

        ofstream file2;
        file2.open("NIT_WARANGAL_LIST");
    
        file2<<"STUDENTS IN CSE BRANCH \n";
        for(auto i : nit_warangal_students_list["CSE"])
        {   
            file2<<i<<"\n";
        }
        file2<<"STUDENTS IN ECE BRANCH \n";
        for(auto i : nit_warangal_students_list["ECE"])
        {
            file2<<i<<"\n";
        }
        file2<<"STUDENTS IN MECH BRANCH \n";
        for(auto i : nit_warangal_students_list["MECH"])
        {
            file2<<i<<"\n";  
        }
        file2.close();

        ofstream file3;
        file3.open("NIT_CALICUT_LIST");
    
        file3<<"STUDENTS IN CSE BRANCH \n";
        for(auto i : nit_calicut_students_list["CSE"])
        {
            file3<<i<<"\n";
        }
        file3<<"STUDENTS IN ECE BRANCH \n";
        for(auto i : nit_calicut_students_list["ECE"])
        {   
            file3<<i<<"\n";
        }
        file3<<"STUDENTS IN MECH BRANCH \n";
        for(auto i : nit_calicut_students_list["MECH"])
        {
            file3<<i<<"\n";
        }
        file3.close();

        ofstream file4;
        file4.open("IIIT_TRICHY_LIST");  
        file4<<"STUDENTS IN CSE BRANCH \n";
        for(auto i : iiit_trichy_students_list["CSE"])  
        {
            file4<<i<<"\n";
        }
        file4<<"STUDENTS IN ECE BRANCH \n";
        for(auto i : iiit_trichy_students_list["ECE"])
        {
            file4<<i<<"\n";
        }
        file4<<"STUDENTS IN MECH BRANCH \n";
        for(auto i : iiit_trichy_students_list["MECH"])
        {
            file4<<i<<"\n";
        }
        file4.close();

        ofstream file5;
        file5.open("IIIT_RANCHI_LIST");
        file5<<"STUDENTS IN CSE BRANCH \n";
        for(auto i : iiit_ranchi_students_list["CSE"])
        {
            file5<<i<<"\n";
        }
        file5<<"STUDENTS IN ECE BRANCH \n";
        for(auto i : iiit_ranchi_students_list["ECE"])
        {
            file5<<i<<"\n";
        }
        file5<<"STUDENTS IN MECH BRANCH \n";
        for(auto i : iiit_ranchi_students_list["MECH"])
        {
            file5<<i<<"\n";
        }
        file5.close();
    }
};
int main()
{
    SeatAllocater obj;
    obj.allocateSeat();
}
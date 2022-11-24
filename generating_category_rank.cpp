#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Applicant
{
    public:
    int id;
    int crl;
    int rrank;
    string caste;

};
int main()
{
    Applicant obj[500];
    ifstream file;
    file.open("input_info_ids.txt");
    string id;
    string caste;
    string rank;
    int n=0;
    while(getline(file,id))
    {
        getline(file,caste);
        getline(file,rank);
        obj[n].id=stoi(id);
        obj[n].caste=caste;
        obj[n].crl=stoi(rank);
        n++;
    }
    file.close();
    map<int,Applicant*> mp;
    for(int i=0;i<500;i++)
    {
        mp[obj[i].crl]=&obj[i];
    }
    int ews=1,sc=1,st=1,obc=1;
    for(auto i:mp)
    {
        if(i.second->caste=="SC")
        {
            i.second->rrank=sc++;
        }
        else if(i.second->caste=="ST")
        {
            i.second->rrank=st++;
        }
        else if(i.second->caste=="OBC")
        {
            i.second->rrank=obc++;
        }
        else if(i.second->caste=="OC")
        {
            i.second->rrank=i.second->crl;
        }
        else if(i.second->caste=="EWS")
        {
            i.second->rrank=ews++;
        }
    }
    ofstream file2;
    file2.open("info_category.txt");
    for(int i=0;i<500;i++)
    {
        file2<<obj[i].id<<"\n"<<obj[i].caste<<"\n"<<obj[i].crl<<"\n"<<obj[i].rrank<<"\n";
    }
    file2.close();
    return 0;
}
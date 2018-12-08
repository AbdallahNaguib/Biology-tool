#include "Sequence.h"
#include <iostream>
#include <cstring>
using namespace std;


Sequence::Sequence()
{
    //ctor
}

Sequence::~Sequence()
{
    //dtor
}

int memo[1000][1000];/// this table is for memorization
int LCS(char* str1 , char* str2 , int i,int j , int sz1 , int sz2){
    /// if we have already solved this subproblem then return its value at once
    if(memo[i][j] != -1){
        return memo[i][j];
    }
    /// if we reached the end of any string then just simply return 0
    if(i == sz1 || j == sz2){
        return 0;
    }
    /// if we found two equal characters then we add 1 and solve the subproblem of (i+1, j+1)
    if(str1[i] == str2[j]){
        return memo[i][j] = 1+LCS(str1 , str2 , i+1 , j+1 , sz1 , sz2);
    }
    /// we decide which is best for us (i+1 , j) or (i , j+1)
    return memo[i][j] = max(LCS(str1 , str2 , i+1 , j , sz1, sz2) , LCS(str1 , str2 , i , j+1 , sz1 , sz2));
}
string buildLCS(char* str1 , char* str2 , int i,int j , int sz1 , int sz2){

    if(i == sz1 || j == sz2){
        return "";
    }
    if(str1[i] == str2[j]){
        return str1[i] + buildLCS(str1 , str2 , i+1 , j+1 , sz1 , sz2);
    }
    if(memo[i][j] == memo[i+1][j]){
        return buildLCS(str1 , str2 , i+1 , j , sz1 , sz2);
    }else{
        return buildLCS(str1 , str2 , i , j+1 , sz1 , sz2);
    }
}

string Align(Sequence * s1, Sequence * s2){
    memset(memo , -1,sizeof memo);/// this function fills the whole array with -1
    LCS(s1->seq , s2->seq , 0 , 0 , s1->sz , s2->sz);
    return buildLCS(s1->seq , s2->seq , 0,0 , s1->sz , s2->sz);
}

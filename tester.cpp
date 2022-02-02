#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
int main()
{
    std::string s;
    for(int i=0; i<10;i++)
    {
       std::string numer="test";
       numer+='0'+i;
       std::cout<<"test: "<<numer<<"\n";
       s ="E:\\laby_ok\\OK\\a.exe<"+numer;
       int x=system(s.c_str());
       std::cout<<"\n";
    }
    return 0;
}
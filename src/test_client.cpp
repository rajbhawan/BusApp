#include "../include/redisclient.h"
#include<stdio.h>
#include<string>
#include <iostream>
#include <sstream>
#include <boost/date_time.hpp>
#include"../include/CurlHttpGet.h"
using namespace std;
int main(int argc,char *argv[])
{
  try 
  {
	    string host = "127.0.0.1";
	    boost::shared_ptr<redis::client> shared_c( new redis::client(host) );;
	    redis::client & c = *shared_c;
   
            string source;
            string dest;
            string str1="http://www.redbus.in/bus-tickets/";
            string str2=".aspx#!02-Jun-2015";
            if(argc==3)
            {
            source=argv[1];
            dest=argv[2];
            string key=source+'-'+dest;

            string url=str1+key+str2;
            char *url1=new char[url.length()+1];
            strcpy(url1,url.c_str());
            c.select(2);
         if(c.exists(key)==0)
         {		 
           CurlHttpGet *obj=new CurlHttpGet(url1);
           std::vector<char> *bodyData= obj->get();
         
           std::string siteData( bodyData->begin(), bodyData->end() );
           c.set(key,siteData);
           c.save();
           string value=c.get(key);
           std::cout<<"bus information is here by the site"<<endl;
           std::cout<<value;
           delete obj;

         }
         else
         {
          string value=c.get(key);
          std::cout<<"bus information is here default"<<endl;
          std::cout<<value;
         }
         }
         else
         {
         cout<<"invalid number argument is here tell";
         }
    }
  catch (redis::redis_error & e) 
  {
    cerr << "got exception: " << e.what() << endl << "FAIL" << endl;
    return 1;
  }

  cout << endl << "testing completed successfully" << endl;
  return 0;
}

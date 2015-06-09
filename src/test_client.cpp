#include "../include/redisclient.h"
#include<stdio.h>
#include<string>
#include <iostream>
#include <boost/date_time.hpp>
#include"../include/CurlHttpGet.h"
using namespace std;
// Low level API
void setValueInList(redis::client & c)
{
    if(c.exists("delhi-mumbai"), false);
    {
        c.lpush("bus1:delhi-mumbai","name:raj,source:delhi,deistination:mumbai,time:2.30,fare:500rs");
    }
    c.save();
    std::string bus=c.lpop("bus1:delhi-mumbai");
    std::cout<<"available buses is"<<bus;
}
void setValueInSet(redis::client & c)
{

    c.sadd("set1", "sval1");
    c.sadd("set1", "sval2");
    c.save();

}
int main(int argc,char *argv[])
{
  try 
  {
    string host = "127.0.0.1";
    boost::shared_ptr<redis::client> shared_c( new redis::client(host) );;
    redis::client & c = *shared_c;
    
    // Test on high number databases
    cout<<"host"<<host<<endl;
     // Test on high number databases


            string source;
            string dest;
            string str1="http://www.redbus.in/bus-tickets/";
            string str2=".aspx#!02-Jun-2015";
            if(argc==3)
            {
            source=argv[1];
            dest=argv[2];
            string key=source+'-'+dest;
            char *keyIn=new char[key.length()+1];
            strcpy(keyIn,key.c_str());
            string url=str1+source+'-'+dest+str2;
            char *url1=new char[url.length()+1];
            strcpy(url1,url.c_str());
            c.select(1);
           string value=c.get(keyIn);
           //cout<<"value"<<value<<"key is"<<keyIn;
        //   c.flushdb();
       if(value.size()>0)
        {
           //setValueInList(c);
           cout<<"value"<<value<<"key is"<<keyIn;
           setValueInSet(c);
         }
       else
       {
           CurlHttpGet *obj=new CurlHttpGet(url1);
           obj->get();
           delete obj;

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

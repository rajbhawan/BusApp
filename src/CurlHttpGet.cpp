
#include "../include/CurlHttpGet.h"
#include <curl/curl.h>
#include<iostream>
using namespace std;
CurlHttpGet::CurlHttpGet(const char* url) {
	this->url = url;
}

CurlHttpGet::~CurlHttpGet() {
}

int CurlHttpGet::writer(char *data, size_t size, size_t nmemb, std::vector<char> *headersOrBody) {
	if (headersOrBody != NULL) {
		const char * d = data;
		// Append the data to the buffer
		headersOrBody->insert(headersOrBody->end(), d, d + (size * nmemb));
		return size * nmemb;
	}
	
	return 0;
}

vector<char> * CurlHttpGet::get() {
	
	CURL *curl;
	CURLcode result;
	
	// Clear the body so that the same instance can be used across requests
	body.clear();

	// Create our curl handle
	curl = curl_easy_init();

	if (curl) {
		// Now set up all of the curl options
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);		
		curl_easy_setopt(curl, CURLOPT_URL, url);
                struct curl_slist *headers=NULL;
                headers = curl_slist_append(headers, "Content-Type: text/html");
                curl_easy_setopt(curl, CURLOPT_HEADER,1);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);   
                curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);      
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlHttpGet::writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
		// Attempt to retrieve the remote page
		result = curl_easy_perform(curl);
		if (result == CURLE_OK)
		{
			// Get the HTTP response code and header size
			long httpCode = 0;
			size_t headerSize = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
			curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &headerSize);
			// Cleanup
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
			if(headerSize < body.size() && httpCode == 200)
			{ // std::vector<char>::iterator it=body.begin();
			  //for(;it<=body.end();it++)
                           //{
                             //cout<<*it;
                           //}
                        return &body;
			}
			
		}
		else
		{
			// Cleanup
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
			
		}
	}

	
}


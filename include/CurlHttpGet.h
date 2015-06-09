

#ifndef CURLHTTPGET_H_
#define CURLHTTPGET_H_

#include <sstream>
#include <vector>

class CurlHttpGet {
private:
	std::vector<char>body;
	const char* url;

	static int writer(char *data, size_t size, size_t nmemb, std::vector<char> *headersOrBody);
public:	
	CurlHttpGet(const char* url);
	virtual ~CurlHttpGet();
	std::vector<char> * get();
};
#endif 

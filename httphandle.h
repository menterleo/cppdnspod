#ifndef httphandle_h
#define httphandle_h

#include<stdio.h>
#include<string>
#include<curl/curl.h>

enum HTTP_METHOD{
	GET,
	POST
};

class HTTPHANDLE{
	private:
		CURL *curl;
		CURLcode res;
	public:
		HTTPHANDLE(const char * url,HTTP_METHOD method,const char * useragent, const char * postdata);
		std::string getinfo();
};

#endif

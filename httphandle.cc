#include<stdio.h>
#include<iostream>
#include<string>
#include<curl/curl.h>
#include"httphandle.h"

static std::string HTTPHANDLE_HTMLCODE;
static size_t write_data(char *buffer, size_t size, size_t nmemb, void *userp){
	HTTPHANDLE_HTMLCODE = buffer;
	return size;
}

HTTPHANDLE::HTTPHANDLE(const char * url,HTTP_METHOD method,const char * useragent, const char * postdata){
	curl = curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,url);
	if(method == POST)
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,postdata);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&write_data);
	curl_easy_setopt(curl,CURLOPT_USERAGENT,useragent);
	curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,10);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,10);
}

std::string HTTPHANDLE::getinfo(){
	if(curl){
		HTTPHANDLE_HTMLCODE = "";
		curl_easy_perform(curl);
		//curl_easy_cleanup(curl);
		return HTTPHANDLE_HTMLCODE;
	}
}


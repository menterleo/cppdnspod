#include<stdio.h>
#include<iostream>
#include<string>
#include<time.h>
#include"httphandle.h"

const std::string updatednsurl   = "https://dnsapi.cn/Record.Ddns";
const std::string publicipurl    = "http://checkip.dyndns.org/";
const std::string privateipurl   = "http://yourdomain/show_my_user_agent.php";//你自己的web页面，返回user agent
const std::string privateuacheck = "myself ua check key";
const std::string dnspodagent    = "CppDdnsPodForLinux Client/1.0.0 (menterleo@gmail.com)";
const std::string postdnsdata    = "login_email=&login_password=&domain_id=&record_id=&sub_domain=&record_line=默认&format=json";//补全相关内容

HTTPHANDLE hhmyself(privateipurl.c_str(),GET,privateuacheck.c_str(),"");
HTTPHANDLE hhpublic(publicipurl.c_str(),GET,"getip,thanks!","");
HTTPHANDLE hhdnspod(updatednsurl.c_str(), POST, dnspodagent.c_str(), postdnsdata.c_str());

std::string gettime()
{
	time_t timep;
	time(&timep);
	std::string now = ctime(&timep);
	return now.replace(now.find("\n"),2,"");
}

bool updateDns(){
	while(1){
		std::string result;
		result = hhdnspod.getinfo();
		std::cout << result << std::endl;
		if(result.find("Action completed successful") == -1){
			std::cout << "Update Error!! It will retry in 60s..." << std::endl;
			sleep(60);
		}
		else{
			break;
		}
	}
	return 1;
}

bool check_ip_from_public_server(){
	static std::string ip;
	std::string currentip;
	std::cout << gettime() << " Check IP from public server." << std::endl;
	if((currentip = hhpublic.getinfo()) != ""){
		if(ip == currentip){
			//ip not changed.
			return 1;
		}
		else{
			//ip changed!
			if(updateDns()){
				ip = currentip;
				return 1;
			}
			else
				return 0;
		}
	}
	else
		return 0;
}

bool check_myself_host(){
	static int count = 0;
	std::string currentip;
	//check_ip_from_private_server
	currentip = hhmyself.getinfo();
	if(currentip.find(privateuacheck) == -1){
		if(count++ % 10 == 0){
			if(check_ip_from_public_server()){
				return 1;
			}
			else{
				std::cout << "CHECK IP from " << publicipurl << " failed!" << std::endl;
				return 0;
			}
		}
	}
	else{
		count = 0;
	}
	return 1;
}

int main(){
	std::cout << gettime() << " Start cppdnspod." << std::endl;
	while(1){
		if(!check_myself_host()){
			//std::cout << "CHECK IP failed！" << std::endl;
		}
		sleep(7);
	}
	return 0;
}


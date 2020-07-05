#include<iostream>
#include<conio.h>
#include<string>
using namespace std;
const string ALPH="abcdefghijklmnopqrstuvwxyz";
char newChar(char m,char k){
	int mInt,kInt;
	for(auto it=ALPH.begin();it!=ALPH.end();++it){
		if(*it==k){kInt=it-ALPH.begin();}
		if(*it==m){mInt=it-ALPH.begin();}
	}
	int pos=mInt+kInt;
	if(pos>25){pos-=26;}
	return ALPH[pos];
}
char oldChar(char m,char k){
	int mInt,kInt;
	for(auto it=ALPH.begin();it!=ALPH.end();++it){
		if(*it==k){kInt=it-ALPH.begin();}
		if(*it==m){mInt=it-ALPH.begin();}
	}
	int pos=mInt-kInt;
	if(pos<0){pos+=26;}
	return ALPH[pos];
}
string newKey(string message,string key){
	string ret="";
	if(message.size()>key.size()){
		auto it=key.begin();
		while(ret.size()!=message.size()){
			ret+=*it;
			if(it==key.end()-1){it=key.begin();}
			else{++it;}
		}
	}else{ret=key;}
	return ret;
}
string encrypt(string message,string key){
	string ret="";
	key=newKey(message,key);
	for(int i=0;i!=message.size();++i){
		ret+=newChar(message[i],key[i]);
	}
	return ret;
}
string decrypt(string message,string key){
	string ret="";
	key=newKey(message,key);
	for(int i=0;i!=message.size();++i){
		ret+=oldChar(message[i],key[i]);
	}
	return ret;
}
int main(){
	//cout<<encrypt("imsocooliwannadieimsocooliwannadieimsocooliwannadieimsocooliwannadieimsocooliwannadieimsocooliwannadie","also")<<endl;
	cout<<decrypt("tbpcwieowjneyxhbpicuygcnkpypmasjhnxuokjkkhcmcsvxqnbhykqyjourphjumnlhmgyqxqjarlxuyjiblnorkokujbkxbncl","pghkourojgwafgtghquglnvjj")<<endl;
	getch();
}
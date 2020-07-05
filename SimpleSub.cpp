#include<iostream>
#include<conio.h>
#include<string>
#include<cctype>
using namespace std;
const string ALPH="abcdefghijklmnopqrstuvwxyz";
string encrypt(string message,string key){
	string ret,cleanMessage;
	for(int i=0;i!=message.size();++i){
		cleanMessage+=tolower(message[i]);
	}
	for(auto iter=cleanMessage.begin();iter!=cleanMessage.end();++iter){
		if(isalpha(*iter)){
			ret+=key[ALPH.find(*iter)];
		}
	}
	return ret;
}
string decrypt(string message,string key){
	string ret;
	for(auto iter=message.begin();iter!=message.end();++iter){
		ret+=ALPH[key.find(*iter)];
	}
	return ret;
}
int main(){
	//cout<<encrypt("imsocooliwannadie","bcdefghijklmnopqrstuvwxyza")<<endl;
	cout<<decrypt("craqxuqfivsjcryxgakvrisftrwctswaksufkwrjgysfhyrckvscaqkvuwcvstgrmujrofuzfafiakkvrcajrksjriwrajsfhuxk","agmirxhvsloyjfutnwckqdzbep")<<endl;
	getch();
}
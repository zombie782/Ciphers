#include<iostream>
#include<conio.h>
#include<string>
#include<cctype>
#include<utility>
using namespace std;
string createSquare(string key){
	string ret="abcdefghiklmnopqrstuvwxyz";
	for(auto it=key.end()-1;it>=key.begin();--it){
		if(*it=='j'){*it='i';}
		for(auto jt=ret.begin();jt!=ret.end();++jt){
			if(*it==*jt){
				ret.erase(jt);
				ret.insert(ret.begin(),*it);
				break;
			}
		}
	}
	return ret;
}
string modMessage(string message){
	if(message.size()%2){
		message+='x';
	}
	for(auto it=message.begin();it!=message.end();it+=2){
		if(*it=='j'){*it='i';}
		if(*(it+1)=='j'){*(it+1)='i';}
		if(*it==*(it+1)){
			*(it+1)='x';
		}
	}
	return message;
}
pair<int,int> getPositions(char one,char two,string key){
	return make_pair(key.find(one),key.find(two));
}
string encrypt(string message,string key){
	key=createSquare(key);
	message=modMessage(message);
	string ret="";
	for(auto it=message.begin();it!=message.end();it+=2){
		pair<int,int> pos=getPositions(*it,*(it+1),key);
		if(pos.first%5==pos.second%5){
			if(pos.first>19){pos.first-=20;}
			else{pos.first+=5;}
			if(pos.second>19){pos.second-=20;}
			else{pos.second+=5;}
		}else if(pos.first/5==pos.second/5){
			if(pos.first%5==4){pos.first-=4;}
			else{++pos.first;}
			if(pos.second%5==4){pos.second-=4;}
			else{++pos.second;}
		}else{
			int dif=pos.first%5-pos.second%5;
			pos.first-=dif;
			pos.second+=dif;
		}
		ret+=key[pos.first];
		ret+=key[pos.second];
	}
	return ret;
}
string decrypt(string message,string key){
	key=createSquare(key);
	string ret="";
	for(auto it=message.begin();it!=message.end();it+=2){
		pair<int,int> pos=getPositions(*it,*(it+1),key);
		if(pos.first%5==pos.second%5){
			if(pos.first<5){pos.first+=20;}
			else{pos.first-=5;}
			if(pos.second<5){pos.second+=20;}
			else{pos.second-=5;}
		}else if(pos.first/5==pos.second/5){
			if(pos.first%5==0){pos.first+=4;}
			else{--pos.first;}
			if(pos.second%5==0){pos.second+=4;}
			else{--pos.second;}
		}else{
			int dif=pos.first%5-pos.second%5;
			pos.first-=dif;
			pos.second+=dif;
		}
		ret+=key[pos.first];
		ret+=key[pos.second];
	}
	return ret;
}
int main(){
	//cout<<encrypt("imsocooliwannadie","lmao")<<endl;
	cout<<decrypt("pwkgbzbsmpgzkovthbtxcotbdisfqhpscpnwpiwcwfnrkloemvdeemgrzdimywmpufngbzbzpiaekgpsemyqmgnporokveqvxpie","fghwaqcnt")<<endl;
	getch();
}
#include<iostream>
#include<conio.h>
#include<string>
#include<cctype>
#include<map>
#include<algorithm>
using namespace std;
string encrypt(string message,string key){
	while(message.size()%key.size()!=0){
		message+="x";
	}
	map<char,string>grid;
	for(int i=0;i!=key.size();++i){
		string str="";
		for(int j=0;j!=message.size()/key.size();++j){
			str+=message[j*key.size()+i];
		}
		if(!isalpha(str[str.size()-1])){str.pop_back();}
		grid.insert(make_pair(key[i],str));
	}
	string ret="";
	for(auto e:grid){
		ret+=e.second;
	}
	return ret;
}
string decrypt(string message,string key){
	double d=static_cast<double>(message.size())/key.size();
	if(d!=static_cast<int>(d)){
		cerr<<"Must be rectangular decryption"<<endl;
		return "";
	}else{
		map<char,string>grid;
		string oKey=key;
		sort(key.begin(),key.end());
		int length=message.size()/key.size();
		for(int i=0;i!=key.size();++i){
			grid.insert(make_pair(key[i],message.substr(i*length,length)));
		}
		string ret;
		for(int i=0;i!=length;++i){
			for(int j=0;j!=oKey.size();++j){
				ret+=grid[oKey[j]][i];
			}
		}
		return ret;
	}
}
int main(){
	//cout<<encrypt("imsocooliwannadie","cat")<<endl;
	cout<<decrypt("aceoneersltfloiethnauteoergigotiofationyitlizuysiefcruldntutmoerthlsefacbhdnsartnmcohetsirrthfhotsdm","fevinklwbhrtzasdjcypgoqmu")<<endl;
	getch();
}
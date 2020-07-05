#include<iostream>
#include<conio.h>
#include<utility>
#include<vector>
#include<cmath>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;
const string ALPH="abcdefghijklmnopqrstuvwxyz";
int convert(char c){
	for(auto it=ALPH.begin();it!=ALPH.end();++it){
		if(*it==c){return it-ALPH.begin();}
	}
	return -1;
}
char convert(int i){
	for(auto it=ALPH.begin();it!=ALPH.end();++it){
		if(i==it-ALPH.begin()){return *it;}
	}
	return '?';
}
string convertBlock(MatrixXd m,int r){
	string ret="";
	for(int i=0;i!=r;++i){
		ret+=convert(static_cast<int>(m(i,0)));
	}
	return ret;
}
double cofactor(MatrixXd m,int r,int c){
	MatrixXd newM(m.rows()-1,m.cols()-1);
	vector<double>elements;
	for(int i=0;i<m.rows();++i){
		for(int j=0;j<m.cols();++j){
			if(i!=r && j!=c){
				elements.push_back(m(i,j));
			}
		}
	}
	int k=0;
	for(int i=0;i!=newM.rows();++i){
		for(int j=0;j!=newM.cols();++j){
			newM(i,j)=elements[k];
			++k;
		}
	}
	if((r+c)%2){
		return -(newM.determinant());
	}
	return newM.determinant();
}
MatrixXd cofactors(MatrixXd m){
	MatrixXd ret(m.rows(),m.cols());
	for(int i=0;i!=m.rows();++i){
		for(int j=0;j!=m.cols();++j){
			ret(i,j)=cofactor(m,i,j);
		}
	}
	return ret;
}
MatrixXd adjugate(MatrixXd m){
	return cofactors(m).transpose();
}
int mod(int x,int y){
	if(x<0){
		while(x<0){x+=y;}
		return x;
	}
	return x%y;
}
MatrixXd mod(MatrixXd m,int divisor){
	MatrixXd ret(m.rows(),m.cols());
	for(int i=0;i!=m.rows();++i){
		for(int j=0;j!=m.cols();++j){
			ret(i,j)=mod(static_cast<int>(round(m(i,j))),divisor);
		}
	}
	return ret;
}
int dInverse(int det,int divisor){
	for(int i=0;i!=divisor;++i){
		if(mod((i*det-1),divisor)==0){
			return i;
		}
	}
}
MatrixXd modInverseMatrix(MatrixXd m,int divisor){
	return mod(adjugate(m)*dInverse(static_cast<int>(round(m.determinant())),divisor),divisor);
}
pair<string,MatrixXd> encrypt(string message,MatrixXd key){
	if(static_cast<int>(round(key.determinant()))==0){
		cerr<<"Try another matrix."<<endl;
		return make_pair("",key);
	}
	while(message.size()%key.rows()!=0){message+="x";}
	vector<MatrixXd>matrices;
	for(int i=0;i!=message.size();i+=key.rows()){
		MatrixXd curr(key.rows(),1);
		for(int j=0;j!=key.cols();++j){
			curr(j,0)=convert(message[i+j]);
		}
		matrices.push_back(curr);
	}
	string ret="";
	for(auto it=matrices.begin();it!=matrices.end();++it){
		*it=key*(*it);
		*it=mod(*it,26);
		ret+=convertBlock(*it,key.rows());
	}
	return make_pair(ret,modInverseMatrix(key,26));
}
pair<string,MatrixXd> encrypt(string message,string wordKey){
	MatrixXd key(static_cast<int>(sqrt(wordKey.size())),static_cast<int>(sqrt(wordKey.size())));
	int k=0;
	for(int i=0;i!=key.rows();++i){
		for(int j=0;j!=key.cols();++j){
			key(i,j)=convert(wordKey[k]);
			++k;
		}
	}
	if(static_cast<int>(round(key.determinant()))==0){
		cerr<<"Try another matrix."<<endl;
		return make_pair("",key);
	}
	while(message.size()%key.rows()!=0){message+="x";}
	vector<MatrixXd>matrices;
	for(int i=0;i!=message.size();i+=key.rows()){
		MatrixXd curr(key.rows(),1);
		for(int j=0;j!=key.cols();++j){
			curr(j,0)=convert(message[i+j]);
		}
		matrices.push_back(curr);
	}
	string ret="";
	for(auto it=matrices.begin();it!=matrices.end();++it){
		*it=key*(*it);
		*it=mod(*it,26);
		ret+=convertBlock(*it,key.rows());
	}
	return make_pair(ret,modInverseMatrix(key,26));
}
int main(){
	MatrixXd m(4,4);
	m<<20,2,18,21,11,9,21,7,18,12,17,10,5,16,4,20;
	//m<<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16;
	auto result=encrypt("jgglgpecxqevpkfwhaqbcymipsulyatndlvkuioieswyeshedqwszehwxzwqeukscjwoyrimnxarjnukfmmhxapkiivgnswkkgxi",
						m);
	cout<<result.first<<endl<<result.second<<endl;
	/*auto result2=encrypt("iusmctscibsonjnneebg",result.second);
	cout<<result2.first<<endl<<result2.second<<endl;*/
	getch();
}
#include <iostream>
#include <fstream>
 
using namespace std;
//struct ()


 string substitution_cipher(string key, string a,int f) {
char m[a.size()];
string newkey = key.append("abcdefghijklmnopqrstuvxyz");
 cout << newkey << " "<< '\n';
 cout << a << " "<< '\n';  

for ( int i = 0; i < a.size();i++ )
{
    if (i < newkey.size()){
    m[i] = (a.at(i) + (int)(newkey.at(i)));  
   }else{
    m[i] = (a.at(i));
   }

}
string str(m); 
return str;
};

string caesar_cipher(string a,int f) {
char m[a.size()]; 
if (f){
for ( int i = 0; i < a.size();i++ )
{
    m[i] = (a.at(i) - 3);  
}
}else{
for ( int i = 0; i < a.size();i++ )
{
    m[i] = (a.at(i) + 3);  
}
}
string str(m); 
return str;
};

string monoalphabetic_cipher(string key, string a) {
return "Enqrypted";
};

string polyalphabetic_cipher(string key, string a) {
return "Enqrypted";
};

string transpositon_cipher(string key, string a) {
return "Enqrypted";
};


string enqrypt(char *argv[]){
char * str1 = argv[1];
char * str2 = argv[2]; 
int flag; 
string b = " Invalid commad";
if(strcmp(str1,"--encrypt")==0){
    flag = 0;
}else if(strcmp(str1,"--decrypt")==0){
    flag = 1;
}
        if(strcmp(str2,"-subst")==0){
          //b = "Substitution";
          b = substitution_cipher(argv[3],argv[4],flag);
        }
        else if(strcmp(str2,"-ces")==0){
          b = caesar_cipher(argv[3],flag);;
          //monoalphabetic_cipher(argv[1],argv[2]);  
        }
        else if(strcmp(str2,"-mono")==0){
          b = "Monoalphabetic";
          //monoalphabetic_cipher(argv[1],argv[2]);  
        }
        else if(strcmp(str2,"-vig")==0){
          b = "Transpositon";
          //transpositon_cipher(argv[1], argv[2]); 
        }

return b;
}


int main ( int argc, char *argv[] ) {
  int i = 0;
 string a = "message";
 string b = enqrypt(argv);

 cout << b << " "<< '\n'; 
    return 0;
}
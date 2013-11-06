#include <iostream>
#include <fstream>
 
using namespace std;
//struct ()


string caesar_cipher(string key, string a) {
char m[a.size()];  
for ( int i = 0; i < a.size();i++ )
{
    if (i < key.size()){
    m[i] = (a.at(i) + (int)(key.at(i) + i));  
   }else{
    m[i] = (a.at(i) + i);
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
string b = " Invalid commad";

if(strcmp(str1,"-subst")==0){
  //b = "Substitution";
  b = caesar_cipher(argv[2],argv[3]);
}
else if(strcmp(str1,"-mono")==0){
  b = "Monoalphabetic";
  //monoalphabetic_cipher(argv[1],argv[2]);  
}
else if(strcmp(str1,"-vig")==0){
  b = "Transpositon";
  //transpositon_cipher(argv[1], argv[2]); 
}
return b;
}


int main ( int argc, char *argv[] ) {
  int i = 0;
 string a = "message";
 string b = enqrypt(argv);

 cout << b << '\n'; 
    return 0;
}
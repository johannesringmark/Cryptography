#include <iostream>
#include <fstream>
 
using namespace std;
//struct ()


//  string substitution_cipher(string key, string a) {
// char m[a.size()];  
// for ( int i = 0; i < a.size();i++ )
// {
//     if (i < key.size()){
//     m[i] = (a.at(i) + (int)(key.at(i) + i));  
//    }else{
//     m[i] = (a.at(i) + i);
//    }

// }
// string str(m); 
// return str;
//};

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
string b = " Invalid commad";
if(strcmp(str1,"--encrypt")==0){
        if(strcmp(str2,"-subst")==0){
          //b = "Substitution";
          b = caesar_cipher(argv[3],0);
        }
        else if(strcmp(str2,"-subst")==0){
          b = "Monoalphabetic";
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

}else if(strcmp(str1,"--decrypt")==0){
                if(strcmp(str2,"-subst")==0){
               //b = "Substitution";
                b = caesar_cipher(argv[3],1);
        }
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
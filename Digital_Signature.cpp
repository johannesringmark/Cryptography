#include <iostream>
#include <fstream>
#include <gmp.h>
 
using namespace std;
const int L=1024;
const int N=160;
typedef struct{
	int prime1;
	int prime2;
} tuple;

typedef struct{
	int key1;
	int key2;
} key_pair;

typedef struct {
	string secret_key;
	string public_key;
} sign_pair;

typedef struct {
}message_digest;
key_pair genkey_pair(int n){
	mpz_t rand_Num;
    unsigned long int i, seed;
    gmp_randstate_t r_state;

    seed = 123456;

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init2(rand_Num,160);
    for (int i = 0; i < n ; i++){
    	// fix size error
       mpz_urandomb(rand_Num,r_state,(N+1));
       gmp_printf("x=%Zd\n", rand_Num);
       mpz_urandomb(rand_Num,r_state,(N+1));
   	   gmp_printf("y=%Zd\n", rand_Num);
    }

    gmp_randclear(r_state);
    mpz_clear(rand_Num);
	key_pair nes;
	//nes = 

return	nes ;
}

sign_pair signing_operation(int p,int q,int g,key_pair a){
	 sign_pair hej;
	return hej;
 }
bool verification_algorithm(){
return 0;
 }

 int invalid(string p,string q, string g){
 	return 0;
 }

int main(){
	string p,q,g,n; 
	cout << "Input p" << endl;	
		cin >> p;
	cout << "Input q" << endl;
		cin >> q;
	cout << "Input g" << endl;
		cin >> g;

		if (invalid(p,q,g)){
			cout << "invalid_group" << endl;
			return 0;
		}else{
			cout << "valid_group" << endl;
		};

	cout << "Input n" << endl;
		cin >> n;

	int a = 10;
	int b = 10;
	int c = 20;
	genkey_pair(5);
		
	if(strcmp(n.c_str(),"genkey") == 0){
	  	cout << "genkey" << endl;
	  	
	
	}
	else if(strcmp(n.c_str(),"sign") == 0){
	   	string x,y,d1,d2,d3; 
	   	cout << "sign" << endl;
	   cout << "Input x" << endl;	
		cin >> x;
		cout << "Input y" << endl;
		cin >> y;
		cout << "Input D" << endl;
		cin >> d1;
		cout << "Input D" << endl;
		cin >> d2;
		cout << "Input D" << endl;
		cin >> d3;
	 }
	else if(strcmp(n.c_str(),"verify")== 0){
		string p,q,g;
		cout << "verify" << endl;
		cout << "Input y" << endl;	
		cin >> p;
		cout << "Input q" << endl;
		cin >> q;
		cout << "Input g" << endl;
		cin >> g;
	};
	

	cout << "Error while opening the file" << endl;
return 0;
 }
 
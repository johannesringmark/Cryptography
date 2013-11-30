#include <iostream>
#include <fstream>
#include <gmp.h>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <cstring> 
#include <sstream>
#include <ctime>
using namespace std;
//#macros
const int L = 1024;
const int N = 160;


typedef struct{
	mpz_t p;
	mpz_t q;
	mpz_t g;
} tuple;

typedef struct{
	bool valid;
	mpz_t p;

}m_inverse;

typedef struct{
	mpz_t x;
	mpz_t y;
} key_pair;

typedef struct {
	mpz_t r;
	mpz_t s;
} sign_pair;

typedef struct {
	string  M;
}message_digest;


key_pair genkey_pair(tuple* pqg){ // generates a new ``key_pair'' with a pseudo random x 
	key_pair pair;
	unsigned long x_raise = rand();  

	mpz_t x;
	mpz_t y;

	mpz_init(pair.x);
	mpz_init(pair.y);
	mpz_init(y);

	mpz_init_set_ui(x,x_raise);
	mpz_powm_ui(x,x,x_raise,(*pqg).q); // big random number is create with boundarys 0 < x < q


	do{ // while x is less then p find next prime for x
		mpz_nextprime (x, x);	

	}while( !(mpz_cmp(x,(*pqg).p) < 0) );
		mpz_set(pair.x,x);

	// y is created from raising g to x modulo p
	mpz_powm(y,(*pqg).g,x,(*pqg).p);
	mpz_set(pair.y,y);

    mpz_clear(x);
    mpz_clear(y);

return	pair;
}





//C.1 Computation of the Inverse Value;
m_inverse inverse_value(mpz_t* z,mpz_t* a){ //from assignment 2
	mpz_t i,j,y,y1,y2,rem,quotient,tmp;
	m_inverse zinv;
	mpz_init(zinv.p);
	//commits is fun!
	
	if ( !(mpz_cmp(*a,*z) && mpz_cmp_si(*z,0))){
		cout << "invalid arguments" << endl;
		zinv.valid = 0;
		return zinv;
	}
	 mpz_init(i);mpz_init(j);mpz_init(y);mpz_init(y1);
	 mpz_init(y2);mpz_init(rem); mpz_init(quotient);mpz_init(tmp);
	mpz_set(i,*a);
	mpz_set(j,*z);
	mpz_set_ui(y2,0);
	mpz_set_ui(y1,1);
	do{
		//quotient = floor((i+0.0)/(j+0.0));
		mpz_div(quotient,i,j);

		//rem = i - ( j * quotient);
		mpz_mul(tmp,j,quotient);
		mpz_sub(rem,i,tmp);

		//y = y2 - (y1 * quotient);
		mpz_mul(tmp,y1,quotient);
		mpz_sub(y,y2,tmp);

		//i = j; j = rem; y2 = y1;y1 = y;
		mpz_set(i,j);
		mpz_set(j,rem);
		mpz_set(y2,y1);
		mpz_set(y1,y);

	}while(mpz_cmp_si(j,0));
		if (mpz_cmp_si(i,1) != 0){
			cout << "Error_" << endl;
			zinv.valid = 0;
			return zinv;
		};

	zinv.valid = 1;
	//zinv.p = (y2 % a);
	mpz_mod (zinv.p, y2, *a);
	mpz_clear(i);mpz_clear(j);mpz_clear(y);mpz_clear(y1);
	 mpz_clear(y2);mpz_clear(rem); mpz_clear(quotient);mpz_clear(tmp);
	return zinv;
}








sign_pair signing_operation(tuple* pqg,key_pair (*a),message_digest* m){
	 mpz_t r,s,k,k_inv,z,tmp;
	 key_pair kp = genkey_pair(pqg);
	 sign_pair out;
	 mpz_init(out.r);
	 mpz_init(out.s);
	 mpz_init(r);mpz_init(s);mpz_init(k);mpz_init(k_inv);mpz_init(tmp);mpz_init(z);
	 mpz_set(k,kp.x);


	string message_  = ((*m).M);
	mpz_set(k_inv,inverse_value(&k,&(*pqg).q).p);

	mpz_powm(r,(*pqg).g,k,(*pqg).p);
	mpz_mod(r,r,(*pqg).q);

	//z = the leftmost min(N,outlen) bits of hash(M) 
	mpz_set_str(z,message_.c_str(),16);
	
	//s = (k^-1)(z+xr) mod q
	mpz_mul(tmp,(*a).x,r);
	mpz_add(tmp,tmp,z);


	mpz_mul(s,k_inv,tmp);
	mpz_mod(s,s,(*pqg).q);
	mpz_set(out.r,r);
	mpz_set(out.s,s);
	// 

	mpz_clear(r);mpz_clear(s);mpz_clear(k);mpz_clear(k_inv);mpz_clear(tmp);mpz_clear(z);
	return out;
 }

//Defines the signing operation
bool verification_algorithm(tuple* pqg, mpz_t* y, message_digest* m,sign_pair* rs){
	 mpz_t w,u1,u2,v,tmp2,tmp1,r,z;
	  
	  mpz_init(w);mpz_init(u1);mpz_init(u2);mpz_init(v);mpz_init(tmp1);mpz_init(tmp2);
	  mpz_init(z);
	  string message_  = ((*m).M);
	  
	//1;
	//check 0 < r' < q and 0 < s' < q; if either condition is violated,
	if(!((mpz_cmp_ui((*rs).r,0)> 0) && 
		(mpz_cmp((*pqg).q,(*rs).r)> 0) && (mpz_cmp_ui((*rs).s,0) > 0) && (mpz_cmp((*pqg).q,(*rs).s)> 0)) ){
		return 0;	
	} 

	//2;
	// w = s'^-1 mod q
	mpz_mod(w,inverse_value(&(*rs).s,&(*pqg).q).p,(*pqg).q);

	// z = the leftmost min(N,outlen) bits of Hash(M')(should bee converted to integer)
	mpz_set_str(z,message_.c_str(),16);
	// u1 = (zw) mod q
	mpz_mul(u1,w,z);
	mpz_mod(u1,u1,(*pqg).q);
	// u2 = ((r')w) mod q.
	mpz_mul(u2,(*rs).r,w);
	mpz_mod(u2,u2,(*pqg).q);
	
	// v  = (g^u1 y^u2 mod p)mod q
	mpz_powm(tmp1,(*pqg).g,u1,(*pqg).p);
	mpz_powm(tmp2,(*y),u2,(*pqg).p);
	mpz_mul(v,tmp1,tmp2);
	mpz_mod(v,v,(*pqg).p);
	mpz_mod(v,v,(*pqg).q);

	//3;
	//if v = r', then signarture is verified else return invalid 
	if (mpz_cmp(v,(*rs).r) != 0){
		return 0;
	}
	
return 1;
 }


 //Define the verification algorithm
 int isvalid(tuple* pqg){

 	//retriving binary length's 
 	int length_p = ((string) mpz_get_str(NULL,2,(*pqg).p)).length();
 	int length_q = ((string) mpz_get_str(NULL,2,(*pqg).q)).length();
 	
 	mpz_t t,tmp1,tmp2;
 	mpz_init(tmp1);
 	mpz_init(tmp2);
 	mpz_init(t);

 	//precalculating q-1
 	mpz_sub_ui(t,(*pqg).p,1);

 	//precalculating g^q mod p
 	mpz_powm(tmp1,(*pqg).g,(*pqg).q,(*pqg).p);

 	if (
	//both p and q are probably primes;
 	mpz_probab_prime_p((*pqg).p,25) &&
 	mpz_probab_prime_p((*pqg).q,25) &&
 	//q is a divisor of p-1;
 	mpz_divisible_p(t,(*pqg).q) &&
 	//g has order q i.e. g^q mod p = 1 and g > 1.
 	!mpz_cmp_ui(tmp1,1) &&
 	mpz_cmp_ui((*pqg).g,1) &&
 	//p is a 1024 bit number and q a 160 bit number
 	(length_p == L ) &&
 	(length_q == N )
 	){

 	cout << "valid_group" << endl;
 	return 1;
	}
	
	cout << "invalid_group" << endl;
	return 0;
 }



int main(int argc, char *argv[]){
  tuple pqg;
   mpz_t z;
   mpz_t a;
   mpz_t y;
   string line;
   srand(time(NULL)); // Initializing the pseudo random number generator based on the time. 

  mpz_init(pqg.p);
  mpz_init(pqg.q);
  mpz_init(pqg.g); 

  	// parses data from the std input
  	getline (cin,line);
  	mpz_set_str(pqg.p,&line.c_str()[2],10);
	getline (cin,line);
  	mpz_set_str(pqg.q,&line.c_str()[2],10);
  	getline (cin,line);
  	mpz_set_str(pqg.g,&line.c_str()[2],10);

  	 if (!isvalid(&pqg)){
  	 	return 0;
  	 }

  	getline (cin,line);
  	if(strcmp(line.c_str(),"genkey") == 0){
	  	int n;
	  	getline (cin,line);
	  	n = atoi(&line.c_str()[2]);
	  	for(int i = 0; i < n;i++){
	  		key_pair a = genkey_pair(&pqg);
	  		gmp_printf("x=%Zd\n", a.x);
	  		gmp_printf("y=%Zd\n", a.y);

	  	}
	
	}
	else if(strcmp(line.c_str(),"sign") == 0){
	   	message_digest D;
	   	key_pair xy;
	   	mpz_init(xy.y);
	   	mpz_init(xy.x);
	   	cout << "sign" << endl;
	 
	   	getline (cin,line);   	
  		mpz_set_str(xy.x,&line.c_str()[2],10);
		getline (cin,line);
  		mpz_set_str(xy.y,&line.c_str()[2],10);
  		
  		while ( getline (cin,line) )
    	{

  			D.M = &line.c_str()[2];
  			sign_pair sign = signing_operation(&pqg,&xy,&D);
  			gmp_printf("r=%Zd\n", sign.r);
			gmp_printf("s=%Zd\n", sign.s);
  			
    	}
	 }
	else if(strcmp(line.c_str(),"verify") == 0){
		key_pair xy;
		sign_pair rs;
		message_digest D;
		mpz_init(xy.y);
		mpz_init(rs.s);
		mpz_init(rs.r);
		cout << "verify" << endl;
		getline (cin,line);
  		mpz_set_str(xy.y,&line.c_str()[2],10);
  		( getline (cin,line) && line.length() > 0 );
  		do 
    	{
  			D.M = &line.c_str()[2];
    		getline (cin,line);
  			mpz_set_str(rs.r,&line.c_str()[2],10);
  			getline (cin,line);
  			mpz_set_str(rs.s,&line.c_str()[2],10);
      		if(verification_algorithm(&pqg, &xy.y, &D,&rs)){
      			cout << "signature_valid" << endl;
      		}else{
      			cout << "signature_invalid" << endl;
      		}
    	}while(( getline (cin,line) ));

	};
    mpz_clear(pqg.p);
  	mpz_clear(pqg.q);
  	mpz_clear(pqg.g);
return 0;
 }
 
#include <iostream>
#include <fstream>
#include <gmp.h>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <cstring> 
#include <sstream>
using namespace std;
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


key_pair genkey_pair(){
	mpz_t rand_Num;
	mpz_t rand_Num2;
    unsigned long int i, seed;
    gmp_randstate_t r_state;
    key_pair pair;
    seed = 123456;
    mpz_init(pair.x);
    mpz_init(pair.y);
    mpz_init(rand_Num2);
    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init2(rand_Num,160);
    
    for (int i = 0; i < 5 ; i++){
    	// fix size error
       mpz_urandomb(rand_Num,r_state,(N+1));
       mpz_set(rand_Num2,rand_Num);
       mpz_urandomb(rand_Num2,r_state,(N+1));
    }
    //gmp_printf("x=%Zd\n", rand_Num);
    //gmp_printf("y=%Zd\n", rand_Num2);
    mpz_set(pair.x,rand_Num2);
    mpz_set(pair.y,rand_Num);
    gmp_randclear(r_state);
    mpz_clear(rand_Num);
    mpz_clear(rand_Num2);
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
			cout << "Error2" << endl;
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


int signing_operation(tuple* pqg,key_pair (*a),message_digest* m){
	 mpz_t r,s,k,k_inv,z,tmp;
	 key_pair kp;// = genkey_pair();
	 
	 mpz_init(r);mpz_init(s);mpz_init(k);mpz_init(k_inv);mpz_init(tmp);mpz_init(z);
	 mpz_set(k,kp.y);
	 mpz_set_ui(k,3);
	 gmp_printf("k%Zd\n", k);
	 string message_  = " \n";//((*m).M);
	mpz_set(k_inv,inverse_value(&k,&(*pqg).q).p);
	gmp_printf("kinv=%Zd\n", k_inv);
	mpz_powm(r,(*pqg).g,k,(*pqg).p);
	mpz_mod(r,r,(*pqg).q);

	//z = the leftmost min(N,outlen) bits of hash(M) 
	mpz_set_str(z,message_.c_str(),16);
	//s = (k^-1)(z+xr) mod q
	mpz_mul(tmp,(*a).x,r);
	gmp_printf("tmp=%Zd\n", tmp);
	//gmp_printf("z=%Zd\n", (*m).Mi);
	mpz_add(tmp,tmp,z);
	//gmp_printf("tmp=%Zd\n", tmp);

	mpz_mul(s,k_inv,tmp);
	mpz_mod(s,s,(*pqg).q);

	// 
	gmp_printf("r=%Zd\n", r);
	gmp_printf("s=%Zd\n", s);

	mpz_clear(r);mpz_clear(s);mpz_clear(k);mpz_clear(k_inv);mpz_clear(tmp);mpz_clear(z);
	return 0;
 }

bool verification_algorithm(tuple* pqg, mpz_t* y, message_digest* m,sign_pair* rs){
	 mpz_t w,u1,u2,v,M,tmp2,tmp1,r,a1,a2,z;
	  
	  mpz_init(w);mpz_init(u1);mpz_init(u2);mpz_init(v);mpz_init(M);mpz_init(tmp1);mpz_init(tmp2);
	  mpz_init(z);
	  string message_  = ((*m).M);
	  
	//1;
	//check 0 < r' < q and 0 < s' < q; if either condition is violated,
	if(!((mpz_cmp_ui((*rs).r,0)> 0) && 
		(mpz_cmp((*pqg).q,(*rs).r)> 0) && (mpz_cmp_ui((*rs).s,0) > 0) && (mpz_cmp((*pqg).q,(*rs).s)> 0)) ){
		cout << "signature_invalid" << 1 << endl;
		return 0;	
	} 
	//Following code tests if the inverse is computed accuartly
	//mpz_init(a1);
	//mpz_init(a2);
	//mpz_mul(a1,(inverse_value(&(*rs).s,&(*pqg).q).p),(*rs).s);
	//mpz_mod(a1,a1,(*pqg).q);
	//gmp_printf("e %Zd\n", a1);
	
	//2;
	// w = s'^-1 mod q
	// z = the leftmost min(N,outlen) bits of Hash(M')(should bee converted to integer)
	// u1 = (zw) mod q
	// u2 = ((r')w) mod q.
	// v  = (g^u1 y^u2 mod p)mod q

	mpz_mod(w,inverse_value(&(*rs).s,&(*pqg).q).p,(*pqg).q);
	//gmp_printf("w %Zd\n", w);
	mpz_set_str(z,message_.c_str(),16);

	//cout << "zp=" << "280816750736115958639389702959908921601077495092" << endl;
	mpz_mul(u1,w,z);
	mpz_mod(u1,u1,(*pqg).q);
	//gmp_printf("u1 %Zd\n", u1);
	mpz_mul(u2,(*rs).r,w);
	mpz_mod(u2,u2,(*pqg).q);
	//gmp_printf("u2 %Zd\n", u2);
	
	//v  = (((pqg.g^(u1) * y^(u2)) % pqg.p) % pqg.q);
	mpz_powm(tmp1,(*pqg).g,u1,(*pqg).p);
	mpz_powm(tmp2,(*y),u2,(*pqg).p);
	mpz_mul(v,tmp1,tmp2);
	mpz_mod(v,v,(*pqg).p);
	mpz_mod(v,v,(*pqg).q);

	//3;
	//if v = r', then signarture is verified else return invalid 
	if (mpz_cmp(v,(*rs).r) != 0){
		//gmp_printf("v=%Zd\n", v);
		 //gmp_printf("r=%Zd\n", (*rs).r);
		cout << "signature_invalid" <<  2 << endl;
		return 0;
	}
	cout << "signature_valid" << endl;
return 1;
 }

 int isvalid(tuple* pqg){
 	mpz_t t,tmp1,tmp2;
 	mpz_init(tmp1);
 	mpz_init(tmp2);
 	mpz_init(t);
 	mpz_sub_ui(t,(*pqg).p,1);
 	mpz_powm(tmp1,(*pqg).g,(*pqg).q,(*pqg).p);

 	if (mpz_probab_prime_p((*pqg).p,25) &&
 	mpz_probab_prime_p((*pqg).q,25) &&
 	mpz_divisible_p(t,(*pqg).q) &&
 	!mpz_cmp_ui(tmp1,1) &&
 	mpz_cmp_ui((*pqg).g,1)){
 	cout << "valid_group" << endl;
 		//test för längd saknas 
 	return 1;
	}
	cout << "invalid_group" << endl;
	return 0;
 }
  int Test(mpz_t *a){
 	mpz_t t,tmp1,tmp2;
 	mpz_init(tmp1);
 	mpz_init(tmp2);
 	mpz_init(t);
 	
	return 0;
 }

int main(int argc, char *argv[]){
 //int main(){
  tuple pqg;
   mpz_t z;
   mpz_t a;
   mpz_t y;
   //string input;
   string line;  
  mpz_init(pqg.p);
  mpz_init(pqg.q);
  mpz_init(pqg.g); 
  //ifstream myfile(line);//argv[1]);

  	getline (cin,line);
  	mpz_set_str(pqg.p,&line.c_str()[2],10);
  	//ßcout <<"p="<< (&line.c_str()[2]) << endl;

	getline (cin,line);
  	mpz_set_str(pqg.q,&line.c_str()[2],10);
  	//cout <<"q="<< &line.c_str()[2] << endl;

  	getline (cin,line);
  	mpz_set_str(pqg.g,&line.c_str()[2],10);
  	//cout <<"g="<< &line.c_str()[2] << endl;

  	 if (!isvalid(&pqg)){
  	 	return 0;
  	 }

  	getline (cin,line);
  	if(strcmp(line.c_str(),"genkey") == 0){
	  	//cout << "genkey" << endl
	  	int n;
	  	getline (cin,line);
	  	n = atoi(&line.c_str()[2]);
	  	//cout << n << endl;
	  	for(int i = 0; i < n;i++){
	  		key_pair a = genkey_pair();
	  		gmp_printf("r=%Zd\n", a.x);
	  		gmp_printf("s=%Zd\n", a.y);
	  	}
	
	}
	else if(strcmp(line.c_str(),"sign") == 0){
	   	message_digest D;
	   	key_pair xy;
	   	mpz_init(xy.y);
	   	mpz_init(xy.x);
	   	cout << "sign" << endl;
	   	cout << "next" << endl;
	   	getline (cin,line);
	   	cout << "next" << endl;
  		mpz_set_str(xy.x,&line.c_str()[2],10);
  		cout << "next" << endl;
  		//cout << (&line.c_str()[2]) << endl;
  		//free(line)
		getline (cin,line);
		cout << "next" << endl;
  		mpz_set_str(xy.y,&line.c_str()[2],10);
  		cout << "next" << endl;
  		while ( getline (cin,line) )
    	{
  			D.M = &line.c_str()[2];
  			
  			signing_operation(&pqg,&xy,&D);
  			cout << "next" << endl;	
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

  		while ( getline (cin,line) )
    	{
  			D.M = &line.c_str()[2];
    		getline (cin,line);
  			mpz_set_str(rs.r,&line.c_str()[2],10);
  			getline (cin,line);
  			mpz_set_str(rs.s,&line.c_str()[2],10);
      		verification_algorithm(&pqg, &xy.y, &D,&rs);
    	}

	};
    mpz_clear(pqg.p);
  	mpz_clear(pqg.q);
  	mpz_clear(pqg.g);

return 0;
 }
 
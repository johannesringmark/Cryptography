#include <iostream>
#include <fstream>
#include <gmp.h>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <cstring> 
using namespace std;
const int L=1024;
const int N=160;

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
	mpz_t   Mi;
}message_digest;


key_pair genkey_pair(){
	mpz_t rand_Num;
    unsigned long int i, seed;
    gmp_randstate_t r_state;

    seed = 123456;

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init2(rand_Num,160);
    for (int i = 0; i < 1 ; i++){
    	// fix size error
       mpz_urandomb(rand_Num,r_state,(N+1));
       gmp_printf("x=%Zd\n", rand_Num);
       mpz_urandomb(rand_Num,r_state,(N+1));
   	   gmp_printf("y=%Zd\n", rand_Num);
    }

    gmp_randclear(r_state);
    mpz_clear(rand_Num);
	key_pair pair;
	//nes = 

return	pair;
}

//C.1 Computation of the Inverse Value
m_inverse inverse_value(mpz_t* z,mpz_t* a){ //seems ok tested with the values from assignment 2
	mpz_t i,j,y,y1,y2,rem,quotient,tmp;
	m_inverse zinv;
	mpz_init(zinv.p);
	
	if ( !(mpz_cmp(*a,*z) && mpz_cmp_si(*z,0))){
		cout << "invalid arguments" << endl;
		 //printf("a < r' %i\n", mpz_cmp(*a,*z));
		// printf("0 < r' %i\n", mpz_cmp_si(*z,0));
		zinv.valid = 0;
		return zinv;
	}
	 //cout << "not here f1" << endl;
	 mpz_init(i);mpz_init(j);mpz_init(y);mpz_init(y1);
	 mpz_init(y2);mpz_init(rem); mpz_init(quotient);mpz_init(tmp);
	 //cout << "not here f2" << endl;
	mpz_set(i,*a);
	mpz_set(j,*z);
	mpz_set_ui(y2,0);
	mpz_set_ui(y1,1);
	 //cout << "not here f3" << endl;
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
	//cout << "not here f4" << endl; 
		if (mpz_cmp_si(i,1) != 0){
			cout << "Error2" << endl;
			zinv.valid = 0;
			return zinv;
		};
	zinv.valid = 1;
	//zinv.p = (y2 % a);
	//cout << "not here f5" << endl;
	mpz_mod (zinv.p, y2, *a);
	//cout << "not here f6" << endl;
	mpz_clear(i);mpz_clear(j);mpz_clear(y);mpz_clear(y1);
	 mpz_clear(y2);mpz_clear(rem); mpz_clear(quotient);mpz_clear(tmp);
	 //cout << "not here f7" << endl;
	return zinv;
}
 int message_to_int (message_digest* M){ // fucked upp as fuck
	//cout << "not here 1" << endl;
	int n = ((*M).M.length() + 1);
	char* p = new char[n];
	//cout << "not here 2" << endl;
	strncpy(p,(*M).M.c_str(), (*M).M.length());
	//cout << "not here 3" << endl;
	mpz_t C;
	mpz_init(C);
	mpz_init((*M).Mi);
	//cout << "not here 4" << endl;
	int tmp,tmp2;
	
	for(int i = 1;i <= n; i++){
		for(int t = 0; t < 8;t++){
		int a = (2^(n-i)); 
		bitset<8> b(p[i]);
		tmp = tmp + (a * (b[t] + 0));
		//cout << b[t];
		}
  	}
		
	
	//free(p);
	//cout << "not here 5" << endl;
	mpz_add_ui(C,C,tmp);
	//cout << "not here 6" << endl;
	mpz_set((*M).Mi,C);
	//cout << "not here 7" << endl;
	//gmp_printf("M=%Zd\n", (*M).Mi);
	mpz_clear(C);
	//cout << "not here 6" << endl;
return 0;
}

sign_pair signing_operation(tuple pqg,key_pair a,message_digest m){
	 mpz_t r,s,k,k_inv,tmp;
	 message_to_int(&m);
	 int z;
	 int L = (m.M.size() * 8);  
	 mpz_init(r);mpz_init(s);mpz_init(k);mpz_init(k_inv);mpz_init(tmp);
	//generate k
	mpz_set(k_inv,inverse_value(&k,&pqg.q).p);

	//r = g^k mod p
	mpz_powm(r,pqg.g,k,pqg.q);
	

	//z = the leftmost min(N,outlen) bits of hash(M) 
	z = mpz_get_ui(m.Mi) >> min(N,L);
	//s = (k^-1)(z+xr) mod q
//mpz_mul(tmp,a.x,r);
	mpz_add_ui(tmp,tmp,z);
	//mpz_mul(s,kinv,tmp);

	// 
	gmp_printf("M=%Zd\n", r);
	gmp_printf("M=%Zd\n", s);
	 sign_pair hej;
	 //set(hej.x)
	return hej;
 }
bool verification_algorithm(tuple* pqg, mpz_t* y, message_digest* m,sign_pair* rs){
	 //cout << "not here 8" << endl;
	 mpz_t w,z,u1,u2,v,M,tmp2,tmp1,r;
	  //cout << "not here 8" << endl;
	  mpz_init(w);mpz_init(z);mpz_init(u1);mpz_init(u2);mpz_init(v);mpz_init(M);mpz_init(tmp1);mpz_init(tmp2);
	  mpz_init((*m).Mi);
	  message_to_int(&(*m));
	//1;

	//check 0 < r' < q and 0 < s' < q; if either condition is violated,
	if(!(mpz_cmp_ui((*rs).r,0) && mpz_cmp((*pqg).q,(*rs).r) && mpz_cmp_ui((*rs).s,0) && mpz_cmp((*pqg).q,(*rs).s)) ){
		cout << "signature_invalid" << endl;
		// printf("0 < r' %i\n", mpz_cmp_ui(rs.r,0));
		// printf("0 < s' %i\n", mpz_cmp(pqg.q,rs.r));
		// printf("r' < q %i\n", mpz_cmp_ui(rs.s,0));
		 //printf("s' < q %i\n", mpz_cmp((*pqg).q,(*rs).s));
		
		return 0;
		
	} 
	
	//2;
	// w = s'^-1 mod q
	// z = the leftmost min(N,outlen) bits of Hash(M')(should bee converted to integer)
	// u1 = (zw) mod q
	// u2 = ((r')w) mod q.
	// v  = (g^u1 y^u2 mod p)mod q
	//cout << "not here 8" << endl;
	mpz_set(w,inverse_value(&(*rs).s,&(*pqg).q).p);// mod q;
	//cout << "not here 8" << endl;
	mpz_set(z,(*m).Mi) ;
	mpz_mul(u1, z,w);
	mpz_mod(u1,u1,(*pqg).q);
	//gmp_printf("u1 %Zd\n", u1);
	
	//cout << "not here 9" << endl;
	mpz_mul(u2,(*rs).r,w);
	mpz_mod(u2,u2,(*pqg).q);
	//gmp_printf("u2 %Zd\n", u2);
	
	//v  = (((pqg.g^(u1) * y^(u2)) % pqg.p) % pqg.q);
	mpz_powm(tmp1,(*pqg).g,u1,(*pqg).p);
	mpz_powm(tmp2,(*y),u2,(*pqg).p);
	mpz_mul(v,tmp1,tmp2);
	//gmp_printf("v %Zd\n", v);
	mpz_mod(v,v,(*pqg).p);
	mpz_mod(v,v,(*pqg).q);

	//3;
	//if v = r', then signarture is verified else return invalid 
	if (mpz_cmp(v,(*rs).r) != 0){
		//mzp_t = 
		//int 
		gmp_printf("v=%Zd\n", v);
		//gmp_printf("M=%Zd\n", s.Mi);
		 gmp_printf("r=%Zd\n", (*rs).r);
		cout << "signature_invalid" << endl;
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
 	mpz_divisible_p((*pqg).q,t) &&
 	mpz_cmp_ui((*pqg).g,1) &&
 	!mpz_cmp_ui((*pqg).g,1)

 	){
 	cout << "valid_group" << endl;
 		//test för längd 
 	return 1;
	}
	cout << "invalid_group" << endl;
	return 0;
 }

int main(int argc, char *argv[]){
 //int main(){
  tuple pqg;
   mpz_t z;
   mpz_t a;
   mpz_t y;
   string input;
   //cout <<" Enter file path "<< input;
   //cin << input;

  mpz_init(pqg.p);
  mpz_init(pqg.q);
  mpz_init(pqg.g);
    
  string line;
  ifstream myfile (argv[1]);
  if (myfile.is_open())
  {
  	getline (myfile,line);
  	mpz_set_str(pqg.p,&line.c_str()[2],10);
  	//cout << (&line.c_str()[2]) << endl;

	getline (myfile,line);
  	mpz_set_str(pqg.q,&line.c_str()[2],10);
  	//cout << &line.c_str()[2] << endl;

  	getline (myfile,line);
  	mpz_set_str(pqg.g,&line.c_str()[2],10);
  	//cout << &line.c_str()[2] << endl;

  	isvalid(&pqg);

  	getline (myfile,line);
  	if(strcmp(line.c_str(),"genkey") == 0){
	  	//cout << "genkey" << endl;
	  	int n;
	  	getline (myfile,line);
	  	n = atoi(&line.c_str()[2]);
	  	//cout << n << endl;
	  	for(int i = 0; i < n;i++){
	  		genkey_pair();
	  	}
	
	}
	else if(strcmp(line.c_str(),"sign") == 0){
	   	message_digest D;
	   	key_pair xy;
	   	cout << "sign" << endl;
	   	getline (myfile,line);
  		mpz_set_str(xy.x,&line.c_str()[2],10);
  		cout << (&line.c_str()[2]) << endl;
  		//free(line)
		getline (myfile,line);
  		mpz_set_str(xy.y,&line.c_str()[2],10);
  		cout << &line.c_str()[2] << endl;

  		while ( getline (myfile,line) )
    	{
      		getline (myfile,line);
  			//D.M = &line.c_str()[2];
  			cout << (&line.c_str()[2]) << endl;
  			//signing_operation(pqg,xy,D);
      		
    	}
    	mpz_clear(xy.y);
  		mpz_clear(xy.x);
  		//free(D);

	 }
	else if(strcmp(line.c_str(),"verify") == 0){
		key_pair xy;
		sign_pair rs;
		message_digest D;
		mpz_init(xy.y);
		mpz_init(rs.s);
		mpz_init(rs.r);
		//cout << "verify" << endl;
		getline (myfile,line);
  		mpz_set_str(xy.y,&line.c_str()[2],10);
  		//cout << (&line.c_str()[2]) << endl;

  		while ( getline (myfile,line) )
    	{
    		getline (myfile,line);
  			D.M = &line.c_str()[2];
  			//cout << (&line.c_str()[2]) << endl;

    		getline (myfile,line);
  			mpz_set_str(rs.r,&line.c_str()[2],10);
  			//cout << (&line.c_str()[2]) << endl;

  			getline (myfile,line);
  			mpz_set_str(rs.s,&line.c_str()[2],10);
  			//cout << (&line.c_str()[2]) << endl;
      		verification_algorithm(&pqg, &xy.y, &D,&rs);
    	}
  		mpz_clear(xy.y);
  		mpz_clear(rs.r);
  		mpz_clear(rs.s);
	};


    // while ( getline (myfile,line) )
    // {
    //   cout << line << endl;
    // }
    mpz_clear(pqg.p);
  	mpz_clear(pqg.q);
  	mpz_clear(pqg.g);
    myfile.close();

  }
   else cout << "Unable to open file"<< endl; 

return 0;
 }
 
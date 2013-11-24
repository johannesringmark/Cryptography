#include <iostream>
#include <fstream>
#include <gmp.h>
#include <cmath>
 
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
	int key1;
	int key2;
} key_pair;

typedef struct {
	mpz_t r;
	mpz_t s;
} sign_pair;

typedef struct {
	string  M;
	mpz_t   Mi;
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
		cout << "Error1" << endl;
		 printf("a < r' %i\n", mpz_cmp(*a,*z));
		 printf("0 < r' %i\n", mpz_cmp_si(*z,0));
		zinv.valid = 0;
		return zinv;
	}
	 cout << "not here f1" << endl;
	 mpz_init(i);mpz_init(j);mpz_init(y);mpz_init(y1);
	 mpz_init(y2);mpz_init(rem); mpz_init(quotient);mpz_init(tmp);
	 cout << "not here f2" << endl;
	mpz_set(i,*a);
	mpz_set(j,*z);
	mpz_set_ui(y2,0);
	mpz_set_ui(y1,1);
	cout << "not here f3" << endl;
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
	cout << "not here f4" << endl; 
		if (mpz_cmp_si(i,1) != 0){
			cout << "Error2" << endl;
			zinv.valid = 0;
			return zinv;
		};
	zinv.valid = 1;
	//zinv.p = (y2 % a);
	cout << "not here f5" << endl;
	mpz_mod (zinv.p, y2, *a);
	cout << "not here f6" << endl;
	mpz_clear(i);mpz_clear(j);mpz_clear(y);mpz_clear(y1);
	 mpz_clear(y2);mpz_clear(rem); mpz_clear(quotient);mpz_clear(tmp);
	 cout << "not here f7" << endl;
	return zinv;
}
 int message_to_int (message_digest* M){ // fucked upp as fuck
	cout << "not here 1" << endl;
	int n = ((*M).M.length() + 1);
	char* p = new char[n];
	cout << "not here 2" << endl;
	strncpy(p,(*M).M.c_str(), (*M).M.length());
	cout << "not here 3" << endl;
	mpz_t C;
	mpz_init(C);
	mpz_init((*M).Mi);
	cout << "not here 4" << endl;
	int tmp,tmp2;
	
	for(int i = 1;i <= n; i++){
		int a = (2^(n-i)); 
		tmp = tmp + (a * (p[i] + 0));
		
	}
	free(p);
	cout << "not here 5" << endl;
	mpz_add_ui(C,C,tmp);
	cout << "not here 6" << endl;
	mpz_set((*M).Mi,C);
	cout << "not here 7" << endl;
	gmp_printf("M=%Zd\n", (*M).Mi);
	mpz_clear(C);
	cout << "not here 6" << endl;
return 0;
}

sign_pair signing_operation(tuple pqg,key_pair a,message_digest M){
	 
	//r = g^k mod p
	//z = the leftmost min(N,outlen) bits of hash(M) 
	 sign_pair hej;
	return hej;
 }
bool verification_algorithm(tuple pqg, mpz_t y, message_digest m,sign_pair rs){
	 mpz_t w,z,u1,u2,v,M,tmp2,tmp1,r;
	  mpz_init(w);mpz_init(z);mpz_init(u1);mpz_init(u2);mpz_init(v);mpz_init(M);mpz_init(tmp1);mpz_init(tmp2);
	  mpz_init(m.Mi);
	  message_to_int(&m);
	//1;

	//check 0 < r' < q and 0 < s' < q; if either condition is violated,
	if(!(mpz_cmp_ui(rs.r,0) && mpz_cmp(pqg.q,rs.r) && mpz_cmp_ui(rs.s,0) && mpz_cmp(pqg.q,rs.s)) ){
		cout << "signature_invalid 1" << endl;
		// printf("0 < r' %i\n", mpz_cmp_ui(rs.r,0));
		// printf("0 < s' %i\n", mpz_cmp(pqg.q,rs.r));
		// printf("r' < q %i\n", mpz_cmp_ui(rs.s,0));
		// printf("s' < q %i\n", mpz_cmp(pqg.q,rs.s));
		
		return 0;
		
	} 
	
	//2;
	// w = s'^-1 mod q
	// z = the leftmost min(N,outlen) bits of Hash(M')(should bee converted to integer)
	// u1 = (zw) mod q
	// u2 = ((r')w) mod q.
	// v  = (g^u1 y^u2 mod p)mod q
	cout << "not here 8" << endl;
	mpz_set(w,inverse_value(&rs.s,&pqg.q).p);// mod q;
	cout << "not here 8" << endl;
	mpz_set(z,m.Mi) ;
	mpz_mul(u1, z,w);
	mpz_mod(u1,u1,pqg.q);
	gmp_printf("u1 %Zd\n", u1);
	
	cout << "not here 9" << endl;
	mpz_mul(u2, r,w);
	mpz_mod(u2,u2,pqg.q);
	gmp_printf("u2 %Zd\n", u2);
	
	//v  = (((pqg.g^(u1) * y^(u2)) % pqg.p) % pqg.q);
	mpz_powm(tmp1,pqg.g,u1,pqg.p);
	mpz_powm(tmp2,y,u2,pqg.p);
	mpz_mul(v,tmp1,tmp2);
	gmp_printf("v %Zd\n", v);
	mpz_mod(v,v,pqg.p);
	mpz_mod(v,v,pqg.q);

	//3;
	//if v = r', then signarture is verified else return invalid 
	if (mpz_cmp(v,rs.r) != 0){
		gmp_printf("v %Zd\n", v);
		//gmp_printf("M=%Zd\n", s.Mi);
		 gmp_printf("r' %Zd\n", rs.r);
		cout << "signature_invalid 2" << endl;
		return 0;
	}
	cout << "signature_valid" << endl;
return 1;
 }

 int invalid(string p,string q, string g){
 	return 0;
 }

int main(){
	// string p,q,g,n; 
	// cout << "Input p" << endl;	
	// 	cin >> p;
	// cout << "Input q" << endl;
	// 	cin >> q;
	// cout << "Input g" << endl;
	// 	cin >> g;

	// 	if (invalid(p,q,g)){
	// 		cout << "invalid_group" << endl;
	// 		return 0;
	// 	}else{
	// 		cout << "valid_group" << endl;
	// 	};

	// cout << "Input n" << endl;
	// 	cin >> n;

	// int a = 10;
	// int b = 10;
	// int c = 20;
	//genkey_pair(5);

	
	// if(strcmp(n.c_str(),"genkey") == 0){
	//   	cout << "genkey" << endl;
	  	
	
	// }
	// else if(strcmp(n.c_str(),"sign") == 0){
	//    	string x,y,d1,d2,d3; 
	//    	cout << "sign" << endl;
	//    cout << "Input x" << endl;	
	// 	cin >> x;
	// 	cout << "Input y" << endl;
	// 	cin >> y;
	// 	cout << "Input D" << endl;
	// 	cin >> d1;
	// 	cout << "Input D" << endl;
	// 	cin >> d2;
	// 	cout << "Input D" << endl;
	// 	cin >> d3;
	//  }
	// else if(strcmp(n.c_str(),"verify")== 0){
	// 	string p,q,g;
	// 	cout << "verify" << endl;
	// 	cout << "Input y" << endl;	
	// 	cin >> p;
	// 	cout << "Input q" << endl;
	// 	cin >> q;
	// 	cout << "Input g" << endl;
	// 	cin >> g;
	// };

						//m_inverse i = inverse_value(12,23);//
						//	cout << i.p << i.valid << endl;
	 tuple pqg;
	// mpz_init (pqg.p);
	// // Convert the 1024-bit number 'input' into an mpz_t, with the most significant byte
	// // first and using native endianness within each byte.
	// char input[]= "102865584259843077175583195011997798900482038016705824136288380475734860009055428071534495956844807748416572686838253895244634687898659646424515259679129905513743899853971066468883670407530107234961085482225328667572772611162756643027105617873895021996158552984843708233824989792811721408577351617080369547993";
	// mpz_import(pqg.p, sizeof(input), 1, sizeof(input[0]), 0, 0, input);;
 mpz_t z;
 mpz_t a;
 // mpz_t x;
  mpz_t y;
 // mpz_t result;
 
 //mpz_init(z);
 //mpz_init(a);
  mpz_init(pqg.p);
  mpz_init(pqg.q);
  mpz_init(pqg.g);
  mpz_init(y);

 //mpz_set_str(a, "23", 10);
 //mpz_set_str(z, "12", 10);

 
//  mpz_set_str(pqg.p, "7612058254738945", 10);
//  mpz_set_str(pqg.q, "9263591128439081", 10);
 
//  mpz_mul(result, pqg.p, pqg.q);

	
mpz_set_str(pqg.p,"102865584259843077175583195011997798900482038016705824136288380475734860009055428071534495956844807748416572686838253895244634687898659646424515259679129905513743899853971066468883670407530107234961085482225328667572772611162756643027105617873895021996158552984843708233824989792811721408577351617080369547993", 10);
mpz_set_str(pqg.q,"734415599462729831694143846331445277609193755927", 10);
mpz_set_str(pqg.g,"63615006880335642768473038477258757436464860136916565207798584167060621564899979263408565137993978149206751054438974059615983337126379668370747907507911540381031959187353048278562320341063050939775344313271013777131358834376209974551749493023310606751625276738876397935042130121966817767949476523717161640453", 10);
mpz_set_str(y,"1099906791313925528746008054081768734007884349815325963667520491768596235922636596649198172987598573083011790017146356061273962023338014420645127092468263770753970716461208880423045761205934804880887634821616587683235765408867072852094816664326084550730344050243082288308837441908172297994552279650972016922", 10);
 message_digest s;
 s.M = "10B4D55F2376DBA00CE4A6AE2B122E9554035EF2"; 
 //mpz_init(s.Mi);
 //mpz_set_str(s.Mi, "23", 10);
 sign_pair rs;
 mpz_init(rs.r);
 mpz_init(rs.s);
 mpz_set_str(rs.r,"497727687827108870230917469165124644171957997527", 10);
 mpz_set_str(rs.s,"69924200561536940344114164706214298822631922629", 10);
	//m_inverse i = inverse_value(z,a);
	//gmp_printf("x=%Zd\n", i.p);
	//cout << "not here 1" << endl;
	//gmp_printf("M=%Zd\n", s.Mi);
	verification_algorithm(pqg,y,s,rs);
	cout << "Error while opening the file" << endl;
return 0;
 }
 
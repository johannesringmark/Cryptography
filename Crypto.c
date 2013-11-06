#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main() {
    vector<int> vektor;
    int tal;
 
    while(cin >> tal) {
       vektor.push_back(tal);
    }
 
    sort(vektor.begin(), vektor.end());
 
    for (vector<int>::const_iterator i = vektor.begin(); i != vektor.end(); ++i) {
        cout << *i << endl;
    }
 
    return 0;
}
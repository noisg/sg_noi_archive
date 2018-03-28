#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <numeric>
#define MAX_LINES 1000000
#define MAX_VALUE 1000000000000000000
#define NUM_MODS 10
using namespace std;
struct quit_exception{};
inline pair<unsigned long long, unsigned long long>* read_file(const char* filename, pair<unsigned long long, unsigned long long>* out){ // expects out to be zeroed
    const pair<unsigned long long, unsigned long long>* pend=out+MAX_LINES;
    {
        ifstream in(filename);
        while(true){
            unsigned long long a,b;
            in>>a;
            if(in.eof())break;
            in>>b;
            if(in.eof()||in.fail()){
                cerr << "Invalid output format!" << endl;
                cout << 0 << endl;
                throw quit_exception();
            }
            if(in.bad()){
                cerr << "Internal error (stream broken).  Please report this." << endl;
                cout << 0 << endl;
                throw quit_exception();
            }
            if(out==pend){
                cerr << "Too many numbers in output." << endl;
                cout << 0 << endl;
                throw quit_exception();
            }
            if(1>a||a>MAX_VALUE||1>b||b>MAX_VALUE){
                cerr << "A number in your output is outside the required range specified in the output format." << endl;
                cout << 0 << endl;
                throw quit_exception();
            }
            *out++=make_pair(a,b);
        }
    }
    return out;
}
inline unsigned mulmod(unsigned a, unsigned b, unsigned mod){
    return static_cast<unsigned>(static_cast<unsigned long long>(a)*b%mod);
}
inline unsigned powmod(unsigned b, unsigned long long e, unsigned mod){
    unsigned res=1;
    while(e>0){
        if(e&1){
            res=mulmod(res,b,mod);
        }
        e>>=1;
        b=mulmod(b,b,mod);
    }
    return res;
}
inline unsigned prod_mod(const pair<unsigned long long, unsigned long long>* begin1, const pair<unsigned long long, unsigned long long>* end1, unsigned mod){
    return accumulate(begin1, end1, 1u, [mod](unsigned prev, const pair<unsigned long long, unsigned long long>& curr){
        return mulmod(prev, powmod(static_cast<unsigned>(curr.first%mod), curr.second, mod), mod);
    });
}
inline bool equal_product(const pair<unsigned long long, unsigned long long>* begin1, const pair<unsigned long long, unsigned long long>* end1, const pair<unsigned long long, unsigned long long>* begin2, const pair<unsigned long long, unsigned long long>* end2, unsigned mod){
    return prod_mod(begin1, end1, mod) == prod_mod(begin2, end2, mod);
}
pair<unsigned long long, unsigned long long> contestant_arr[MAX_LINES], correct_arr[MAX_LINES];
pair<unsigned long long, unsigned long long> *contestant_arr_end, *correct_arr_end;
const unsigned mods[NUM_MODS] = {1000000007, 982451653, 1008431029, 1037499119, 1204207141, 1412205281, 1613477381, 1613477647, 1854892421, 1854896497};
int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(argc!=4){
        cerr << "Expected exactly 3 arguments to checker!" << endl;
        cout << 0 << endl;
        return 0;
    }
    const char* correct_output = argv[2];
    const char* contestant_output = argv[3];
    try{
        correct_arr_end=read_file(correct_output, correct_arr);
        contestant_arr_end=read_file(contestant_output, contestant_arr);
    }
    catch(quit_exception&){
        return 0;
    }
    if(all_of(mods,mods+NUM_MODS,[](const unsigned& mod){
        return equal_product(correct_arr,correct_arr_end,contestant_arr,contestant_arr_end,mod);
    })){
        cerr << "Correct :)" << endl;
        cout << 1 << endl;
        return 0;
    }
    else{
        cerr << "Incorrect :(" << endl;
        cout << 0 << endl;
        return 0;
    }
}

//#pragma GCC optimize(3)
#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
struct item{
	long long value;
	int weight;
	long long copies;
};
pair<long long,int> pseudoitems[3000000];
pair<long long,int> *pi_end; // value, weight
item items[100000];
item *items_end;
long long gcd(long long a, long long b){
    if(a==0)return b;
    if(b==0)return a;
    return gcd(b,a%b);
}
int main(){
	ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);
	int s,n;
	while(cin>>s>>n&&s){
		assert(s>=1&&s<=2000);
		assert(n>=1&&n<=100000);
		pi_end=pseudoitems;
		for(int i=0;i<n;++i){
            cin>>items[i].value>>items[i].weight>>items[i].copies;
            assert(items[i].value>=1&&items[i].value<=1000000);
            assert(items[i].weight>=1&&items[i].weight<=s);
            assert(items[i].copies>=1&&items[i].copies<=1000000000);
            /*int x=(int)gcd(items[i].value,items[i].weight);
            items[i].value/=x;
            items[i].weight/=x;
            items[i].copies*=x;*/
		}
		sort(items,items+n,[](const item& a, const item& b){
		    if(b.weight==a.weight)return a.value>b.value;
		    return a.weight<b.weight;
		});
		items_end=items+n;
		/*items_end=remove_if(items,items+n,[](const item& itm){
		    //return itm.value<30;
		    return itm.value/itm.weight<4000;
		});*/
		auto it=items+1;
		auto it_end=items_end;
		items_end=items;
		int ct=0;
		//cout<<"test"<<endl;
		for(;it!=it_end;++it){
            item itm=*it;
            if(itm.weight==items_end->weight){
                if(ct>s/itm.weight);//items_end->copies+=itm.copies;
                else *(++items_end)=itm;
                ++ct;
                //items_end->value=max(items_end->value,it->value);
            }
            else{
                *(++items_end)=itm;
                ct=0;
            }
		}
		//cout<<"test"<<endl;
		++items_end;
		for(auto it=items;it!=items_end;++it){
			const item& itm=*it;
			int p;
			for(p=0;(1ll<<(p+1))<=itm.copies;++p){
				if((long long)itm.weight*(1ll<<p)<=s){
					*pi_end++=make_pair(itm.value*(1ll<<p),itm.weight*(1ll<<p));
				}
			}
			long long cp=itm.copies-((1ll<<p)-1);
			if((long long)itm.weight*cp<=s){
				*pi_end++=make_pair(itm.value*cp,itm.weight*cp);
			}
		}
		//cout<<"test"<<endl;
		long long* prev=new long long[s+1];
		fill_n(prev,s+1,0);
		for(auto it=pseudoitems;it!=pi_end;++it){
			long long* curr = new long long[s+1];
			for(int j=0;j<=s;++j){
				curr[j]=prev[j];
				if(j+it->second<=s){
					curr[j]=max(curr[j],prev[j+it->second]+it->first);
				}
			}
			delete[] prev;
			prev=curr;
		}
		//cout<<"test"<<endl;
		cout<<prev[0]<<'\n';
	}
}


#include<iostream>
#include<algorithm>
#include<cstdio>
#include<complex>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<string>
#include<cstdlib>
#include<memory.h>
#include<ctime>

using namespace std;


typedef long double ld;

typedef long long ll;
typedef pair<int,int>    pii;
typedef pair<ld,ld>    pdd;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef pair<ll,ll> pl;

#define FOR(i,a,b)        for(int i=(a);i<(b);i++)
#define REP(i,n)        FOR(i,0,n)
#define SORT(v)            sort((v).begin(),(v).end())
#define UN(v)            SORT(v),(v).erase(unique((v).begin(),(v).end()),(v).end())
#define CL(a,b)            memset(a,b,sizeof a)
#define pb                push_back


const int mod = 1000000007;

int cc[55][55];
bool hasc;

ll c(int n,int m){
    if(m>n || m<0 || n<0) return 0;
    if(!hasc){
        hasc=1;
        REP(i,55){
            cc[i][i]=cc[i][0]=1;
            FOR(j,1,i)
                cc[i][j]=(cc[i-1][j-1]+cc[i-1][j])%mod;
        }
    }
    return cc[n][m];
}

ll tr[33][33][33];

ll tree(int n,int d,int m){
    if(d==1){
        if(n==1 && m==1) return 1;
        return 0;
    }
    if(tr[n][d][m]!=-1)
        return tr[n][d][m];
    ll val = 0;
    FOR(pr,1,n-m+1){
        ll t = tree(n-m,d-1,pr);
        REP(i,m) t*=pr,t%=mod;
        t *= c(n,m);t%=mod;
        val += t;val%=mod;
    }
    return tr[n][d][m] = val;
}
ll qp(ll d,ll st){
    ll r =1;
    while(st){
        if(st&1)r*=d,r%=mod;
        d*=d,d%=mod;
        st>>=1;
    }
    return r;
}
ll nt[33];
bool hasnt;
ll numt(int d){
    if(!hasnt){
        hasnt=true;
        CL(nt,-1);
    }
    if(nt[d]!=-1)return nt[d];
    ll res = 0;
    FOR(l,1,d+1)FOR(nl,1,d+1)
        res+=tree(d,l,nl),res%=mod;
    res*=qp(d,mod-2);res%=mod;
    return nt[d]=res;
}

ll w[333][1<<9];
vi v;
int n;    

ll go(int numv,int mmask){
    if(mmask==0) return 1;
    else{
        if(w[numv][mmask]!=-1) return w[numv][mmask];

        ll res = 0;
        for(int mask=mmask;mask;mask=(mask-1)&mmask){
            int nnv = 0;
            vi nt;
            ll ncc = 1;
            REP(j,n-1) if(mask&(1<<j)){
                nnv += v[j];
                ncc*=numv;ncc%=mod;
                ncc*=v[j];ncc%=mod;
                ncc*=numt(v[j]);ncc%=mod;
            }else nt.pb(v[j]);

            res += ncc * go(nnv,mmask^mask);
            res %= mod;
        }
        return w[numv][mmask]=res;
    }
}

int main(){
#ifdef LocalHost
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
#endif
    CL(tr,-1);
    int tc;
    cin>>tc;
    REP(TC,tc){
        cin>>n;
        v.resize(n);
        REP(i,n)cin>>v[i];
        vi t = v;
        t.erase(t.begin());
        CL(w,-1);
        ll res=numt(v[n-1])*go(v[n-1],(1<<(n-1))-1)%mod;
        cout<<res<<endl;
    }

#ifdef LocalHost
    printf("TIME: %.3lf\n",ld(clock())/CLOCKS_PER_SEC);
#endif
    return 0;
}

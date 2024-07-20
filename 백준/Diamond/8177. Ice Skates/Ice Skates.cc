#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pi;
 
ll n,m,k,d;
ll lf[800006],rg[800006],ar[200005],tree[800006],sum[800006];
 
ll getupd(ll l,ll r,ll nd,ll c)
{
    if(r<c||c<l) return tree[nd];
    if(l==r&&l==c)
    {
        lf[nd]=ar[l],rg[nd]=ar[l],sum[nd]=ar[l];
        return tree[nd]=ar[l];
    }
    ll md=(l+r)>>1,ret=-1e17;
    ll candl=getupd(l,md,nd*2,c),candr=getupd(md+1,r,nd*2+1,c);
    sum[nd]=sum[nd*2]+sum[nd*2+1]; 
    lf[nd]=max(sum[nd*2]+lf[nd*2+1],lf[nd*2]);
    rg[nd]=max(sum[nd*2+1]+rg[nd*2],rg[nd*2+1]);
    ret=max(ret,candl),ret=max(ret,candr);
    ret=max(ret,rg[nd*2]+lf[nd*2+1]);
    return tree[nd]=ret;
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m>>k>>d;
    for(int i=1;i<=n;i++)
        ar[i]=-k,getupd(1,n,1,i);
    for(int i=1;i<=m;i++)
    {
        ll a,b;cin>>a>>b;
        ar[a]+=b;
        ll c=getupd(1,n,1,a);
        if(c>k*d) cout<<"NIE"<<"\n";
        else cout<<"TAK"<<"\n";
    }
    return 0;
}
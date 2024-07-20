#include<cstdio>
#include<algorithm>
using namespace std;

int n, m, r;
int robot[1000005];
int rdif[2000005];

int sum, mxsum;

int main()
{
    scanf("%d",&n);
    scanf("%d %d",&r,&m);
    for(int i=0 ; i<n ; i++) {
        scanf("%d",&robot[i]);
    }
    sort(robot,robot+n);
    robot[n] = robot[0] + m;
    for(int i=0 ; i<n ; i++) {
        rdif[i] = rdif[i+n] = robot[i+1] - robot[i] - r * 2;
    }
    for(int i=0 ; i<2*n-1 ; i++) {
        sum += rdif[i];
        if(sum < 0) sum = 0;
        mxsum = mxsum>sum?mxsum:sum;
    }
    printf("%d",(mxsum+1)/2);
}
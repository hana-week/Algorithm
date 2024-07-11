cost=int(input())
cnt=int(input())
sum=0

for i in range(cnt):
    a,b=map(int,input().split())
    sum+=a*b
    
if cost==sum:
    print('Yes')
else:
    print('No')
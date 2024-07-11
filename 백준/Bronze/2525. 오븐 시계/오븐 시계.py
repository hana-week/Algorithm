a,b=map(int,input().split())
c=int(input())

print((a+((b+c)//60))%24,(b+c)%60)
a,b=map(int,input().split())
x=list(map(int,input().split()))
li=[]
for i in range(len(x)):
    if x[i]<b:
        li.append(x[i])
for j in range(len(li)):
    print(li[j],end=' ')
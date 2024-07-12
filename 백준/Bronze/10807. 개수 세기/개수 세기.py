n=int(input())
num=list(map(int,input().split()))
selnum=int(input())
count=0

for i in range(len(num)):
    if num[i]==selnum:
        count+=1
print(count)
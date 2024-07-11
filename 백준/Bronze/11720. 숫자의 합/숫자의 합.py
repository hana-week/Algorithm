n=int(input())
list_=[]
x=input()
sum=0
for i in range(n):
    list_.append(x[i])
    temp=int(list_[i])
    sum+=temp
print(sum)


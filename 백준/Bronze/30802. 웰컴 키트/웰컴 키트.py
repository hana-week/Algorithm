n=int(input())
shirt=list(map(int,input().split()))
T,P=map(int,input().split())
T_sum=0
for i in range(6):
    if shirt[i]==0:
        pass
    else:
        if shirt[i]>T:
            if shirt[i]%T!=0:
                T_sum+=shirt[i]//T + 1
            else:
                T_sum+=shirt[i]//T
        else:
            T_sum+=1
        
print(T_sum)
print(n//P,n%P,sep=' ')
import math
n=int(input())
ans=(-3+math.sqrt(12*n-3))/6+1
if n==1 :
    print(1)
elif ans==int(ans):
    print(int(ans))
else : 
    print(int(ans+1))
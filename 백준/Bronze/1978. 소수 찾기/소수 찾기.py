#num=int(input())
#li=list(map(int,input().split()))
#prime=0

N = int(input())
nums = list(map(int,input().split()))
cnt = 0
flag = False

for i in range(N):
    if nums[i] == 2:
        cnt = cnt + 1
    elif nums[i] != 1:
        for j in range(nums[i]-2):
            a = nums[i]%(j+2)
            if a == 0:
                flag = True
        if flag == False:
            cnt = cnt + 1
        elif flag == True:
            flag = False

print(cnt)


#def is_prime_num(n):
#    if n==1:
#        return False
#    elif n==2:
#        return True
#    else:    
#        for i in range(2, n):
#            if n % i == 0:
#                return False
#        return True
#for a in range(len(li)):
#    if is_prime_num(li[a])==True:
#        prime+=1
#    else:
#        pass

#for j in range(len(li)):
#    for i in range(2,li[j]):
#        if li[j] % i ==0:
#            return False
#    prime+=1
#print(prime)
            
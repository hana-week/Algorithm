li=list(map(str,input()))
x=[-1]*26
# a:97~z:122, ord:str>int, chr:int>str
for i in range(len(li)):
    j=ord(li[i])-97
    if x[j]==-1:
        x[j]=i
print(*x)

#for i in range(len(S)):
#    index = ord(S[i]) - 97
#    if inputList[index] == -1:
#        inputList[index] = i # Update location        
#print(inputList)
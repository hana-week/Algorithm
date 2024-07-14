li=[]
ans=[]
for i in range(1,31):
    li.append(i)
for j in range(28):
    x=int(input())
    ans.append(x)
ans.sort()
for k in range(28):
    if ans[k] in li:
        li.remove(ans[k])
print(li[0])
print(li[1])
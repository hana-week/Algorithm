li=[]
for _ in range(5):
    x=int(input())
    if x<=40:
        li.append(40)
    else:
        li.append(x)
print(sum(li)//5)
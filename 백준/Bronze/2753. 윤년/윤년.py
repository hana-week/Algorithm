x=int(input())
if (x%4==0) and ((x%400==0) or (x%100!=0)):
    print(1)
else:
    print(0)
#A+: 4.3, A0: 4.0, A-: 3.7
#B+: 3.3, B0: 3.0, B-: 2.7
#C+: 2.3, C0: 2.0, C-: 1.7
#D+: 1.3, D0: 1.0, D-: 0.7
#F: 0.0

a=['A','B','C','D','F']
a.sort(reverse=True)
t=list(input())
for i in a:
    if t[0]=='F':
        print(float(0))
        break
    elif t[0]==i:
        if t[1]=='+':
            print(float(a.index(i)+0.3))
        elif t[1]=='-':
            print(float(a.index(i)-0.3))
        else:
            print(float(a.index(i)))
        break

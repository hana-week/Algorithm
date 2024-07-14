while True:
    tri=list(map(int,input().split()))
    if tri[0]==0 and tri[1]==0 and tri[2]==0:
        break
    tri.sort()
    if tri[0]**2+tri[1]**2==tri[2]**2:
        print('right')
    else:
        print('wrong')
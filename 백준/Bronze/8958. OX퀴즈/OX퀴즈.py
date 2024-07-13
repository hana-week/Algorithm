CASE = int(input())

score_l = []
                       
for i in range(CASE):           
    A = list(str(input()))      #OX입력
    x = 0                       #가산 점수, 각 케이스 점수초기화
    score = 0           
    
    for i in range(len(A)):     #각 케이스 점수 계산
        if A[i] == 'O':         
            x += 1
            score += x
        elif A[i] == 'X':       
            x = 0
        
    score_l.append(score)       #점수리스트에 점수 추가
    
for i in range(CASE):           #점수 출력
    print(score_l[i])
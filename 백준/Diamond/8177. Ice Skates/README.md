# [Diamond III] Ice Skates - 8177 

[문제 링크](https://www.acmicpc.net/problem/8177) 

### 성능 요약

메모리: 28584 KB, 시간: 468 ms

### 분류

자료 구조, 홀의 결혼 정리, 세그먼트 트리

### 제출 일자

2024년 7월 20일 22:55:54

### 문제 설명

<p>Byteasar runs a skate club. Its members meet on a regular basis and train together, and they always use the club's ice-skates. The skate sizes are (by convention) numbered from 1 to n. Naturally, each club member has some foot size, but that is not all to it! Skaters have skate size tolerance factor d: a skater with foot size r can wear skates with sizes from r up to r+d. It should be noted, though, that no skater ever wears two skates of different size simultaneously.</p>

<p>To supply the club, Byteasar bought k pairs of ice-skates of each size, i.e. from 1 to n. As time passes, some people join the club, just as some established members leave it. Byteasar worries if he will have enough skates of appropriate size for every member at each training.</p>

<p>We assume that initially the club has no members at all. Byteasar will give you a sequence of m events of the following form: x (new) members with foot size r have joined/left the club. Right after each such event Byteasar wants to know whether he has enough skates of appropriate size for every club member. He asks you to write a programme that will check it for him.</p>

### 입력 

 <p>The first line of the standard input contains four integers n, m, k  and d (1 ≤ n ≤ 200,000, 1 ≤ m ≤ 500,000, 1 ≤ k ≤ 10<sup>9</sup>, 0 ≤ d < n), separated by single spaces, that denote, respectively: maximum skate size, number of events, number of skate pairs of each size Byteasar initially bought, and the skate size tolerance factor. The following m lines contain the sequence of m events, one per line. The (i+1)-th line (for 1 ≤ i ≤ m) holds two integers: r<sub>i</sub> and x<sub>i</sub> (1 ≤ r<sub>i</sub> ≤ n-d, -10<sup>9</sup> ≤ x<sub>i</sub> ≤ 10<sup>9</sup>), separated by a single space. If x<sub>i</sub> ≥ 0, it means that x<sub>i</sub> new members with foot size r<sub>i</sub> each have just joined the club. And if x<sub>i</sub> < 0, it means that x<sub>i</sub> members with foot size r<sub>i</sub> each have just left the club. You may assume the sequence is sensible, i.e. someone who never joined the club cannot leave it.</p>

### 출력 

 <p>Your programme should print out  lines to the standard output. The i-th line (for 1 ≤ i ≤ m) should either contain the word TAK (Polish for yes), or the word NIE (Polish for no), depending on whether Byteasar has the skates of appropriate size for every club member right after the i-th event.</p>

<p> </p>


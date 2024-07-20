# [Diamond III] BOJ 수열 1 - 13323 

[문제 링크](https://www.acmicpc.net/problem/13323) 

### 성능 요약

메모리: 8176 KB, 시간: 720 ms

### 분류

자료 구조, 다이나믹 프로그래밍, 우선순위 큐, 함수 개형을 이용한 최적화

### 제출 일자

2024년 7월 20일 22:34:53

### 문제 설명

<p>수열 A<sub>1</sub>, A<sub>2</sub> .. A<sub>N</sub> 이 주어진다.</p>

<p>B<sub>1</sub> < B<sub>2</sub> < ... < B<sub>N</sub> 을 만족하면서, |B<sub>1</sub> - A<sub>1</sub>| + |B<sub>2</sub> - A<sub>2</sub>| ... |B<sub>N</sub> - A<sub>N</sub>| 을 최소화하는 수열 B가 존재할 때, 당신은 그러한 값의 가능한 최솟값을 출력해야 한다.</p>

<p>수열 A와 B는 정수로만 이루어진 수열이고, 수열 B의 원소는 32비트 정수형 범위 안에 들어있어야 한다.</p>

### 입력 

 <p>첫 번째 줄에 N이 주어진다. (N ≤ 1,000,000) 두 번째 줄에 수열 A의 원소가 순서대로 주어진다. (0 ≤ A<sub>i</sub> ≤ 2 × 10<sup>9</sup>) </p>

### 출력 

 <p>가능한 |B<sub>1</sub> - A<sub>1</sub>| + |B<sub>2</sub> - A<sub>2</sub>| ... |B<sub>N</sub> - A<sub>N</sub>| 값의 최소를 출력한다.</p>


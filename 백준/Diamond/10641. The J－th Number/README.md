# [Diamond III] The J-th Number - 10641 

[문제 링크](https://www.acmicpc.net/problem/10641) 

### 성능 요약

메모리: 487988 KB, 시간: 940 ms

### 분류

이분 탐색, 값 / 좌표 압축, 자료 구조, 느리게 갱신되는 세그먼트 트리, 병렬 이분 탐색, 세그먼트 트리

### 제출 일자

2024년 7월 20일 22:53:25

### 문제 설명

<p>You are given N empty arrays, t<sub>1</sub>,…,t<sub>n</sub>. At first, you execute M queries as follows.</p>

<ul>
	<li>add a value v to array t<sub>i</sub> (a ≤ i ≤ b)</li>
</ul>

<p>Next, you process Q following output queries.</p>

<ul>
	<li>output the j-th number of the sequence sorted all values in t<sub>i</sub> (x ≤ i ≤ y)</li>
</ul>

### 입력 

 <p>The dataset is formatted as follows.</p>

<pre>N M Q
a<sub>1</sub> b<sub>1</sub> v<sub>1</sub>
...
a<sub>M</sub> b<sub>M</sub> v<sub>M</sub>
x<sub>1</sub> y<sub>1</sub> j<sub>1</sub>
...
x<sub>Q</sub> y<sub>Q</sub> j<sub>Q</sub>
</pre>

<p>The first line contains three integers N (1 ≤ N ≤ 10<sup>9</sup>), M (1 ≤ M ≤ 10<sup>5</sup>) and Q (1 ≤ Q ≤ 10<sup>5</sup>). Each of the following M lines consists of three integers a<sub>i</sub>, b<sub>i</sub> and v<sub>i</sub> (1 ≤ a<sub>i</sub> ≤ b<sub>i</sub> ≤ N, 1 ≤ v<sub>i</sub> ≤ 10<sup>9</sup>). Finally the following Q lines give the list of output queries, each of these lines consists of three integers x<sub>i</sub>, y<sub>i</sub> and j<sub>i</sub> (1 ≤ x<sub>i</sub> ≤ y<sub>i</sub> ≤ N,1≤ j<sub>i</sub> ≤ Σ<sub>xi≤k≤yi</sub>|tk|).</p>

### 출력 

 <p>For each output query, print in a line the j-th number.</p>

<p> </p>


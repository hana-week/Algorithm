# [Platinum I] 발리의 조각상 - 10846 

[문제 링크](https://www.acmicpc.net/problem/10846) 

### 성능 요약

메모리: 2056 KB, 시간: 224 ms

### 분류

다이나믹 프로그래밍, 그리디 알고리즘

### 제출 일자

2024년 7월 20일 22:48:41

### 문제 설명

<p>발리의 길에는 많은 조각상들이 있다. 큰길 하나에 있는 조각상들을 생각해 보자.</p>

<p>그 길에는 <em>N</em>개의 조각상들이 있고 1부터 <em>N</em>까지 순서대로 번호가 붙어 있다. 조각상 <em>i</em>의 나이는 <em>Y</em><sub><em>i</em></sub>년이다, 즉, <em>Y</em><sub><em>i</em></sub>년 전에 만든 것이다. 길을 더 아름답게 만들기 위해 정부는 조각상들을 몇 개의 그룹으로 나누려고 한다. 그룹이 정해지고 나면 그룹들 사이에 아름다운 나무들을 심어서 관광객이 더 많이 오도록 만들려는 것이다.</p>

<p>조각상을 그룹으로 분할하는 규칙은 다음과 같다.</p>

<ul>
	<li>조각상들은 정확히 <em>X</em>개의 그룹으로 분할되어야 한다. 단, <em>A</em> ≤ <em>X</em> ≤ <em>B</em>이다. 각 그룹에는 최소한 하나의 조각상이 있어야 한다. 각 조각상은 단 하나의 그룹에만 속해야 한다. 각 그룹의 조각상들은 도로 상에 연속으로 존재해야 한다.</li>
	<li>각 그룹에 대해서, 그룹에 속한 조각상들의 나이를 더한다.</li>
	<li>그룹 별 합에 대해서, 모든 그룹 별 합의 비트 OR를 계산한다. 이 값을 분할의 아름다움 정도라고 하자.</li>
	<li>아름다움 정도를 최소화 한다면 어떤 값이 될 것인가?</li>
</ul>

<p>주의; 음수가 아닌 두 정수 <em>P</em>와 <em>Q</em>의 비트 OR는 다음과 같이 계산한다:</p>

<ul>
	<li><em>P</em>와 <em>Q</em>를 2진수로 변환.</li>
	<li><em>nP</em>를 <em>P</em>의 비트 수라고 하고, <em>nQ</em>를 <em>Q</em>의 비트 수라고 하자. <em>M</em>은 max(<em>nP</em>, <em>nQ</em>)이다.</li>
	<li><em>P</em>의 이진수 표현이 <em>p</em><sub><em>M</em> - 1</sub><em>p</em><sub><em>M</em><sub>2</sub></sub>... <em>p</em><sub>1</sub><em>p</em><sub>0</sub>이고 <em>Q</em>의 이진수 표현이 <em>q</em><sub><em>M</em> - 1</sub><em>q</em><sub><em>M</em><sub>2</sub></sub>... <em>q</em><sub>1</sub><em>q</em><sub>0</sub>라고 하자. 단, <em>p</em><sub><em>i</em></sub>와 <em>q</em><sub><em>i</em></sub>는 각각 <em>P</em>와 <em>Q</em>의 <em>i</em>번째 비트이다. 첨자가 (<em>M</em> - 1)인 비트가 가장 높은 자리수이며 첨자가 0인 비트가 가장 낮은 자리수이다.</li>
	<li>2진수로 <em>P</em> OR <em>Q</em>의 결과는 (<em>p</em><sub><em>M</em> - 1</sub><em> OR q</em><sub><em>M</em> - 1</sub>)(<em>p</em><sub><em>M</em> - 2</sub><em> OR q</em><sub><em>M</em> - 2</sub>)... (<em>p</em><sub>1</sub><em> OR q</em><sub>1</sub>)(<em>p</em><sub>0</sub><em> OR q</em><sub>0</sub>)이다. 단,
	<ul>
		<li>0 OR 0 = 0</li>
		<li>0 OR 1 = 1</li>
		<li>1 OR 0 = 1</li>
		<li>1 OR 1 = 1</li>
	</ul>
	</li>
</ul>

### 입력 

 <p>첫 줄에는 세 개의 정수 <em>N</em>, <em>A</em>, <em>B</em>가 주어진다. 둘째 줄에는 <em>N</em>개의 정수 <em>Y</em><sub>1</sub>, <em>Y</em><sub>2</sub>, ..., <em>Y</em><sub><em>N</em></sub>이 주어진다.</p>

<ul>
	<li>1 ≤ N ≤ 2,000</li>
	<li>1 ≤ A ≤ B ≤ N</li>
	<li>0 ≤ Y<sub>i</sub> ≤ 1, 000, 000, 000</li>
	<li>N이 100을 초과하는 경우, A = 1임이 보장된다.</li>
</ul>

### 출력 

 <p>출력은 단 한 줄이며 최소로 가능한 아름다움 정도를 출력해야 한다.</p>


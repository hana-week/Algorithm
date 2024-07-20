#include <iostream>
#include <queue>
using namespace std;
 
int main() {
	int n;
	int num;
	long long result (0);
	priority_queue<int> pq;
 
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num; 
		num -= i; 
 
		if (!pq.empty() && pq.top() > num){
            pq.push(num); // 꼭 넣어줘야함
            result+=pq.top()-num;
            pq.pop();
            pq.push(num);
        }
        else{
            pq.push(num);
        }
	}
	cout << result << '\n';
 
	return 0;
}
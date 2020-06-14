/*
1000 자리의 수들의 덧셈, 뺄셈, 곱셈, 나눗셈을 수행하는 프로그램을 만들어보세요. 
나눗셈의 경우 소수 부분을 잘라버리세요. 
물론, 소수 부도 1000 자리로 구현해도 됩니다. 
1000 자리 수들의 연산 수행 시간은 1 초 미만이여야 합니다. (난이도 : 上)
*/

// 빅 인티저 구현 RSA 2048 bit에서 해봤었기 때문에 패쓰...
// 오래 걸리기도 하고... 힘들기도 하고... 귀찮기도 하고...
// INT가 32bit이므로 2048bit는 INT 64개의 배열로 구현 가능 (각 인덱스 별 연산 별도 처리)
// 이 문제는 RSA처럼 비트 단위로 들어가는 것이 아니므로 비트 단위 캐리 와 인덱스 별 캐리에 대해 고려 불필요 (더 간단)
// 단순히 CHAR 1000개의 배열을 통해서 인덱스에 해당하는 값과의 연산 후 캐리 처리만 필요
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

/*
Bug description::
Problem description: gets an incorrect answer to the large 100 city test case.
Failing runs: run the code and input the 100 and the output prints a 0 and the exe exited with the code 0.
Other runs: run the code and input the 10 and the output prints a 0 and the exe exited with the code .
Code: considering the result is prints a 0, the code would be printf("%d", 0);
Hypothesis: when the input is 100 and 10 the code considers that the n is 1, so the input module has bug which means the bug would be in buf[1] = '\0';  or/and n = atoi(buf);
Prediction: the code buf[1] = '\0'; change the input and make the string end so the bug is in this code buf[1] = '\0'; 
Experienment1: run the code and input the 15 and the output prints a 0 and the exe exited with the code 0.
Experienment2: run the code and input the 25 and after I entered the first line data the exe get the output which means it thinks the n is 2.
Conclusion: the code buf[1] = '\0'; add a "\n" to the seconed place in the input so it change the value of the n. the "\n"should appear at the last position to let the atoi function knows character string is end.
Fix: considering the input would be 1<= n <= 100, delete the code buf[1] = '\0', because when press the enter button it already contain a EOL in the char array.
Confirm: run the code and input the 5/10/15/25/100 and do not get the wrong output like before. 
*/

/*
Name: Zhiguo Lai
Start time: 10/18/2019 1130AM 
Stop time: 10/18/2019 1142AM
Start time: 10/18/2019 1230PM
Stop time: 10/18/2019 0330PM
Start time: 10/20/2019 0116pm
Stop time: 10/20/2019 0125pm
Start time: 10/20/2019 0330pm
Stop time: 10/20/2019 0403pm
Time used: 3 hours 53 minutes
*/


int minDistance(int* dist, bool* cityVisited, int n);
void dijkstra(int n);
int caculateTime(int* dist, int head,int tail);

//difine the array used for the dijkstra
int dist_info[100][100];
//difine the inout space for a line, the biggest inout would be 
char buf[1100];

//get the next city to travel to
int minDistance(int* dist, bool* cityVisited, int n) {
	int min = INT_MAX;
	int min_index = 0;
	for (int i = 0; i < n; i++) {
		if (*(cityVisited+i) == false && *(dist+i) <= min) {
			min = *(dist+i), min_index = i;
		}
	}
	return min_index;
}

//get the output for this problem
int caculateTime(int* dist,int head, int tail) {
	int lmax, rmax, mid;
	if (head == tail) {
		return dist[head];
	}
	else if (tail == 2) {
		return dist[1];
	}
	else
	{
		mid = (head + tail) / 2;
		lmax=caculateTime(dist, head, mid);
		rmax=caculateTime(dist, mid + 1, tail);
		return lmax > rmax ? lmax : rmax;
	}
}

// run ths Dijukstra algorithms to find the min distance from the capital to each city
void dijkstra(int n) {
	int max;
	int* dist;
	dist = calloc(n, sizeof(int));
	bool* cityVisited;
	cityVisited = calloc(n, sizeof(bool));
	if (dist != NULL && cityVisited != NULL) {
		for (int i = 0; i < n; i++) {
			*(dist + i) = INT_MAX;
			*(cityVisited + i) = false;
		}
		*(dist)=0;
		for (int citiesToBeVisited = 0; citiesToBeVisited < n - 1; citiesToBeVisited++) {

			int index = minDistance(dist, cityVisited, n);
			*(cityVisited+index) = true;
			for (int j = 0; j < n; j++) {
				if (!*(cityVisited+j) && dist_info[index][j] && *(dist+index) != INT_MAX
					&& *(dist+index) + dist_info[index][j] < *(dist+j))
					*(dist+j) = *(dist+index) + dist_info[index][j];
			}
		}

		max = caculateTime(dist,0, n-1);
		printf("\nthe output is:%d", max);
		free(dist);
		free(cityVisited);
	}
	else
	{
		printf("you do not have the enough memory ");
		return;
	}
}

int main() {
	

	/*input function
	consider the boundary condition
	check whether n is right;
	*/
	int n = 0;
	char* token;
	char* next_token = NULL;
	printf("Input n: \n");
	
	fgets(buf,sizeof(buf),stdin);
	n = atoi(buf);// get the value of n
	
	if (n == 1) { // check the value of n, if n is 1. the output should be 0.
		printf("\nThe output is: %d", 0);
		return 0;
	}
	else if (n < 1) {
		printf("please input the right parameter");
		return 0;
	}
	printf("Input the matrix:\n");
	int lines = 1;
	while (lines != n) {
		fgets(buf, sizeof(buf), stdin);
		int i =  0;
		token = strtok_s(buf, " ", &next_token);
		while (token != NULL)
		{
			if (token[0] == 'x') {
				dist_info[lines][i] = 0;
				dist_info[i][lines] = dist_info[lines][i];
				i++;
				token = strtok_s(NULL, " ", &next_token);
				continue;
			}
			dist_info[lines][i] = atoi(token);
			dist_info[i][lines] = dist_info[lines][i];
			i++;
			token = strtok_s(NULL, " ",&next_token);
		}
		lines++;
	}
	/*
	using jidkstra algorithms to update the array of the time traveling from the capital(city 0) to every city. The answer is the largest element in the array.
	*/
	dijkstra(n);
	return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


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
int caculateTime(int* dist, int n);

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
int caculateTime(int* dist, int n) {
	int maxTime = 0;
	for (int i = 0; i < n; i++) {
		maxTime = *(dist+i) > maxTime ? *(dist+i) : maxTime;
	}
	printf("\nthe output is:%d",maxTime);
	return 0;
}
// run ths Dijukstra algorithms to find the min distance from the capital to each city
void dijkstra(int n) {
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

		caculateTime(dist, n);
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
	buf[1] = '\0';
	n = atoi(buf);// get the value of n
	
	if (n == 1) { // check the value of n, if n is 1. the output should be 0.
		printf("%d", 0);
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
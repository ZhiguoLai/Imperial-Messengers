#include <stdio.h>
#include<stdbool.h>


//name Zhiguo Lai
//Start time : 10/18/2019 1130AM 
//first stop time : 10/18/2019 1142AM
//start time: 10/18/2019 1230PM

typedef struct {
	 int src;
	 int dest;
	 int distance;
	bool reachable;
}Distance_Information;

typedef struct{
	int n;
	unsigned long int minTime;
}Adjacency_Matrix;











int main() {
	Distance_Information dist_info[];
	Adjacency_Matrix adj_matrix;
	/*input function
	consider the input boundary
	n, each line check , how many lines
	*/
	printf("Enter the n");
	gets(adj_matrix.n);
	int lines = adj_matrix.n;
	//while (lines != 1) {
	//	
	//}



}
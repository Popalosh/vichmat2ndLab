#include <iostream>
#include <stdio.h>
#include <math.h>
#include "lib\MATRIX.H"
#include "lib\MATRIX.CPP"

using namespace std;

double norma(MATRIX(a), int N){
    double res = 0;
    for (int i = 0; i < N; ++i)
    {
    	for (int k = 0; k < N; ++k)
    	{
    		res += (a[i][k]*a[i][k]);
    	}
    }
    return pow(res,0.5);
}

void makeE(MATRIX(a)){
    for (int i=0; i<=7; i++)
        for (int j=0; j<=7; j++)
            if (i != j) a[i][j] = 0;
                else a[i][j] = 1;
}

void matrixInit( MATRIX(a), int N) {
	for (int i = 0; i < N; ++i) {
		for (int k = 0; k < N; ++k) {
			if (i == k) {
				a[i][k] = 0.01/((N - i + k)*(i+1));
			}

			if (i < k) {
				a[i][k] = 0.0;
			}

			if (i > k) {
				a[i][k] = i*(N-k);
			}
		}
	}
}

void matrixMultiplication(MATRIX(m1), MATRIX(m2), MATRIX(m3), int n){
    int sum = 0;
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){
        sum = 0;
        for (int k = 0; k < n; k++){
            sum += m1[i][k] * m2[k][j];
            m3[i][j] = sum;
        }
    }
}

int main(){
    int n[3] = {3,6,9};
    MATRIX(m);
    MATRIX(notM);

    for (int i = 0; i < 3; ++i) {
    	printf("\n\n\tmatrix: ");
    	int N = n[i];
    	int *ipvt = new int[n[i]];
    	float *cond = new float;
    	float *work = new float[n[i]];

	    matrixInit(m, n[i]);
	    MATRIX(temp);
	    for (int i = 0; i < N; i++) {
	        for (int j = 0; j < N; j++) {
	            temp[i][j] = m[i][j]; //копия для decomp
	        }
	    }

	    decomp(N,temp,cond,ipvt,work);
	    MATRIX(e);
	    makeE(e);

	    for (int j = 0; j < N; j++){
	        solve(N, temp, e[j], ipvt);
	        for (int i = 0; i < N; i++) {
	        	notM[i][j] = e[j][i];
	    	}
	    }   

	    MATRIX(res);

	    matrixMultiplication(m,notM,res,N);
	    for (int i = 0; i < N; i++) {
		    for (int j = 0; j < N; j++) {
		    	res[i][j] += e[i][j];
			}
		}

	    printf("\n %s %.3f \n", "Norma", norma(res,N));

	    for (int i = 0; i < N; i++) {
	        printf("\n");
	        for (int j = 0; j < N; j++) {
		        printf(" %.2f  ", res[i][j]);
		    }
	    }
    }
    return 0;
}
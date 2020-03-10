#include <iostream>
#include <math.h>
#include <chrono>
extern "C" {
void dgetrf_(int *m, int *n, double *a,  int  *lda,
            int *ipivot, int *info) ;
void dgetrs_(char*  trans, int *n, int *nrhs,  double *a,  int  *lda,
             int *ipivot, double *b, int *ldb, int *info) ;
}

double a[1000][1000];
double b[1][1000];
int ipiv[1000];

int n=1000;
int lda = n;
int ldb = n;

using namespace std;
int main(){
    int k;
    int max_k=10;
    int sum1=0;
    int sum2=0;
    // Values needed for functions
    for(k = 0; k < max_k; k++){
        //int n;
        //cout << "Enter n:";
        //cin >> n;
        int nrhs = 1;
        int info;
        char N = 'N';
        // Other values
        int i,j;

        // Fill the values of the matrix
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                if (i==j) {
                    a[j][i]=1;
                }
                else {
                    a[j][i]=1/abs(i-j);
                }
            };
            b[0][i]=sin(i);
        }

        // Solve the linear system
        auto t1 = chrono::high_resolution_clock::now();
        dgetrf_(&n, &n, &a[0][0], &lda, ipiv, &info);
        auto t2 = chrono::high_resolution_clock::now();

        cout << "Hello \n";

        auto t3 = chrono::high_resolution_clock::now();

        dgetrs_(&N, &n, &nrhs, &a[0][0], &lda, ipiv, &b[0][0], &ldb, &info);
        auto t4 = chrono::high_resolution_clock::now();
        // Check for success
        auto duration_init = chrono::duration_cast<chrono::microseconds>(t2 - t1 ).count();
        auto duration_solve = chrono::duration_cast<chrono::microseconds>(t4 - t3).count();
        if(info == 0)
        {
            // Write the answer
            cout << "The answer for n = " << n << " is found\n";
            //for(i = 0; i < n; i++)
            //    cout << "b[" << i << "]\t" << b[0][i] << "\n";
            cout << "Time for initialization = " << duration_init << "\n";
            sum1+=duration_init;
            cout << "Time for the rest solving = " << duration_solve << "\n";
            sum2+=duration_solve;
        }
        else
        {
            // Write an error message
            cerr << "dgesv returned error " << info << "\n";
        }
        //return info;
    }
    cout << "Final time for initialization = " << sum1/max_k << "\n";
    cout << "Final time for the rest solving = " << sum2/max_k << "\n";
}
//
// Created by sarzhina on 02.03.2020.
//


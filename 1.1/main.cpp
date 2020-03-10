#include <iostream>
extern "C" {
void dgesv_(int *n, int *nrhs,  double *a,  int  *lda,
            int *ipivot, double *b, int *ldb, int *info) ;
}


#define MAX 10
using namespace std;
int main(){
    // Values needed for dgesv
    int a[4];


}

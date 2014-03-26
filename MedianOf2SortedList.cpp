#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); i++)
#define RAND(a, b) (rand()%(b-a)+a)

/* statement: 
 * given two sorted vector<int> va and vb. you are to find the median number of the merged list
 * of va and vb.
 */
int work(const vector<int> &a, const vector<int> &b, int a0, int an, int b0, int bn, int k) { 
    // limitation.
    if (a0 == an)
        return b[b0+k];
    if (b0 == bn)
        return a[a0+k];
    
    // iteration.
    if (an-a0 < bn-b0) {
        return work(b, a, b0, bn, a0, an, k);
    }
    int midk = (an+a0-1)/2;
    int posk = lower_bound(b.begin()+b0, b.begin()+bn, a[midk])-b.begin();
    int nhead = (midk - a0) + (posk - b0); 
    // printf("a:%d->%d, b:%d->%d, k:%d midk:%d, posk:%d, nhead:%d\n", a0, an, b0, bn, k, midk, posk, nhead);
    if (nhead == k)
        return a[midk];
    else if (nhead < k) {
        return work(a, b, midk+1, an, posk, bn, k-nhead-1);
    } else {
        return work(a, b, a0, midk, b0, posk, k);
    }
}

int main(int argc, char **argv) {
    REP(icase, 5) {
        int na = RAND(1, 5);
        int nb = RAND(1, 5);
        if ((na + nb) % 2 == 0)
            na += 1;
        vector<int> a(na, 0), b(nb, 0);
        REP(i, na) a[i] = RAND(0, 100);
        REP(i, nb) b[i] = RAND(0, 100);
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        printf("A: "); REP(i, na) printf("%d->", a[i]); printf("\n");
        printf("B: "); REP(i, nb) printf("%d->", b[i]); printf("\n"); 

        int res = work(a, b, 0, na, 0, nb, (na+nb)/2); // 3->1, 5->2
        printf("res:%d\n\n\n", res);
    }
}

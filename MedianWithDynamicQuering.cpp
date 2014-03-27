#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); i++)
#define RAND(a, b) (rand()%(b-a)+a)

/* statement: 
 * given a list of operations on list L.
 *     ADD(x): add x to L.
 *     QUERY(): find the median of L, L will not be empty.
 */
void work(const vector<pair<int,int> > &ops) {
    priority_queue<int, vector<int>, less<int> > maxheap;
    priority_queue<int, vector<int>, greater<int> > minheap;
    int center = -1;
    REP(i, ops.size()) {
        printf("%s", ops[i].first==0?"ADD":"QUERY");
        if (ops[i].first==0) printf(" %d", ops[i].second);
        printf("\n");
        if (ops[i].first == 0) {
            if (center == -1) {
                if(maxheap.size() == 0) {
                    center = ops[i].second;
                    //printf("set center to %d\n", ops[i].second);
                } else {
                    if (maxheap.top() <= ops[i].second && ops[i].second <= minheap.top()) {
                        center = ops[i].second;
                        //printf("set center to %d\n", ops[i].second);
                    } else if (maxheap.top() > ops[i].second) {
                        center = maxheap.top();
                        maxheap.pop();
                        maxheap.push(ops[i].second);
                        //printf("maxheap to center %d, add %d\n", center, ops[i].second);
                    } else {
                        center = minheap.top();
                        minheap.pop();
                        minheap.push(ops[i].second);
                        //printf("minheap to center %d, add %d\n", center, ops[i].second);
                    }
                }
            } else {
                if (center <= ops[i].second) {
                    maxheap.push(center);
                    minheap.push(ops[i].second);
                    center = -1;
                } else {
                    minheap.push(center);
                    maxheap.push(ops[i].second);
                    center = -1;
                }
            }
        } else {
            if (center != -1) printf("%.1f\n", 1.0*center);
            else printf("%.1f\n", 0.5*(minheap.top()+maxheap.top()));
        }
    }
    printf("END\n\n");
}

int main(int argc, char **argv) {
    REP(icase, 5) {
        int opnum = RAND(10, 20);
        vector<pair<int,int> > ops(opnum, make_pair(0,0));
        REP(i, opnum) {
            ops[i].first = RAND(0,2);
            if (i == 0)
                ops[i].first = 0;
            if (ops[i].first == 0)
                ops[i].second = RAND(0, 100);
        }
        work(ops);
    }
    return 0;
}

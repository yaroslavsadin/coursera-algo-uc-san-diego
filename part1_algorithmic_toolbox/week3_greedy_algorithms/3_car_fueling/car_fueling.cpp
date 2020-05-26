#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    if(!stops.size() || stops[0] > tank) {
        return -1;
    }
    int res = 0;
    int current_station = 0;
    for(auto it = std::lower_bound(stops.begin(),stops.end(),tank); 
        current_station + tank < dist;
        it = std::lower_bound(it,stops.end(),current_station + tank), res++
    ) {
        if(*it == current_station + tank) {
            current_station = *it;
        } else if(current_station != *prev(it) && *prev(it) <= current_station + tank) {
            current_station = *prev(it);
        } else {
            return -1;
        }
    }

    return res;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);


vector<int>seg;

void buildSegTree(int idx, int low, int high, int arr[], int OR)
{
    if (low == high)
    {
        seg[idx] = arr[low];
        return;
    }

    int mid = (low + high) >> 1;
    buildSegTree(2 * idx + 1, low, mid, arr, ! OR);
    buildSegTree(2 * idx + 2, mid + 1, high, arr, ! OR);

    if(OR){
        seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
    }
    else{
        seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }
    
    return;
}

void update(int idx, int low, int high, int id, int value, int OR)
{
    if (low == high)
    {
        seg[idx] = value;
        return;
    }

    int mid = (low + high) >> 1;
    if (id <= mid)
    {
        update(2 * idx + 1, low, mid, id, value, ! OR);
    }
    else
    {
        update(2 * idx + 2, mid + 1, high, id, value, ! OR);
    }

    if(OR){
        seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
    }
    else{
        seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }

    return;
}

int main()
{
    FAST_IO;

    int n, k;
    cin >> n >> k;
    
    int size = pow(2, n);
    int arr[size];
    for (int i = 0; i < size; i++){
        cin >> arr[i];
    }

    seg.resize(4 * size);

 
    buildSegTree(0, 0, size - 1, arr, n % 2);     // OR at top if n is odd
    

    for(int i = 0; i < k; i ++){
        int id, val;
        cin >> id >> val;
        update(0, 0, size - 1, id - 1, val, n % 2);
        cout<< seg[0] << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> seg;

public:
    SegmentTree(int n) {
        seg.resize(4 * n);
    }

    void build(int idx, int low, int high, vector<int> &arr) {
        if (low == high) {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r) {
        if (r < low || l > high) return 0;  // No overlap
        if (l <= low && high <= r) return seg[idx];  // Complete overlap

        // Partial overlap
        int mid = (low + high) >> 1;
        return query(2 * idx + 1, low, mid, l, r) +
               query(2 * idx + 2, mid + 1, high, l, r);
    }

    void update(int idx, int low, int high, int pos, int value) {
        if (low == high) {
            seg[idx] = value;
            return;
        }

        int mid = (low + high) >> 1;
        if (pos <= mid)
            update(2 * idx + 1, low, mid, pos, value);
        else
            update(2 * idx + 2, mid + 1, high, pos, value);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(n);
    st.build(0, 0, n - 1, arr);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << st.query(0, 0, n - 1, l, r) << endl;
        } else {
            int pos, value;
            cin >> pos >> value;
            st.update(0, 0, n - 1, pos, value);
        }
    }
    return 0;
}

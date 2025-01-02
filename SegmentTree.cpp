#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

class seg_tree {
    vector<int> seg;

public:
    seg_tree(int n) {
        seg.resize(4 * n);
    }

    void buildSegTree(int idx, int low, int high, int arr[]) {
        if (low == high) {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        buildSegTree(2 * idx + 1, low, mid, arr);
        buildSegTree(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
        return;
    }

    int query_min(int idx, int low, int high, int l, int r) {
        // No overlap
        if (high < l || r < low) {
            return INT_MAX;
        }

        // Complete overlap
        if (low >= l && r >= high) {
            return seg[idx];
        }

        // Partial overlap
        int mid = (low + high) >> 1;
        int left = query_min(2 * idx + 1, low, mid, l, r);
        int right = query_min(2 * idx + 2, mid + 1, high, l, r);

        return min(left, right);
    }

    void update(int idx, int low, int high, int id, int value) {
        if (low == high) {
            seg[idx] = value;
            return;
        }

        int mid = (low + high) >> 1;
        if (id <= mid) {
            update(2 * idx + 1, low, mid, id, value);
        } else {
            update(2 * idx + 2, mid + 1, high, id, value);
        }
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);

        return;
    }
};

int main() {
    FAST_IO;

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    seg_tree seg1(n);
    seg1.buildSegTree(0, 0, n - 1, arr);

    int q;
    cin >> q; // Number of queries
    while (q--) {
        int type;
        cin >> type; // 1 for query, 2 for update
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << "Minimum in range [" << l << ", " << r << "] is: "
                 << seg1.query_min(0, 0, n - 1, l - 1, r - 1) << endl;
        } else if (type == 2) {
            int id, value;
            cin >> id >> value;
            seg1.update(0, 0, n - 1, id - 1, value);
            cout << "Updated index " << id << " to value " << value << endl;
        }
    }

    return 0;
}

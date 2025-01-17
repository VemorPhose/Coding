#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define ull             uint64_t
#define Int             int32_t
#define uint            uint32_t
#define pii             pair<ll, ll>
#define vi              vector<ll>
#define vvi             vector<vector<ll>>
#define mpii            map<ll, ll>
#define umpii           unordered_map<ll, ll>
#define vs              vector<string>

// shortcuts
#define MOD             1000000007
#define mod             998244353
#define INF             1000000000000000010
#define PI              2 * acos(0.0)
#define LL_MAX          LLONG_MAX
#define LL_MIN          LLONG_MIN
#define ULL_MAX         ULLONG_MAX
#define endl            "\n"

// binary operations
#define swap(a,b)       a=a^b; b=b^a; a=a^b
#define setibit(n,i)    (n | (1<<i))
#define extibit(n,i)    (n & (1<<i))
#define clribit(n,i)    (n & ~(1<<i))
#define invibit(n,i)    (n ^ (1<<i))
#define setbits(x)      __builtin_popcountll(x)
#define lzbits(x)       __builtin_clzll(x)
#define tzbits(x)       __builtin_ctzll(x)

// pairs
#define ff              first
#define ss              second
#define mp              make_pair

// iterable operations
#define pub             push_back
#define pob             pop_back
#define ft              front()
#define bk              back()
#define ins             insert
#define sz(x)           (ll)x.size()
#define all(x)          (x).begin(), (x).end()

// looping
#define FOR(i, a, b)    for (ll i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n)       for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }
#define coutN           cout << "NO" << endl
#define coutY           cout << "YES" << endl

// Recursive function to find the kth element in two sorted
// arrays
int kth(int* arr1, int* arr2, int* end1, int* end2, int k)
{
    // If the first array is exhausted, return the k-th
    // element from the second array
    if (arr1 == end1)
        return arr2[k];
    // If the second array is exhausted, return the k-th
    // element from the first array
    if (arr2 == end2)
        return arr1[k];

    // Calculate midpoints for both arrays
    int mid1 = (end1 - arr1) / 2;
    int mid2 = (end2 - arr2) / 2;
    if (mid1 + mid2 < k) {
        // If the value at mid1 in the first array is
        // greater, discard the left part of the second
        // array
        if (arr1[mid1] > arr2[mid2])
            return kth(arr1, arr2 + mid2 + 1, end1, end2,
                       k - mid2 - 1);
        // Otherwise, discard the left part of the first
        // array
        else
            return kth(arr1 + mid1 + 1, arr2, end1, end2,
                       k - mid1 - 1);
    }
    else {
        // If the value at mid1 in the first array is
        // greater, discard the right part of the first
        // array
        if (arr1[mid1] > arr2[mid2])
            return kth(arr1, arr2, arr1 + mid1, end2, k);
        // Otherwise, discard the right part of the second
        // array
        else
            return kth(arr1, arr2, end1, arr2 + mid2, k);
    }
}

// Function to find the k-th element in two sorted arrays
int kthElement(int arr1[], int arr2[], int n, int m, int k)
{
    return kth(arr1, arr2, arr1 + n, arr2 + m, k - 1);
}

int main(){
    fastio();
    int n = 5, m = 4;
    int arr1[] = { 2, 3, 6, 7, 9 };
    int arr2[] = { 1, 4, 8, 10 };
    int k = 5;

    cout << kthElement(arr1, arr2, n, m, k);
    return 0;
}
#include <iostream>

using namespace std;

#define L 100000

int main() {
    // static for memory issues in Windows
    static int prefix_table[L], j, s_len, t_len, i;
    static long long result;
    string s, t;

    cin >> s >> t;
    result = 0;
    j = -1;
    prefix_table[0] = -1;
    s_len = s.size();
    t_len = t.size();

    // Build KMP prefix table ---------------------------
    for (i = 1; i < t_len; i++) {
        while (j >= 0 && t[j + 1] != t[i]) {
            j = prefix_table[j];
        }
        if (t[j + 1] == t[i]) {
            j++;
        }
        prefix_table[i] = j;
    }

    // Run KMP ------------------------------------------
    j = -1;
    for (i = 0; i < s_len; i++) {
        if (t[j + 1] == s[i]) {
            j++;
        } else {
            while (j >= 0 && t[j + 1] != s[i]) {
                j = prefix_table[j];
            }
            if (t[j + 1] == s[i]) {
                j++;
            }
        }
        if (j == t_len - 1) {
            result += 1;
            j =-1;

        }
    }

    cout << result << endl;
    return 0;
}
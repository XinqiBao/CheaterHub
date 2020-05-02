#include <iostream>
#include <string>
#include <vector>

#include "wordscapes.h"
using namespace std;

int main()
{
    Wordscapes ws;
    string given, search;
    cout << "given:\n>> ";
    cin >> given;

    cout << "\nsearch:\n>> ";
    while (cin >> search)
    {
        auto result = ws.solve(given, search);
        for (auto& res : result) cout << res << endl;

        cout << "\nsearch:\n>> ";
    }

    return 0;
}

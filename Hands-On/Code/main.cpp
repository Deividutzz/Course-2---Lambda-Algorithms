#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct UserRole
{
    string user;
    string role;
};

// Continue declaring the other structs...

int main()
{
    ifstream inFile("input.txt");

    int n, m, q;

    inFile >> n;
    vector<UserRole> userRoles(n);
    for (UserRole &ur : userRoles)
    {
        inFile >> ur.user >> ur.role;
    }

    // Continue reading the other input...

    // Write your code here

    return 0;
}

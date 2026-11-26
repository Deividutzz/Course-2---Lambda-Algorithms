#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr int maxLen = 20005;
static int n,m,k;

static int convertIt(const string& name) {
    const char ch = (char) name[name.length() - 1];
    const int poz = (int) (ch - '0');
    return poz;
}
static string mergePerms(string currentP, const string& beforeP) {
    if (beforeP == "---d" || currentP == "---d") return "---d";

    constexpr char letter[] = {'r', 'w', 'x', 'd'};
    for (int i = 0; i < currentP.length(); i++) {
        if (currentP[i] == letter[i] || beforeP[i] == letter[i]) {
            currentP[i] = letter[i];
            //beforeP[i] = letter[i];
        }
    }
    return currentP;
}
static string buildCurrentP(const string& action) {
    string permissions = "----";
    for (int i = 0; i < action.length(); i++) {
        if (action[i] == 'd')
            return "---d";

        switch (action[i]) {
            case 'r':
                permissions[0] = 'r';
                break;
            case 'w':
                permissions[1] = 'w';
                break;
            case 'x':
                permissions[2] = 'x';
                break;
            default:
                permissions[3] = 'd';
        }
    }
    return permissions;
}
static bool admins[maxLen];
static vector <int> users[maxLen];
static vector <string> userPermission[maxLen];
static vector <string> beforePermission(maxLen);

static void computePermissionPerUser(const string& action, const vector <int>& userIds, const int nrRoles, const int rolePoz, const int permPoz) {

    // if permission == d => ---d for permI
    // if permission then permI (like permPoz) = merge from role
    const string rolePermIsol = buildCurrentP(action); // string with permissions for role x and for p Y
    for (const auto userId : userIds) {
        for (int j = 1; j <= nrRoles; j++) {
            if (users[userId][j] == 1 && j < users[userId].size()) {
                // then user x has the role y
                if (j == rolePoz) { // if is the role we are seeking then add to user the perm
                    // it is the iterator of user

                    userPermission[userId].resize(permPoz + 5);

                    auto& accumulated = userPermission[userId];
                    if (accumulated.size() <= permPoz)
                        accumulated.resize(permPoz + 1, "----");

                    if (accumulated[permPoz].empty())
                        accumulated[permPoz] = "----";

                    accumulated[permPoz] =
                    mergePerms(accumulated[permPoz], rolePermIsol);
                }
            }
        }
    }
}

static void input() {
    vector<int> userIds;
    cin >> n; // users
    //int maxim = -1;
    int nrRoles = -1;
    int nrUsers = -1;
    int nrPerms = -1;
    for (int i = 0; i < n; i++) {
        string usr;
        string role;
        cin >> usr >> role;
        int userPoz = convertIt(usr);
        int rolePoz = convertIt(role);

        if (users[userPoz].empty())
            userIds.push_back(userPoz);

        nrRoles = max(nrRoles, rolePoz);
        nrUsers = max(nrUsers, userPoz);
        users[userPoz].resize(rolePoz + 5);
        users[userPoz][rolePoz] = 1;
    }
    cin >> m; // roles
    vector <string> usersSol; /// solution perms for each user
    for (int i = 0; i < m; i++) {
        string role;
        string permission;
        string action;
        cin >> role >> permission >> action;
        const int rolePoz = convertIt(role);
        const int permPoz = convertIt(permission);

        nrPerms = max(nrPerms, permPoz);

        computePermissionPerUser(action,userIds,nrRoles,rolePoz,permPoz); /// computing each permission (that applies)
        /// for each user that has the specific roles that are checked too.
    }

    for (const int userId : userIds) {
        bool isAdmin = true;

        for (int p = 1; p <= nrPerms; ++p) {
            if (p >= userPermission[userId].size() ||
                userPermission[userId][p] != "rwx-") {
                isAdmin = false;
                break;
                }
        }

        admins[userId] = isAdmin;
    }

    cin >> k; // queries
    for (int i = 0; i < k; i++) {
        string usr;
        string permission;
        cin >> usr >> permission;
        const int userPoz = convertIt(usr);
        const int permPoz = convertIt(permission);
        userPermission[userPoz].resize(permPoz + 5);
        string solution = userPermission[userPoz][permPoz];

        if (solution.empty()) solution = "----";
        cout << usr << " " << permission << " " << solution;
        cout << '\n';
    }
    for (int i = 1; i <= nrUsers; i++) {
        if (admins[i]) {
            cout << "user" << i << " is admin" << '\n';
        }
    }
}
int main()
{
    input(); /// main function, that also manipulates the input
    return 0;
}
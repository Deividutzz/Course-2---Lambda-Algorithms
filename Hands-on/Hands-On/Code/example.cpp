#include <algorithm> // <-- needed for algorithms
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void PrintInts(const vector<int> &ints)
{
    for (int i = 0; i < ints.size(); i++)
        cout << ints[i] << ' ';
    cout << endl;

    cout << "Vector size: " << ints.size() << endl;
    cout << "Vector capacity: " << ints.capacity() << endl;
    cout << endl;
}

void Example1()
{
    vector<int> vec(2, 5);
    PrintInts(vec);

    vec.push_back(7);
    PrintInts(vec);

    vec.emplace_back(5);
    PrintInts(vec);

    vec.erase(vec.begin() + 1);
    PrintInts(vec);
}

struct Volunteer
{
    string name;
    int age = 0;

    Volunteer() = default;

    Volunteer(const string &name, const int age) : name(name), age(age)
    {
    }

    // Operator overload for sorting by age
    bool operator<(const Volunteer &other) const
    {
        return age < other.age;
    }
};

void PrintVolunteers(const vector<Volunteer> &volunteers)
{
    for (auto it = volunteers.begin(); it != volunteers.end(); it++)
        cout << "Volunteer name: " << it->name << " and age: " << it->age << endl;

    cout << endl;
}

void Example2()
{
    vector<Volunteer> youngVolunteers;

    Volunteer volunteer1;
    volunteer1.name = "Branza Alexandru";
    volunteer1.age = 39;

    youngVolunteers.push_back(volunteer1);
    PrintVolunteers(youngVolunteers);

    youngVolunteers.emplace_back("Smantana Andrei", 10);
    PrintVolunteers(youngVolunteers);

    Volunteer volunteer2;
    volunteer2.name = "Mamaliga Ionut";
    volunteer2.age = 4;

    youngVolunteers.insert(youngVolunteers.begin(), volunteer2);
    PrintVolunteers(youngVolunteers);

    youngVolunteers.erase(youngVolunteers.begin(), youngVolunteers.begin() + 2);
    PrintVolunteers(youngVolunteers);
}

//
// ----------------------------
// ALGORITHMS + LAMBDAS EXAMPLES
// ----------------------------
//

void AlgorithmExamples()
{
    cout << "\n=== Algorithm Examples with Lambdas ===\n";

    vector<int> nums = {3, 7, 1, 4, 7, 10};

    // ---------------- FIND ----------------
    cout << "\nfind example: looking for 7\n";
    auto it = find(nums.begin(), nums.end(), 7);
    if (it != nums.end())
        cout << "Found 7 at index: " << (it - nums.begin()) << endl;

    // ---------------- FIND_IF with lambda ----------------
    cout << "\nfind_if example: first number > 5\n";
    auto it2 = find_if(nums.begin(), nums.end(), [](int x) { return x > 5; });
    if (it2 != nums.end())
        cout << "First number > 5: " << *it2 << endl;

    // ---------------- SORT for binary_search ----------------
    sort(nums.begin(), nums.end());
    cout << "\nSorted nums for binary_search: ";
    for (int n : nums)
        cout << n << " ";
    cout << endl;

    // ---------------- BINARY_SEARCH ----------------
    cout << "\nbinary_search for 4: ";
    if (binary_search(nums.begin(), nums.end(), 4))
        cout << "Found\n";
    else
        cout << "Not found\n";

    // ---------------- LOWER_BOUND ----------------
    cout << "\nlower_bound for value 7\n";
    auto lb = lower_bound(nums.begin(), nums.end(), 7);
    if (lb != nums.end())
        cout << "First element >= 7 is at index " << (lb - nums.begin()) << endl;
    else
        cout << "No element >= 7 was found\n";

    // ---------------- REMOVE ----------------
    cout << "\nremove example: remove number 7\n";
    auto newEnd = remove(nums.begin(), nums.end(), 7);
    nums.erase(newEnd, nums.end());
    for (int n : nums)
        cout << n << " ";
    cout << endl;

    // ---------------- REMOVE_IF + LAMBDA ----------------
    cout << "\nremove_if example: remove numbers < 4\n";
    nums = {3, 7, 1, 4, 7, 10}; // reset the numbers

    nums.erase(remove_if(nums.begin(), nums.end(), [](int x) { return x < 4; }), nums.end());

    for (int n : nums)
        cout << n << " ";
    cout << endl;
}

//
// Example: Sorting Volunteers using operator<
//
void SortVolunteersExample()
{
    cout << "\n=== Sorting Volunteers Example ===\n";

    vector<Volunteer> volunteers = {
        {"Branza Alexandru", 39}, {"Smantana Andrei", 10}, {"Mamaliga Ionut", 4}, {"Zacusca Rares", 18}};

    cout << "\nBefore sorting:\n";
    PrintVolunteers(volunteers);

    sort(volunteers.begin(), volunteers.end()); // uses operator<

    cout << "After sorting by age (operator<):\n";
    PrintVolunteers(volunteers);
}

int main()
{
    Example1();
    Example2();
    AlgorithmExamples();
    SortVolunteersExample();

    return 0;
}

// clang++ -std=c++14 cpp-vector-demo.cpp ; ./a.out

#include <iostream>
#include <vector>
#include <string>
 
int demo_vectors()
{
    using namespace std;

    // integers
	vector<int> integers = {1, 2, 4, 8, 16};
 
    integers.push_back(25);
    integers.push_back(13);
 
    cout << "integers" << endl;
    for(int i : integers) {
        cout << i << '\n';
    }

    cout << "\nStrings\n";
	vector<string> fruits = {"orange", "apple", "raspberry"};

    for(auto f : fruits) {
        cout << "fruit " << f << endl;
    }

    cout << "\ndemo for loop, count, other things like this\n";
    cout << "size " << fruits.size() << endl;


    return 0;
}

int main()
{
    using namespace std;
    cout << "c++ vectors\n";
    demo_vectors();


} 

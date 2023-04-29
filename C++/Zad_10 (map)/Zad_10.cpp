#include <iostream>
#include <map> 

using namespace std;

// 1.
map <string,int> m1 = {
    {"A",1},
    {"B",2},
    {"C",3},
    {"D",4},
    {"E",5}
};
// 2.
map <string,int> m2(m1); // Drugi sposób na kopiowanie: m2 = m1
// 3.
map <string,int> m3 = m1;
// 4.
map <int,int> m4;

int main()
{
    // 4.
    for (int i = 1; i <= 10; i++)
        m4.insert(pair<int, int>(i, i*100));

    // 5.
    cout << m4.at(6) << endl << endl;
    
   // 6.
   for (auto it = m4.find(2); it != m4.upper_bound(8); it++)
        cout << it->first << " : " << it->second << endl;
   cout << endl;
   // 7.
   m4.erase(m4.find(2), m4.find(7));

   // 8.
   m1.swap(m3);
   cout << "m1: " << endl;
   for (auto it = m1.begin(); it != m1.end(); it++)
       cout << it->first << " : " << it->second << endl;

   cout << endl;

   cout << "m3: " << endl;
   for (auto it = m3.begin(); it != m3.end(); it++)
       cout << it->first << " : " << it->second << endl;

   // 9.
   for (auto it = (m1.begin())++; it != (m1.end())--; it++)
       m3[it->first] = it->second;
}

#include <iostream>
#include <list>

using namespace std;

class Person 
{
public:
    string name, surname;
public:
    Person(string n, string s) : name(n), surname(s) {}
    void print()
    {
        cout << name << " " << surname << " ";
    }
    /*
   bool operator < (const Person& personObj)
    {
        return (name < personObj.name) && (surname < personObj.surname);
    }
    */
};

list <Person> persons;

void dodaj_osobe()
{
    string imie, nazwisko;

    cout << "Podaj imie i nazwisko: " << endl;
    cin >> imie;
    cin >> nazwisko;
    cout << endl;
    Person o(imie, nazwisko);
    persons.push_back(o);
}

void wypisz_liste()
{
   for (auto i = persons.begin(); i != persons.end(); ++i) //(list<Person>::iterator i = persons.begin(); i != persons.end(); ++i)
    {
        i->print();
        cout << endl;
    }
}

bool sortByName(const Person& person1, const Person& person2)
{
    if (person1.name == person2.name)
        return person1.name < person2.name;
    return person1.name < person2.name;
}

bool sortBySurname(const Person& person1, const Person& person2)
{
    if (person1.surname == person2.surname)
        return person1.surname < person2.surname;
    return person1.surname < person2.surname;
}


int main()
{
    for (int i = 0; i < 5; i++)
    {
        dodaj_osobe();
    }

    /*
    Person o1("Steve", "Jobs");
    persons.push_back(o1); 
    Person o2("Malia", "Obama");
    persons.push_back(o2);    
    Person o3("Donald", "Trump");
    persons.push_back(o3);
    Person o4("Barack", "Obama");
    persons.push_back(o4);
    Person o5("Michelle", "Obama");
    persons.push_back(o5);
   */

   wypisz_liste();
   cout << endl;
   persons.sort(sortByName);
   persons.sort(sortBySurname);
   wypisz_liste();

}

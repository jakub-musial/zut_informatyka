#include "list.h"

int main()
{  
    Linked_list <some_object> lista;

    some_object o1(1, 'a');
    some_object o2(2, 'b');
    some_object o3(3, 'c');
    some_object o4(4, 'd');
    some_object o8(8, 'h');
    some_object o6(6, 'F');

    std::cout << "-------------" << std::endl;
    std::cout << "| PUSH FRONT |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.push_front(o3);
    lista.push_front(o2);
    lista.push_front(o1);
    lista.display();
    
    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "| PUSH BACK |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.push_back(o4);
    lista.push_back(o8);
    lista.push_back(o6);
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "| POP FRONT |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.pop_front();
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "| POP BACK |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.pop_back();
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "|   FIND    |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    std::cout << "o3 address: " << lista.find(o3) << std::endl << std::endl;

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "|  REMOVE   |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.remove(o3);
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-----------------" << std::endl;
    std::cout << "| SORTED INSERT |" << std::endl;
    std::cout << "-----------------" << std::endl << std::endl;
    some_object o7(7, 'g');
    lista.sorted_insert(o7);
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "|   CLEAR   |" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    lista.clear();
    lista.display();

    std::cout << "-------------------------------------" << std::endl << std::endl;
}

/*
int main()
{
    const int MAX_ORDER = 6;
    Linked_list <some_object*>* ll = new Linked_list<some_object*>;

    srand(time(0));

    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {
        // dodawanie do listy
        const int n = pow(10, o);
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            some_object* so = new some_object(rand() % 10000, 'a' + rand() % 26);
            ll->push_front(so);
        }
        std::cout << "Czas dodawania elementow: " << t1 << std::endl << std::endl;
        
        // wyszukiwanie i usuwanie elementów z listy
        const int m = pow(10, 4);
        t1 = clock();
        for (int i = 0; i < m; i++)
        {
            some_object* so = new some_object(rand() % 10000, 'a' + rand() % 26); // losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
            ll->find(so);
            delete so;
        }
        std::cout << "Czas usuwania elementow: " << t1 << std::endl << std::endl;

        // czyszczenie listy
        clock_t t2 = clock();
        ll->clear(true);
        std::cout << "Czas czyszczenia listy: " << t2 << std::endl << std::endl;

         std::cout << "-------------------------------------------------------------------------------" << std::endl;
    }
   
   delete ll;
   return 0;
}
*/
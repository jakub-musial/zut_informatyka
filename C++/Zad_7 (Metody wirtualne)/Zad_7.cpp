#include <iostream>

using namespace std;

class Czworokat
{
protected:
    float a, b, c, d;

public:
    void wypisz()
    {
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
        cout << "d: " << d << endl;
    }

    virtual void pole() = 0;

    Czworokat(float aa, float bb, float cc, float dd)
    {
        a = aa;
        b = bb;
        c = cc;
        d = dd;
    }
};

class Prostokat : public Czworokat
{
public:
    Prostokat(float aa, float bb) : Czworokat(aa,aa,bb,bb)
    {
        a = aa; b = aa;
        c = bb; d = bb;
    }

    void wymiary(float w1, float w2)
    {
        a = w1; b = w1;
        c = w2; d = w2;
    }

    virtual void pole()
    {
        cout << "Pole prostokata: " << a * c << endl;
    }
};

class Kwadrat : public Czworokat
{
public:
    Kwadrat(float aa) : Czworokat(aa,aa,aa,aa)
    {
        a = aa; b = aa; c = aa; d = aa;
    }

    void wymiary(float w)
    {
        a = w; b = w; c = w; d = w;
    }

    virtual void pole()
    {
        cout << "Pole kwadratu: " << a * a << endl;
    }
};

int main()
{
    Czworokat* wsk;

    float bok_a;
    cin >> bok_a;

    wsk = new Kwadrat(bok_a);
    wsk->pole();

    float bok_b;
    cin >> bok_a;
    cin >> bok_b;

    wsk = new Prostokat(bok_a, bok_b);
    wsk->pole();


}

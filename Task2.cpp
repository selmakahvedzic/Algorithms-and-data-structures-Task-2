#include <iostream>
#include<vector>
using namespace std;

template<typename Tip>
struct Cvor {
    Tip vrijednost;
    Cvor<Tip>* sljedeci;
};


template <typename Tip>
class Stek
{
private:
    int broj=0;
    Cvor<Tip>* top;
public:
    Stek()
    {
        top=nullptr;
        broj=0;
    }

    ~Stek()
    {
        this->brisi();
        top=nullptr;
        broj=0;
    }

    Tip &vrh()
    {
        if(broj==0) throw "Izuzetak";
        return top->vrijednost;
    }

    int brojElemenata() const
    {
        return broj;
    }

    void brisi()
    {
        while (broj>0) {
            this->skini();
        }
        top=nullptr;
    }
    
    Stek(Stek &&s);
    
    Stek &operator=(Stek &&s);

    void stavi(const Tip &el)
    {
        Cvor<Tip>* temp= new Cvor<Tip>();
        temp->vrijednost=el;
        if(broj==0) {
            top=temp;
            top->sljedeci=nullptr;
        } else {
            temp->sljedeci=top;
            top=temp;
        }
        broj++;
    }
    
    Tip skini()
    {
        if(broj==0) throw "Izuzetak";
        Tip element = top->vrijednost;
        if(broj==1) delete top;
        else {
            Cvor<Tip>* temp= top;
            top=top->sljedeci;
            delete temp;

        }
        broj--;
        return element;
    }
    
    void Copy(const Stek &s)
    {
        if(this!= &s) {
            broj=s.broj;
            top= new Cvor<Tip>();
            top->vrijednost= s.top->vrijednost;
            Cvor<Tip>* temp=s.top;
            Cvor<Tip>* pom= top;
            temp=temp->sljedeci;
            while (temp!=nullptr) {
                pom->sljedeci= new Cvor<Tip>();
                pom=pom->sljedeci;
                pom->vrijednost= temp->vrijednost;
                pom->sljedeci= nullptr;
                temp= temp->sljedeci;
            }
        }
    }
    

    Stek(const Stek &s)
    {
        Copy(s);
    }
    
    Stek &operator= (const Stek &s)
    {
        if(this==&s) return * this;
        this->brisi();
        this->Copy(s);
        return *this;
    }

};




void pretraga(Stek<std::vector<int>> &s, int trazeni)
{

    std::vector<int>v= {} ;

    if(s.brojElemenata()==0) {
        cout<<"Nema elementa";
        return;
    }
    if(s.vrh().size()==0) {
        v=s.skini();
        pretraga(s, trazeni);
        s.stavi(v);
    }

    else if(trazeni<s.vrh()[0]) {
        v=s.skini();
        pretraga(s, trazeni);
        s.stavi(v);
    }

    else {
        int glava=0;
        int vrhic=s.vrh().size()-1, sred ;


        while (glava<=vrhic) {
            sred= (vrhic+glava)/2;

            if(s.vrh()[sred]>trazeni) vrhic= sred-1;
            else if(s.vrh()[sred]<trazeni) glava= sred+1;
            else {
                cout<<sred<< " "<< s.brojElemenata()-1;
                s.stavi(v);
                return;
            }
        }
        cout<<"Nema elementa";
        s.stavi(v);
        return;
    }
}



//Napisat cu i 3 testne funkcije
void test1()
{
    Stek<std::vector<int>>s ;
    std::vector<int>v ;
    for(int i=1; i<=5; i++) v.push_back(i);
    s.stavi(v);
    pretraga(s, 40);
}
void test2()
{
    Stek<std::vector<int>>s ;
    std::vector<int> v;
    for(int i=1; i<=10; i++) v.push_back(i);
    s.stavi(v);
    v.resize(0);
    pretraga(s, 10);
}

void test3()
{
    Stek<std::vector<int>> s ;
    std::vector<int>v ;
    for(int i=1; i<=5; i++) v.push_back(i);
    s.stavi(v);
    v.resize(0);
    pretraga(s, -10);
}



int main()
{
    try {
        Stek<std::vector<int>>stek ;
        std::vector<int> v1;
        for(int i=1; i<6; i++)
            v1.push_back(i);
        std::vector<int> v2;
        v2.push_back(6);
        v2.push_back(8);
        test1();
        test2();
        test3();
    } catch(...) {
        cout<<"Bacen izuzetak";
    }
    std::cout << "Zadaća 2, Zadatak 2";
    return 0;
}

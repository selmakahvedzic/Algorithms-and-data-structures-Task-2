#include <iostream>
using namespace std;

template <typename Tip>
struct Cvor {
 Tip vrijednost;
 Cvor<Tip>*prethodni; 
 Cvor<Tip>*sljedeci;
};

template<typename Tip>
class DvostraniRed {
 private:
 int broj;
 
 Cvor<Tip>*pocetak;
 Cvor<Tip>*top;
 
 public:
 DvostraniRed() {
  broj=0;
  pocetak=nullptr; 
  top=nullptr;
 }
 
 Tip &vrh() {
  if(broj==0) throw "Izuzetak"; 
  return top->vrijednost;
 }
 
 Tip &celo() {
  if(broj==0) throw "Izuzetak";
  return pocetak->vrijednost;
 }
 
 Tip skiniSaVrha();
 void brisi() {
  while(broj>0) {
   this->skiniSaVrha(); 
  }
 }
 
 ~DvostraniRed() {
  this->brisi();
 }
 
 DvostraniRed <Tip> operator =(DvostraniRed<Tip> &&d) {
  if(&d==this) return *this; 
  this->brisi(); 
  broj=d.broj; 
  pocetak=d.pocetak;
  top=d.top;
  return *this; 
 }
 
 int brojElemenata() const {
  return broj;
 }
 
 void staviNaVrh(const Tip &el); 
 void staviNaCelo(const Tip &el);
 Tip skiniSaCela();
 DvostraniRed(DvostraniRed<Tip> &&d) {
  broj=d.broj;
  pocetak=d.pocetak;
  top=d.top;
 }

  DvostraniRed(const DvostraniRed<Tip> &d);
  DvostraniRed<Tip>&operator =(const DvostraniRed<Tip>&d);
};

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela() {
 if(broj==0) throw "Izuzetak";
 Cvor<Tip>*temp=pocetak;
 Tip element=pocetak->vrijednost;
 pocetak=pocetak->sljedeci;
 delete temp;
 broj--;
 return element;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha() {
 if(broj==0) throw "Izuzetak"; 
 Cvor<Tip>*temp=top;
 Tip element=top->vrijednost;
 top=top->prethodni;
 delete temp;
 broj--;
 return element;
}

 
template<typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip& el){
 Cvor<Tip>* novi= new Cvor<Tip>(); 
 novi->vrijednost= el; 
 if(broj==0){
  pocetak=top=novi; 
  pocetak->sljedeci=nullptr; 
  top->prethodni=nullptr; 
 }
 else {
  novi->sljedeci=pocetak; 
  pocetak->prethodni=novi; 
  pocetak=pocetak->prethodni; 
 }
 broj++; 
}

template<typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip & el)
{
 Cvor<Tip>* novi= new Cvor<Tip>(); 
 
 novi->vrijednost=el;
 if(broj==0){
  pocetak=top=novi; 
  pocetak->sljedeci=nullptr; 
  top->prethodni=nullptr; 
 }
 else{
   novi->prethodni=top; 
   top->sljedeci=novi; 
   top=top->sljedeci; 
 }
 broj++; 
 }
 

template<typename Tip>
DvostraniRed<Tip> &DvostraniRed<Tip>::operator =(const DvostraniRed<Tip> &d){
 if(&d==this) return *this; 
 this->brisi(); 
 broj=d.broj; 
 Cvor<Tip>* temp= d.pocetak; 
 top=new Cvor<Tip>(); 
 top->vrijednost= temp->vrijednost; 
 pocetak=top; 
 temp=temp->sljedeci; 
 while (temp!=nullptr) {
  top->sljedeci=new Cvor<Tip>(); 
  top->sljedeci->vrijednost=temp->vrijednost; 
  top->sljedeci->prethodni=top; 
  temp=temp->sljedeci; 
  top=top->sljedeci; 
 }
  return *this; 
}

template<typename Tip>
DvostraniRed<Tip>:: DvostraniRed(const DvostraniRed<Tip> &d){
 broj=d.broj; 
 Cvor<Tip> * temp=d.pocetak; 
 top=new Cvor<Tip>(); 
 top->vrijednost= temp->vrijednost; 
 pocetak= top; 
 temp=temp->sljedeci; 
  while (temp!=nullptr) {
    top->sljedeci= new Cvor<Tip>(); 
    top->sljedeci->vrijednost= temp->vrijednost;
    top->sljedeci->prethodni= top; 
    temp= temp->sljedeci; 
    top=top->sljedeci; 
  }
}



//TESTOVI
template<typename Tip>
int testBrojElemenata(const DvostraniRed<Tip> &d){
 return d.brojElemenata(); 
}

template<typename Tip>
void testBrisi(DvostraniRed<Tip> &d){
 d.brisi(); 
}

 template<typename Tip>
 void testStaviNaVrh(DvostraniRed<Tip> &d, const Tip &el){
  d.staviNaVrh(el); 
 }
 
template<typename Tip>
void testStaviNaCelo(DvostraniRed<Tip> &d, const Tip &el){
 d.staviNaCelo(el); 
}

template<typename Tip>
Tip testSkiniSaVrha(DvostraniRed<Tip> &d){
 return d.skiniSaVrha(); 
}

template<typename Tip>
Tip testSkiniSaCela(DvostraniRed<Tip> &d){
 return d.skiniSaCela();
}

template<typename Tip>
Tip testVrh(DvostraniRed<Tip> &d){
 return d.vrh(); 
}

template<typename Tip>
Tip testCelo(DvostraniRed<Tip> &d){
 return d.celo(); 
}


int main() {

 try{
  DvostraniRed<int>d; 
  testStaviNaCelo(d, 1); 
  testStaviNaVrh(d, 4);
  testStaviNaCelo(d, 3); 
  cout<<testBrojElemenata(d)<<endl; 
  cout<<testSkiniSaVrha(d)<<endl; 
  cout<<testSkiniSaCela(d)<<endl; 
  cout<<testBrojElemenata(d)<<endl;
  testBrisi(d); 
 }  catch(...){
   cout<<"OK!"; 
 }
    std::cout << "Zadaća 2, Zadatak 1";
    return 0;
}

#include "table.h"

using namespace std;

Table::Table(unsigned int max_entries){
  data= new CVector [max_entries];
  size=max_entries;
  for (int i=0;i<size;i++){
    data[i]=CVector();
  }
}

Table::Table(unsigned int entries, std::istream& input){
  data= new CVector [entries];
  size=entries;
  for (int i=0;i<size;i++){
    data[i]=CVector();
  }
  for(int i=0; i<entries; i++){
    Entry a;
    input>>a;
    put(a);
  }
}

Table::~Table(){
  delete [] data;
}

void Table::put(unsigned int key, std::string data){
  Entry e(key,data);
  put(e);
}

void Table::put(Entry e){
  unsigned int index=hash(e.get_key());
  CVector check=data[index];
  for(int i=0;i<check.size();i++){
    Entry a=check[i];
    if(a.get_key()==e.get_key()){
      check[i]=e;
      data[index]=check;
      return;
    }
  }
    check.push_back(e);
    data[index]=check;
    entries++;
}

std::string Table::get(unsigned int key) const{
  unsigned int index=hash(key);
  CVector gotVector=data[index];
  for(int i=0;i<gotVector.size();i++){
    if(gotVector[i].get_key()==key)
      return gotVector[i].get_data();
  }
  return "";
}

bool Table::remove(unsigned int key){
  unsigned int index=hash(key);
  CVector gotVector=data[index];
  for(int i=0;i<gotVector.size();i++){
    if(gotVector[i].get_key()==key){
      CVector::iterator n=gotVector.begin()+i;
      gotVector.erase(n);
      entries--;
      data[index]=gotVector;
      return true;
    }
  }
  return false;
}
std::ostream& operator<<(std::ostream& out, const Table& t){
  int num=0;
  Entry a[t.entries];
  for(int i=0; i<t.size; i++){
     for(int j=0; j<t.data[i].size(); j++){
      a[num]=t.data[i][j];
      num++;
     }
  }
  mergesort(a,num);
  for(int i=0;i<num;i++){
    out<<a[i].get_key()<<" "<<a[i].get_data()<<endl;
  }
  return out;
}

unsigned int Table::hash(int key) const{
  return (key%size);
}

void mergesort(Entry *a, size_t n){
  size_t n1;
  size_t n2;
  if(n>1){
  n1=n/2;
  n2=n-n1;

  mergesort(a,n1);
  mergesort((a+n1),n2);

  merge(a,n1,n2);
 }
}

void merge(Entry *a, size_t n1, size_t n2){
  Entry *temp;
  size_t copied=0;
  size_t copied1=0;
  size_t copied2=0;
  size_t i;
  
  temp=new Entry[n1+n2];
  while((copied1<n1)&&(copied2<n2)){
    if(a[copied1]<(a+n1)[copied2])
      temp[copied++]=a[copied1++];
    else{
      temp[copied++]=(a+n1)[copied2++];
    }
  }
  
  while(copied1<n1){
    temp[copied++]=a[copied1++];
  }
  while(copied2<n2){
    temp[copied++]=(a+n1)[copied2++];
  }

  for(i=0; i<n1+n2; ++i){
    a[i]=temp[i];
  }

  delete [] temp;
}

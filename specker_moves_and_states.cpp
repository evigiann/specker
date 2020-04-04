#include <iostream>
#include <stdexcept>
using namespace std;

class  Move {
 public:
 Move(int sh, int sc, int th, int tc)
{sourse=sh;
sourcecoins=sc;
target=th;
targetcoins=tc;}

 int getSource() const{ return sourse;}
 int getSourceCoins() const {return sourcecoins;}
 int getTarget() const {return target;}
 int getTargetCoins() const {return targetcoins;}

 friend ostream & operator << (ostream &out, const Move &move);
private:
int sourse,sourcecoins,target,targetcoins;};

ostream& operator <<(ostream &out,const Move &move){
  out<<"takes "<<move.getSourceCoins()<<" coins from heap "<<move.getSource()<<" and puts ";
  if(move.getTargetCoins()==0)return out<<"nothing";
  else return out<<move.getTargetCoins()<<" coins to heap "<<move.getTarget();
}
 class State {
public:
 State(int h, const int c[]){
     heaps=h;
     heap=new int [h];
     for(int i=0;i<h;i++)
       heap[i]=c[i];
    }
 
 ~State(){
   delete heap;
   }

 void next(const Move &move) throw(logic_error){
   if(heaps<=move.getTarget() || heaps<=move.getSource() || move.getTarget()<0 || move.getSource()<0 || heap[move.getSource()]<move.getSourceCoins() || move.getSourceCoins()<=move.getTargetCoins())
   throw logic_error("invalide heap");
   heap[move.getSource()]-=move.getSourceCoins();
   heap[move.getTarget()]+=move.getTargetCoins();
}
 bool winning() const{
   for(int i=0;i<heaps;i++){
     if(heap[i]!=0) return false;
   }
   return true;
 }

 int getHeaps() const{
   return heaps;
 }
 int getCoins(int h) const throw(logic_error){
   if(h<0 || h>=heaps)
     throw logic_error("invalid heap");
   else return heap[h];
 }

 friend ostream & operator << (ostream &out, const State &state);

private:
 int *heap;//heap array 
 int heaps;//number of original heaps
 };

ostream & operator <<(ostream& out,const State& state){
for(int i=0;i<state.heaps-1;i++){
  out<<state.heap[i]<<", ";
}
  out<<state.heap[state.heaps-1];
  return out;
}
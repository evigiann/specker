//specker full
#include <iostream>
#include <stdexcept>
#include <string.h>
using namespace std;

//MOVES AND STATES!!!!!!!!!!!!!!!!!!!!!!!!!
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

//friend function
ostream & operator <<(ostream& out,const State& state){
for(int i=0;i<state.heaps-1;i++){
  out<<state.heap[i]<<", ";
}
  out<<state.heap[state.heaps-1];
  return out;
}



//PLAYERS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Player {
 public:
 Player(const string &n){
   name=n;
 }
 virtual ~Player();
 virtual const string & getType() const = 0;
 virtual Move play(const State &s) = 0;

 friend ostream & operator << (ostream &out, const Player &player);
 
 private:
 string name;
 };

//friend function
 ostream & operator <<(ostream& out, const Player & player){
   out<<player.getType()<<" player "<<player.name;
 return out;
 }


//greedy player
 class GreedyPlayer: public Player {

   private:
   static const string type; 


   public:

   GreedyPlayer(const string &n):Player(n) {}

   ~GreedyPlayer(){}

   const string & getType() const {
     return type;
   }

   Move play (const State &s){
     int heaps=s.getHeaps(),max_coin_heap;
     for(int i=0;i<heaps;i++){ //finding heap with max coins
       if(s.getCoins(i)>s.getCoins(max_coin_heap))
       max_coin_heap=i;
     }
     Move move(max_coin_heap,s.getCoins(max_coin_heap),0,0);
     return move;
   }
 };
 const string GreedyPlayer::type="Greedy";




//spartan player
class SpartanPlayer :public Player {
 
  private:
  static const string type;
 
 
  public:
 
  SpartanPlayer(const string &n):Player(n){}
 
  ~SpartanPlayer(){}
 
  const string & getType() const {
    return type;
  }
 
  Move play (const State &s){
    int heaps=s.getHeaps(),max_coin_heap;
     for(int i=0;i<heaps;i++){ //finding heap with max coins
       if(s.getCoins(i)>s.getCoins(max_coin_heap))
       max_coin_heap=i;
     }
     Move move(max_coin_heap,1,0,0);
     return move;
  }
};
const string SpartanPlayer::type="Spartan";


//sneaky player
  class SneakyPlayer : public Player{
    
    private:
    static const string type;
    
    
    public:
    
    SneakyPlayer(const string &n):Player(n){}
    
    ~SneakyPlayer(){}
    
    const string & getType() const {
    return type;
    }
    
    Move play (const State &s){
    int heaps=s.getHeaps(),min_coin_heap;
     for(int i=0;i<heaps;i++){ //finding heap with min coins
       if(s.getCoins(i)<s.getCoins(min_coin_heap))
       min_coin_heap=i;
     }
     Move move(min_coin_heap,s.getCoins(min_coin_heap),0,0);
     return move;
  }
  };
  const string SneakyPlayer::type="Sneaky";



//righteous player
  class RighteousPlayer : public Player{
    private:
    static const string type;
    int my_fortune;
    
    public:
    
    RighteousPlayer(const string &n): 
    Player(n),my_fortune(0){}
    
    ~RighteousPlayer(){}

    const string & getType() const {
    return type;
    }
    
    Move play (const State &s){
    int heaps=s.getHeaps(),min_coin_heap,max_coin_heap;
     for(int i=0;i<heaps;i++){
       if(s.getCoins(i)<s.getCoins(min_coin_heap))
       min_coin_heap=i;
       if(s.getCoins(i)>s.getCoins(max_coin_heap))
       max_coin_heap=i;
       }
     Move move(max_coin_heap,my_fortune/2,min_coin_heap,my_fortune/2-1);
     my_fortune++;
     return move;
  }
  };
  const string RighteousPlayer::type="Righteous";
  int main(){}
  
 

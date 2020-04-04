#include <iostream>
#include <string.h>
#include "specker_moves_and_states.cpp"

using namespace std;

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
  
 
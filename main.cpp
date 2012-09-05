#include "event.h"
#include <iostream>
using namespace wl;
using namespace std;

struct args{
};

class A{
public:
  Event<A*, args> _event;
};



class B{
public:
  void HandleEvent(const A* sender, args arg){
    cout << "hello world" << endl;
  }
};

int main()
{
  args arg;
  A a;
  B b;
  a._event.Add(&b, &B::HandleEvent);
  a._event += Subscriber(&b, &B::HandleEvent);
  a._event(&a, arg);
  return 0;
}

#include <iostream>

struct Node {
  int value;
  Node *next;
};

void funcB (Node* in1, Node* in2);

Node* funcA (Node* in)
{
  std::cout<<"Final 0"<<std::endl;
  if (in == NULL) return NULL;
  Node* out = NULL;

  if (in->next != NULL) {
    out = funcA (in->next);
    funcB (in, out);
    in->next = NULL;
    std::cout<<"Final 1"<<std::endl;
    return out;
  }
  std::cout<<"Final 2"<<std::endl;
  return in;
}

void funcB (Node* in1, Node* in2)
{
  if (in2->next != NULL) {
    funcB (in1, in2->next);
    return;
  }

  in2->next = in1;
}

int main() {
  Node node1;
  Node node2;
  Node node3;
  Node node4;
  Node node5;

  Node* in=&node1;

  node1.value=1;
  node1.next=&node2;

  node2.value=2;
  node2.next=&node3;

  node3.value=3;
  node3.next=&node4;

  node4.value=4;
  node4.next=&node5;

  node5.value=5;
  node5.next=NULL;

  Node* test=funcA(in);
  std::cout<<test->value<<std::endl;
  for (int i=0; i<4; i++) {
    test=test->next;
    std::cout<<test->value<<std::endl;
  }
}
// Jason Booth   project 2a   boo-2a
// This file defines the node class for the linked list
#ifndef NODE_CLASS
#define NODE_CLASS

#ifndef NULL
#include <cstddef>
#endif  // NULL

#include "card.h"

// linked list node
class node
{
   public:
      card cardStore;  // card held by the node
      node* next;  // next node in the list

      // default constructor, calls card constructor
      node() : cardStore(card()),  next(NULL) {}

      // constructor. initialize nodeValue and next
      node(card inCard, node* nextCard) : cardStore(inCard), next(nextCard)
      {}

      //  Destructor, will delete the next node in the list
      ~node() {
          delete next;
      }

};

#endif   // NODE_CLASS

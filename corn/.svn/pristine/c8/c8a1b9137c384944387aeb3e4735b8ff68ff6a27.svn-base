#include "corn/container/bilist.h"
#include <iostream>
namespace CORN {
//______________________________________________________________________________
Bidirectional_list::Node::Node(Item *i_data)
: Unidirectional_list::Node(i_data)
, prev(0)
{}
//_Node_constructor____________________________________________________________/
Bidirectional_list::Node::~Node()
{ prev = 0;}
//_Node_destructor__________________________________________________2002-11-18_/
Container::Iterator *Bidirectional_list::iterator()                        const
{  Bidirectional_list &this_container = (Bidirectional_list &)(*this);
   Bidirectional_list::Iterator *itor = new Bidirectional_list::Iterator(this_container);
   return itor;
}
//_iterator_________________________________________________________2006-03-22_/
Bidirectional_list::Iterator::Iterator(Bidirectional_list &i_container)
: Unidirectional_list::Iterator(i_container)
{}
//_Iterator_constructor_____________________________________________2003-06-03_/
Bidirectional_list::Iterator::~Iterator()
{}
//_Iterator_destructor______________________________________________2003-06-03_/
Item *  Bidirectional_list::Iterator::prev()
{  Bidirectional_list::Node *bi_node =
      dynamic_cast<Bidirectional_list::Node *>(curr_node);
   curr_node = bi_node ? bi_node->prev : 0;
   return curr_node ? curr_node->get() : 0;
}
//_Iterator::prev___________________________________________________2006-03-22_/
bool Bidirectional_list::Iterator::has_predecessor()                affirmation_
{  Bidirectional_list::Node *bi_node =                                           //180522
      dynamic_cast<Bidirectional_list::Node *>(curr_node);                       //180522
   return bi_node && bi_node->prev;
}
//_Iterator::has_predecessor________________________________________2018-05-15_/
Item *Bidirectional_list::Iterator::detach_current()
{  Bidirectional_list::Node *detach_node =
      dynamic_cast<Bidirectional_list::Node *>
      //180418 (Bidirectional_list::Node *)
      (curr_node);
   Item *detached_item = 0;
   if (detach_node)
   {  detached_item = detach_node->get();
      Bidirectional_list::Node *next_node =
         dynamic_cast<Bidirectional_list::Node *>
         //180418 (Bidirectional_list::Node *)
         (detach_node->next);
      Bidirectional_list::Node *prev_node =
         dynamic_cast<Bidirectional_list::Node *>
         //180418 (Bidirectional_list::Node *)
         (container.find_prev_of(detach_node));
      if (container.get_head() == detach_node)
      {
         container.head = detach_node->next;
         detached_head = true;
      }
      if (prev_node)
          prev_node->next = next_node;
      if (next_node)                   //180418
         next_node->prev = prev_node;  //180418
      curr_node = prev_node;
      if (detach_node == container.tail)
         container.tail = prev_node;
      if (curr_node == 0)
         curr_node = container.head;
      detach_node->next = 0;
      detach_node->set(0);  // To prevent deletion of the node data
      delete detach_node;
      container.set_modified(true);
   }
   return detached_item;
}
//_detach_current___________________________________________________2018-04-18_/
Bidirectional_list::Bidirectional_list(bool unique_keys_)                        //160615
:Unidirectional_list(unique_keys_)                                               //160615
,moving_forward(true)
{}
//_Bidirectional_list_constructor _____________________________________________/
void Bidirectional_list::append_node(Node *node)
{  //  Prev must be set to Tail before calling unilist functions because they reset tail to new element. 970515
   node->prev = (Node*)tail;
   if (!head) node->prev = 0;
   Unidirectional_list::append_node(node);
}
//_append_node______________________________________________________1998-02-06_/
Item *Bidirectional_list::append(Item *new_element)               appropriation_
{
   Item *appropriatable_element = delete_unappropriatabled(new_element);         //170522_161024
   if (appropriatable_element)                                                   //161024
      append_node(new Node(appropriatable_element));
   return appropriatable_element;                                                //170522_970930
}
//_append______________________________________________________________________/
Item *Bidirectional_list::prepend(Item *new_element)              appropriation_
{
   Item *appropriatable_element = delete_unappropriatabled(new_element);         //161024
   if (appropriatable_element)                                                   //161024
   {
   Node *node = new Node(appropriatable_element);
   if (!tail) node->prev = 0;
   if (head)  ((Node*)(head))->prev = node;
   Unidirectional_list::prepend_node(node);                                      //110821_060317
   node->prev = 0;
   }
   return appropriatable_element;                                                //170522_161024_980206
}
//_prepend_____________________________________________________________________/
Item *Bidirectional_list::add_sorted
   (Item *new_element
   ,Ordering ordering)                                            appropriation_ //971211
{  if (!new_element) return 0 ;
   Item *appropriatable_element = append(new_element);                           //170522
   sort(ordering);
   return appropriatable_element;                                                //170522
}
//_add_sorted__________________________________________________________________/
Item *Bidirectional_list::pop_at_head()
{  Item *popped_data_element = Unidirectional_list::pop_at_head();
   if (head)
      ((Node*)head)->prev = 0;
   return(popped_data_element);
}
//_pop_at_head_________________________________________________________________/
void Bidirectional_list::fixup_pointers()
{  if (head)
      ((Node *)head)->prev = 0;
   for (Node *node = (Node *)head; node; node = (Node *)node->next)              //980218
      if (node->next)
      {  Node *next = (Node *)node->next;                                        //030806
         next->prev = node;
      } else tail = node;
}
//_fixup_pointers__________________________________________________1998-02-06__/
bool Bidirectional_list::remove(Item *element_to_remove)
{  if (!element_to_remove) return false;                                         //170701_970403
   bool removed = Unidirectional_list::remove(element_to_remove);                //170701
   fixup_pointers();
   return removed;                                                               //170701
}
//_remove______________________________________________________________________/
Item *Bidirectional_list::find_matching_reverse
(const Item &item_to_match
,bool from_end) const                                                            //990222
{  Container::Iterator *iter = iterator();
   Item *found_item = 0;
   for (Item *local_curr =  (from_end ? iter->last() : iter->current())
      ; !found_item && local_curr
      ; local_curr = iter->prev())
      if (local_curr->compare(item_to_match) == 0)
         found_item = local_curr;
   return found_item;
}
//_find_matching_reverse____________________________________________2003-07-09_/
void Bidirectional_list::swap_elements
   (Node *element1,
    Node *element2)
{  Item *hold_element = element1->get();
   element1->set(element2->get());
   element2->set(hold_element);
}
//_swap_elements_______________________________________________________________/
void Bidirectional_list::sort(Ordering ordering)
{  int sorted = 0;
   Node *curr_node;
   Node *next_node;
   while (!sorted)
   {  sorted = 1;
      for (curr_node = (Node *)(head)
        ; curr_node
        ; curr_node = (Node *)(curr_node->next))
      {  next_node = (Node *)(curr_node->next);
         if (next_node)
         {
         if (((ordering == ASCENDING) &&
              (is_greater_than(curr_node->get()->compare(*next_node->get()))))||
             ((ordering == DESCENDING) &&                                        //971214
              (is_less_than(curr_node->get()->compare(*next_node->get())))))
         {  swap_elements(curr_node,next_node);
            sorted = 0;
         }
         }
      }
   }
}
//_sort________________________________________________________________________/
nat32 Bidirectional_list::write(std::ostream &strm)                modification_ //150728
{  nat32 written = 0;                                                            //150728
   if (moving_forward) written = Container::write(strm);                         //150728_130514
   else
      for (Item *element = (Item *)tail                                          //990824
          ; element
          ; element = (Item *)find_prev_of(element))                             //990824
         written += element->write(strm);                                        //150728
   return written;                                                               //150728
}
//_write_______________________________________________________________________/
} //  namespace CORN end


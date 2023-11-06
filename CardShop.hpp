/* Kenny Yu
Date: 4/4/23
Description: This is the interface of CardShop class
*/

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

  /** @param: the type of comparison in function form
   * @param: the string of what is being sorted
   * @post: sorts the list's key by the comparator
    */
  template<typename Comparator>
  int bubbleSort(Comparator comp, std::string key);

  /**
 * @param: the type of comparison used to sort
 * @param: the string key of what is being sorted
 * @post: sorts the list by the comparison using Insertion Sort 
 */
template<typename Comparator>
int insertionSort(Comparator comp, std::string key);

/**
 * @param: the type of comparison used to sort
 * @param: the string key of what is being sorted
 * @post: sorts the list by the comparison using Quick Sort
 */
template<typename Comparator>
int quickSort(Comparator comp, std::string key);

/**
 @param: The type of comparison that is used to sort the list
 @param: The string of what value types are being sorted
 @param: The start of the list that is being QuickSorted
 @param: The end of the list that is being QuickSorted
 @param: A counter that is from that increments during swaps
 @post: Paritions the list into 2 parts, on that is less than pivot and one that is greater than pivot
*/
template<typename Comparator>
int partition(Comparator comp, std::string key, int start, int end, int& swap_counter);

/**
 @param: The type of comparison that is used to sort the list
 @param: The string of what value types are being sorted
 @param: The start of the list that is being QuickSorted
 @param: The end of the list that is being QuickSorted
 @param: A counter that is from that increments during swaps
 @post: Recursive function that calls itself and parititon to sort the list
 
*/
template<typename Comparator>
int RecursiveQuickSort(Comparator comp, std::string key, int start, int end,int &swap_counter);
/**
 @param: the type of comparison used to sort
 @param: the string key of what is being sorted
 @post: sorts the list by the comparison using Merge Sort
 */
template<typename Comparator>
int mergeSort(Comparator comp, std::string key);

/**
 @param: the type of comparison used to sort
 @param: the position of the beginning of the first half of the list
 @param: the position of the end of the first half of the list
 @param: the position of the beginning of the second half of the list
 @param: the position of the end of the second half of the list
 @param: the string of the value type that is being sorted
 @post: this merge the 2 partitioned lists based on the positions given
*/

template<typename Comparator>
int merge(Comparator comp, int first_half_start, int first_half_end, int second_half_start, int second_half_end, std::string key);

/**
 @param: the type of comparison used to sort
 @param: the position of the beginning of the list
 @param: the position of the end of the list
 @param: the string of the value type that is being sorted
 @post: splits the lists into 2 halfs
*/
template<typename Comparator>
void RecursiveMergeSort (Comparator comp,int start, int end, std::string key);
};
#endif
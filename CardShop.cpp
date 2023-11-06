/* Kenny Yu
Date: 4/4/23
Description: This is the implementation of CardShop class
*/

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (unsigned int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (unsigned int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (unsigned int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

 /** @param: the type of comparison in function form
   * @param: the string of what is being sorted
   * @post: sorts the list's key by the comparator withj Bubble Sort
    */
template<typename Comparator>
  int CardShop::bubbleSort(Comparator comp, std::string key){
  int counter = 0;
  int items = item_count_;
  while(items > 1){
    for(int i = 1 ; i < items; i++){
      if(key == "atk"){
        if(comp(getItem(i)->getAtk(),getItem(i-1)->getAtk())){
          swap(i-1,i);
          counter++;
        }
      }
      else if(key == "def"){
        if(comp(getItem(i)->getDef(),getItem(i-1)->getDef())){
          swap(i-1,i);
          counter++;
        }
      }
    }
    items--;
  }
  return counter;
}

/**
 * @param: the type of comparison used to sort
 * @param: the string key of what is being sorted
 * @post: sorts the list by the comparison using Insertion Sort 
 */
template<typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key){
  int swap_counter = 0;
  for(unsigned int i = 1 ; i < item_count_;i++){
    if(key == "atk"){
      if(comp(getItem(i)->getAtk(),getItem(i-1)->getAtk())){
        swap(i-1,i);
        swap_counter++;
        for(int j = i - 1; j > 0; j--){
          if(comp(getItem(j)->getAtk(),getItem(j-1)->getAtk())){
            swap(j,j-1);
            swap_counter++;
          }
        }
      }
    }
    else if (key == "def"){
      if(comp(getItem(i)->getDef(),getItem(i-1)->getDef())){
        swap(i-1,i);
        swap_counter++;
        for(int j = i - 1; j > 0; j--){
          if(comp(getItem(j)->getDef(),getItem(j-1)->getDef())){
            swap(j-1,j);
            swap_counter++;
          }
        }
      }
    }
  }
  return swap_counter;
}
/**
 * @param: the type of comparison used to sort
 * @param: the string key of what is being sorted
 * @post: sorts the list by the comparison using Quick Sort
 */
template<typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key){
  int swaps = 0;
  RecursiveQuickSort(comp,key,0,item_count_-1,swaps);
  return swaps;
}

/**
 @param: The type of comparison that is used to sort the list
 @param: The string of what value types are being sorted
 @param: The start of the list that is being QuickSorted
 @param: The end of the list that is being QuickSorted
*/
template<typename Comparator>
int CardShop::partition(Comparator comp, std::string key, int start, int end, int& swap_counter){
  int index = 0; 
  if(key == "atk"){
    int pivot = getItem(start)->getAtk();
    for(int i = start + 1; i <= end; i++){
      if(comp(getItem(i)->getAtk(),pivot) || pivot == getItem(i)->getAtk()){
        index++;
      }
    }
    swap(start,start+ index);
    swap_counter++;
    int i = start, j = end;
    while(i < start+index && j > start+index){
      while(comp(getItem(i)->getAtk(),pivot) || pivot == getItem(i)->getAtk()){
        i++;
      }
      while(comp(pivot,getItem(j)->getAtk())){
        j--;
      }
      if(i < start+index && j > start+index){
        swap(i++,j--);
        swap_counter++;
      }
    }
    return start+index;
  }
  if(key == "def"){
    int pivot = getItem(start)->getDef();
    for(int i = start + 1; i <= end; i++){
      if(comp(getItem(i)->getDef(),pivot) || pivot == getItem(i)->getDef()){
        index++;
      }
    }
    swap(start,start+ index);
    swap_counter++;

    int i = start, j = end;
    while(i < start+index && j > start+index){
      while(comp(getItem(i)->getDef(),pivot) || pivot == getItem(i)->getDef()){
        i++;
      }
      while(comp(pivot,getItem(j)->getDef())){
        j--;
      }
      if(i < start+index && j > start+index){
        swap(i,j);
        swap_counter++;
      }
    }
    return start+index;
  }
  return 0;
  
}

/**
 @param: The type of comparison that is used to sort the list
 @param: The string of what value types are being sorted
 @param: The start of the list that is being QuickSorted
 @param: The end of the list that is being QuickSorted
 @post: Sorts the list using quicksort
*/
template<typename Comparator>
int CardShop::RecursiveQuickSort(Comparator comp, std::string key,int start, int end, int &swap_counter){
  if(start >= end){
    return swap_counter;
  }
  int index = partition(comp, key,start,end, swap_counter);
  RecursiveQuickSort(comp,key, start,index-1, swap_counter); 
  RecursiveQuickSort(comp,key, index+1, end, swap_counter);
  return swap_counter;
}
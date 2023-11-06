#include "DoublyLinkedList.hpp"
#include "CardShop.cpp"
#include <string>

int main(){
    CardShop shop("cards.csv");
    std::cout << shop.quickSort(std::less<int>{},"atk") << std::endl;
    shop.display();
}
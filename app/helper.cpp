#include "helper.hpp"



  
  void zeroAndNullOutArrs(int* bucketSizes, Node** ht, int numBuckets){
    for(int i = 0; i < numBuckets; i++){
      ht[i] = nullptr;
      bucketSizes[i] = 0;
    }
  }


  
  
  void deleteBucketsAndHt(int* bucketSizes, Node** ht, int numBuckets){
    for(int x = 0; x < numBuckets; x++){
      Node* head = ht[x];
      Node* nxt;
      while(head != nullptr){
        nxt = head->next;
        delete head;
        head = nxt;
      }
      ht[x] = nullptr;
    }
    delete[] ht;
    delete[] bucketSizes;
  }


 

  
  
void copyBucketsAndHt(Node** target, Node** source, int* bucketSizes, int targetSize, int sourceSize, std::function<unsigned int(const std::string&)> hf){
    Node* currentHead;
    Node* temp;
    Node* start;
    int index;
    
    for(int i=0; i < sourceSize; i++){
      currentHead = source[i];
      while(currentHead != nullptr){
         
        temp = new Node;
        temp->key = currentHead->key;
        index = hf(currentHead->key) % targetSize;
        temp->value = currentHead->value;
        temp->next = nullptr;
        start = target[index];
      
        if(start == nullptr){
          target[index] = temp;
        }
        else{
          Node* prev = start;
          while(prev->next != nullptr){
            prev = prev->next;
          }
        prev->next = temp;
        }
      currentHead = currentHead->next;
      bucketSizes[index] += 1;
      }
    }
    
  }

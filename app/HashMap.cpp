#include "HashMap.hpp"
#include "Node.hpp"
#include "helper.hpp"
#include <iostream>




namespace{
  //uses username as key
  unsigned int hf(const std::string& key){
    int x = 31;
    int hash = 0;
    for(int i = 0; i < key.size(); i++){
      hash = x * hash + int(key[i]);
    }
    return hash;
  }
  std::function<unsigned int(const std::string&)> defaultHashFunc = hf;
}






HashMap::HashMap()
  : ht{new Node*[HashMap::initialBucketCount]},
    bucketSizes{new int[HashMap::initialBucketCount]},
    kvpairs{0},
    numBuckets{HashMap::initialBucketCount},
    debug{false},
    hasher{defaultHashFunc}
{
  zeroAndNullOutArrs(bucketSizes, ht, numBuckets);
}




HashMap::HashMap(HashFunction hasher)
  : ht{new Node*[HashMap::initialBucketCount]},
    bucketSizes{new int[HashMap::initialBucketCount]},
    kvpairs{0},
    numBuckets{HashMap::initialBucketCount},
    debug{false},
    hasher{hasher}
{
  zeroAndNullOutArrs(bucketSizes, ht, numBuckets);
}





HashMap::~HashMap()
{
  deleteBucketsAndHt(bucketSizes, ht, numBuckets);
}




HashMap::HashMap(const HashMap& hm)
  : ht{new Node*[hm.numBuckets]},
    bucketSizes{new int[hm.numBuckets]},
    kvpairs{hm.kvpairs},
    numBuckets{hm.numBuckets},
    debug{hm.debug},
    hasher{hm.hasher}
{
  zeroAndNullOutArrs(bucketSizes, ht, numBuckets);
  copyBucketsAndHt(ht, hm.ht, bucketSizes, numBuckets, hm.numBuckets, hm.hasher);
}




HashMap& HashMap::operator=(const HashMap& hm)
{
  
  if(this != &hm){
    Node** newHt = new Node*[hm.numBuckets];
    int* newBucketSizes = new int[hm.numBuckets];
    
    zeroAndNullOutArrs(newBucketSizes, newHt, hm.numBuckets);
    copyBucketsAndHt(newHt, hm.ht,newBucketSizes, numBuckets, hm.numBuckets, hm.hasher);
    deleteBucketsAndHt(bucketSizes, ht, numBuckets);
    
    ht = newHt;
    bucketSizes = newBucketSizes;
    kvpairs = hm.kvpairs;
    debug = hm.debug;
    numBuckets = hm.numBuckets;
    hasher = hm.hasher;
  }

  return *this;
}


void HashMap::clearAll(){
  Node** newHt = new Node*[numBuckets];
  int* newBucketSizes = new int[numBuckets];
  zeroAndNullOutArrs(newBucketSizes, newHt, numBuckets);
  deleteBucketsAndHt(bucketSizes, ht, numBuckets);

  ht = newHt;
  bucketSizes = newBucketSizes;
  kvpairs = 0;

}




void HashMap::add(const std::string& key, const std::string& value)
{
  if(loadFactor() >= .8){
    resizeBuckets();
  }
  
    Node* temp = new Node;
    temp->key = key;
    temp->value = value;
    temp->next = nullptr;
    unsigned int index = hasher(key) % numBuckets;
    Node* start = ht[index];

    if(start == nullptr){
      ht[index] = temp;
    }
    else{
      Node* prev = start;
      while(prev->next != nullptr){
      prev = prev->next;
    }
    prev->next = temp;
  }
  
  kvpairs += 1;
  bucketSizes[index] += 1;
}




void HashMap::remove(const std::string& key)
{
  unsigned int index = hasher(key) % numBuckets;
  
  Node* head = ht[index];
  Node* prev = head;

  while(head != nullptr and head->key != key){
    prev = head;
    head = head->next;
  }
  
  if(head == nullptr){
    return; //no matching key found
  }

  kvpairs -= 1;
  bucketSizes[index] -= 1;
  
  if(head == ht[index]){
    ht[index] = head->next; //first key matches
  }else{
    prev->next = head->next;//other key than first matches
  }
  delete head;
}




bool HashMap::contains(const std::string& key) const
{
  unsigned int index = hasher(key) % numBuckets;
  Node* head = ht[index];
  while(head != nullptr){
    if(head->key == key){
      return true;
    }
    head = head->next;
  }
  return false;
}




std::string HashMap::value(const std::string& key) const
{
  std::string empty = "";
  unsigned int index = hasher(key) % numBuckets;
  Node* head = ht[index];
  while(head != nullptr){
    if(head->key == key){
      return head->value;
    }
    head = head->next;
  }
  return empty;
}




bool HashMap::debugging() const
{
  return debug;
}




void HashMap::setMode(bool debugMode)
{
  debug = debugMode;
}





unsigned int HashMap::size() const
{
  return kvpairs;
}




unsigned int HashMap::bucketCount() const
{
  return numBuckets;
}




double HashMap::loadFactor() const
{
  return double(kvpairs) / double(numBuckets);
}




int* HashMap::getBucketSizesArr()
{
  return bucketSizes;
}




void HashMap::resizeBuckets()
{
  unsigned int newNumBuckets = numBuckets * 2 + 1;
  Node** newHt = new Node*[newNumBuckets];
  int* newBucketSizes = new int[newNumBuckets];
  
  zeroAndNullOutArrs(newBucketSizes, newHt, newNumBuckets);
  copyBucketsAndHt(newHt, ht, newBucketSizes, newNumBuckets, numBuckets, hasher);
  deleteBucketsAndHt(bucketSizes, ht, numBuckets);

  bucketSizes = newBucketSizes;
  numBuckets = newNumBuckets;
  ht = newHt;
}




unsigned int HashMap::maxBucketSize() const
{
  unsigned int largest = 0;
  
  for(int i = 0; i < numBuckets; i++){
    if(bucketSizes[i] > largest){
      largest = bucketSizes[i];
    }
  }
  return largest;
}


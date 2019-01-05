#include "Node.hpp"
#include <iostream>
#ifndef HELPER_HPP
#define HELPER_HPP

void zeroAndNullOutArrs(int* bucketSizes, Node** ht, int numBuckets);

void deleteBucketsAndHt(int* bucketSizes, Node** ht, int numBuckets);

void copyBucketsAndHt(Node** target, Node** source, int* bucketSizes, int targetSize, int sourceSize, std::function<unsigned int(const std::string&)> hf);



#endif

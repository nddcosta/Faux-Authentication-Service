// HashMapTests.cpp
//
// ICS 45C Fall 2018
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"



TEST(TestHashMap, intialValuesInHashMap){
  HashMap hm;
  ASSERT_FALSE(hm.debugging());
  ASSERT_EQ(hm.bucketCount(), 10);
  ASSERT_EQ(hm.size(), 0);
  ASSERT_EQ(hm.maxBucketSize(), 0);
  int* bucketSizes = hm.getBucketSizesArr();
  for(int i = 0; i < hm.bucketCount(); i++){
    ASSERT_EQ(bucketSizes[i], 0);
  }
}


TEST(TestHashMap, hashmapAssignmentCopy){
  HashMap hm;
  HashMap x;
  hm.add("Hello", "ok");
  hm.add("Ok", "mmm");
  hm.add("kk", "jfjf");
  hm.setMode(true);

  x = hm;
  
  ASSERT_EQ(x.size(), hm.size());
  ASSERT_EQ(x.debugging(), hm.debugging());
  ASSERT_EQ(x.bucketCount(), hm.bucketCount());
  ASSERT_EQ(x.maxBucketSize(), hm.maxBucketSize());
  ASSERT_TRUE(x.contains("Hello"));
  ASSERT_TRUE(x.contains("Ok"));
  ASSERT_TRUE(x.contains("kk"));
  
}



TEST(TestHashMap, debugModeIntiallyAndSet){
  HashMap hm;
  ASSERT_FALSE(hm.debugging());
  hm.setMode(true);
  ASSERT_TRUE(hm.debugging());
}


TEST(TestHashMap, resizeNumBucketsWhenLoadFactorTooHigh){
  HashMap hm;
  hm.add("1", "value1");
  hm.add("2", "value22");
  hm.add("3", "value23");
  hm.add("4", "value24");
  hm.add("5", "value25");
  hm.add("6", "value26");
  hm.add("7", "value27");
  hm.add("8", "value8");
  ASSERT_EQ(hm.bucketCount(), 10);
  hm.add("9", "value43");
  ASSERT_EQ(hm.bucketCount(), 21);
  hm.add("10", "value33");
  hm.add("11", "value1");
  hm.add("12", "value22");
  hm.add("13", "value23");
  hm.add("14", "value24");
  hm.add("15", "value25");
  hm.add("16", "value26");
  hm.add("17", "value27");
  hm.add("18", "value8");
  hm.add("19", "value43");
  ASSERT_EQ(hm.bucketCount(), 43);
  hm.add("20", "value1");
  hm.add("21", "value22");
  hm.add("22", "value23");
  hm.add("23", "value24");
  hm.add("24", "value25");
  hm.add("25", "value26");
  hm.add("26", "value27");
  hm.add("27", "value8");
  hm.add("28", "value43");
}

TEST(TestHashMap, newBucketArrayAfterResizeEqual){
  HashMap hm;
  
  hm.add("1", "value1");
  hm.add("2", "value22");
  hm.add("3", "value23");
  hm.add("4", "value24");
  hm.add("5", "value25");
  hm.add("6", "value26");
  hm.add("7", "value27");
  hm.add("8", "value8");
  int sum1 = 0;
  int* bucketSizes1 = hm.getBucketSizesArr();
  for(int i = 0; i < hm.bucketCount(); i++){
    sum1 += bucketSizes1[i];
  }
  sum1 += 1;
  hm.add("9", "value43");
  int sum2 = 0;
  int* bucketSizes2 = hm.getBucketSizesArr();
  for(int x = 0; x <hm.bucketCount(); x++){
    sum2 += bucketSizes2[x];
  }

  ASSERT_EQ(sum1,sum2);
 
}

TEST(TestHashMap, hashTableCopiedAfterResize){
  HashMap hm;
  
  hm.add("1", "value1");
  hm.add("2", "value22");
  hm.add("3", "value23");
  hm.add("4", "value24");
  hm.add("5", "value25");
  hm.add("6", "value26");
  hm.add("7", "value27");
  hm.add("8", "value8");
  hm.add("9", "value43");

  ASSERT_TRUE(hm.contains("1"));
  ASSERT_TRUE(hm.contains("2"));
  ASSERT_TRUE(hm.contains("3"));
  ASSERT_TRUE(hm.contains("4"));
  ASSERT_TRUE(hm.contains("5"));
  ASSERT_TRUE(hm.contains("6"));
  ASSERT_TRUE(hm.contains("7"));
  ASSERT_TRUE(hm.contains("8"));
  hm.remove("8");
  ASSERT_TRUE(hm.contains("9"));
  ASSERT_FALSE(hm.contains("8"));
}



TEST(TestHashMap, sizeChangingWhenAddandRemove){
  HashMap hm;
  hm.add("Ok", "yy");
  ASSERT_EQ(hm.size(), 1);
  hm.add("hello", "ok");
  ASSERT_EQ(hm.size(), 2);
  hm.remove("Ok");
  ASSERT_EQ(hm.size(), 1);
  hm.remove("hello");
  ASSERT_EQ(hm.size(), 0);
}





TEST(TestHashMap, removeItemsNotInHashMap)
{
  HashMap hm;
  hm.add("OK", "yeas");
  hm.add("hello", "value");
  hm.remove("Not in hm");
  hm.remove("Also not in hm");
}





TEST(TestHashMap, add8ItemsToHashMap)
{
  HashMap hm;
  hm.add("This", "value1");
  hm.add("Is", "value2");
  hm.add("A", "value3");
  hm.add("Test", "value4");
  hm.add("For", "value5");
  hm.add("Adding", "value6");
  hm.add("10", "value7");
  hm.add("Different", "value8");


  ASSERT_TRUE(hm.contains("This"));
  ASSERT_TRUE(hm.contains("Is"));
  ASSERT_TRUE(hm.contains("A"));
  ASSERT_TRUE(hm.contains("Test"));
  ASSERT_TRUE(hm.contains("For"));
  ASSERT_TRUE(hm.contains("Adding"));
  ASSERT_TRUE(hm.contains("10"));
  ASSERT_TRUE(hm.contains("Different"));
  ASSERT_FALSE(hm.contains("NOT IN HM"));
}


TEST(TestHashMap, checkValueForKeyNotInHashMap)
{
  HashMap hm;
  hm.add("This", "value");
  hm.add("OK", "value2");
  ASSERT_EQ(hm.value("Not in hm"), "");
  ASSERT_EQ(hm.value("ok"), "");
  ASSERT_EQ(hm.value("this"), "");

}


TEST(TestHashMap, check8ValuesInHashMap)
{
  HashMap hm;
  hm.add("T", "value1");
  hm.add("Is", "value2");
  hm.add("A", "value3");
  hm.add("Tst", "value4");
  hm.add("Fr", "value5");
  hm.add("Adng", "value6");
  hm.add("10", "value7");
  hm.add("DI", "value8");
;

  ASSERT_EQ(hm.value("T"), "value1");
  ASSERT_EQ(hm.value("Is"), "value2");
  ASSERT_EQ(hm.value("A"), "value3");
  ASSERT_EQ(hm.value("Tst"), "value4");
  ASSERT_EQ(hm.value("Fr"), "value5");
  ASSERT_EQ(hm.value("Adng"), "value6");
  ASSERT_EQ(hm.value("10"), "value7");
  ASSERT_EQ(hm.value("DI"), "value8");

  
}


TEST(TestHashMap, remove8ItemsFromHashMap)
{
  HashMap hm;
  hm.add("This", "value1");
  hm.add("Is", "value2");
  hm.add("A", "value3");
  hm.add("Test", "value4");
  hm.add("For", "value5");
  hm.add("Adding", "value6");
  hm.add("10", "value7");
  hm.add("Different", "value8");

  hm.remove("This");
  hm.remove("Is");
  hm.remove("A");
  hm.remove("Test");
  hm.remove("For");
  hm.remove("Adding");
  hm.remove("10");
  hm.remove("Different");

  ASSERT_FALSE(hm.contains("This"));
  ASSERT_FALSE(hm.contains("Is"));
  ASSERT_FALSE(hm.contains("A"));
  ASSERT_FALSE(hm.contains("Test"));
  ASSERT_FALSE(hm.contains("For"));
  ASSERT_FALSE(hm.contains("Adding"));
  ASSERT_FALSE(hm.contains("10"));
  ASSERT_FALSE(hm.contains("Different"));


}





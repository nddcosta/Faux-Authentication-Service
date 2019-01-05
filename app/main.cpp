#include <iostream>
#include <sstream>
#include "HashMap.hpp"



int parseLine(HashMap& hm){
  std::string command;
  std::string param1;
  std::string param2;
  std::string temp;
  std::string line;
  
  std::getline(std::cin, line);
  std::istringstream ss(line);
  
  ss >> command;
  
  if(command == "DEBUG"){
    ss >> param1 >> temp;

    if(temp != "" or param1 == ""){
      std::cout <<"INVALID" << std::endl;
      
    }else if(param1 == "ON"){
   
      if(hm.debugging()){
        std::cout << "ON ALREADY" << std::endl;
      }else{
        hm.setMode(true); // debugging mode off
        std::cout << "ON NOW" <<std::endl;
      }
      
    }else if(param1 == "OFF"){
      
      if(hm.debugging()){
        hm.setMode(false);
        std::cout << "OFF NOW" << std::endl;
      }else{
        std::cout << "OFF ALREADY" << std::endl;
      }
      
    }else{
      std::cout << "INVALID" << std::endl;
    }}

 else if(command == "BUCKET"){
    ss >> param1 >> temp;
    
    if(temp == "" and param1 == "COUNT" and hm.debugging()){
      std::cout << hm.bucketCount() << std::endl;

    }else{
      std::cout<< "INVALID" << std::endl;
    }
 }
 
 
else if(command == "LOAD"){
    ss >> param1 >> temp;

    if(temp == "" and param1 == "FACTOR" and hm.debugging()){
      std::cout << hm.loadFactor() <<std::endl;
    }else{
      std::cout << "INVALID" << std::endl;
    }
 }

    
else if(command == "MAX"){
    ss >> param1 >> param2 >> temp;

    if(temp == "" and param1 == "BUCKET" and param2 == "SIZE" and hm.debugging()){
      std::cout << hm.maxBucketSize() << std::endl;
    }else{
    std::cout<< "INVALID" << std::endl;
    }
 }
  

  

  else if(command == "CREATE"){

    ss >> param1 >> param2 >> temp;
    
    if(temp != "" or param1 == "" or param2 == ""){
      std::cout << "INVALID" << std::endl;
    }
    else if(!hm.contains(param1)){
      hm.add(param1, param2);
      std::cout << "CREATED" << std::endl;
    }
    else{
      std::cout << "EXISTS"<<std::endl;
    }
  }
  
    

   else if(command == "LOGIN"){
    
      ss >> param1 >> param2 >> temp;
      
      if(temp != "" or param1 == ""){
        std::cout << "INVALID" << std::endl;       
      }
      else if(param2 != ""){
        if(hm.value(param1) == param2){
          std::cout << "SUCCEEDED" <<std::endl;
        }
        else{
          std::cout << "FAILED"<<std::endl;
        }
      }
      else if(param2 == "" and param1 == "COUNT" and hm.debugging()){
        std::cout << hm.size() << std::endl;
      }
      else{
        std::cout << "INVALID"<< std::endl;
      }
   }

      
   else if(command == "REMOVE"){
    
    ss >> param1 >> temp;
    
    if(temp != "" or param1 == ""){
      std::cout << "INVALID" << std::endl;
    }
    else if(hm.contains(param1)){
      hm.remove(param1);
      std::cout << "REMOVED"<<std::endl;
    }else{
      std::cout << "NONEXISTENT"<<std::endl;
    }
   }
    
 else if(command == "CLEAR"){
    
    ss >> temp;
    
    if(temp != ""){
      std::cout << "INVALID" << std::endl;
    }else{
      hm.clearAll();
      std::cout << "CLEARED" << std::endl;
    }
    
 }else if(command == "QUIT"){

    ss >> temp;
    
    if(temp != ""){
      std::cout << "INVALID" << std::endl;
    }
    else{
      return 0; //EXIT PROGRAM
    }
    
 }
  else{
    std::cout << "INVALID" << std::endl;
  }
  return 1;
}


void run(){
  HashMap hm;
  while(true){
    if(!parseLine(hm)){
      break;
    }
  }
}



int main()
{
  run();
  return 0;
}


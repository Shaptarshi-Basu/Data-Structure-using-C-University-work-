// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"
#include <algorithm>
// For debug
#include <iostream>
using std::cerr;
using std::endl;

#include <random>
using std::minstd_rand;
using std::uniform_int_distribution;

minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(string name, PersonID id, string title, Salary salary)
{
  struct Person p;
  p.name = name;
  p.salary = salary;
  p.title=title;
  p.hasBoss=false;  
  persons.insert ( std::pair<PersonID,Person>(id,p) );
  personOrderName.insert ( std::pair<string,PersonID>(name,id));
  personOrderSalary.insert ( std::pair<Salary,PersonID>(salary,id));
  sortedOrderIndicatorName=false;
  sortedOrderIndicatorSalary=false;

}

void Datastructure::remove_person(PersonID id)
{
     vector<PersonID> updatedChildren;
  it=persons.find(id);
  if ( persons.find(id) != persons.end() ) {
     PersonID removePersonID=it->first;
     Person removePerson=it->second;
     if(removePerson.hasBoss){
     PersonID bossID=removePerson.boss;
     vector<PersonID> child=removePerson.children;
     for (std::vector<PersonID>::iterator iter = child.begin(); iter != child.end(); ++iter){
       (((persons.find(bossID))->second).children).push_back(*iter);
       ((persons.find(*iter))->second).boss=bossID;
      }
     for (std::vector<PersonID>::iterator iter = (((persons.find(bossID))->second).children).begin(); iter != (((persons.find(bossID))->second).children).end(); ++iter){
       if(*iter!=removePersonID){
         updatedChildren.push_back(*iter);
       }
      }
      ((persons.find(bossID))->second).children=updatedChildren;
     }
     else{
      vector<PersonID> child=removePerson.children;
      for (std::vector<PersonID>::iterator iter = child.begin(); iter != child.end(); ++iter){
       ((persons.find(*iter))->second).hasBoss=false;
       }
      }
     for(std::map<string,PersonID>::iterator iter = personOrderName.begin(); iter != personOrderName.end(); ++iter)
       {
           if((iter->second)==removePersonID){
             personOrderName.erase(iter);
             break;  
       }            
       }
      for(std::map<Salary,PersonID>::iterator iter = personOrderSalary.begin(); iter != personOrderSalary.end(); ++iter)
       {
           if((iter->second)==removePersonID){
             personOrderSalary.erase(iter);
             break;  
       }            
       }
      persons.erase(removePersonID);
      sortedOrderIndicatorName=false;
      sortedOrderIndicatorSalary=false;
   }

}

string Datastructure::get_name(PersonID id)
{
    it=persons.find(id);
   if(persons.find(id) != persons.end() ) {
    Person p=it->second;
    return p.name;
    }
}

string Datastructure::get_title(PersonID id)
{
    it=persons.find(id);
    Person p=it->second;
    return p.title;
}

Salary Datastructure::get_salary(PersonID id)
{
    it=persons.find(id);
    Person p=it->second;
    return p.salary;
}

vector<PersonID> Datastructure::find_persons(string name)
{
    vector<PersonID> personName;    
    personsSorted.clear();    
    for(std::unordered_map<PersonID,Person>::iterator it = persons.begin(); it != persons.end(); ++it)
    {
        if((it->second).name==name){
          personsSorted.insert ( std::pair<PersonID,Person>(it->first,it->second));  
    }           
    }
    for(std::map<PersonID,Person>::iterator it = personsSorted.begin(); it != personsSorted.end(); ++it)
    {
        personName.push_back(it->first);
    
    }
    return personName;

}

vector<PersonID> Datastructure::personnel_with_title(string title)
{
  vector<PersonID> personTitle;
    personsSorted.clear();    
    for(std::unordered_map<PersonID,Person>::iterator it = persons.begin(); it != persons.end(); ++it)
    {
        if((it->second).title==title){
          personsSorted.insert ( std::pair<PersonID,Person>(it->first,it->second));  
    }           
    }
    for(std::map<PersonID,Person>::iterator it = personsSorted.begin(); it != personsSorted.end(); ++it)
    {
        personTitle.push_back(it->first);
    
    }
    
    return personTitle;
}

void Datastructure::change_name(PersonID id, string new_name)
{   
    it=persons.find(id);
    (it->second).name=new_name;
        for(std::map<string,PersonID>::iterator ite = personOrderName.begin(); ite != personOrderName.end(); ++ite)
        {
      if(ite->second==id){
             personOrderName.insert ( std::pair<string,PersonID>(new_name,id) ); 
             personOrderName.erase(ite);
             sortedOrderIndicatorName=false;
  
             break;  
      }
        }
}

void Datastructure::change_salary(PersonID id, Salary new_salary)
{
    it=persons.find(id);
    (it->second).salary=new_salary; 
    for(std::map<Salary,PersonID>::iterator ite = personOrderSalary.begin(); ite != personOrderSalary.end(); ++ite)
        {
      if(ite->second==id){          
            personOrderSalary.insert ( std::pair<Salary,PersonID>(new_salary,id) );
            personOrderSalary.erase(ite);
            sortedOrderIndicatorSalary=false;
            break;  
      }
        }    
  
}
   

void Datastructure::add_boss(PersonID id, PersonID bossid)
{
    it=persons.find(id);
        (it->second).boss=bossid;
    (it->second).hasBoss=true;
    it=persons.find(bossid);
    ((it->second).children).push_back(id);

}


unsigned int Datastructure::size()
{
 return persons.size();
}
void Datastructure::clear()
{
    persons.clear();
    personOrderName.clear();
    personOrderSalary.clear();
    sortedOrderIndicatorName=false;
    sortedOrderIndicatorSalary=false;
}

vector<PersonID> Datastructure::underlings(PersonID id)
{
    it=persons.find(id);
        std::sort(((it->second).children).begin(), ((it->second).children).end());
        return (it->second).children;
}

vector<PersonID> Datastructure::personnel_alphabetically()
{        
      if(sortedOrderIndicatorName==false){
        nameOrderList.clear();
      for(std::map<string,PersonID>::iterator ite = personOrderName.begin(); ite != personOrderName.end(); ++ite)
          {         
            nameOrderList.push_back(ite->second);   
      }
        sortedOrderIndicatorName=true;
    }
    return nameOrderList;
}

vector<PersonID> Datastructure::personnel_salary_order()
{   
    if(sortedOrderIndicatorSalary==false){ 
         salaryOrderList.clear();
      for(std::map<Salary,PersonID>::iterator ite = personOrderSalary.begin(); ite != personOrderSalary.end(); ++ite)
          {         
            salaryOrderList.push_back(ite->second); 
      }
      sortedOrderIndicatorSalary=true;
     }
    return salaryOrderList;
}

PersonID Datastructure::find_ceo()
{
   int count=0;
   PersonID personId;
   for(std::unordered_map<PersonID,Person>::iterator ite = persons.begin(); ite != persons.end(); ++ite)
        {           
            if((ite->second).hasBoss==false){
               count++;
               personId=ite->first;
            }
    }
        if(count==1){
          return personId;
        }
    return NO_ID;
    
}

PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2)
{  PersonID boss1;
   PersonID boss2;
   Person person1;
   Person person2;
   int count=0;
     it=persons.find(id1); 
     person1=(it->second);
     it=persons.find(id2);
     person2=(it->second);
   std::set<PersonID> bosses;
   while(person1.hasBoss==true || person2.hasBoss==true){           
    
     if(person1.hasBoss==true){
       boss1=person1.boss;
       bosses.insert(boss1);
       if(count==bosses.size()){
         return boss1;
       }
       person1=(persons.find(boss1))->second;
       count++;
     }
      if(person2.hasBoss==true){
       boss2=person2.boss;
       bosses.insert(boss2);
       if(count==bosses.size()){
         return boss2;
       }
       person2=(persons.find(boss2))->second;
       count++;
     }
         
   }

  

   
    return NO_ID; // If you do not implement this, leave this return value as it is.
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id)
{
 PersonID ceo=find_ceo();
 int lowerRanks=0;
 int higherRanks=0;
  if(ceo!=NO_ID){
  ((persons.find(ceo))->second).rank=0;
  ranking(((persons.find(ceo))->second).children,1); 
  }
 int personRank=((persons.find(id))->second).rank;
 for(std::unordered_map<PersonID,Person>::iterator ite = persons.begin(); ite != persons.end(); ++ite)
        {           
            if((ite->second).rank!=personRank){
               if((ite->second).rank>personRank){
                 lowerRanks++;
               }
               else{
                  higherRanks++;    
               }    
            }
    } 


    return {higherRanks, lowerRanks}; // If you do not implement this, leave this return value as it is.
}
void Datastructure::ranking(vector<PersonID> child,int rank){

   for (std::vector<PersonID>::iterator iter = child.begin(); iter != child.end(); ++iter){
       ((persons.find(*iter))->second).rank=rank;
       (((persons.find(*iter))->second).lev).push_back(rank);
       ranking(((persons.find(*iter))->second).children,rank+1);
       }
}
PersonID Datastructure::min_salary()
{

   return (personOrderSalary.begin())->second;

}

PersonID Datastructure::max_salary()
{
   return (personOrderSalary.rbegin())->second;
}

PersonID Datastructure::median_salary()
{
  if(sortedOrderIndicatorSalary==true){
    return salaryOrderList.at(salaryOrderList.size()/2);
  }
  int count=0;
  int pos = (personOrderSalary.size()/2);
  for (std::map<Salary,PersonID>::iterator it= personOrderSalary.begin(); it!=personOrderSalary.end(); ++it)
  {

      if( count == pos)
      {
        return it->second;
      }
      count++;
  }
}

PersonID Datastructure::first_quartile_salary()
{
    if(sortedOrderIndicatorSalary==true){
    return salaryOrderList.at(salaryOrderList.size()/4);
  }
  int count=0;
  int pos = (personOrderSalary.size()/4);
  for (std::map<Salary,PersonID>::iterator it= personOrderSalary.begin(); it!=personOrderSalary.end(); ++it)
  {

      if( count == pos)
      {
        return it->second;
      }
      count++;
  }
}

PersonID Datastructure::third_quartile_salary()
{
    if(sortedOrderIndicatorSalary==true){
    return salaryOrderList.at(salaryOrderList.size()*3/4);
  }
  int count=0;
  int pos = (personOrderSalary.size()*3/4);
  for (std::map<Salary,PersonID>::iterator it= personOrderSalary.begin(); it!=personOrderSalary.end(); ++it)
  {

      if( count == pos)
      {
        return it->second;
      }
  }
}

// After this are the new operations of hw3
// NOTE!!! Add all your new hw3 code here below these comments (to keep it
// separated from old hw2 code).
void Datastructure::add_friendship(PersonID id, PersonID friendid, Cost cost)
{
    it=persons.find(id);
   if(persons.find(id) != persons.end() ) {
    struct Friendship f;
    f.friendId=friendid;
    f.cost=cost;
    (it->second).friendships.push_back(f);   
    (it->second).edges.push_back(f);
    }
    it=persons.find(friendid);
    if(persons.find(friendid) != persons.end() ) {
    struct Friendship f;
    f.friendId=id;
    f.cost=cost;   
    (it->second).edges.push_back(f);
    }


}

void Datastructure::remove_friendship(PersonID id, PersonID friendid)
{
    it=persons.find(id);
   if(persons.find(id) != persons.end() ) {
    vector<Friendship> fr=(it->second).friendships;
    for(int i=0;i<fr.size();i++){
        if((fr.at(i)).friendId==friendid){
              fr.erase (fr.begin()+i);
        }
    }
    (it->second).friendships=fr;


    }

}

vector<pair<PersonID, Cost>> Datastructure::get_friends(PersonID id)
{
    if(persons.find(id) == persons.end()){
     return {};
    }
    vector<pair<PersonID, Cost>> result;
    std::pair <PersonID,Cost> friends;
    it=persons.find(id);
    vector<Friendship> fr=(it->second).friendships;
    if(!((it->second).friendships).empty()){
    for(int i=0;i<fr.size();i++){
        friends = std::make_pair((fr.at(i)).friendId,(fr.at(i)).cost);
        result.push_back(friends);
    }
  }
   for (std::unordered_map<PersonID,Person>::iterator it= persons.begin(); it!=persons.end(); ++it)
  {
    fr=(it->second).friendships;
    if(!((it->second).friendships).empty() && (it->first)!=id){
    for(int i=0;i<fr.size();i++){
        if(fr.at(i).friendId==id){
        friends = std::make_pair(it->first,(fr.at(i)).cost);  
        result.push_back(friends);
        } 
      }
    }
    
   }
   std::sort(result.begin(), result.end());
    return result;
}
vector<pair<PersonID, PersonID>> Datastructure::all_friendships(){    
    std::pair <PersonID,PersonID> friends;
    vector<pair<PersonID, PersonID>> result; 
   for (std::unordered_map<PersonID,Person>::iterator it= persons.begin(); it!=persons.end(); ++it)
  {
    vector<Friendship> fr=(it->second).friendships;
    for(int i=0;i<fr.size();i++){
        friends = std::make_pair(it->first,(fr.at(i)).friendId);
        result.push_back(friends); 
    } 

   }     
  
    return result; // Replace this with the actual implementation
}

vector<pair<PersonID, Cost>> Datastructure::shortest_friendpath(PersonID fromid, PersonID toid)
{
  if(persons.find(fromid) == persons.end() || persons.find(toid) == persons.end()){
     return {};
    }
  vector<pair<PersonID, Cost>> resultVector;
  for (std::unordered_map<PersonID,Person>::iterator it= persons.begin(); it!=persons.end(); ++it){
    (it->second).visited=false;
  }
  vector<PersonID> nextLevel;
  nextLevel.push_back(fromid);
  int result=searchByBreadth(nextLevel,toid); 
  if(result==1){
  PersonID predPersonID=(((persons.find(toid))->second).pre).first;
  resultVector.push_back((std::make_pair(toid,(((persons.find(toid))->second).pre).second)));  
  while(predPersonID!=fromid){
      std::pair <PersonID,Cost> predecessor = (persons.find(predPersonID)->second).pre;
      resultVector.push_back(std::make_pair(predPersonID,predecessor.second));
      predPersonID=predecessor.first;            
    }

  }
     
std::reverse(resultVector.begin(),resultVector.end());     
return resultVector;
}
int Datastructure::searchByBreadth(vector<PersonID> nextLevel, PersonID toid){
 vector<PersonID> level;
 int count=0;
 while(true){
 for(int i=0;i<nextLevel.size();i++){
  it=persons.find(nextLevel.at(i));
  vector<Friendship> fr=(it->second).edges;
  for(int j=0;j<fr.size();j++){
    if(((persons.find((fr.at(j)).friendId))->second).visited==false){
      ((persons.find((fr.at(j)).friendId))->second).visited=true;
      ((persons.find((fr.at(j)).friendId))->second).pre=std::make_pair(it->first,(fr.at(j)).cost);
      level.push_back((fr.at(j)).friendId);
      count++;
      if((fr.at(j)).friendId==toid){
        return 1;
        }
      }
    }
  }
  if(count==0){
    return 0;
  }
  nextLevel=level;
  level.clear();
  count=0;

}
 

}


bool Datastructure::check_boss_hierarchy()
{
     int count=0;
   PersonID personId;
   for(std::unordered_map<PersonID,Person>::iterator ite = persons.begin(); ite != persons.end(); ++ite)
        {           
            if((ite->second).hasBoss==false){
               count++;
               personId=ite->first;
            }
    }
        if(count==0){
          return false;
        }
        if(count==2){
         return false; 
        }
        if(count==1){
          for(std::unordered_map<PersonID,Person>::iterator ite = persons.begin(); ite != persons.end(); ++ite)
          {
                     
            
            int result=checkCyclic(ite->first);
            if(result==1){
              return false;
            }
          }
       }     
        
      
    return true;// Replace this with the actual implementation
}
int Datastructure::checkCyclic(PersonID id){
   std::set<PersonID> visited;
   visited.insert(id);
   int counts=0;
   while(true){
    
    while(((persons.find(id))->second).hasBoss==true){
     counts=visited.size();
     PersonID bossID=((persons.find(id))->second).boss;
     visited.insert(bossID);
     if(counts==visited.size()){
      return 1;
     }
     id=bossID;

    }
    return 0;   
   }
}

vector<pair<PersonID, Cost>> Datastructure::cheapest_friendpath(PersonID fromid, PersonID toid)
{
  if(persons.find(fromid) == persons.end() || persons.find(toid) == persons.end()){
     return {};
    }
vector<pair<PersonID, Cost>> resultVector;
  for (std::unordered_map<PersonID,Person>::iterator it= persons.begin(); it!=persons.end(); ++it){
    (it->second).visited=false;
  }
  vector<PersonID> nextLevel;
  ((persons.find(fromid))->second).weight=0;
  nextLevel.push_back(fromid);
  int result=DJKalgorithm(nextLevel,toid); 
  if(result==1){
  PersonID predPersonID=(((persons.find(toid))->second).pre).first;
  resultVector.push_back((std::make_pair(toid,(((persons.find(toid))->second).pre).second)));  
  while(predPersonID!=fromid){
      std::pair <PersonID,Cost> predecessor = (persons.find(predPersonID)->second).pre;
      resultVector.push_back(std::make_pair(predPersonID,predecessor.second));
      predPersonID=predecessor.first;            
    }

  }
  if(result==0){
  	return {};
  }
     
std::reverse(resultVector.begin(),resultVector.end());     
return resultVector; // Replace this with the actual implementation
}
int Datastructure::DJKalgorithm(vector<PersonID> unvisited,PersonID toid){
  while(true){
  PersonID minEdge=minUnvisited(unvisited);
  int count=0;
  vector<PersonID> newUnvisited;
  for(int i=0;i<unvisited.size();i++){
    if(unvisited.at(i)!=minEdge){
      newUnvisited.push_back(unvisited.at(i));
      ((persons.find(minEdge))->second).visited=true;
    }
  }
  vector<Friendship> levelEdges=((persons.find(minEdge))->second).edges;
  for(int j=0;j<levelEdges.size();j++){
    if(((persons.find((levelEdges.at(j)).friendId))->second).visited==false && ((persons.find((levelEdges.at(j)).friendId))->second).weight>((levelEdges.at(j)).cost+((persons.find(minEdge))->second).weight)){
       ((persons.find((levelEdges.at(j)).friendId))->second).weight=(levelEdges.at(j)).cost+((persons.find(minEdge))->second).weight;
       ((persons.find((levelEdges.at(j)).friendId))->second).pre=std::make_pair(minEdge,(levelEdges.at(j)).cost);
       newUnvisited.push_back((levelEdges.at(j)).friendId);
       count++;
       if((levelEdges.at(j)).friendId==toid){
        return 1;
       }
    }
  }
  if(count==0){
    return 0;
  }
  unvisited=newUnvisited;
  newUnvisited.clear();
  count=0;
}
  
}
PersonID Datastructure::minUnvisited(vector<PersonID> unvisited){
  PersonID min;
  if(unvisited.size()>0){
  min=unvisited.at(0);
  Cost minCost=((persons.find(min))->second).weight;
  for(int i=0;i<unvisited.size();i++){    
     if((((persons.find(unvisited.at(i)))->second).weight)<minCost){
      minCost=((persons.find(unvisited.at(i)))->second).weight;
      min=unvisited.at(i);
     }
  }
}
  return min;
}


pair<unsigned int, Cost> Datastructure::leave_cheapest_friendforest()
{
    return {}; // Replace this with the actual implementation
}

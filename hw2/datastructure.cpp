// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#include "datastructure.hpp"
#include <algorithm>
// For debug
#include <iostream>
using std::cerr;
using std::endl;

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = rand() % range;
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
      count++;
  }
}

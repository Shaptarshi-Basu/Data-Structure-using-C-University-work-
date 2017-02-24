// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;
using std::swap;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
//template <typename Type>
//Type random_in_range(Type start, Type end)
//{
//    auto range = end-start;
//    ++range;
//
//    auto num = rand() % range;
//    return static_cast<Type>(start+num);
//}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{
}


void Datastructure::add_person(std::string name, int salary)
{
  struct Person p;
  p.name = name;
  p.salary = salary;
  person.push_back(p);
  reshuffleRequiredSalary=true;
  reshuffleRequiredAlphabet=true;
}
void Datastructure::reshuffleSalary(){

	pointerForSalary.clear();
 	for(list<Person>::iterator it = person.begin(); it != person.end();++it) {
	pointerForSalary.push_back(&(*it));
  }
	if(reshuffleRequiredSalary==true){
	quickSort(pointerForSalary,0,pointerForSalary.size()-1);
	reshuffleRequiredSalary=false;
	}
}
void Datastructure::reshuffleName(){
  pointerForAlphabet.clear();
 	for(list<Person>::iterator it = person.begin(); it != person.end();++it) {
	pointerForAlphabet.push_back(&(*it));
  }
	if(reshuffleRequiredAlphabet==true){
	quickSortForName(pointerForAlphabet,0,pointerForAlphabet.size()-1);
	reshuffleRequiredAlphabet=false;
	}
}
unsigned int Datastructure::size()
{
  return person.size();
}

void Datastructure::clear()
{
  return person.clear();
}

vector<Person *> Datastructure::personnel_alphabetically()
{
if(reshuffleRequiredAlphabet==true){
   reshuffleName();
   }
 return pointerForAlphabet;
}

vector<Person *> Datastructure::personnel_salary_order()
{
if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }
return pointerForSalary;
}

Person* Datastructure::min_salary()
{
 if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }

  return pointerForSalary.at(0);
}

Person* Datastructure::max_salary()
{
if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }

  return pointerForSalary.at(pointerForSalary.size()-1);
}

Person* Datastructure::median_salary()
{

  if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }

  return pointerForSalary.at(pointerForSalary.size()/2);


}

Person* Datastructure::first_quartile_salary()
{
  if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }

  return pointerForSalary.at(pointerForSalary.size()/4);

}

Person* Datastructure::third_quartile_salary()
{
 if(reshuffleRequiredSalary==true){
   reshuffleSalary();
   }

  return pointerForSalary.at(pointerForSalary.size()*3/4);


}
void Datastructure::quickSort(vector<Person*>& pointerForSalary, int top, int bottom){

  if(top < bottom){
    int middle = partition(pointerForSalary, top, bottom);
    quickSort(pointerForSalary, top, middle);  // sort top partition
    quickSort(pointerForSalary, middle + 1, bottom);  //sort bottom partition
  }
}

int Datastructure::partition(vector<Person*>& sal, int top, int bottom){

  int pivot = sal[top]->salary;
  int left_index = top - 1;
  int right_index = bottom + 1;
  string tmp;

  do{
    do{
      right_index--;
    }while( pivot<sal[right_index]->salary);

    do{
      left_index++;
    }while( pivot>sal[left_index]->salary);

    if (left_index < right_index)
      swap(sal[left_index], sal[right_index]);

  }while( left_index < right_index );

  return right_index;
}
void Datastructure::quickSortForName(vector<Person*>& v, int top, int bottom){

  if(top < bottom){
    int middle = partitionForName(v, top, bottom);
    quickSortForName(v, top, middle);  // sort top partition
    quickSortForName(v, middle + 1, bottom);  //sort bottom partition
  }
}

int Datastructure::partitionForName(vector<Person*>& v, int top, int bottom){

  std::string pivot = v[top]->name;
  int left_index = top - 1;
  int right_index = bottom + 1;
  string tmp;

  do{
    do{
      right_index--;
    }while( pivot.compare(v[right_index]->name) < 0 );

    do{
      left_index++;
    }while( pivot.compare(v[left_index]->name) > 0);

    if (left_index < right_index)
      swap(v[left_index], v[right_index]);

  }while( left_index < right_index );

  return right_index;
}

///////////////////////////////////////////////////////////////////////

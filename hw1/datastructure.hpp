// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

struct Person
{
  string name;
  int salary;
};

class Datastructure
{
public:
  Datastructure();
  ~Datastructure();

  void add_person(string name, int salary);

  unsigned int size();
  void clear();

  vector<Person*> personnel_alphabetically();
  vector<Person*> personnel_salary_order();

  Person* min_salary();
  Person* max_salary();

  Person* median_salary();
  Person* first_quartile_salary();
  Person* third_quartile_salary();

private:

  //Below are the used variable...........
  list <Person> person;

  vector<Person*> pointerForSalary ;
  vector<Person*> pointerForAlphabet ;
  bool reshuffleRequiredSalary=true;
  bool reshuffleRequiredAlphabet=true;
  vector<Person*> personnelSortedBySalary;


  // Below are Used Functions.....
  void reshuffleSalary();
  void reshuffleName();
  void quickSort(vector<Person*>& person, int left, int right);
  int partition(vector<Person*>& persons, int left, int right);
  void quickSortForName(vector<Person*>& person, int left, int right);
  int partitionForName(vector<Person*>& persons, int left, int right);


};

#endif // DATASTRUCTURE_HPP

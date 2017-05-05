// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>

#include <utility>
using std::pair;

#include <map>
using std::map;

#include <map>
using std::multimap;

#include <set>
using std::set;

#include <unordered_map>
using std::unordered_map;

using PersonID = string;
PersonID const NO_ID = "";

using Salary = int;
Salary const NO_SALARY = -1;

using Cost = int;
Cost const NO_COST = -1;


struct Friendship
{
  PersonID friendId;
  Cost cost;
};
struct Person
{
  string name;
  string title;
  Salary salary;
  PersonID boss;
  vector<PersonID> children;
  vector<Friendship> friendships;
  vector<int> lev;
  vector<Friendship> edges;
  bool hasBoss;
  int rank;
  bool visited;
  std::pair <PersonID,Cost> pre;
  Cost weight;      
};


class Datastructure
{
public:
    Datastructure();
    ~Datastructure();

    void add_person(string name, PersonID id, string title, Salary salary);
    void remove_person(PersonID id);

    string get_name(PersonID id);
    string get_title(PersonID id);
    Salary get_salary(PersonID id);
    vector<PersonID> find_persons(string name);
    vector<PersonID> personnel_with_title(string title);

    void change_name(PersonID id, string new_name);
    void change_salary(PersonID id, Salary new_salary);

    void add_boss(PersonID id, PersonID bossid);

    unsigned int size();
    void clear();

    vector<PersonID> underlings(PersonID id);
    vector<PersonID> personnel_alphabetically();
    vector<PersonID> personnel_salary_order();

    PersonID find_ceo();
    PersonID nearest_common_boss(PersonID id1, PersonID id2);
    pair<unsigned int, unsigned int> higher_lower_ranks(PersonID id);

    PersonID min_salary();
    PersonID max_salary();

    PersonID median_salary();
    PersonID first_quartile_salary();
    PersonID third_quartile_salary();

    // After this are the new operations of hw3
    void add_friendship(PersonID id, PersonID friendid, Cost cost);
    void remove_friendship(PersonID id, PersonID friendid);
    vector<pair<PersonID, Cost>> get_friends(PersonID id);
    vector<pair<PersonID, PersonID>> all_friendships();

    bool check_boss_hierarchy();
    vector<pair<PersonID, Cost>> shortest_friendpath(PersonID fromid, PersonID toid);
    vector<pair<PersonID, Cost>> cheapest_friendpath(PersonID fromid, PersonID toid);
    pair<unsigned int, Cost> leave_cheapest_friendforest();

private:
// Add your implementation here
unordered_map<PersonID,Person> persons;
std::unordered_map<PersonID,Person>::iterator it;
std::vector<Person>::iterator iter;
std::multimap<string,PersonID> personOrderName;
std::multimap<Salary,PersonID> personOrderSalary;
vector<PersonID> nameOrderList;
vector<PersonID> salaryOrderList;
bool sortedOrderIndicatorName=false;
bool sortedOrderIndicatorSalary=false;
bool updatedNameMap=false;
map<PersonID, Person> personsSorted;
void ranking(vector<PersonID> childern, int rank);
int searchByBreadth(vector<PersonID> personLevel, PersonID findPerson);
int DJKalgorithm(vector<PersonID> unvisited,PersonID toid);
PersonID minUnvisited(vector<PersonID> unvisited);
int checkCyclic(PersonID id);
};

#endif // DATASTRUCTURE_HPP

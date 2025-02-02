#include <algorithm>
#include "Person.h"
#include <vector>
using std::string;
Person::Person(const Person &person) {
    this->ID = person.ID;
    this->name = person.name;
    this->age = person.age;
    this->gender = person.gender;
    this->occupation = person.occupation;
    listOfFriends = person.listOfFriends;
}
Person::Person(int ID, std::string name, int age, std::string gender, std::string occupation,std::vector<int> friends) {
    this->ID = ID;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->occupation = occupation;
    listOfFriends = friends;
}
Person::Person() = default;
int Person::getFriendListSize() const{return listOfFriends.size();}
int Person::getFriendID (int index) const{
    return listOfFriends.at(index);
}
int Person::getAge() const{return age;}

string Person::getGender() const{return gender;}

int Person::getID() const{return ID;}

string Person::getName() const{return name;}

string Person::getOccupation() const{return occupation;}


void Person::removeFriend(int id) {
    auto it = std::find(listOfFriends.begin(), listOfFriends.end(),id);
    if (it != listOfFriends.end()) {
        listOfFriends.erase(it);
    }
}

const std::vector<int> &Person::getListOfFriends() const {
    return listOfFriends;
}
bool Person::areFriends(const Person& person) const {
    bool areFriends = false;
    for (int i = 0; i < getFriendListSize(); ++i) {
        if (getFriendID(i) == person.ID) {
            areFriends = true;
            break;
        }
    }
    return areFriends;
}
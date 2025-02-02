
#ifndef TERMPROJECT_PERSON_H
#define TERMPROJECT_PERSON_H
#include <iostream>
#include <vector>

#include <string>

using std::string;
class Person{
public:
    int getID() const;
    string getName() const;
    int getAge() const;
    const std::vector<int> &getListOfFriends() const;
    string getGender() const;
    string getOccupation() const;
    int getFriendID(int index) const;
    Person(int ID,string name,int age,string gender,string occupation,std::vector<int> friends);
    Person();
    Person(const Person &person);
    int getFriendListSize() const;
    void removeFriend(int index);
    bool areFriends(const Person& person) const;
private:
    int ID,age;
    string name,gender,occupation;
    std::vector<int> listOfFriends;
};

#endif //TERMPROJECT_PERSON_H

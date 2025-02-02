
#ifndef TERMPROJECT_GRAPH_H
#define TERMPROJECT_GRAPH_H
#include "Person.h"
#include <iostream>
#include <vector>
#include <utility>
class Graph{
    public:
        void addPerson(int id, const Person &person);
        Person *getPerson(int id) const;
        void suggestFriends(int person_id,int mode);
        void suggestFriendsByCommonFriends(const Person *person) const;
        void suggestFriendsByOccupation(const Person *person) const;
        void suggestFriendsByAge(const Person *person) const;
        void removeFriendship(int id1,int id2);
        int getSize() const;
        const std::vector<std::pair<int, Person>> &getGraph() const;
        void degreeCentrality() const;
        double clusteringCoefficient(int id) const;
        double edgeWeight(const Graph &graph, int u, int v) const;
        std::vector<std::vector<int>> girvanNewman(int iterations) const;
        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
    private:
        std::vector<std::pair<int,Person>> graph;
        int size = 0;
};


#endif
#include <iostream>
#include "Graph.h"
#include "Person.h"
#include <utility>
#include <queue>
#include <algorithm>

int Graph::getSize() const {
    return size;
}

void Graph::addPerson(int id, const Person &person) {
    graph.emplace_back(id, person);
    size++;
}

Person* Graph::getPerson(int id) const {
    for (const auto & it : graph) {
        if (it.first == id) {
            return const_cast<Person*>(&it.second);
        }
    }
    return nullptr;
}

void Graph::suggestFriends(int person_id, int mode) {
    Person* person = getPerson(person_id);
    if (person) {
        switch (mode) {
            case 1:
                suggestFriendsByCommonFriends(person);
                break;
            case 2:
                suggestFriendsByOccupation(person);
                break;
            case 3:
                suggestFriendsByAge(person);
                break;
            default:
                std::cout << "Invalid mode\n";
        }
    } else {
        std::cout << "Person not found\n";
    }
}

void Graph::suggestFriendsByCommonFriends(const Person *person) const {
    std::vector<std::pair<int, Person>> suggestionWithComFriendNo;
    int maxCommonFriends = 0;

    for (auto it = graph.begin(); it != graph.end(); ++it) {
        if ((*it).first == person->getID() || person->areFriends((*it).second)) continue;

        int commonFriendNo = 0;
        for (int friend_id : (*it).second.getListOfFriends()) {
            if (person->areFriends(*getPerson(friend_id))) {
                commonFriendNo++;
            }
        }

        if (commonFriendNo > maxCommonFriends) maxCommonFriends = commonFriendNo;
        if (commonFriendNo != 0) {
            suggestionWithComFriendNo.emplace_back(commonFriendNo, (*it).second);
        }
    }if (maxCommonFriends != 0) {
        std::cout << "People you might want to connect:\n";
        for (int p = 0;p < suggestionWithComFriendNo.size();p++) {
            std::cout << suggestionWithComFriendNo.at(p).second.getName() << " - " << suggestionWithComFriendNo.at(p).first << " common friends\n";
        }
    }
}


void Graph::suggestFriendsByOccupation(const Person *person) const {
    std::cout << "People that have the same occupation as you:\n";
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        if ((*it).first == person->getID() || person->areFriends((Person)(*it).second)) continue;
        if ((*it).second.getOccupation() == person->getOccupation()) {
            std::cout << (*it).second.getName() << " - " << (*it).second.getOccupation() << '\n';
        }
    }
}

void Graph::suggestFriendsByAge(const Person *person) const {
    std::cout << "People that are of a similar age to you:\n";
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        if ((*it).first == person->getID() || person->areFriends(((*it).second))) continue;
        if (std::abs((*it).second.getAge() - person->getAge()) <= 5) {
            std::cout << (*it).second.getName() << " - " << (*it).second.getAge() << " years old\n";
        }
    }
}

const std::vector<std::pair<int, Person>> &Graph::getGraph() const {
    return graph;
}

void Graph::removeFriendship(int id1, int id2) {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        if ((*it).first == id1) (*it).second.removeFriend(id2);
        else if ((*it).first == id2) (*it).second.removeFriend(id1);
    }
}

void Graph::degreeCentrality() const {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        std::cout << (*it).second.getName() << " has " << (*it).second.getFriendListSize() << " connections. (Degree centrality is: " << (*it).second.getFriendListSize() << ")\n";
    }
}

double Graph::clusteringCoefficient(int id) const {
    std::vector<int> linkVector;
    int neighborLinks;
    int vertexDegree = getPerson(id)->getFriendListSize();
    for(int i = 0;i < getPerson(id)->getFriendListSize();i++){
        Person person = *getPerson(getPerson(id)->getFriendID(i));
        for(int j = 0;j < person.getFriendListSize();j++){
            if(person.getFriendID(j) == id) continue;
            bool isFriends = false;
            for(int k = 0;k < getPerson(person.getFriendID(j))->getFriendListSize();k++) {
                isFriends = getPerson(person.getFriendID(j))->getFriendID(k) == id;
                if(isFriends)break;
            }
            if(!isFriends) continue;
            int link;
            person.getFriendID(j) > person.getID() ? link = person.getID() * 10 + person.getFriendID(j) : link = person.getFriendID(j) * 10 + person.getID();
            bool isInLinkVList = false;
            for(int k = 0;k < linkVector.size();k++)
                if(linkVector.at(k) == link) isInLinkVList = true;
            if(isInLinkVList) continue;
            linkVector.push_back(link);
        }
    }
    neighborLinks = linkVector.size();
    return 2.0*neighborLinks/(vertexDegree*(vertexDegree-1));
}


double Graph::edgeWeight(const Graph &graph, int u, int v) const {
    const Person* personU = getPerson(u);
    const Person* personV = getPerson(v);
    if (!personU || !personV) return 0.0;

    std::vector<int> uFriends = personU->getListOfFriends();
    std::vector<int> vFriends = personV->getListOfFriends();

    int common = 0;
    for (int uFriend : uFriends) {
        for (int vFriend : vFriends) {
            if (uFriend == vFriend) common++;
        }
    }

    return common;
}

std::vector<std::vector<int>> Graph::girvanNewman(int iterations) const {
    Graph graphCopy(*this);
    std::vector<std::vector<int>> communities;

    for (int i = 0; i < iterations; i++) {
        double maxWeight = 0;
        int id1Max = -1, id2Max = -1;

        for (auto it = graphCopy.graph.begin(); it != graphCopy.graph.end() - 1; ++it) {
            for (auto jt = it + 1; jt != graphCopy.graph.end(); ++jt) {
                if ((*it).second.areFriends((*jt).second)) {
                    double eW = edgeWeight(graphCopy, (*it).first, (*jt).first);
                    if (eW > maxWeight) {
                        maxWeight = eW;
                        id1Max = (*it).first;
                        id2Max = (*jt).first;
                    }
                }
            }
        }

        if (maxWeight != 0) {
            graphCopy.removeFriendship(id1Max, id2Max);
        }
    }

    int min_id = graphCopy.graph.begin()->first;
    int max_id = graphCopy.graph.rbegin()->first;

    std::vector<int> community(max_id - min_id + 1, -1);
    int currentCommunity = 0;

    for (auto it = graphCopy.graph.begin(); it != graphCopy.graph.end(); ++it) {
        if (community[(*it).first - min_id] == -1) {
            std::vector<int> members;
            members.push_back((*it).first);

            for (int friend_id : (*it).second.getListOfFriends()) {
                if (community[friend_id - min_id] == -1) {
                    members.push_back(friend_id);
                    community[friend_id - min_id] = currentCommunity;
                }
            }

            communities.push_back(members);
            currentCommunity++;
        }
    }

    communities.erase(std::remove_if(communities.begin(), communities.end(), [](const std::vector<int>& vec) { return vec.empty(); }), communities.end());
    return communities;
}

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
    for (auto it = graph.graph.begin(); it != graph.graph.end(); ++it) {
        os << (*it).first << ' ';
        os << (*it).second.getName() << ' ';
        os << (*it).second.getAge() << ' ';
        os << (*it).second.getGender() << ' ';
        os << (*it).second.getOccupation() << std::endl;
    }
    return os;
}

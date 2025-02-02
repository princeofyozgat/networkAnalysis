

#include "Graph.h"
#include "Person.h"
#include "utils.h"
#include <iostream>
int main(){
    Graph graph = readData("social_network.csv");
    int choice = 0;
    int id;
    while(choice != 6) {
        std::cout << "1.Display the social network,\n"
                     "2.Suggest friends for users based on common friends, similar occupation, or similar age,\n"
                     "3.Calculate degree centrality for each user,\n"
                     "4.Calculate clustering coefficient for each user,\n"
                     "5.Detect communities using the Girvan-Newman algorithm,\n"
                     "6.Exit the program." << std::endl;
        std::cin >> choice;
        if(choice == 1){
            std::cout << graph << std::endl;
        }
        else if(choice == 2){
            std::cout << "Enter id: ";
            std::cin >> id;
            int mode;
            std::cout << "Enter mode\n1. By common friends\n2. By occupation\n3. By age\n";
            std::cin >> mode;
            graph.suggestFriends(id,mode);
        }
        else if(choice == 3){
            graph.degreeCentrality();
        }
        else if(choice == 4){
            for(int i = 0;i < graph.getSize();i++){
                std::cout<<"Clustering coefficient of "<< graph.getGraph().at(i).second.getName() <<" is: "<<graph.clusteringCoefficient(graph.getGraph().at(i).first)<<'\n' ;
            }
        }
        else if(choice == 5) {
            int iterations;
            std::cout << "Enter no. of iterations: ";
            std::cin >> iterations;
            std::vector<std::vector<int>>gcopy = graph.girvanNewman(iterations);
            for(const auto& i : gcopy){
                for(int j : i){
                    std::cout << j << ' ';
                }
                std::cout << '\n';
            }
        }
    }
    return 0;
}

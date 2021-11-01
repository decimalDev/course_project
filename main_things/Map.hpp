#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Machine.hpp"
#include<time.h>

class Map{
	public:
	std::vector<Street> all_streets;
	std::vector<Machine> machines;
	std::vector<CrossRoads> all_cross_roads;
	
	void crt_streets(){
		for(int i = 0;i<all_streets.size();i++){
			for(int j = 0;j<all_streets.size();j++){
			if(i==j) continue;
				if(all_streets[i].cross[1].point==all_streets[j].cross[0].point){
					all_streets[i].next_Street(all_streets[j]);
					all_streets[j].last_Street(all_streets[i]);
					all_streets[i].is_last_street = 0;
				}
//				/*
				if(all_streets[i].cross[1].point==all_streets[j].cross[1].point){
					all_streets[i].next_Street(all_streets[j]);
					all_streets[j].next_Street(all_streets[i]);
					all_streets[i].is_last_street = 0;
					all_streets[j].is_last_street = 0;
				}
				
				if(all_streets[i].cross[0].point==all_streets[j].cross[0].point){
					all_streets[i].last_Street(all_streets[j]);
					all_streets[j].last_Street(all_streets[i]);
				}
				
//				*/
			}
		}
	}
	
	Map(){}
	Map(std::vector<Street> &strts){
	srand(time(0));
		all_streets = strts;
		for(int i = 0;i<all_streets.size();i++){
			all_streets[i].number = i;
		}
		crt_streets();
		int j = 0;
		int flag1 = 1;
		int flag2 = 1;
		int s1,s2;
		for(int i = 0;i<all_streets.size();i++){
			for(int k = 0;k<all_cross_roads.size();k++){
				if(all_cross_roads[k].point==all_streets[i].cross[0].point){
					flag1 = 0;
					s1 = k;
				}
				if(all_cross_roads[k].point==all_streets[i].cross[1].point){
					flag2 = 0;
					s2 = k;
				}
			}
			if(flag1){
				all_streets[i].cross[0].number = j;
				all_cross_roads.push_back(all_streets[i].cross[0]);
				j++;
			}else{
				all_streets[i].cross[0].number = all_cross_roads[s1].number;
				std::cout<<"what's going on?"<<std::endl;//debug
			}
			
			if(flag2){
				all_streets[i].cross[1].number = j;
				all_cross_roads.push_back(all_streets[i].cross[1]);
				j++;
			}else{
				all_streets[i].cross[1].number = all_cross_roads[s2].number;
				std::cout<<"what's going on here?"<<std::endl;//debug
			}
			flag1 = 1;
			flag2 = 1;
		}
		
		//debug
		std::cout<<"cross_roads: ";
		for(int i = 0;i<all_cross_roads.size();i++) std::cout<<all_cross_roads[i].number<<" ";//here debug
		std::cout<<std::endl;
		
		std::cout<<"streets: ";
		for(int i = 0;i<all_streets.size();i++) std::cout<<all_streets[i].number<<" ";//here debug
		std::cout<<std::endl;
		
		for(int i = 0;i<all_streets.size();i++) std::cout<<"this street: "<<all_streets[i].number<<" "<<all_streets[i].cross[0].number<<" "<<all_streets[i].cross[1].number<<std::endl;//here debug
		std::cout<<std::endl;
		//here
		
		
		srand(time(0));
		int n;
		for(int i = 0;i<1;i++){
		n = rand()%(all_streets.size());
		machines.push_back(Machine(all_streets[n],all_streets));
		}
		
	}
	
	
	void checking(){
	int k = 0;
	srand(time(0));
	int n = rand()%(all_streets.size()); 
	for(int j = 0;j<machines.size();j++)
	if((machines[j].dx!=0||machines[j].dy!=0))  k++;
		if(k<1) machines.push_back(Machine(all_streets[n],all_streets));
		
		for(int j = 0;j<machines.size();j++)
			if(machines[j].is_way_completed) machines.erase(machines.begin()+j);
	}
	
	
	void save(){
	std::ofstream file("Map.txt");
	file<<"map_size: "<<all_streets.size()<<std::endl;
	for(int i = 0;i<all_streets.size();i++)
	file<<all_streets[i];
	}
	
	
	void load_map(){
		std::ifstream file("Map.txt");
		all_streets.clear();
		machines.clear();
		std::string s;
		Street a;
		int size;
		file>>s>>size;
		for(int i = 0;i<size;i++){
			file>>a;
			all_streets.push_back(a);
		}
		
	}
};

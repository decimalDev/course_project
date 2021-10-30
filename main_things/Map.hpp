#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Machine.hpp"

bool find(Street x, Street y){
	return (x.cross[1].point == y.cross[0].point);
}

class Map{
	public:
	std::vector<Street> all_streets;
	std::vector<Machine> machines;
	
	void crt_streets(){
		for(int i = 0;i<all_streets.size();i++){
			for(int j = 0;j<all_streets.size();j++)
				if(find(all_streets[i],all_streets[j])){
					all_streets[i].next_Street(all_streets[j]);
					all_streets[i].is_last_street = 0;
				}
		}
	}
	
	Map(){}
	Map(std::vector<Street> &strts){
		all_streets = strts;
		for(int i = 0;i<all_streets.size();i++){
			all_streets[i].number = i;
		}
		crt_streets();
		
		int n;
		for(int i = 0;i<10;i++){
		n = rand()%(all_streets.size());
		machines.push_back(Machine(all_streets[n],all_streets));
		}
		
	}
	void checking(){
	int k = 0;
	int n = rand()%(all_streets.size()); 
	for(int j = 0;j<machines.size();j++)
	if((machines[j].dx!=0||machines[j].dy!=0))  k++;
		if(k<10) machines.push_back(Machine(all_streets[n],all_streets));
		
		for(int j = 0;j<machines.size();j++)
			if(machines[j].is_way_completed) machines.erase(machines.begin()+j);
	//}
	}
	void save(){
//	/*
	std::ofstream file("Map.txt");
	file<<"map_size: "<<all_streets.size()<<std::endl;
	for(int i = 0;i<all_streets.size();i++)
	file<<all_streets[i];
	/*
	for(int i = 0;i<streets.size();i++){
		
	}
//	*/
		
	}
	void load_map(){
		std::ifstream file("Map.txt");
		std::string s;
		std::vector<Street> strs;
		Street a;
		int size;
		file>>s>>size;
		for(int i = 0;i<size;i++){
			file>>a;
			strs.push_back(a);
			std::cout<<a<<std::endl<<std::endl;
		}
		
		all_streets = strs;
	}
	
	
};



/*
	улицы не могут иметь больше 4х соеденений с другими улицами в концах улицы
	
	улицы будут лежать в полярной системе координат для определения однозначного расположения
	начало отчёта в середение карты
	
	длина улицы будет умнажаться на некоторый коэфициент масштабирования чтобы при масштабировании карты отношение длин улиц оставался одинаковой
	
	ошибка в представлении вектора(массива) хронящий список но на самом деле оно не хранило список
	*/
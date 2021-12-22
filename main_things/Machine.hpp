#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "TrafficLight.hpp"
//debug
class Machine{
	public:
	float x;
	float y;
	float width;
	float length;
	float dx;
	float dy;//unit vector of direction
	float velocity;
	float max_velocity;
	int street_count;
	int number;
	int is_way_completed;
	int max_streets;
	std::vector<int> way;
	Street street;//current street
	CrossRoads next_cross;
	CrossRoads cur_cross;//start of current street
	
	
	
	std::vector<int> way1;
	sf::RectangleShape rectangle;
	sf::RectangleShape model;
	sf::Color color;
	std::vector<Street>* all_streets;
	float traversed_path = 1;
	int is_there_machine_in_forward = 0;
	int is_machine_broken = 0;
	sf::Time broken_in;
	int is_public_transport = -1;
	
	void showInf(){
		std::cout<<"*********************"<<std::endl;
		std::cout<<"number:"<<number<<std::endl;
		std::cout<<"way: ";
		for(int i = 0;i<way.size();i++) std::cout<<way[i]<<" ";
		std::cout<<std::endl;
		std::cout<<"*********************"<<std::endl;
	}
	
	void generate_way(){
	std::cout<<"Machine:"<<"generate_way"<<std::endl;//debug
		srand(time(0));
		street_count = 0;
		
		way.push_back(street.number);//add first street of way
		
		Street str = street;//current iteration street
		int flag = 1;
		int num = -1;//num=-1 mean that it's first iteration
		int num_of_strs = 0;//number of streets in the way in current iteration
		
		
		std::cout<<"Machine:"<<"generate_way:"<<"loop"<<std::endl;//debug
		while(num_of_strs<max_streets){
			std::cout<<"Machine:"<<"generate_way:"<<"loop: conditions"<<std::endl;//debug
			std::cout<<"Machine:"<<"generate_way: vector way: ";//debug
			std::cout<<std::endl;//debug
			for(int i = 0;i<way.size();i++) std::cout<<way[i];//debug
			std::cout<<std::endl;//debug
			if(str.next_streets.size()==0){//condition if current of iteration street don't have next neighbour street then way is completed
				std::cout<<"Machine:"<<"generate_way:"<<"loop: first condition"<<std::endl;//debug
				return;
			}
			int n;
			if(num!=-1&&str.cross[1].number==all_streets->at(way[way.size()-2]).cross[1].number){// if it isn't first iteration and end of str equal to end of last street of way now. for reverse direction in next street
				std::cout<<"Machine:"<<"generate_way:"<<"loop: second condition"<<std::endl;//debug
			
		//	/*
				if(str.last_streets.size()==0){
					std::cout<<"@@@@@@Yes it's condition work???"<<std::endl;//need to check
					break;//когда крайняя точка
				}
		//	*/   
				//std::cout<<"Machine:"<<"we caught you here"<<std::endl;//debug
				n = rand()%(str.last_streets.size());
				num = str.last_streets[n];
				
				//std::cout<<"what 1"<<std::endl;//debug
				
			}else if(num!=-1&&str.cross[1].number==all_streets->at(way[way.size()-2]).cross[0].number){//if it isn't first iteration and end of str equal to start of last street of way now
				std::cout<<"Machine:"<<"generate_way:"<<"loop: third condition"<<std::endl;//debug
				if(str.last_streets.size()==0) break;//когда крайняя точка
					n = rand()%(str.last_streets.size());
					num = str.last_streets[n];
					//std::cout<<"what 2"<<std::endl;//debug
					
			}else if(num==-1&&str.cross[1].number==cur_cross.number){//if it is first iteration and end of str equal to start of curent street(street) now. ?????
				std::cout<<"Machine:"<<"generate_way:"<<"loop: fourth condition"<<std::endl;//debug
				if(str.last_streets.size()==0) break;//когда крайняя точка//могут ли точки совпасть в итоге из за этого возникнуть ошибки?
				//обычно если машина едет в обратную сторону и доходит до крайней точки?
				std::cout<<"Machine:"<<"generate_way:"<<"loop: fourth condition: str.last_streets.size()=="<<str.last_streets.size()<<std::endl;//debug
					n = rand()%(str.last_streets.size());
					num = str.last_streets[n];//choosing reverse direction street
			}else{
				//for reserve direction on ways
				std::cout<<"Machine:"<<"generate_way:"<<"loop: fifth condition"<<std::endl;//debug
				if(rand()%2&&way.size()==1&&str.last_streets.size()>0&&flag){//random for random direction. And current street have last street.we have flag to do it only once
						std::cout<<"Machine:"<<"generate_way:"<<"loop: flag conditions"<<std::endl;//debug
						
						n = rand()%(str.last_streets.size());
						num = str.last_streets[n];
						
						if(street.cross[0].number==all_streets->at(num).cross[1].number){//if chosen street of reverse direction
						///*
							x = street.cross[0].point.x;
							y = street.cross[0].point.y;
							dx = -all_streets->at(num).street_dx;
							dy = -all_streets->at(num).street_dy;
						//*/
							next_cross = all_streets->at(num).cross[0];
							cur_cross = all_streets->at(num).cross[1];
							//std::cout<<"here detected"<<std::endl;//debug
							
						}else{//if chosen next street
						///*
							x = street.cross[0].point.x;
							y = street.cross[0].point.y;
							dx = all_streets->at(num).street_dx;
							dy = all_streets->at(num).street_dy;
						//*/
							next_cross = all_streets->at(num).cross[1];
							cur_cross = all_streets->at(num).cross[0];
							//std::cout<<"I see"<<std::endl;//debug
						}
						//std::cout<<"out old str "<<street.number<<std::endl;//debug
						street = all_streets->at(num); //if chosem reverse direction then new first street
						str = street;
						
						
						way[0] = street.number;
						
						num = -1;
						
						//std::cout<<"out new str "<<street.number<<std::endl;//debug
						flag = 0;
						continue;
				}
				std::cout<<"Machine:"<<"generate_way:"<<"loop: end of conditions"<<std::endl;//debug
				//std::cout<<"Machine:"<<"you catch me here"<<std::endl;//debug
				n = rand()%(str.next_streets.size());
				num = str.next_streets[n];
				//std::cout<<"Machine:"<<"catch me if you can"<<std::endl;//debug
		//}
			}
			
			
			
			str = all_streets->at(num);
			
/*
			if(way[0]==num){
				way.push_back(num);
				break;
			}
			
			for(int i = 0;i<way.size();i++){
				if(all_streets->at(way[i]).number==str.number){
					way.push_back(num);
					return;
				}
			}
			*/
			//debug
			//std::cout<<"our_num: "<<num<<std::endl;
			
			way.push_back(num);
			num_of_strs++;
			std::cout<<"Machine:"<<"generate_way:"<<"loop_end"<<std::endl;//debug
			}
		std::cout<<"Machine:"<<"generate_way_end"<<std::endl;//debug
	}
	
	
	//Machine(Street street1, std::vector<Street> &all_streets);
	//Machine(){}
	
	
	virtual void move(float time,sf::Clock &clock) = 0;
	
	void check_forward(Machine *m,sf::Clock &clock){
		
		if(dx==m->dx&&dy==m->dy&&(m->x - x)*dx>0&&(m->y - y)*dy>0){
			float dist = sqrt((x-m->x)*(x-m->x) + (y-m->y)*(y-m->y));
			if(dist<50&&!is_machine_broken){
				velocity = m->velocity;
				is_there_machine_in_forward = 1;
			}
			if(dist<45&&!is_machine_broken){
				velocity = 0;
				is_there_machine_in_forward = 1;
			}
			if(dist<30&&!is_machine_broken){
				velocity = 0;
				is_there_machine_in_forward = 1;
				is_machine_broken = 1;
				m->is_machine_broken = 1;
				m->velocity = 0;
				broken_in = clock.getElapsedTime();
			}
		}
	}
	
	
	
	bool is_in_cross(){
	return (((x - next_cross.point.x)*(x - next_cross.point.x) + (y - next_cross.point.y)*(y - next_cross.point.y))<100);
	}
	
	
	
	virtual void next_Street(std::vector<Street> &all_streets) = 0;
};
//std::cout<<"Machine:"<<"catch me if you can"<<std::endl;//debug
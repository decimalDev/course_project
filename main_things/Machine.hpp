#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Street.hpp"

class Machine{
	public:
	float x;
	float y;
	float width;
	float length;
	float dx;
	float dy;
	float velocity;
	int street_count;
	int is_way_completed;
	int max_streets;
	std::vector<int> way;
	Street street;
	CrossRoads next_cross;
	CrossRoads cur_cross;
	std::vector<int> way1;
	sf::RectangleShape rectangle;
	sf::Color color;
	std::vector<Street>* all_streets;
	/*
	void generate_way(std::vector<Street> &all_streets){
	this->all_streets = &all_streets;
		way.push_back(street.number);
		Street str = street;
		int num;
		
		while(!str.next_streets.empty()){
			if(str.next_streets.size()==0){
				return;
			}
			int n = rand()%(str.next_streets.size());
			num = str.next_streets[n];
			
			str = all_streets[num];
			
			if(str.next_streets.size()==0){
				way.push_back(str.number);
				return;
			}
			if(way[0]==num){
				way.push_back(num);
				break;
			}
			for(int i = 0;i<way.size();i++)
			if(all_streets[way[i]].street_dx==-str.street_dx&&all_streets[way[i]].street_dy==-str.street_dy){
				way.push_back(num);
				return;
			}
			way.push_back(num);
			
			}

	}
	*/
	
	void generate_way(){
		srand(time(0));
		street_count = 0;
		way.push_back(street.number);
		Street str = street;
		int flag = 1;
		int num = -1;
		int num_of_strs = 0;
		while(num_of_strs<max_streets){
			if(str.next_streets.size()==0){
				return;
			}
			int n;
			
			
			if(num!=-1)
			std::cout<<"here: "<<str.cross[1].number<<" "<<all_streets->at(way[way.size()-2]).cross[1].number<<std::endl;//debug
		
		
			if(num!=-1&&str.cross[1].number==all_streets->at(way[way.size()-2]).cross[1].number){
				if(str.last_streets.size()==0) break;//когда крайняя точка
				
				n = rand()%(str.last_streets.size());
				num = str.last_streets[n];
				
			}else if(num!=-1&&str.cross[1].number==all_streets->at(way[way.size()-2]).cross[0].number){
				if(str.last_streets.size()==0) break;//когда крайняя точка
				
					n = rand()%(str.last_streets.size());
					num = str.last_streets[n];
					
			}else if(str.cross[1].number==cur_cross.number){
			
				if(str.last_streets.size()==0) break;//когда крайняя точка
					n = rand()%(str.last_streets.size());
					num = str.last_streets[n];
			}else{
			
				if(rand()%2&&way.size()==1&&str.last_streets.size()>0&&flag){
						n = rand()%(str.last_streets.size());
						num = str.last_streets[n];
						
						if(street.cross[0].number==all_streets->at(num).cross[1].number){
							x = street.cross[0].point.x;
							y = street.cross[0].point.y;
							dx = -all_streets->at(num).street_dx;
							dy = -all_streets->at(num).street_dy;
							next_cross = all_streets->at(num).cross[0];
							cur_cross = all_streets->at(num).cross[1];
							std::cout<<"here detected"<<std::endl;
							
						}else{
							x = street.cross[0].point.x;
							y = street.cross[0].point.y;
							dx = all_streets->at(num).street_dx;
							dy = all_streets->at(num).street_dy;
							next_cross = all_streets->at(num).cross[1];
							cur_cross = all_streets->at(num).cross[0];
						}
						std::cout<<"out old str "<<street.number<<std::endl;
						street = all_streets->at(num);
						str = street;
						
						
						way[0] = street.number;
						
						num = -1;
						
						std::cout<<"out new str "<<street.number<<std::endl;
						flag = 0;
						continue;
				}
				
				n = rand()%(str.next_streets.size());
				num = str.next_streets[n];
				
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
			std::cout<<"our_num: "<<num<<std::endl;
			
			way.push_back(num);
			num_of_strs++;
			}

	}
	
	
	
	
	
	
	Machine(Street street1, std::vector<Street> &all_streets){
	srand(time(0));
	this->all_streets = &all_streets;
	street_count = 0;
	is_way_completed = 0;
		length = 50.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		this->street = street1;
		
		dx = street.street_dx;
		dy = street.street_dy;
		
		max_streets = 1+rand()%10;
		x = street.cross[0].point.x;
		y = street.cross[0].point.y;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		generate_way();
		
		velocity = 100;
		rectangle.setPosition(sf::Vector2f(x,y));
		
		
		//generate()
		color = sf::Color(rand()%255,rand()%255,rand()%255);
		rectangle.setFillColor(color);
		
		//debug
		std::cout<<"way: ";
		for(int i = 0;i<way.size();i++) std::cout<<way[i]<<" ";
		std::cout<<std::endl;
		
	}
	
	
	void move(float time){
		x+=time*dx*velocity;
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
	}
	
	
	
	bool is_in_cross(){
	return (((x - next_cross.point.x)*(x - next_cross.point.x) + (y - next_cross.point.y)*(y - next_cross.point.y))<100);
	}
	
	
	
	void next_Street(std::vector<Street> &all_streets){
	if(all_streets[way[street_count]].is_last_street){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	street_count++;
	
	if(way.size()==street_count){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	//if(street_count==way.size()-1&&way[0] == way.back()) street_count = 0;
	
	if(way.size()==0){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	std::cout<<"str count: "<<street_count<<" "<<way.size()<<std::endl;
	if(next_cross.number==street.cross[0].number){
		
	}
		
	street = all_streets[way[street_count]];
	
	std::cout<<"next street: "<<street.number<<std::endl;//debug
	
	std::cout<<next_cross.number<<" "<<street.cross[0].number<<std::endl;
	if(next_cross.number==street.cross[0].number){
		dx = street.street_dx;
		dy = street.street_dy;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		
	}else{
		dx = -street.street_dx;
		dy = -street.street_dy;
		next_cross = street.cross[0];
		cur_cross = street.cross[1];
	}
	
	}
};
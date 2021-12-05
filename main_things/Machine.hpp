#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Street.hpp"
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
	sf::Color color;
	std::vector<Street>* all_streets;
	float traversed path;
	
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
			std::cout<<"Machine:"<<"generate_way: vector way: ";
			std::cout<<std::endl;
			for(int i = 0;i<way.size();i++) std::cout<<way[i];
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
	
	
	Machine(Street street1, std::vector<Street> &all_streets){
	std::cout<<"Machine:"<<"Construct"<<std::endl;//debug
		srand(time(0));
		this->all_streets = &all_streets;
		
		std::cout<<"Machine:"<<"number of streets: "<<this->all_streets->size()<<std::endl;//debug
		
		street_count = 0;
		number = -1;
		is_way_completed = 0;
		length = 25.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		this->street = street1; //defining current street
		
		std::cout<<"Machine:"<<"number of street: "<<street.number<<std::endl;//debug
		
		dx = street.street_dx;
		dy = street.street_dy;
		
		max_streets = 1+rand()%10;//
		
		x = street.cross[0].point.x;
		y = street.cross[0].point.y;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		
		generate_way();
		//std::cout<<"Machine:"<<"catch me if you can"<<std::endl;//debug
		
		srand(time(0));
		
		velocity = 50+rand()%150;
		rectangle.setPosition(sf::Vector2f(x,y));
		
		
		//generate()
		color = sf::Color(rand()%255,rand()%255,rand()%255);
		rectangle.setFillColor(color);
		
		//debug
		//showInf();
		/*
		std::cout<<"car x "<<x<<" car y "<<y<<std::endl;
		std::cout<<"rectangle x"<<rectangle.getPosition().x<<" rectangle y "<<rectangle.getPosition().y<<std::endl;
		std::cout<<"street x"<<street.cross[0].point.x<<" street y "<<street.cross[0].point.y<<std::endl;
		std::cout<<std::endl;
		*/
		std::cout<<"Machine:"<<"Construct_end"<<std::endl;//debug
	}
	
	
	void move(float time){
	/* debug
		std::cout<<"car x "<<x<<" car y "<<y<<std::endl;
		std::cout<<"car dx "<<dx<<" car dy "<<dy<<std::endl;
		std::cout<<"$time = "<<time<<std::endl;
	*/
		x+=time*dx*velocity;//troubles in time
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
		/* debug
		std::cout<<"car_next x "<<x<<" car_next y "<<y<<std::endl;
		std::cout<<"car_next dx "<<dx<<" car_next dy "<<dy<<std::endl;
		*/
		
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
	//std::cout<<"str count: "<<street_count<<" "<<way.size()<<std::endl;//debug
	if(next_cross.number==street.cross[0].number){
		
	}
		
	street = all_streets[way[street_count]];
	
	//std::cout<<"next street: "<<street.number<<std::endl;//debug
	
	//std::cout<<next_cross.number<<" "<<street.cross[0].number<<std::endl;//debug
	if(next_cross.number==street.cross[0].number){
		dx = street.street_dx;
		dy = street.street_dy;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		x = cur_cross.point.x;
		y = cur_cross.point.y;
		
	}else{
		dx = -street.street_dx;
		dy = -street.street_dy;
		next_cross = street.cross[0];
		cur_cross = street.cross[1];
		x = cur_cross.point.x;
		y = cur_cross.point.y;
	}
	
	}
};
//std::cout<<"Machine:"<<"catch me if you can"<<std::endl;//debug
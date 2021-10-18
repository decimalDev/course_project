#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
class CrossRoads{
	public:
	sf::Vector2f point;
	float length;
	float cos_angle;
	int number;
	CrossRoads(){}
	CrossRoads(sf::Vector2f point, int w_width, int w_height){
		length = sqrt((point.x-w_width)*(point.x-w_width) + (point.y-w_height)*(point.y-w_height));
		cos_angle = (point.x-w_width)/length;
		this->point = point;
	}
};

class Street{
	public:
	CrossRoads cross[2];
	int number;
	int counts_of_ways;
	float width;
	float length;
	float right_dx;
	float right_dy;
	Street *next_street;
	Street *last_street;
	Street(){}
	Street(CrossRoads crs1, CrossRoads crs2, int i){
		cross[0] = crs1;
		cross[1] = crs2;
		number = i;
		length = sqrt((cross[1].point.x - cross[0].point.x)*(cross[1].point.x - cross[0].point.x) + (cross[1].point.y - cross[0].point.y)*(cross[1].point.y - cross[0].point.y));
		right_dx = (cross[1].point.x - cross[0].point.x)/length;
		right_dy = (cross[1].point.y - cross[0].point.y)/length;
	}
	void next_Street(Street *strt){
		next_street = strt;
	}
	void last_Street(Street *strt){
		last_street = strt;
	}
};

class Machine{
	public:
	float x;
	float y;
	float width;
	float length;
	float dx;
	float dy;
	float velocity;
	Street *street;
	sf::RectangleShape rectangle;
	Machine(Street *street){
		length = 50.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		this->street = street;
		x = street->cross[0].point.x;
		y = street->cross[0].point.y;
		dx = street->right_dx;
		dy = street->right_dy;
		velocity = 100;
		rectangle.setPosition(sf::Vector2f(x,y));
		std::cout<<"create: "<<this->street->cross[1].point.x<<" "<<this->street->cross[1].point.y<<" "<<this->street->number<<std::endl;
		//sf::sleep(sf::seconds(0.5));
	}
	void move(float time){
		x+=time*dx*velocity;
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
	}
	bool is_in_cross(){
		//std::cout<<street->next_street->number<<std::endl;
		//std::cout<<street->cross[1].point.x<<" "<<street->cross[1].point.y<<" "<<street->number<<std::endl;
		//sf::sleep(sf::seconds(0.5));
	return (((x - street->cross[1].point.x)*(x - street->cross[1].point.x) + (y - street->cross[1].point.y)*(y - street->cross[1].point.y))<100);
	}
	void next_Street(){
		street = street->next_street;
		dx = street->right_dx;
		dy = street->right_dy;
		std::cout<<"next\n"<<street->right_dx<<" "<<street->right_dy<<std::endl;
	}
};

class Map{
	public:
	std::vector<Street> streets;
	std::vector<Machine> machines;
	Map(){}
	Map(std::vector<Street> strts){
		streets = strts;
		for(int i = 1;i<streets.size();i++){
			streets[i-1].next_Street(&streets[i]);
			std::cout<<streets[i-1].next_street->number<<std::endl;
	}
		machines.push_back(Machine(&streets[0]));
	}
};



/*
	улицы не могут иметь больше 4х соеденений с другими улицами в концах улицы
	
	улицы будут лежать в полярной системе координат для определения однозначного расположения
	начало отчёта в середение карты
	
	длина улицы будет умнажаться на некоторый коэфициент масштабирования чтобы при масштабировании карты отношение длин улиц оставался одинаковой
	*/
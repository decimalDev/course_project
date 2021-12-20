#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>


class CrossRoads{
	public:
	sf::Vector2f point;
	int number;
	CrossRoads(){}
	CrossRoads(sf::Vector2f point){
		this->point = point;
	}
	
	friend std::ostream& operator<<(std::ostream& out,const CrossRoads& c){
		out<<"CrossRoads: "<<c.point.x<<" "<<c.point.y<<std::endl;
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in,CrossRoads& r){
	//std::cout<<"hi"<<std::endl;
		std::string s;
		in>>s;
		
		int x,y;
		in>>x>>y;
		r.point = sf::Vector2f(x,y);
		return in;
	}
	CrossRoads& operator=(const CrossRoads& r){
		this->point = r.point;
		this->number = r.number;
		return *this;
	}
};
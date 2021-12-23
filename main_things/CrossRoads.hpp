#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>


class CrossRoads{
	private:
	int number;
	sf::Vector2f point;
	
	public:
	int getNumber(){ return number; }
	void setNumber(int num){ number = num; }
	void setPoint(sf::Vector2f point){ this->point = point; }
	sf::Vector2f getPoint(){ return point; }
	
	CrossRoads(){}
	CrossRoads(sf::Vector2f point){
		this->point = point;
	}
	
	friend std::ostream& operator<<(std::ostream& out,const CrossRoads& c){
		out<<"CrossRoads: "<<c.point.x<<" "<<c.point.y<<std::endl;
		return out;
	}

	CrossRoads& operator=(const CrossRoads& r){
		this->point = r.point;
		this->number = r.number;
		return *this;
	}
};
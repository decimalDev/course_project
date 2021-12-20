#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include"CrossRoads.hpp"
class Street{
	public:
	CrossRoads cross[2];
	int number;
	float length;
	float street_dx;
	float street_dy;
	int is_last_street = 1;
	std::vector<int> next_streets;//store numbers of streets
	std::vector<int> last_streets;//store numbers of streets
	Street(){}
	Street(CrossRoads crs1, CrossRoads crs2){
	is_last_street = 1;
		cross[0] = crs1;
		cross[1] = crs2;
		length = sqrt((cross[1].point.x - cross[0].point.x)*(cross[1].point.x - cross[0].point.x) + (cross[1].point.y - cross[0].point.y)*(cross[1].point.y - cross[0].point.y));
		street_dx = (cross[1].point.x - cross[0].point.x)/length;
		street_dy = (cross[1].point.y - cross[0].point.y)/length;
	}
	void next_Street(Street &strt){
		next_streets.push_back(strt.number);
	}
	void last_Street(Street &strt){
		last_streets.push_back(strt.number);
	}
//	/*
	friend std::ostream& operator<<(std::ostream& out,const Street& s){
	
		out<<"Street:\n"<<s.cross[0]<<s.cross[1];
		out<<"number: "<<s.number<<std::endl;
		out<<"length: "<<s.length<<std::endl;
		out<<"street_dx: "<<s.street_dx<<std::endl;
		out<<"street_dy: "<<s.street_dy<<std::endl;
		out<<"is_last_street: "<<s.is_last_street<<std::endl;
		out<<"next_streets: "<<std::endl;
		out<<"size: "<<s.next_streets.size()<<std::endl;
		for(int i = 0;i<s.next_streets.size();i++) out<<s.next_streets[i]<<" ";
		out<<std::endl;
		out<<std::endl;
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in,Street& r){
		std::string s;
		char a;
		in>>s;
		CrossRoads cr[2];
		in>>cr[0]>>cr[1];in>>s;
		r.cross[0] = cr[0];
		r.cross[1] = cr[1];
		
		in>>r.number; in>>s;
		
		in>>r.length; in>>s;
		
		in>>r.street_dx; in>>s;
		
		in>>r.street_dy; in>>s;
		
		in>>r.is_last_street; in>>s;
		in>>s; // read size
		int size;
		in>>size; //in>>a;
		int d;
		std::vector<int> streets;
		for(int i = 0;i<size;i++){
			in>>d;
			streets.push_back(d);
		}
		r.next_streets = streets;
		return in;
	}
};
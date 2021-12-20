#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Machine.hpp"
#include<time.h>
#include "Car.hpp"
#include "Public_transport.hpp"
#include "Bus.hpp"
#include "Train.hpp"
//rewrite
class AbstractModel{
	public:
	std::vector<Street> all_streets;
	std::vector<Machine*> machines;
	std::vector<CrossRoads> all_cross_roads;
	std::vector<TrafficLight> all_traffic_lights;
	int count_of_cars = 10;
	sf::Time time1;
	sf::Time time2;
	sf::Clock clock;
	
	void crt_streets(){ // it's work correctly. Problems not occured
		for(int i = 0;i<all_streets.size();i++){
			for(int j = 0;j<all_streets.size();j++){
			if(i==j) continue;
				if(all_streets[i].cross[1].point==all_streets[j].cross[0].point){ //if end of the i street equalent to start of street j
					all_streets[i].next_Street(all_streets[j]);
					all_streets[j].last_Street(all_streets[i]);
					all_streets[i].is_last_street = 0;
				}
				if(all_streets[i].cross[1].point==all_streets[j].cross[1].point){ //if end of the i street equalent to end of street j
					all_streets[i].next_Street(all_streets[j]);
					all_streets[j].next_Street(all_streets[i]);
					all_streets[i].is_last_street = 0;
					all_streets[j].is_last_street = 0;
				}
				
				if(all_streets[i].cross[0].point==all_streets[j].cross[0].point){ //if start of the i street equalent to start of street j
					all_streets[i].last_Street(all_streets[j]);
					all_streets[j].last_Street(all_streets[i]);
				}
			}
		}
	}
	
	
	
	AbstractModel(){}
	
	AbstractModel(std::vector<Street> &strts){
		std::cout<<"AbstracModel:"<<"Construct"<<std::endl;//debug
		
		srand(time(0));
		all_streets = strts;
		count_of_cars = 10;
		
		//numbering of streets
		for(int i = 0;i<all_streets.size();i++){
			all_streets[i].number = i;
		}
		
		
		//debug
		std::cout<<"AbstracModel:"<<"streets numbers: ";
		for(int i = 0;i<all_streets.size();i++){
			std::cout<<all_streets[i].number<<" ";
		}
		std::cout<<std::endl;
		
		
		crt_streets();
		
		
		
		
		//numering of streets_cross
		int j = 0;
		int flag1 = 1;
		int flag2 = 1;
		int s1,s2;
		for(int i = 0;i<all_streets.size();i++){
			for(int k = 0;k<all_cross_roads.size();k++){ //checking vector all_cross_roads to existence of cross_roads of street i
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
				all_streets[i].cross[0].number = all_cross_roads[s1].number;//giving number for existing in vector cross_roads
			}
			
			if(flag2){
				all_streets[i].cross[1].number = j;
				all_cross_roads.push_back(all_streets[i].cross[1]);
				j++;
			}else{
				all_streets[i].cross[1].number = all_cross_roads[s2].number; //giving number for existing in vector cross_roads
			}
			flag1 = 1;
			flag2 = 1;
		}
		
		//debug
		std::cout<<"AbstracModel:"<<"Cross roads: "<<std::endl;
		for(int i = 0;i<all_cross_roads.size();i++){
			std::cout<<all_cross_roads[i].number<<" "<<all_cross_roads[i].point.x<<" "<<all_cross_roads[i].point.y<<std::endl;
		}
		std::cout<<std::endl;
		
		
		std::cout<<"AbstracModel:"<<"number of streets: "<<all_streets.size()<<std::endl;//debug
		
		//srand(time(0));
		int n;
		for(int i = 0;i<count_of_cars;i++){
			n = rand()%(all_streets.size());
			//Machine* mach;
			Car a;
			Bus b;
			Train c;
			
			switch(rand()%3){
			
			case 0: 
			a = Car(all_streets[n],all_streets); 
			machines.push_back(&a);
			break;
			
			case 1:
			b = Bus(all_streets[n],all_streets); 
			machines.push_back(&b);
			break;
			
			case 2:
			c = Train(all_streets[n],all_streets);
			machines.push_back(&c);
			break;
			
			}
			//machines.push_back(Machine(all_streets[n],all_streets));
		}
		
		std::cout<<"AbstracModel:"<<"number of cars: "<<machines.size()<<std::endl;//debug
		
		
		//std::cout<<"AbstracModel:"<<"catch me if you can"<<std::endl;//debug
		//numering of cars
		for(int i = 0;i<machines.size();i++) machines[i]->number = i;
		
		
		std::cout<<"AbstracModel:"<<"cars: "<<std::endl;//debug
		for(int i = 0;i<machines.size();i++) std::cout<<machines[i]->number<<" ";
		std::cout<<std::endl;
		
	//	/*
		
		for(int i = 0;i<machines.size();i++){//deleting near cars in initional moment
			std::vector<Machine*>::iterator it = machines.end()-1;// take last car
			int f = 0;
			Machine* m1 = *it;//take last car
			for(Machine* m:machines)
				if((m1->x-m->x)*(m1->x-m->x) + (m1->y-m->y)*(m1->y-m->y)<2500&&m->number!=m1->number) f = 1;//if distance less than 50 and it not the same car
			if(f){
				machines.erase(machines.end()-1);
			}
		}
	//	*/
		clock.restart();
		time1 = clock.getElapsedTime();
		
		all_traffic_lights = std::vector<TrafficLight>();
		all_traffic_lights.reserve(all_cross_roads.size());
		std::cout<<"AbstracModel:"<<"TrafficLight loop********************************************************************************"<<std::endl;//debug
		std::cout<<"AbstracModel:"<<"rand = "<<rand()%2<<std::endl;//debug
		for(int i = 0;i<all_streets.size();i++){
			if((rand()+all_streets[i].cross[0].number)%2){
				all_traffic_lights.push_back(TrafficLight(all_streets[i].cross[0],all_streets[i],clock));
				std::cout<<"AbstracModel:"<<"TrafficLight first"<<std::endl;//debug
			}
			if((rand()+all_streets[i].cross[1].number)%2){
				all_traffic_lights.push_back(TrafficLight(all_streets[i].cross[1],all_streets[i],clock));
				std::cout<<"AbstracModel:"<<"TrafficLight second"<<std::endl;//debug
			}
		}
		/*
		int k;
		for(int i = 0;i<machines.size();i++){
			k = rand()%3;
			if(k==0){
				machines[i] = Car();
			}
		}
		*/
		physics();
		std::cout<<"AbstracModel:"<<"Construct_end: Traffic lights size = "<<all_traffic_lights.size()<<std::endl;//debug
		
		//here it works correctly. there isn't any problem occured
		std::cout<<"AbstracModel:"<<"Construct_end"<<std::endl;//debug
	}
	
	
	void checking(){
		std::cout<<"AbstracModel:"<<"checking"<<std::endl;//debug
		std::cout<<"AbstracModel:"<<"checking: Cars:size = "<<machines.size()<<std::endl;//debug
		std::cout<<"AbstracModel:"<<"checking: Traffic lights size = "<<all_traffic_lights.size()<<std::endl;//debug
		//std::cout<<"AbstracModel:"<<"checking: Traffic lights size_error = "<<error->size()<<std::endl;//debug
		int k = 0;

		srand(time(0));
		int n = (rand()+machines.size())%(all_streets.size()); 
		
		int f = 1;
		while(f){
			f = 0;
			for(int j = 0;j<machines.size();j++)
				if(machines[j]->is_way_completed&&!machines[j]->is_public_transport){//||(machines[j].dx==0&&machines[j].dy==0)
					f = 1;
					machines.erase(machines.begin()+j);
					break;
				}
			if(f) break;
		}
		
	
		std::vector<Machine*>::iterator it;
	
		std::cout<<"AbstracModel:"<<"checking: Cars:size = "<<machines.size()<<" count_of_cars: "<<count_of_cars<<std::endl;//debug
		
		if(machines.size()<count_of_cars){//we add only one car in each call
			std::cout<<"AbstracModel:"<<"checking: adding a new car"<<std::endl;//debug
			Car a(all_streets[n],all_streets);
			machines.push_back(&a);//here i should add other transport. rewrite
			int i = 0;
			int f = 1;
			while(f){//number for new car
				f = 0;
				for(Machine *m:machines){
					if(m->number==i){
						i++;
						f = 1;
						//std::cout<<"AbstracModel:"<<"it's work"<<std::endl;//debug
						break;
					}
				}
			}
		
			it = machines.end()-1;
			(*it)->number = i;
			f = 0;
			Machine* m1 = *it;
			
			for(Machine *m:machines)
				if((m1->x-m->x)*(m1->x-m->x) + (m1->y-m->y)*(m1->y-m->y)<2500&&m->number!=m1->number) f = 1;//if distance less than 50 and it not the same car
		
			if(f) machines.erase(machines.end()-1);
		}
	//*/
		
		/*
		for(int j = 0;j<machines.size();j++)
			if(machines[j].is_way_completed) machines.erase(machines.begin()+j);
		*/
		
		std::cout<<"AbstracModel:"<<"checking: Cars:"<<std::endl;//debug
		std::cout<<"AbstracModel:"<<"checking: Cars:size = "<<machines.size()<<std::endl;//debug
		for(int j = 0;j<machines.size();j++)
			std::cout<<machines[j]->number<<" ";//debug
		std::cout<<std::endl;//debug
		
		for(int i = 0;i<machines.size();i++){
			machines[i]->is_there_machine_in_forward = 0;
			for(int j = 0;j<machines.size();j++){
				if(i==j) continue; 
				machines[i]->check_forward(machines[j],clock);
			}
		}
		
		
		std::cout<<"AbstracModel:"<<"checking_end"<<std::endl;//debug
		std::cout<<"AbstracModel:"<<"checking_end: Traffic lights size = "<<all_traffic_lights.size()<<std::endl;//debug
	}
	
	void save(){
		std::ofstream file("AbstractModel.txt");
		file<<"AbstractModel_size: "<<all_streets.size()<<std::endl;
		for(int i = 0;i<all_streets.size();i++)
		file<<all_streets[i];
	}
	
	
	void load_AbstractModel(){
	std::cout<<"AbstracModel:"<<"load_AbstractModel"<<std::endl;//debug
		std::ifstream file("AbstractModel.txt");
		all_streets.clear();
		machines.clear();
		std::string s;
		Street a;
		int size;
		file>>s>>size;
		std::cout<<"AbstracModel:"<<"load_AbstractModel_goood"<<std::endl;//debug
		for(int i = 0;i<size;i++){
			file>>a;
			all_streets.push_back(a);
		}
		
		
		
		int j = 0;
		int flag1 = 1;
		int flag2 = 1;
		int s1,s2;
		for(int i = 0;i<all_streets.size();i++){
			for(int k = 0;k<all_cross_roads.size();k++){ //checking vector all_cross_roads to existence of cross_roads of street i
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
				all_streets[i].cross[0].number = all_cross_roads[s1].number;//giving number for existing in vector cross_roads
			}
			
			if(flag2){
				all_streets[i].cross[1].number = j;
				all_cross_roads.push_back(all_streets[i].cross[1]);
				j++;
			}else{
				all_streets[i].cross[1].number = all_cross_roads[s2].number; //giving number for existing in vector cross_roads
			}
			flag1 = 1;
			flag2 = 1;
		}
		
		//this = &(AbstractModel(all_streets));
		
		showInf();
		
		
		//std::cout<<"AbstracModel:"<<"load_AbstractModel_end"<<std::endl;//debug
		
		
		/*
		srand(time(0));
		int n;
		for(int i = 0;i<count_of_cars;i++){
			n = rand()%(all_streets.size());
			machines.push_back(Machine(all_streets[n],all_streets));
		}
		
		std::cout<<"AbstracModel:"<<"number of cars: "<<machines.size()<<std::endl;//debug
		
		
		//std::cout<<"AbstracModel:"<<"catch me if you can"<<std::endl;//debug
		//numbering of cars
		for(int i = 0;i<machines.size();i++) machines[i].number = i;
		
		
		std::cout<<"AbstracModel:"<<"cars: "<<std::endl;//debug
		for(int i = 0;i<machines.size();i++) std::cout<<machines[i].number<<" ";
		std::cout<<std::endl;
		

		
		for(int i = 0;i<machines.size();i++){//deleting near cars in initional moment
			std::vector<Machine>::iterator it = machines.end()-1;// take last car
			int f = 0;
			Machine m1 = *it;//take last car
			for(Machine m:machines)
				if((m1.x-m.x)*(m1.x-m.x) + (m1.y-m.y)*(m1.y-m.y)<2500&&m.number!=m1.number) f = 1;//if distance less than 50 and it not the same car
			if(f){
				machines.erase(machines.end()-1);
			}
		}

		clock.restart();
		time1 = clock.getElapsedTime();
		physics();
		*/
		
		
		
	}
	AbstractModel& operator=(const AbstractModel& a){
		this->all_streets = a.all_streets;
		this->machines = a.machines;
		this->all_cross_roads = a.all_cross_roads;
		return *this;
	}
	
	void physics(){
	
	std::cout<<"AbstracModel:"<<"physics"<<std::endl;//debug
	std::cout<<"AbstracModel:"<<"physics: Traffic lights size = "<<all_traffic_lights.size()<<std::endl;//debug
	time2 = clock.getElapsedTime();
	
	
	//std::cout<<"time1 = "<<time1.asSeconds()<<" time2 = "<<time2.asSeconds()<<" dt = "<<(double)(time2-time1).asSeconds()<<std::endl<<std::endl;//debug
	
	float t = (time2-time1).asSeconds();
	for(Machine* m: machines){
		Machine* m2 = m; 
		std::cout<<"there is a problem";
		m2->move(t,clock);//rewrite
		std::cout<<"there is a problem";
		if(m->is_in_cross()){
			m->next_Street(all_streets);
		}
	}
	time1 = time2;
	checking();
	//AbstractModel.test2();
	std::cout<<"AbstracModel:"<<"physics_end"<<std::endl;//debug
}

void draw_AbstractModel(sf::RenderWindow &window){
	std::cout<<"AbstracModel:"<<"draw_AbstractModel"<<std::endl;//debug
	std::cout<<"AbstracModel:"<<"draw_AbstractModel: Traffic lights size = "<<all_traffic_lights.size()<<std::endl;//debug
	sf::Vertex line[2];
	
	for(Street &s: all_streets){
		line[0].position = s.cross[0].point;
		line[1].position = s.cross[1].point;
		window.draw(line,2,sf::Lines);
	}
	
	for(Machine* m: machines)
		window.draw(m->rectangle);
	
	for(TrafficLight &l: all_traffic_lights){
		window.draw(l.shape);
	}
	std::cout<<"AbstracModel:"<<"draw_AbstractModel_end"<<std::endl;//debug
}

void showInf(){
	std::cout<<"*****************************"<<std::endl;
	
	//debug
		std::cout<<"AbstracModel:"<<"Cross roads: "<<std::endl;
		for(int i = 0;i<all_cross_roads.size();i++){
			std::cout<<all_cross_roads[i].number<<" "<<all_cross_roads[i].point.x<<" "<<all_cross_roads[i].point.y<<std::endl;
		}
		std::cout<<std::endl;
	
	std::cout<<"AbstracModel:"<<"streets numbers: ";
		for(int i = 0;i<all_streets.size();i++){
			std::cout<<all_streets[i].number<<" ";
		}
		std::cout<<std::endl;
		std::cout<<"*****************************"<<std::endl;
}
};
//std::cout<<"AbstracModel:"<<"catch me if you can"<<std::endl;//debug
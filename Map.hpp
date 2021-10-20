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
	std::vector<Street> next_streets;
	std::vector<Street> last_streets;
	Street(){}
	Street(CrossRoads crs1, CrossRoads crs2, int i){
		cross[0] = crs1;
		cross[1] = crs2;
		number = i;
		length = sqrt((cross[1].point.x - cross[0].point.x)*(cross[1].point.x - cross[0].point.x) + (cross[1].point.y - cross[0].point.y)*(cross[1].point.y - cross[0].point.y));
		right_dx = (cross[1].point.x - cross[0].point.x)/length;
		right_dy = (cross[1].point.y - cross[0].point.y)/length;
	}
	void next_Street(Street &strt){
		next_streets.push_back(strt);
	}
	void last_Street(Street strt){
		last_streets.push_back(strt);
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
	std::vector<Street> way;
	Street street;
	sf::RectangleShape rectangle;
	sf::Color color;
	
	void generate_way(std::vector<Street> streets2){
		way.push_back(street);
		Street str = street;
		while(!str.next_streets.empty()){
			int n = rand()%(str.next_streets.size());
			str = str.next_streets[n];
			for(Street s:streets2){
				if(str.number==s.number){
					str=s;
					std::cout<<"result: "<<str.number<<std::endl;
					break;
					
				}
				
			}
			way.push_back(str);
			
			}
			for(int i = 0;i<way.size();i++)
			std::cout<<"Street "<<way[i].number<<" "<<way[i].right_dx<<" "<<way[i].right_dy<<std::endl;

	}
	Machine(Street street1, std::vector<Street> streets2){
		length = 50.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		this->street = street1;
		x = street.cross[0].point.x;
		y = street.cross[0].point.y;
		dx = street.right_dx;
		dy = street.right_dy;
		velocity = 100;
		rectangle.setPosition(sf::Vector2f(x,y));
		//std::cout<<"before"<<std::endl;
		
		generate_way(streets2);
		color = sf::Color(rand()%255,rand()%255,rand()%255);
		rectangle.setFillColor(color);

	}
	void move(float time){
		x+=time*dx*velocity;
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
	}
	bool is_in_cross(){
	return (((x - street.cross[1].point.x)*(x - street.cross[1].point.x) + (y - street.cross[1].point.y)*(y - street.cross[1].point.y))<100);
	}
	
	void next_Street(){
	if(way.size()==0) return;
	way.erase(way.begin());
	if(way.size()==0){
		dx = 0;
		dy = 0;
		return;
	}
	street = way[0];
	dx = street.right_dx;
	dy = street.right_dy;
	std::cout<<"cur_street: "<<street.number<<std::endl;
	}
};
bool find(Street x, Street y){
	return (x.cross[1].point == y.cross[0].point);
}

class Map{
	public:
	std::vector<Street> streets;
	std::vector<Machine> machines;
	
	void crt_streets(){
		for(int i = 0;i<streets.size();i++){
			for(int j = 0;j<streets.size();j++)
				if(find(streets[i],streets[j]))
					streets[i].next_Street(streets[j]);
		}
	}
	
	Map(){}
	Map(std::vector<Street> &strts){
		streets = strts;
		crt_streets();
		int n;
		for(int i = 0;i<10;i++){
		n = rand()%(streets.size());
		machines.push_back(Machine(streets[n],streets));
		}
		
	}
	void checking(){
	int k = 0;
	int n = rand()%(streets.size()); 
	/*
		for(int i = 0;i<machines.size();i++){
		for(int j = 0;j<machines.size();j++)
		if(machines[j].dx==0&&machines[j].dy==0) k = 1;
		if((machines[i].dx!=0||machines[i].dy!=0))  k=0;
		else k = 1;
		}
		if(k==1) 
			for(int i = 0;i<10;i++){
		n = rand()%(streets.size());
		machines.push_back(Machine(streets[n],streets));
	*/
	for(int j = 0;j<machines.size();j++)
	if((machines[j].dx!=0||machines[j].dy!=0))  k++;
		if(k<10) machines.push_back(Machine(streets[n],streets));
	//}
	}
	
	
};



/*
	улицы не могут иметь больше 4х соеденений с другими улицами в концах улицы
	
	улицы будут лежать в полярной системе координат для определения однозначного расположения
	начало отчёта в середение карты
	
	длина улицы будет умнажаться на некоторый коэфициент масштабирования чтобы при масштабировании карты отношение длин улиц оставался одинаковой
	
	ошибка в представлении вектора(массива) хронящий список но на самом деле оно не хранило список
	*/
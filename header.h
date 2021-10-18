#include<vector>
#include<string>
class Moveable{
	private:
	float[2] position;
	float cur_v,v_max;
	float[2] direction;
	vector<int[2]> way;
	bool is_moving;
	
	public:
	void move();
	float[2] getPosition();
	float getCur_Velocity();
	float getMax_Velocity();
	float[2] getDirection();
	bool is_moving();
	void stop();
}

class Transport:public Moveable{
	private:
	string number;
	int[2] size;
	int weight;
	bool is_light_on;
	float acceleration;
	bool is_in_accident;
	
	public:
	string getNumber();
	int[2] getSize();
	int getWeight();
	void turn_on_light();
	void turn_off_light();
	void braking();
	void sound();
}

class People: public Moveable{
	private:
	string name;
	string last_name;
	int age;
	string sex;
	bool in_a_transport
	
	public:
	string getName();
	string getLast_Name();
	int getAge();
	string getSex();
	bool in_a_Transport();
}

class Car: public Transport{
	private:
	bool right_light, left_light;
	
	public:
	bool state_right_light();
	bool state_left_light();
	void turn_on_right_light();
	void turn_off_right_light();
	void turn_on_left_light();
	void turn_off_left_light();
	
}

class Public_transport: public Transport{
	private:
	int number_of_place;
	float price;
	bool are_doors_open;
	bool is_full;
	vector<float[2]> station;
	
	public:
	void open_doors();
	bool is_Full();
}

class Train: public Public_transport{
	private:
	int cur_rails;
	
	public:
	int num_of_rails();
}

class Bus: public Public_transport{
	private:
	bool right_light, left_light;
	
	public:
	bool state_right_light();
	bool state_left_light();
	void turn_on_right_light();
	void turn_off_right_light();
	void turn_on_left_light();
	void turn_off_left_light();
}

/* Moveable
	direction - единичный вектор
	way - последовательность координат описывающие путь обьекта
	direction*cur_v - вектор движения
	stop() - зануляет cur_v
	move() - делает cur_v больше нуля
*/

/* Transport
	number - номер машины
	braking - торможение(сбавление скорости)
*/


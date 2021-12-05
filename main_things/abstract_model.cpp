
#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>
#include<string>
#include "AbstractModel.hpp"
#include<iostream>
Street crt_street(int w_width, int w_height, std::vector<sf::Vector2f> &lines,int i){
	sf::Vector2f our_line1 = lines[i-1];
	sf::Vector2f our_line2 = lines[i];
	//lines.pop_back();
	CrossRoads cross[2];
	cross[0] = CrossRoads(our_line1);
	cross[1] = CrossRoads(our_line2);
	Street street(cross[0], cross[1]);
	return street;
}

AbstractModel generation(std::vector<Street> &streets, std::vector<sf::Vector2f> &lines, int w_width, int w_height){
	for(int i = 1;i<lines.size();i+=2){
		streets.push_back(crt_street(w_width, w_height, lines, i));
	}
	
	AbstractModel abstractModel(streets);
	return abstractModel;
}

void start(AbstractModel &abstractModel, sf::Text &text,int &mode, sf::Clock &clock, int &started, sf::Time &time1){
	text.setString("started");
	started = 1;
	mode = 2;
	//abstractModel.clock.restart();
	abstractModel.time1 = clock.getElapsedTime();
}



void PressedLeftButtonMouse(sf::Vector2f &localPosition,std::vector<sf::Vector2f> &lines, sf::RenderWindow &window,int &mode,sf::CircleShape &shape, sf::CircleShape &shape2){
	localPosition.x = (float) sf::Mouse::getPosition(window).x;
	localPosition.y = (float) sf::Mouse::getPosition(window).y;
	if(mode==0&&lines.size()>0&&
		((localPosition.x-lines.back().x)*(localPosition.x-lines.back().x)+(localPosition.y-lines.back().y)*(localPosition.y-lines.back().y)>10000)){
			lines.push_back(localPosition);
			mode = ++mode%2; //mode = 0 если точка не выбрана или когда уже выбираем 2ю точку
			shape.setFillColor(sf::Color::Red);
		}
		else if(lines.size()==0){
			lines.push_back(localPosition);
			
		}
	else if(mode==1){ // mode = 1 режим когда надо выбрать точку чтобы перейти в режим 0 где мы создаем путь выбрав вторую точку
		for(int i = 0;i<lines.size();i++){
		localPosition.x = (float) sf::Mouse::getPosition(window).x;
		localPosition.y = (float) sf::Mouse::getPosition(window).y;
		if((localPosition.x-lines[i].x)*(localPosition.x-lines[i].x) + (localPosition.y-lines[i].y)*(localPosition.y-lines[i].y)<50){
			lines.push_back(lines[i]);
			shape.setPosition(lines[i]);
			shape.setFillColor(sf::Color::Green);
			mode = ++mode%2;
			break;
		}
		}
	}else if(mode==3){
		for(int i = 0;i<lines.size();i++){
		localPosition.x = (float) sf::Mouse::getPosition(window).x;
		localPosition.y = (float) sf::Mouse::getPosition(window).y;
		if((localPosition.x-lines[i].x)*(localPosition.x-lines[i].x) + (localPosition.y-lines[i].y)*(localPosition.y-lines[i].y)<50){
			lines.push_back(lines[i]);
			shape2.setPosition(lines[i]);
			mode = 1;
			shape.setFillColor(sf::Color::Red);
			break;
		}
	}
	}
}

void Mode1(std::vector<sf::Vector2f> &lines, sf::Vector2f &localPosition, sf::CircleShape &shape, sf::RenderWindow &window){
	for(int i = 0;i<lines.size();i++){
		localPosition.x = (float) sf::Mouse::getPosition(window).x;
		localPosition.y = (float) sf::Mouse::getPosition(window).y;
		if((localPosition.x-lines[i].x)*(localPosition.x-lines[i].x) + (localPosition.y-lines[i].y)*(localPosition.y-lines[i].y)<2500)
			shape.setPosition(lines[i]);
		
	}
	}

void Mode3(std::vector<sf::Vector2f> &lines, sf::Vector2f &localPosition, sf::CircleShape &shape2, sf::RenderWindow &window){
	for(int i = 0;i<lines.size();i++){
	if(lines[i].x==lines.back().x&&lines[i].y==lines.back().y) continue;
		localPosition.x = (float) sf::Mouse::getPosition(window).x;
		localPosition.y = (float) sf::Mouse::getPosition(window).y;
		if((localPosition.x-lines[i].x)*(localPosition.x-lines[i].x) + (localPosition.y-lines[i].y)*(localPosition.y-lines[i].y)<2500)
			shape2.setPosition(lines[i]);
		
	}
}



AbstractModel abstract_model_view(){
	int w_width = 800;
	int w_height = 800;
	sf::RenderWindow window(sf::VideoMode(w_width,w_height),"picture");
	
	std::vector<sf::Vector2f> lines;
	sf::Vector2f localPosition;
	sf::Vertex line[2];
	
	sf::Text text;
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	text.setFont(font);
	text.setString("drawing mode");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setStyle(sf::Text::Bold);
	text.setPosition(0,0);
	
	int mode = 0;
	
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	char stime[2];
	//stime[0] = ((int)time.asSeconds())%10+'0';
	stime[0] = mode+'0';
	stime[1] = '\0';
	
	sf::Text text1;
	text1.setFont(font);
	text1.setString(stime);
	text1.setCharacterSize(24);
	text1.setFillColor(sf::Color::White);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(200,0);
	
	
	int started = 0;

	sf::CircleShape shape(5);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(2.5,2.5);
	
	sf::CircleShape shape2(5);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(2.5,2.5);
	shape.setFillColor(sf::Color::Red);
	
	std::vector<Street> streets;
	
	
	int exit = 0;
	
	AbstractModel abstractModel;
	
	float frametime = 0;
	int frame = 0;
	
	sf::Time time1;
	sf::Time time2;
	
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
		
			switch(event.type){
				case sf::Event::Closed: window.close(); break;
				
				case sf::Event::KeyReleased: 
					//if (event.key.code==sf::Keyboard::LControl) PressedLControle(text,mode,started);
					if (event.key.code==sf::Keyboard::Escape){
						if(mode==1){
							abstractModel = generation(streets, lines, w_width, w_height);
							start(abstractModel,text,mode,clock,started,time1);
						}else if(mode==2){ 
						mode = 1;
						abstractModel.machines.clear();
						abstractModel.all_streets.clear();
						abstractModel.all_cross_roads.clear();
						streets.clear();
						
						started = 0;
						}
					}else if(event.key.code==sf::Keyboard::LAlt){
						if(mode==0){
							mode = 3;
						}
					}else if(event.key.code==sf::Keyboard::S&&mode==2){ //save map not avaible
						abstractModel.save();
					}
					else if(event.key.code==sf::Keyboard::L){ //loading map not avaible
						if(mode==1||mode==2||mode==0){
						lines.clear();
						streets.clear();
						abstractModel.load_AbstractModel();
						
						for(int i = 0;i<abstractModel.all_streets.size();i++){
							lines.push_back(abstractModel.all_streets[i].cross[0].point);
							lines.push_back(abstractModel.all_streets[i].cross[1].point);
						}
						//lines = lines2;
						start(abstractModel,text,mode,clock,started,time1);
						}
					}else if(event.key.code==sf::Keyboard::Q&&mode==2) return abstractModel;
				break;
				
				case sf::Event::MouseButtonReleased:
				if((event.mouseButton.button==sf::Mouse::Left)){
					PressedLeftButtonMouse(localPosition, lines, window,mode,shape, shape2);
					
				}
			}
			
		}
		
		time = clock.getElapsedTime();
		//stime[0] = ((int)time.asSeconds())%10+'0';
		stime[0] = mode+'0';
		stime[1] = '\0';
		text1.setString(stime);
		
		
		window.clear(sf::Color::Black);

		if(mode!=2){
		for(int i = 1;i<lines.size();i+=2){
			line[0].position = lines[i-1];
			line[1].position = lines[i];
			window.draw(line,2,sf::Lines);
		}
		
		if(mode==1&&lines.size()>1) Mode1(lines, localPosition, shape, window);
		if(mode==3&&lines.size()>0) Mode3(lines, localPosition, shape2, window);
		window.draw(text);
		window.draw(text1);
		if(lines.size()>1) window.draw(shape);
		if(mode==3&&lines.size()>1) window.draw(shape2);
		
		}
		
		if(mode==2){
		abstractModel.draw_AbstractModel(window);
		abstractModel.physics();
		}
		frame++;
	
	//}else{
			
//}
		window.display();
		//std::cout<<"mouse x = "<<sf::Mouse::getPosition(window).x<<" y = "<<sf::Mouse::getPosition(window).y<<std::endl;//debug
	}
//	}
	return abstractModel;
}

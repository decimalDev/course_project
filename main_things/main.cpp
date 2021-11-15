#include "Map.hpp"
int main(){
	int w_width = 800;
	int w_height = 800;
	AbstractModel abstract_model = abstract_model_view(); 
	Map map(w_width,w_height,abstract_model);
	map.loop();
}
//g++ main.cpp -o test.exe -I"C:\Users\Hp\Desktop\SFML-2.5.1\include" -L"C:\Users\Hp\Desktop\SFML-2.5.1\lib" -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -lsfml-audio -lopengl32
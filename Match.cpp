#include "Match.h"
#include "Menu.h"
#include "Game.h"
#include <SFML/Audio/Music.hpp>
#include "GameOver.h"
#include <SFML/System/Time.hpp>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics/Text.hpp>
using namespace std;

Match::Match() {
	stage_music.openFromFile("stage_music.ogg");
	background_texture.loadFromFile("background.jfif");
	background.setTexture(background_texture);
	background.setPosition(0,-150);
	face_texture.loadFromFile("zeds-face.png");
	Zeds_face.setTexture(face_texture);
	Zeds_face.setPosition(250,20);
	Zeds_face.setScale(0.666,0.666);
	coffee_texture.loadFromFile("coffee-pickup.png");
	Pickup.setTexture(coffee_texture);
	Pickup.setPosition(500,20);
	Pickup.setScale(0.666,0.666);
	shadow_texture.loadFromFile("zeds-shadow.png");
	Shadow.setTexture(shadow_texture);
	Shadow.setPosition(-200,48);
	Shadow.setScale(2.0,2.0);
	
	coffeeMugTexture.loadFromFile("coffee-pickup.png");
	coffeeMug.setTexture(coffeeMugTexture);
	
	stage_music.setVolume(10);
	// stage_music.play();
	
	int min_y = 230;
	int max_y = 341;
	
	enemy_texture.loadFromFile("calc.png");
	
	scoreFont.loadFromFile("FreePixel.ttf");
	
	scoreText.setFont(scoreFont);
	scoreText.setString("score: ");
	scoreText.setCharacterSize(40);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(150,8.7);
	scoreText.setColor(sf::Color::Red);
	
	scoreToStr = to_string(puntaje);
	scorePrint.setFont(scoreFont);
	scorePrint.setString(scoreToStr);
	scorePrint.setCharacterSize(40);
	scorePrint.setStyle(sf::Text::Bold);
	scorePrint.setPosition(300,8.7);
	scorePrint.setColor(sf::Color::Red);
}

void Match::Draw (RenderWindow & window) {
	window.clear(Color(125,60,0,100));		///maximo 255
	window.draw(background);
	//window.draw(Zeds_face);
	window.draw(Pickup);
	//window.draw(score_text);
	window.draw(Shadow);
	player.Draw(window); 
/*	shadow.Draw(window); */
	
	scorePrint.setString(scoreToStr);
	window.draw(scoreText);
	window.draw(scorePrint);
	
	for(int i = 0; i<enemies.size(); i++) {
		enemies[i].Draw(window);
	}
	
	window.display();
}

bool estaafuera(Enemy enemigo){
	if(enemigo.posicion().x==-10){
		return true;
	}else{
		return false;
	}
}

void Match::Update ( Game &gamee ) {
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
		gamee.SetScene(new Menu());
		stage_music.stop();
	}
	player.Update();
	for(Enemy &e : enemies) {
		e.Update();
	}
	
	Time time = tiempoenemigos.getElapsedTime();
	float secsPassed  = time.asSeconds();
	
	if(secsPassed >= distan) {
		Enemy aux(enemy_texture,speed);
		
		int result = rand() % 2; 
		if(result == 1){
			aux.CambiarPosicion(341,0);
		}else{
			aux.CambiarPosicion(230,0);
		}
		enemies.push_back(aux);
		speed=speed-0.2;
		int valordistan = rand()%3;
		if(valordistan == 1){
			distan=distan-0.02;
		}else{
			if(valordistan == 2){
				distan=distan+0.10;
			}else{
				distan=distan-0.15;
			}
		}
		tiempoenemigos.restart();
		
	}
	
	
	auto it = remove_if(enemies.begin(),enemies.end(),estaafuera);
	int cant = enemies.end()-it;
	enemies.erase(it,enemies.end());
	
	
	//se suman puntos cuando los enemigos vayan siendo eliminados de la pantalla
		puntaje += 1;
		scoreToStr = to_string(puntaje);
	
	for(int i=0;i<enemies.size();i++){ // colisi�n jugador-obst�culo
		auto bb1 = enemies[i].GetBB(); 
		auto bb2 = player.GetBB();
		
	/// modificaciones del RectangleShape de obstaculo para darle mas precisi�n a la colisi�n 
		bb1.height-=10; // se "achica" la altura 
		
		bb2.left+=20;  //se "alarga" la coordenada del lado izquierdo
		bb2.height-=20;// se achica la altura
		bb2.width-=50; // se achica el ancho 
		
		if(bb1.intersects(bb2)){
			gamee.SetScene(new GameOver(puntaje));
		}
	}
	
}

Match::~Match ( ) {
	stage_music.stop();
}

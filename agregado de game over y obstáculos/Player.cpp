#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() : Objeto ("walk.png") , m_pos(270,304){
	m_s.scale(0.5,0.5);
	
	// agregado del texto para el acumulador de puntos
	m_font.loadFromFile("FreePixel.ttf");
	m_text_score.setFont(m_font);
	m_text_score.setString(score + " m");
	m_text_score.setFillColor({150,150,150});
	m_text_score.setPosition(600 ,100);
	m_text_score.setCharacterSize(20);
}


void Player::Update (Time elapsed ) {

	auto tex_sz = m_t.getSize();
	m_s.setTextureRect({(m_num_frame/10)*int(tex_sz.x)/4,0,int(tex_sz.x)/4,int(tex_sz.y)});
	m_num_frame = (m_num_frame+1)%40;
	
	
	
	m_speed.y += 0.15;
	m_pos += m_speed;
	
	score += m_speed.x * elapsed.asSeconds() ; //el score aumenta a medida que pasa el tiempo
	m_text_score.setString(score + " m");
	
	if(m_pos.y>=304){
		m_speed.y = 0;
		m_pos.y = 304;
		if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
			m_speed.y = -6;
		}
	}
	
	m_s.setPosition(m_pos);
}


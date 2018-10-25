#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

void update_state(float dt);
void render_frame();

RenderWindow window;

RectangleShape shape;

Texture tex;

SoundBuffer buf;
Sound sound;

Font font;

int main()
{
	window.create(VideoMode(800, 600), "SFML In Class Example");

	tex.loadFromFile("cowboy.png");

	buf.loadFromFile("pistol.wav");
	sound.setBuffer(buf);

	font.loadFromFile("font.ttf");

	shape.setSize(Vector2f(200, 200));
	shape.setPosition(100, 100);
	//shape.setFillColor(Color::Red);
	shape.setTexture(&tex);

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		update_state(dt);
		render_frame();
		window.display();
	}

	return 0;
}

void update_state(float dt)
{
	Vector2f pos = shape.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Left))
		pos.x -= 200 * dt;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		pos.x += 200 * dt;
	if (Keyboard::isKeyPressed(Keyboard::Up))
		pos.y -= 200 * dt;
	if (Keyboard::isKeyPressed(Keyboard::Down))
		pos.y += 200 * dt;

	if (Keyboard::isKeyPressed(Keyboard::Space) && sound.getStatus() != SoundSource::Playing)
		sound.play();

	shape.setPosition(pos);
}

void render_frame()
{
	window.clear(Color(0, 0, 255));

	window.draw(shape);

	Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setString("Hello, cowboy!");
	text.setFillColor(Color::Green);
	text.setPosition(50, 300);
	window.draw(text);
}
//author mohammad alhourani
//date 17/09/2018

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

float anglebetween( sf::Vector2f t_angle1, sf::Vector2f t_angle2);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");

	sf::CircleShape circleShape(2.0f);
	circleShape.setFillColor(sf::Color::Green);

	sf::Vector2f velocity(0, 0);

	float velocityX = 0;
	float velocityY = 0;

	sf::Vector2f circlePos(100, 496);

	sf::RectangleShape rectangleShape(sf::Vector2f(800.0f,50.0f));
	rectangleShape.setPosition(sf::Vector2f(0.0f, 500.0f));

	sf::Vector2f gravity(0.0f, 9.8f);

	bool onGround = false;

	sf::Clock clock;

	float timeChange = (1.0f / 60.0f);

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Vector2f groundVec(1, 0);



	clock.restart();

	while (window.isOpen())
	{

		//read keyboard inout
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				circlePos = sf::Vector2f(100, 496);

				velocity = sf::Vector2f(0, 0);

				velocityX = 0;

				onGround = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround == true)                
			{
				
				onGround = false;
				velocity = sf::Vector2f(velocityX, velocityY);
			}
			window.clear();

			// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().

			if (onGround == false)
			{
				if (circleShape.getGlobalBounds().intersects(rectangleShape.getGlobalBounds()))
				{
					onGround = true;
				}

				velocity = velocity + gravity * timeChange;

				circlePos = circlePos + (velocity * timeChange) + 0.5f*gravity*(timeChange*timeChange);
			}

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				velocityX += 1;
				velocity.x = static_cast<float>(velocityX);
				std::cout << anglebetween(velocity, groundVec) << " angle from ground" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				velocityX += -1;

				if (velocityX < 0)
				{
					velocityX = 0;
				}

				velocity.x = static_cast<float>(velocityX);
				std::cout << anglebetween(velocity, groundVec) << " angle from ground" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				velocityY += 1;
				velocity.y = static_cast<float>(velocityY);

				if (velocityY > 0)
				{
					velocityY = 0;
				}

				std::cout << std::to_string(velocityY) << "velocity" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				velocityY += -1;
				velocity.y = static_cast<float>(velocityY);

				if (velocityY > 0)
				{
					velocityY = 0;
				}

				std::cout << std::to_string(velocityY) << "velocity" << std::endl;
			}
			

			//update shape on screen
			circleShape.setPosition(circlePos);

			window.draw(rectangleShape);
			window.draw(circleShape);
			

			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}



	}

	return 0;
}

float anglebetween(sf::Vector2f t_angle1, sf::Vector2f t_angle2)
{
	float angleBetween = 0;

	float dotProduct = 0;
	float directionA1 = 0;
	float directionA2 = 0;

	dotProduct = (t_angle1.x * t_angle2.x) + (t_angle1.y * t_angle2.y);

	directionA1 = sqrt((t_angle1.x * t_angle1.x) + (t_angle1.y * t_angle1.y));
	
	directionA2 = sqrt((t_angle2.x * t_angle2.x) + (t_angle2.y * t_angle2.y));

	angleBetween =  std::acos(dotProduct / (directionA1 * directionA2));

	angleBetween = angleBetween * (180.0 / 3.14);

	return angleBetween;
}

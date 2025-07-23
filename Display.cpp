#include "Display.hpp"

IMPLEMENT_SUBCLASS(Display, "Display")
EMPTY_DELETEDATA(Display)
EMPTY_SLOTTABLE(Display);
EMPTY_COPYDATA(Display);

BEGIN_EVENT_HANDLER(Display)
ON_EVENT(LEFT_ARROW_KEY, moveLeft)
ON_EVENT(RIGHT_ARROW_KEY, moveRight)
ON_EVENT(DOWN_ARROW_KEY, moveDown)
ON_EVENT(UP_ARROW_KEY, moveUp)
ON_EVENT(SPACE_BAR, startGame)
END_EVENT_HANDLER()

Display::Display() {
	STANDARD_CONSTRUCTOR();

}

bool Display::startGame() {
	collisionCheckSet.clear();
	snake.clear();
	if (getComponents() != nullptr) {
		getComponents()->clear();
	}
	direction = 3;
	xpos = 0, ypos = 5, score = 0;
	playing = true;
	createApple();
	return true;
}

bool Display::moveLeft() {
	if (direction == 3) return false;
	direction = 1;
	return true;
}

bool Display::moveDown() {
	if (direction == 4) return false;
	direction = 2;
	return true;
}

bool Display::moveRight() {
	if (direction == 1) return false;
	direction = 3;
	return true;
}

bool Display::moveUp() {
	if (direction == 2) return false;
	direction = 4;
	return true;
}

void Display::updateData(const double dt)
{
	BaseClass::updateData(dt);
	if (playing) {
		if (mixr::base::getComputerTime() - lastMove > .15) {
			lastMove = mixr::base::getComputerTime();
			
			switch (direction) {
			case(1): {
				xpos -= 1;
				break;
			}
			case(2): {
				ypos -= 1;
				break;
			}
			case(3): {
				xpos += 1;
				break;
			}
			case(4): {
				ypos += 1;
				break;
			}
			}
			if (collisionCheckSet.find(std::to_string(xpos) + std::to_string(ypos)) != collisionCheckSet.end()
				|| xpos < 0 || xpos > 9 || ypos < 0 || ypos > 9) {
				playing = false;
				std::cout << "loser.. you got " << score;
			}
			else {
				mixr::graphics::Polygon* square = new mixr::graphics::Polygon();
				mixr::base::Vec3d* vert = new mixr::base::Vec3d[4];
				vert[0].set(xpos, ypos, 0);  // Bottom-left corner
				vert[1].set(xpos + 1.0, ypos, 0);  // Bottom-right corner
				vert[2].set(xpos + 1.0, ypos + 1.0, 0);  // Top-right corner
				vert[3].set(xpos, ypos + 1.0, 0);  // Top-left corner
				// Set vertices to the polygon
				square->setVertices(vert, 4);
				std::string name = std::to_string(xpos) + std::to_string(ypos);
				snake.push_back(std::to_string(xpos) + std::to_string(ypos));
				collisionCheckSet.insert(std::to_string(xpos) + std::to_string(ypos));
				mixr::base::Pair* pair = new mixr::base::Pair(name.c_str(), square);
				addComponent(pair);
				//remove last bodypart
				if (std::to_string(xpos) + std::to_string(ypos) == apple) {
					score++;
					createApple();
				}
				else if(snake.size() > 1) 
				{
					mixr::base::PairStream* pairStream = getComponents();
					pairStream->remove(findByName(snake.front().c_str()));
					collisionCheckSet.erase(snake.front());
					snake.erase(snake.begin());
					
					
				}
				
			}
		}
	}

}


void Display::createApple() {
	//remove last apple
	if (apple != "") {
		mixr::base::PairStream* pairStream = getComponents();
		pairStream->remove(findByName("Apple"));
	}
	while (true) {
		int x = std::rand() % 10;
		int y = std::rand() % 10;
		if (collisionCheckSet.find(std::to_string(x) + std::to_string(y)) != collisionCheckSet.end()) {
		}
		else {
			mixr::graphics::Polygon* square = new mixr::graphics::Polygon();
			mixr::base::Vec3d* vert = new mixr::base::Vec3d[4];
			vert[0].set(x, y, 0);  // Bottom-left corner
			vert[1].set(x + 1.0, y, 0);  // Bottom-right corner
			vert[2].set(x + 1.0, y + 1.0, 0);  // Top-right corner
			vert[3].set(x, y + 1.0, 0);  // Top-left corner
			mixr::base::Color* newColor = new mixr::base::Color();
			newColor->setRed(0.95);
			newColor->setGreen(0.1);
			newColor->setBlue(.1);
			square->setColor(newColor);
			// Set vertices to the polygon
			square->setVertices(vert, 4);
			std::string name = "Apple";
			mixr::base::Pair* pair = new mixr::base::Pair(name.c_str(), square);
			addComponent(pair);
			apple = std::to_string(x) + std::to_string(y);
			return;
		}
	}
}

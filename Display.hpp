#ifndef __Display_H__
#define __Display_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include "mixr/base/util/system_utils.hpp"
#include <vector>
#include "mixr/graphics/Shapes.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/Vectors.hpp"
#include <unordered_set>
#include "mixr/base/PairStream.hpp"
#include <cmath>
#include "mixr/base/colors/Color.hpp"
class Display final : public  mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(Display, mixr::glut::GlutDisplay)

public:

	Display();
	bool event(const int event, mixr::base::Object* const obj = nullptr) final;
	void updateData(const double dt);
	bool moveLeft();
	bool startGame();
	bool moveDown();
	bool moveRight();
	bool moveUp();

	//void updateTC(const double dt);

private:
	
	std::vector<std::string> snake{};
	std::unordered_set<std::string> collisionCheckSet{};
	int xpos{ 0 }, ypos{ 5 };
	int direction{ 3 };
	int score{};
	double lastMove{};
	void createApple();
	bool playing{};
	std::string apple = {};
};

#endif


#ifndef __MyStation_H__
#define __MyStation_H__

#include "mixr/simulation/Station.hpp"
#include "Display.hpp"

class Station final : public mixr::simulation::Station
{
	DECLARE_SUBCLASS(Station, mixr::simulation::Station)

public:
	Station();
	void reset() final;

private:
	bool displayInit{};
};

#endif

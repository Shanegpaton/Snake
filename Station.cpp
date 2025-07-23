#include "Station.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/ui/glut/GlutDisplay.hpp"


IMPLEMENT_SUBCLASS(Station, "Station")
EMPTY_DELETEDATA(Station)
EMPTY_SLOTTABLE(Station);

Station::Station() {
    STANDARD_CONSTRUCTOR();
}

void Station::copyData(const Station& org, const bool) {
    BaseClass::copyData(org);
}

void Station::reset() {

    mixr::base::PairStream* comp = getComponents();
    mixr::base::List::Item* item = comp->getFirstItem();
    while (item != nullptr) {
        mixr::base::Object* value = item->getValue();
        mixr::base::Pair* pair = dynamic_cast<mixr::base::Pair*>(value);
        auto* component = pair->object();
        if (!displayInit && component->isClassType(typeid(Display))) {
            Display* display = dynamic_cast<Display*>(component);
            display->createWindow();
            displayInit = true;
        }
        item = item->getNext();

    }

    BaseClass::reset();
}

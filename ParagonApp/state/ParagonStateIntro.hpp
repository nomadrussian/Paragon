#ifndef PARAGONSTATEINTRO_HPP
#define PARAGONSTATEINTRO_HPP

#include "ParagonState.hpp"

class ParagonStateIntro : public ParagonState
{
public:
    ParagonStateIntro();
    ~ParagonStateIntro();
    void onEntry() override;
    void onLeave() override;
};

#endif // PARAGONSTATEINTRO_HPP

#ifndef PARAGONSTATEINTRO_HPP
#define PARAGONSTATEINTRO_HPP

#include <ParagonApp/scene/ParagonSceneIntro.hpp>

#include "ParagonState.hpp"

class ParagonStateIntro : public ParagonState
{
private:
    ParagonSceneIntro scene;
public:
    ParagonStateIntro();
    ~ParagonStateIntro();
    void onEntry() override;
    void onLeave() override;
    const ParagonScene& getScene() const;
};

#endif // PARAGONSTATEINTRO_HPP

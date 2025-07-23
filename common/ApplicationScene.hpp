/* Application - base class for ParagonScene and EditorScene */

#ifndef APPLICATIONSCENE_HPP
#define APPLICATIONSCENE_HPP

#include <memory>

class ApplicationScene
{
public:
    virtual ~ApplicationScene() = default;
protected:
    ApplicationScene() = default;
};

#endif // APPLICATIONSCENE_HPP

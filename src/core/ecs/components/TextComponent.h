//
// Created by Justin on 2/04/2021.
//

#ifndef I3D_TEXTCOMPONENT_H
#define I3D_TEXTCOMPONENT_H

#include "../Component.h"
#include "../../Renderer.h"

class TextComponent : public Component {
private:
    std::string text;

    TextOrigin origin = TextOrigin::centre;
public:
    TextOrigin getOrigin() const;

    void setOrigin(TextOrigin origin);

private:
    float size;
    Vector3 offset;

public:
    TextComponent();

    explicit TextComponent(std::string text = "", Vector3 pos = Vector3::zero(), float size = 1, TextOrigin origin = TextOrigin::centre);

    const Vector3& getOffset() const;

    const std::string& getText() const;

    void setText(const std::string& text);

    float getSize() const;

    void setPosition(const Vector3& position);
};


#endif //I3D_TEXTCOMPONENT_H

#pragma once

// engine
#include <core/Signal.hpp>
#include <core/Transformation.hpp>

class FlatTransformation : public Transformation {
public:
    using OnUpdateSignal = Signal<void()>;

public:
    FlatTransformation(const Position& position);
    FlatTransformation();

public:
    OnUpdateSignal& onUpdate();

public:
    virtual const Position& origin() const override;
    virtual const Position& position() const override;
    virtual const Position& scale() const override;
    virtual float rotation() const override;

    virtual void setOrigin(const Position& origin) override;
    virtual void setPosition(const Position& position) override;
    virtual void setScale(const Position& factor) override;
    virtual void setRotation(float angle) override;

private:
    Position mPosition;
    Position mOrigin;
    Position mScale;
    float mAngle;
    OnUpdateSignal mOnUpdate;
};

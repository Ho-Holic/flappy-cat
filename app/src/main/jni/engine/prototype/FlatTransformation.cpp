// engine
#include "FlatTransformation.hpp"

FlatTransformation::FlatTransformation(const Position& position)
    : Transformation()
    , mPosition(position)
    , mOrigin(0.f, 0.f)
    , mScale(1.f, 1.f)
    , m_angle(0.f)
    , mOnUpdate()
{
    //
}

FlatTransformation::FlatTransformation()
    : FlatTransformation(Position(0.f, 0.f))
{
    //
}

FlatTransformation::OnUpdateSignal& FlatTransformation::onUpdate()
{

    return mOnUpdate;
}

const Position& FlatTransformation::position() const
{

    return mPosition;
}

const Position& FlatTransformation::origin() const
{

    return mOrigin;
}

const Position& FlatTransformation::scale() const
{

    return mScale;
}

float FlatTransformation::rotation() const
{

    return m_angle;
}

void FlatTransformation::setPosition(const Position& position)
{

    mPosition = position;
    mOnUpdate.emit();
}

void FlatTransformation::setOrigin(const Position& origin)
{

    mOrigin = origin;
    mOnUpdate.emit();
}

void FlatTransformation::setScale(const Position& factor)
{

    mScale = factor;
    mOnUpdate.emit();
}

void FlatTransformation::setRotation(float angle)
{

    m_angle = angle;
    mOnUpdate.emit();
}

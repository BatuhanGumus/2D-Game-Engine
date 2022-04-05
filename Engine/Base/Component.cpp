#include "Component.h"

using namespace ArtemisEngine;

Component::Component()
{

}

template <typename DerivedType>
DerivedType* Component::GetDerived()
{
    return dynamic_cast<DerivedType*>(this);
}

void Component::Update() {

}

void Component::Render() {

}

void Component::OnTrigger(GameObject* other)
{

}

void Component::OnTriggerEnter(GameObject* other)
{

}

void Component::OnTriggerExit(GameObject* other)
{

}

void Component::Start() {

}

#include "RenderComponent.h"

RenderComponent::RenderComponent() : Component(RENDER) {

	m_bVisible = true;
}

RenderComponent::~RenderComponent() {

}

void RenderComponent::setVisible(bool visible) {

	m_bVisible = visible;
}

bool RenderComponent::getVisible() const {

	return m_bVisible;
}
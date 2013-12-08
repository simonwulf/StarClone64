#include "Component.h"

Component::Component(Component::Type type) {

	m_iType = type;
}

Component::~Component() {

}

Component::Type Component::type() {

	return m_iType;
}
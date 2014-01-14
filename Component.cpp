#include "Component.h"

unsigned int Component::s_iAllocatedMemorySize = 0;

Component::Component(Component::Type type) {

	m_iType = type;

	//m_xGameObject = nullptr;
}

Component::~Component() {

}

void* Component::operator new(size_t size) {

	void* ptr = ::operator new(size);
	s_iAllocatedMemorySize += _msize(ptr);

	return ptr;
}

void* Component::operator new(size_t size, void* p) {

	return ::operator new(size, p);
}

void Component::operator delete(void* ptr) {

	s_iAllocatedMemorySize -= _msize(ptr);
	::operator delete(ptr);
}

unsigned int Component::getAllocatedMemorySize() {

	return s_iAllocatedMemorySize;
}

/*void Component::update(float delta, float elapsedTime) {

}*/

Component::Type Component::getType() {

	return m_iType;
}

GameObject* Component::getGameObject() {

	return m_xGameObject;
}
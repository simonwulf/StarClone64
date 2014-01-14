#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>

template <class Base, class Identifier = unsigned int>
class Factory {

  public:

	Factory() {
	
	}

	~Factory() {
	
		for (CreatorMap::iterator i = m_xCreators.begin(); i != m_xCreators.end(); ++i) {
		
			delete i->second;
		}
	}

	template <class T>
	T* create(Identifier identifier) {
	
		CreatorMap::iterator itr = m_xCreators.find(identifier);

		if (itr == m_xCreators.end())
			return nullptr;

		return static_cast<T*>(itr->second->create());
	}

	Base* create(Identifier identifier) {
	
		return create<Base>(identifier);
	}

	template <class Derived>
	void registerCreator(Identifier identifier) {
	
		Creator<Derived>* creator = new Creator<Derived>();

		CreatorMap::iterator itr = m_xCreators.find(identifier);
		if (itr != m_xCreators.end())
			delete itr->second;

		m_xCreators[identifier] = creator;
	}

  private:

	class SuperCreator {

	  public:

		virtual Base* create() = 0;
	};

	template <class Derived>
	class Creator : public SuperCreator {

	  public:

		Base* create() {
		
			return new Derived();
		}
	};

	typedef std::unordered_map<Identifier, SuperCreator*> CreatorMap;
	CreatorMap m_xCreators;
};

#endif
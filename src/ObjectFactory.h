#pragma once
template
<
	class AbstractProduct,
	class IdentifierType,
	typename ProductCreator = AbstractProduct* (*)()
>
class ObjectFactory
{
private:
	ObjectFactory() {};
	ObjectFactory(ObjectFactory& factory);
	ObjectFactory& operator=(const ObjectFactory& factory);

public:
	bool Register(const IdentifierType& id, ProductCreator creator)
	{
		associations_[id] = creator;
		return true;
	}

	bool Unregister(const IdentifierType& id)
	{
		return associations_.erase(id) == 1;
	}

	AbstractProduct * CreateObject(const IdentifierType& id)
	{
		AssocMap::const_iterator i = associations_.find(id);
		if (i != associations_.end())
		{
			return (i->second)();
		}
		return NULL;
	}

	static ObjectFactory* Instance()
	{
		static ObjectFactory * pFactory = NULL;
		if (!pFactory)
		{
			static ObjectFactory factory;
			pFactory = &factory;
		}
		return pFactory;
	}

private:
	typedef std::map<IdentifierType, ProductCreator> AssocMap;
	AssocMap associations_;
};

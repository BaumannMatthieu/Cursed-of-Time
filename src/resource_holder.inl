#include <iostream>
#include <map>
#include <assert.h>

template<typename ResourceID, typename Resource>
Resource_Holder<ResourceID, Resource>::Resource_Holder() { }

template<typename ResourceID, typename Resource>
Resource_Holder<ResourceID, Resource>::~Resource_Holder()
{ 
	for(auto it = _resources.begin(); it != _resources.end(); it++) {
		delete it->second;
	}
}

template<typename ResourceID, typename Resource>
void Resource_Holder<ResourceID, Resource>::load(const ResourceID resourceID, const std::string file)
{
	Resource* resource = new Resource;
	if(!resource->loadFromFile(file)) {
		std::cerr << "Error when loading the resource : " << file << std::endl;
	}

	_resources.insert(std::pair<ResourceID, Resource>(resourceID, resource));
}

template<typename ResourceID, typename Resource>
Resource Resource_Holder<ResourceID, Resource>::get(const ResourceID resourceID)
{
	auto found = _resources.find(resourceID);
	assert(found != _resources.end());

	return found->second;	
}


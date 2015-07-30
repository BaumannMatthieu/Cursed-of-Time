#ifndef __RESOURCE_HOLDER__
#define __RESOURCE_HOLDER__

#include <map>

template<typename ResourceID, typename Resource>
class Resource_Holder
{
	public:
		Resource_Holder();
		~Resource_Holder();

		void load(const ResourceID resourceID, const std::string file);
		Resource get(const ResourceID resourceID);

	private:
		std::map<ResourceID, Resource*> _resources;			
	
};

#include "resource_holder.inl"

#endif

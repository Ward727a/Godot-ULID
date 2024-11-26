#include "ulid_wrapper.h"

using namespace godot;

void ULIDWrapper::_bind_methods()
{
}

ULIDWrapper::ULIDWrapper()
{
}

ULIDWrapper::ULIDWrapper(ulid::ULID ulid)
{
	this->ulid = ulid;
	defined_ulid = true;
}

ULIDWrapper::~ULIDWrapper()
{
}

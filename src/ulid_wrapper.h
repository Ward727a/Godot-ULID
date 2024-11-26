#ifndef ULIDWRAPPER_H
#define ULIDWRAPPER_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "ulid.hh"

namespace godot {

	class ULIDWrapper : public RefCounted {
		GDCLASS(ULIDWrapper, RefCounted)
	protected:
		static void _bind_methods();
	public:
		bool defined_ulid = false;
		ulid::ULID ulid = NULL;
		ULIDWrapper();
		ULIDWrapper(ulid::ULID ulid);
		~ULIDWrapper();

	};

}

#endif
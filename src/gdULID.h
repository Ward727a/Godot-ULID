#ifndef GDULID_H
#define GDULID_H

#include <chrono>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "ulid.hh"
#include "ulid_wrapper.h"

namespace godot {

	class ULIDWrapper;

	class GDULID : public Object {
		GDCLASS(GDULID, Object)
	private:
		double time_passed;

		static bool is_valid_wrapper(Ref<ULIDWrapper> ULID_Wrapper);
		static time_t double_to_time_t(double timestamp);
		static double time_t_to_double(time_t timestamp);

	protected:
		static void _bind_methods();

	public:

		static void EncodeTime(double timestamp, Ref<ULIDWrapper> ULID_wrapper);
		// TODO: For all static functions below, add & check args
		// LINK: https://github.com/suyash/ulid/blob/master/src/ulid_uint128.hh#L58
		static void EncodeTimeSystemClockNow(Ref<ULIDWrapper> ULID_wrapper);
		static void EncodeEntropyRand(Ref<ULIDWrapper> ULID_wrapper);
		static void EncodeNowRand(Ref<ULIDWrapper> ULID_wrapper);
		static Ref<ULIDWrapper> Create(int rng_key);
		static Ref<ULIDWrapper> CreateNowRand();
		static String ToString(Ref<ULIDWrapper> ULID_wrapper);
		static PackedByteArray ToBinary(Ref<ULIDWrapper> ULID_wrapper);
		static Ref<ULIDWrapper> FromString(String str);
		static Ref<ULIDWrapper> FromBinary(PackedByteArray bytes);
		static int CompareULIDS(Ref<ULIDWrapper> ULID_wrapper1, Ref<ULIDWrapper> ULID_wrapper2);
		static double Time(Ref<ULIDWrapper> ULID_wrapper);

		GDULID();
		~GDULID();
	};

}

#endif
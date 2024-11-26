#include "gdULID.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/string.hpp>


using namespace std;
using namespace godot;

bool GDULID::is_valid_wrapper(Ref<ULIDWrapper> ULID_Wrapper)
{
	if (!ULID_Wrapper->defined_ulid)
	{
		ERR_PRINT_ED("GDULID Wrapper isn't valid, you should not create a wrapper yourself!!");
		return false;
	}
	return true;
}

time_t GDULID::double_to_time_t(double timestamp)
{
	// From: https://stackoverflow.com/a/50495821
	return chrono::system_clock::to_time_t(chrono::system_clock::time_point(chrono::duration_cast<chrono::seconds>(chrono::duration<double>(timestamp))));
}

double GDULID::time_t_to_double(time_t timestamp)
{
	return chrono::duration_cast<chrono::duration<double>>(chrono::system_clock::from_time_t(timestamp).time_since_epoch()).count();
}

void GDULID::_bind_methods() {
	ClassDB::bind_static_method(get_class_static(), D_METHOD("Create", "rng_key"), &GDULID::Create);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("CreateNowRand"), &GDULID::CreateNowRand);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("EncodeTime", "timestamp", "ULID_wrapper"), &GDULID::EncodeTime);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("EncodeTimeSystemClockNow", "ULID_wrapper"), &GDULID::EncodeTimeSystemClockNow);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("EncodeEntropyRand", "ULID_wrapper"), &GDULID::EncodeEntropyRand);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("EncodeNowRand", "ULID_wrapper"), &GDULID::EncodeNowRand);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("ToString", "ULID_wrapper"), &GDULID::ToString);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("ToBinary", "ULID_wrapper"), &GDULID::ToBinary);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("FromString", "str"), &GDULID::FromString);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("FromBinary", "bytes"), &GDULID::FromBinary);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("CompareULIDS", "ULID_wrapper1", "ULID_wrapper2"), &GDULID::CompareULIDS);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("Time", "ULID_wrapper"), &GDULID::Time);
}

void GDULID::EncodeTime(double timestamp, Ref<ULIDWrapper> ULID_wrapper)
{

	if (!is_valid_wrapper(ULID_wrapper))
	{
		return;
	}

	time_t time = double_to_time_t(timestamp);

	ulid::EncodeTime(time, ULID_wrapper->ulid);
}

void GDULID::EncodeTimeSystemClockNow(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return;
	}
	ulid::EncodeTimeSystemClockNow(ULID_wrapper->ulid);
}

void GDULID::EncodeEntropyRand(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return;
	}
	ulid::EncodeEntropyRand(ULID_wrapper->ulid);
}

void GDULID::EncodeNowRand(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return;
	}
	ulid::EncodeNowRand(ULID_wrapper->ulid);
}

Ref<ULIDWrapper> GDULID::Create(int rng_key)
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	Ref<ULIDWrapper> wrapper;
	wrapper.instantiate();
	wrapper->defined_ulid = true;
	wrapper->ulid = ulid::Create(ms.count(), [rng_key]() { return rng_key; });
	return wrapper;
}

Ref<ULIDWrapper> GDULID::CreateNowRand()
{
	Ref<ULIDWrapper> wrapper;
	wrapper.instantiate();
	wrapper->defined_ulid = true;
	wrapper->ulid = ulid::CreateNowRand();
	return wrapper;
}

String GDULID::ToString(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return "";
	}

	String return_string = (ulid::Marshal(ULID_wrapper->ulid).c_str());

	return return_string;
}

PackedByteArray GDULID::ToBinary(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return PackedByteArray();
	}

	std::vector<uint8_t> bytes = ulid::MarshalBinary(ULID_wrapper->ulid);

	PackedByteArray packed_bytes;
	packed_bytes.resize(bytes.size());

	for (uint8_t byte : bytes)
	{
		packed_bytes.push_back(byte);
	}

	return packed_bytes;
}

Ref<ULIDWrapper> GDULID::FromString(String str)
{
	Ref<ULIDWrapper> wrapper;
	wrapper.instantiate();
	wrapper->defined_ulid = true;
	wrapper->ulid = ulid::Unmarshal(str.utf8().get_data());
	return wrapper;
}

Ref<ULIDWrapper> GDULID::FromBinary(PackedByteArray bytes)
{

	if (bytes.size() != 26)
	{
		ERR_PRINT_ED("Invalid ULID binary size (should be 26)");
		return Ref<ULIDWrapper>();
	}

	std::vector<uint8_t> byte_vector;
	for (int i = 0; i < bytes.size(); i++)
	{
		byte_vector.push_back(bytes[i]);
	}
	Ref<ULIDWrapper> wrapper;
	wrapper.instantiate();
	wrapper->defined_ulid = true;
	wrapper->ulid = ulid::UnmarshalBinary(byte_vector);
	return wrapper;
}

int GDULID::CompareULIDS(Ref<ULIDWrapper> ULID_wrapper1, Ref<ULIDWrapper> ULID_wrapper2)
{
	if (!is_valid_wrapper(ULID_wrapper1) || !is_valid_wrapper(ULID_wrapper2))
	{
		return 0;
	}
	return ulid::CompareULIDs(ULID_wrapper1->ulid, ULID_wrapper2->ulid);
}

double GDULID::Time(Ref<ULIDWrapper> ULID_wrapper)
{
	if (!is_valid_wrapper(ULID_wrapper))
	{
		return 0;
	}
	return time_t_to_double(ulid::Time(ULID_wrapper->ulid));
}

GDULID::GDULID() {

}

GDULID::~GDULID() {
}

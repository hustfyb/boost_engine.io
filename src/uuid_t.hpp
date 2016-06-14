#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost;
using namespace boost::uuids;
class uuid_t :public uuid {
public:
	static random_generator rgen;
	static string_generator sgen;
	uuid_t() :uuid(rgen()) {}
	uuid_t(int) :uuid(nil_uuid()) {}
	uuid_t(const char* str) :uuid(sgen(str)) {}
	uuid_t(const uuid& u, const char* str) :uuid(name_generator(u)(str)) {}
	explicit uuid_t(const uuid& u) : uuid(u) {}
	operator uuid() {
		return static_cast<uuid&>(*this);
	}
	operator uuid() const {
		return static_cast<const uuid&>(*this);
	}
public:
	std::string toString() {
		std::stringstream ss; ss << *this;
		std::string str; ss >> str;
		return str;
	}
};

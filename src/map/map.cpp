#include "map/map.h"

#include <stdexcept>

ENV_NSPC::Facility::Facility() noexcept
	: _dc{ 0 }, _rc{ 0 } {
}

ENV_NSPC::Facility::Room& ENV_NSPC::Facility::room(INDEX ind) {
	if (ind > _rc)
		throw std::out_of_range{ "index out of bounds" };
	return _rs[ind];
}
ENV_NSPC::Facility::Door& ENV_NSPC::Facility::door(INDEX ind) {
	if (ind > _dc)
		throw std::out_of_range{ "index out of bounds" };
	return _ds[ind];
}

ENV_NSPC::Facility::Door::Door() noexcept
	: _rs{ 0, 0 } {
}

ENV_NSPC::Facility::Room::Room() noexcept
	: _dc{ 0 } {
}
ENV_NSPC::Facility::Room::Room(size_t dc)
	: _dc{ dc } {
	_ds = std::make_unique<INDEX[]>(_dc);
}

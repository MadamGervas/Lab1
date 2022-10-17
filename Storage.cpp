#include "Storage.h"

Storage* Storage::getInstance()
{
		if (storage == nullptr) {
			storage = new Storage();
		}
		return storage;
}

Clients* Storage::getClients(long id)
{
	return &(this->clients.find(id)->second);
}

Master* Storage::getMaster(long id)
{
	return &(this->master.find(id)->second);
}

Materials* Storage::getMaterials(long id)
{
	return &(this->materials.find(id)->second);
}

Staff_Transfer* Storage::getStaffTransfer(long id)
{
	return &(this->staff_transfer.find(id)->second);
}

Service* Storage::getService(long id)
{
	return &(this->service.find(id)->second);
}

Staff* Storage::getStaff(long id)
{
	return &(this->staff.find(id)->second);
}

Specialization* Storage::getSpecialization(long id)
{
	return &(this->specialization.find(id)->second);
}

void Storage::putClients(Clients clients)
{
	auto it = this->clients.find(clients.getId());
	if (it == this->clients.end()) {
		this->clients[clients.getId()] = clients;
		return;
	}
	auto& c = it->second;
	c.setName(clients.getName());
	c.setSurname(clients.getSurname());
	c.setPatronymic(clients.getPatronymic());
	c.setServiceId(clients.getServiceId());
	c.setPhoneNumber(clients.getPhoneNumber());
	c.setOrderTime(clients.getOrderTime());

}

void Storage::putMaster(Master masters)
{
	auto it = this->master.find(masters.getId());
	if (it == this->master.end()) {
		this->master[masters.getId()] = masters;
		return;
	}
	auto& m = it->second;
	m.setSurname(masters.getSurname());
	m.setStaffId(masters.getStaffId());
}

void Storage::putMaterials(Materials materials)
{
	auto it = this->materials.find(materials.getId());
	if (it == this->materials.end()) {
		this->materials[materials.getId()] = materials;
		return;
	}
	auto& m = it->second;
	m.setName(materials.getName());
	m.setCost(materials.getCost());
	m.setUnitMeasurement(materials.getUnitMeasurement());

}

void Storage::putStaffTransfer(Staff_Transfer staff_transfer)
{
	auto it = this->staff_transfer.find(staff_transfer.getId());
	if (it == this->staff_transfer.end()) {
		this->staff_transfer[staff_transfer.getId()] = staff_transfer;
		return;
	}
	auto& mi = it->second;
	mi.setNumber(staff_transfer.getNumber());
	mi.setPosition(staff_transfer.getPosition());
	mi.setDate(staff_transfer.getDate());
	mi.setReason(staff_transfer.getReason());
}

void Storage::putService(Service service)
{
	auto it = this->service.find(service.getId());
	if (it == this->service.end()) {
		this->service[service.getId()] = service;
		return;
	}
	auto& o = it->second;
	o.setService(service.getService());
	o.setCost(service.getCost());
	o.setMasterId(service.getMasterId());
}

void Storage::putStaff(Staff staff)
{
	auto it = this->staff.find(staff.getId());
	if (it == this->staff.end()) {
		this->staff[staff.getId()] = staff;
		return;
	}
	auto& s = it->second;
	s.setName(staff.getName());
	s.setSurname(staff.getSurname());
	s.setPatronymic(staff.getPatronymic());
	s.setAddress(staff.getAddress());
	s.setDate(staff.getDate());
	s.setPosition(staff.getPosition());
	s.setSalary(staff.getSalary());
}

void Storage::putSpecialization(Specialization specialization)
{
	auto it = this->specialization.find(specialization.getId());
	if (it == this->specialization.end()) {
		this->specialization[specialization.getId()] = specialization;
		return;
	}
	it->second.setServicesList(specialization.getServicesList());
}

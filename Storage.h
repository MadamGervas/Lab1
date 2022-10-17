#pragma once
#ifndef Storage_HEADER
#define Storage_HEADER
#include <map>
#include "Clients.h"
#include "Master.h"
#include "Materials.h"
#include "Staff_Transfer.h"
#include "Service.h"
#include "Staff.h"
#include "Storage.h"
#include "Specialization.h"

class Storage {
private:
	std::map<long, Clients> clients;
	std::map<long, Master> master;
	std::map<long, Materials> materials;
	std::map<long, Staff_Transfer> staff_transfer;
	std::map<long, Service> service;
	std::map<long, Staff> staff;
	std::map<long, Specialization> specialization;

	Storage();
	static Storage* storage;

public:
	Storage(Storage& other) = delete;
	void operator=(const Storage&) = delete;
	static Storage* getInstance();
	Clients* getClients(long);
	Master* getMaster(long);
	Materials* getMaterials(long);
	Staff_Transfer* getStaffTransfer(long);
	Service* getService(long);
	Staff* getStaff(long);
	Specialization* getSpecialization(long);

	void putClients(Clients clients);
	void putMaster(Master masters);
	void putMaterials(Materials materials);
	void putStaffTransfer(Staff_Transfer moving_info);
	void putService(Service service);
	void putStaff(Staff staff);
	void putSpecialization(Specialization specialization);
};
#endif
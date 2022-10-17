#include "Staff_Transfer_Map.h"
#include "Clients_Map.h"
#include "Master_Map.h"
#include "Materials_Map.h"
#include "Service_Map.h"
#include "Specialization_Map.h"
#include "Staff_Map.h"

enum option {
	NONE_OPT,
	MATERIAL_OPT,
	SPECIALIZATION_OPT
};

void printStaffTransfer(const vector<Staff_Transfer*>& staff_transfer) {
	for (int i = 0; i < staff_transfer.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Position: " << staff_transfer[i]->getPosition() << endl
			<< "\t" << "Transfer reason: " << staff_transfer[i]->getReason() << endl
			<< "\t" << "Num of order: " << staff_transfer[i]->getNumber() << endl
			<< "\t" << "Date of order: " << staff_transfer[i]->toStringDate() << endl << endl;
	}
}

void printClients(const vector<Clients*>& clients) {
	for (int i = 0; i < clients.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << clients[i]->getName() << endl
			<< "\t" << "Surname: " << clients[i]->getSurname() << endl
			<< "\t" << "Patronymic: " << clients[i]->getPatronymic() << endl
			<< "\t" << "Phone: " << clients[i]->getPhoneNumber() << endl
			<< "\t" << "Date of order: " << clients[i]->toStringTime() << endl << endl;
	}
}

void printMaster(const vector<Master*>& master) {
	for (int i = 0; i < master.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Surname: " << master[i]->getSurname() << endl << endl;
	}
}

void printMaterials(const vector<Materials*>& materials) {
	for (int i = 0; i < materials.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << materials[i]->getName() << endl
			<< "\t" << "Measurement: " << materials[i]->getUnitMeasurement() << endl
			<< "\t" << "Cost: " << materials[i]->getCost() << " RUB" << endl << endl;
	}
}

void printService(const vector<Service*>& service) {
	for (int i = 0; i < service.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name of service: " << service[i]->getService() << endl
			<< "\t" << "Price of service: " << service[i]->getCost() << " RUB" << endl << endl;
	}
}

void printSpecialization(const vector<Specialization*>& specialization) {
	for (int i = 0; i < specialization.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << specialization[i]->getServicesList() << endl << endl;
	}
}

void printStaff(const vector<Staff*>& staff) {
	for (int i = 0; i < staff.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << staff[i]->getName() << endl
			<< "\t" << "Surname: " << staff[i]->getSurname() << endl
			<< "\t" << "Patronymic: " << staff[i]->getPatronymic() << endl
			<< "\t" << "Address: " << staff[i]->getAddress() << endl
			<< "\t" << "Date of birth: " << staff[i]->toStringDate() << endl
			<< "\t" << "Position: " << staff[i]->getPosition() << endl
			<< "\t" << "Salary: " << staff[i]->getSalary() << " RUB" << endl << endl;
	}
}

pair<long, long> choice(const vector<Master*>& master, const vector<Materials*>& material, const vector<Specialization*>& specialization, option opt) {
	long num, num2;
	cout << "Enter master number from (or 0 to break)" << endl;
	printMaster(master);
	cin >> num;
	if (opt == MATERIAL_OPT) {
		cout << "Enter number of material (or 0 to break)" << endl;
		printMaterials(material);
		cin >> num2;
	}
	if (opt == SPECIALIZATION_OPT) {
		cout << "Enter number of specialization (or 0 to break)" << endl;
		printSpecialization(specialization);
		cin >> num2;
	}
	return { num, num2 };
}

int staffTransferMenu(int variant, Staff_Transfer& staff_transfer,
	Staff_Transfer_Map& staff_transfer_map, vector<Staff_Transfer*>& staff_transfers) {
	string position, reason, order_date, number;
	int id;
	Date order_date_;
	switch (variant)
	{
	case 1:
		printStaffTransfer(staff_transfer_map.findAll());
		break;
	case 2:
		cout << "Enter position:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, position);

		cout << "Enter transffer reason:" << endl;
		getline(cin, reason);

		cout << "Enter date of order (year-month-day):" << endl;
		getline(cin, order_date);

		cout << "Enter order number:" << endl;
		cin >> number;

		staff_transfer.setId(-1);
		staff_transfer.setPosition(position);
		staff_transfer.setReason(reason);
		order_date_ = staff_transfer.setStringDate(order_date);
		staff_transfer.setDate(order_date_);
		staff_transfer.setNumber(number);
		staff_transfer_map.save(staff_transfer);
		break;

	case 3:
		printStaffTransfer(staff_transfers = staff_transfer_map.findAll());
		cout << "Enter moving information id" << endl;
		cin >> id;

		cout << "Enter new position:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, position);

		cout << "Enter new transffer reason:" << endl;
		getline(cin, reason);

		cout << "Enter new date of order (year-month-day):" << endl;
		getline(cin, order_date);

		cout << "Enter new order number:" << endl;
		cin >> number;

		staff_transfer.setId(staff_transfers[id - 1L]->getId());
		staff_transfer.setPosition(position);
		staff_transfer.setReason(reason);
		order_date_ = staff_transfer.setStringDate(order_date);
		staff_transfer.setDate(order_date_);
		staff_transfer.setNumber(number);
		staff_transfer_map.save(staff_transfer);
		break;

	case 4:
		printStaffTransfer(staff_transfers = staff_transfer_map.findAll());
		cout << "Enter moving information id" << endl;
		cin >> id;
		staff_transfer_map.remove(staff_transfers[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int staffMenu(int variant, Staff& staff,
	Staff_Map& staff_map, vector<Staff*>& staffs) {
	string name, surname, patronymic, address, date_of_birth, position;
	int salary, id;
	Date date_of_birth_;
	switch (variant)
	{
	case 1:
		printStaff(staff_map.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter surname:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter adress:" << endl;
		getline(cin, address);

		cout << "Enter birth_date of order (year-month-day):" << endl;
		getline(cin, date_of_birth);

		cout << "Enter position:" << endl;
		getline(cin, position);

		cout << "Enter salary:" << endl;
		cin >> salary;

		staff.setId(-1);
		staff.setName(name);
		staff.setSurname(surname);
		staff.setPatronymic(patronymic);
		staff.setAddress(address);
		staff.setPosition(position);
		date_of_birth_ = staff.setStringDate(date_of_birth);
		staff.setDate(date_of_birth_);
		staff_map.save(staff);
		break;

	case 3:
		printStaff(staffs = staff_map.findAll());
		cout << "Enter staff id" << endl;
		cin >> id;

		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter new surname:" << endl;
		getline(cin, surname);

		cout << "Enter new patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter new adress:" << endl;
		getline(cin, address);

		cout << "Enter new birth_date of order (year-month-day):" << endl;
		getline(cin, date_of_birth);

		cout << "Enter new position:" << endl;
		getline(cin, position);

		cout << "Enter new salary:" << endl;
		cin >> salary;

		staff.setId(staffs[id - 1L]->getId());
		staff.setName(name);
		staff.setSurname(surname);
		staff.setPatronymic(patronymic);
		staff.setAddress(address);
		staff.setPosition(position);
		date_of_birth_ = staff.setStringDate(date_of_birth);
		staff.setDate(date_of_birth_);
		staff_map.save(staff);
		break;

	case 4:
		printStaff(staffs = staff_map.findAll());
		cout << "Enter staff id" << endl;
		cin >> id;
		staff_map.remove(staffs[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int masterMenu(int variant,
	Master& master, Master_Map& master_map, vector<Master*>& masters,
	Materials& material, Materials_Map& material_map, vector<Materials*>& materials,
	Specialization& specialization, Specialization_Map& specialization_map,
	vector<Specialization*>& specializations) {
	string surname;
	int staff_id, id;
	long num, num_, quantity;
	pair<long, long> choice_;
	switch (variant)
	{
	case 1:
		printMaster(master_map.findAll());
		break;
	case 2:
		cout << "Enter surname of the master:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, surname);

		cout << "Enter the number of the staff to which the master belongs (id):" << endl;
		cin >> staff_id;

		master.setId(-1);
		master.setSurname(surname);
		master.setStaffId(staff_id);
		master_map.save(master);
		break;

	case 3:
		printMaster(masters = master_map.findAll());
		num = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), NONE_OPT).first;
		if (!num) break;
		cout << "Enter surname of the master:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, surname);

		cout << "Enter the number of the staff to which the master belongs (id):" << endl;
		cin >> staff_id;

		master.setId(masters[num - 1]->getId());
		master.setSurname(surname);
		master.setStaffId(staff_id);
		master_map.save(master);

		break;

	case 4:
		printMaster(masters = master_map.findAll());
		num = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), NONE_OPT).first;
		if (!num) return 0;
		master_map.remove(masters[num - 1]->getId());
		break;
	case 5:
		choice_ = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), MATERIAL_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		cout << "Write quantity:" << endl;
		cin >> quantity;
		master_map.addMaterials(masters[num - 1]->getId(), materials[num_ - 1]->getId(), quantity);
		break;

	case 6:
		choice_ = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), MATERIAL_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		cout << "Write quantity:" << endl;
		cin >> quantity;
		master_map.removeMaterials(masters[num - 1]->getId(), materials[num_ - 1]->getId(), quantity);

		break;

	case 7:
		/*cout << "7. Add specialization to master" << endl;*/
		choice_ = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), SPECIALIZATION_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		master_map.addSpecialization(masters[num - 1]->getId(), specializations[num_ - 1]->getId());
		break;

	case 8:
		/*cout << "8. Remove specialization from master" << endl; */
		choice_ = choice(masters = master_map.findAll(),
			materials = material_map.findAll(),
			specializations = specialization_map.findAll(), SPECIALIZATION_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		master_map.removeSpecialization(masters[num - 1]->getId(), specializations[num_ - 1]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int materialMenu(int variant, Materials& material,
	Materials_Map& material_map, vector<Materials*>& materials) {
	string name, unit_measurement;
	int cost, id;
	switch (variant)
	{
	case 1:
		printMaterials(material_map.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter unit measurement:" << endl;
		getline(cin, unit_measurement);

		cout << "Enter cost:" << endl;
		cin >> cost;

		material.setId(-1);
		material.setName(name);
		material.setUnitMeasurement(unit_measurement);
		material.setCost(cost);
		material_map.save(material);
		break;

	case 3:
		printMaterials(material_map.findAll());
		cout << "Enter material id" << endl;
		cin >> id;

		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter new unit measurement:" << endl;
		getline(cin, unit_measurement);

		cout << "Enter new cost:" << endl;
		cin >> cost;

		material.setId(materials[id - 1L]->getId());
		material.setName(name);
		material.setUnitMeasurement(unit_measurement);
		material.setCost(cost);
		material_map.save(material);
		break;

	case 4:
		printMaterials(materials = material_map.findAll());
		cout << "Enter material id" << endl;
		cin >> id;
		material_map.remove(materials[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int specializationMenu(int variant, Specialization& specialization,
	Specialization_Map& specialization_map, vector<Specialization*>& specializations) {
	string name;
	int id;
	switch (variant)
	{
	case 1:
		printSpecialization(specialization_map.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		specialization.setId(-1);
		specialization.setServicesList(name);
		specialization_map.save(specialization);
		break;

	case 3:
		printSpecialization(specializations = specialization_map.findAll());
		cout << "Enter specialization id" << endl;
		cin >> id;

		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		specialization.setId(specializations[id - 1L]->getId());
		specialization.setServicesList(name);
		specialization_map.save(specialization);
		break;

	case 4:
		printSpecialization(specializations = specialization_map.findAll());
		cout << "Enter specialization id" << endl;
		cin >> id;
		specialization_map.remove(specializations[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int orderMenu(int variant, Service& service,
	Service_Map& service_map, vector<Service*>& services) {
	string service_name, cost;
	int  master_id, id;
	switch (variant)
	{
	case 1:
		printService(service_map.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, service_name);

		cout << "Enter service price:" << endl;
		cin >> cost;

		cout << "Enter id of master:" << endl;
		cin >> master_id;

		service.setId(-1);
		service.setService(service_name);
		service.setMasterId(master_id);
		service.setCost(cost);
		service_map.save(service);
		break;

	case 3:
		printService(services = service_map.findAll());
		cout << "Select id of orders" << endl;
		cin >> id;

		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, service_name);

		cout << "Enter new service price:" << endl;
		cin >> cost;

		cout << "Enter new number of master(id):" << endl;
		cin >> master_id;

		service.setId(services[id - 1L]->getId());
		service.setService(service_name);
		service.setMasterId(master_id);
		service.setCost(cost);
		service_map.save(service);
		break;

	case 4:
		printService(services = service_map.findAll());
		cout << "Enter order id" << endl;
		cin >> id;
		service_map.remove(services[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int clientMenu(int variant, Clients& client,
	Clients_Map& client_map, vector<Clients*>& clients) {
	string name, surname, patronymic, phone_number, order_time;
	int service_id, id;
	
	
	Timestamp order_time_;
	switch (variant)
	{
	case 1:
		printClients(client_map.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter surname:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter phone number:" << endl;
		getline(cin, phone_number);

		cout << "Enter order time (hours:minute-second):" << endl;
		getline(cin, order_time);

		cout << "Enter number of order(id):" << endl;
		cin >> service_id;

		client.setId(-1);
		client.setName(name);
		client.setSurname(surname);
		client.setPatronymic(patronymic);
		client.setPhoneNumber(phone_number);
		order_time_ = client.setStringTime(order_time);
		client.setOrderTime(order_time_);
		client.setServiceId(service_id);
		client_map.save(client);
		break;

	case 3:
		printClients(clients = client_map.findAll());
		cout << "Select id of clients" << endl;
		cin >> id;

		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter new surname:" << endl;
		getline(cin, surname);

		cout << "Enter new patronymic:" << endl;

		getline(cin, patronymic);

		cout << "Enter new phone number:" << endl;

		getline(cin, phone_number);

		cout << "Enter new order time (hours:minute-second):" << endl;

		getline(cin, order_time);

		cout << "Enter new number of order(id):" << endl;
		cin >> service_id;

		client.setId(clients[id - 1L]->getId());
		client.setName(name);
		client.setSurname(surname);
		client.setPatronymic(patronymic);
		client.setPhoneNumber(phone_number);
		order_time_ = client.setStringTime(order_time);
		client.setOrderTime(order_time_);
		client.setServiceId(service_id);
		client_map.save(client);
		break;

	case 4:
		printClients(clients = client_map.findAll());
		cout << "Enter id of cliets:" << endl;
		cin >> id;
		client_map.remove(clients[id - 1L]->getId());
		break;

	default:
		break;
	}
	return 0;
}


int get_variant(int count) {
	int variant;
	string s;
	getline(cin, s);
	while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
		cout << "Incorrect input. Try again: ";
		getline(cin, s);
	}
	return variant;
}

void menu() {
	DB db = DB();
	Staff_Transfer_Map staff_transfer_map(db);
	Clients_Map clients_map(db);
	Materials_Map materials_map(db);
	Service_Map service_map(db);
	Specialization_Map specialization_map(db);
	Staff_Map staff_map(db);
	Master_Map master_map(db, specialization_map, materials_map);

	vector<Staff_Transfer*> staff_transfers;
	Staff_Transfer staff_transfer;

	vector<Clients*> clients;
	Clients client;

	vector<Master*> masters;
	Master master;

	vector<Materials*> materials;
	Materials material;

	vector<Service*> services;
	Service service;

	vector<Specialization*> specializations;
	Specialization specialization;

	vector<Staff*> staffs;
	Staff staff;

	pair<long, long> c;

	vector<int> nums;
	long num;
	long num2;
	double d_num;
	bool flag;
	int variant, sec_variant;

	while (true) {
		cout << "Salon" << endl;
		cout << "----------------------" << endl;
		cout << "1. Staff Transfer" << endl;
		cout << "2. Staff" << endl;
		cout << "3. Masters" << endl;
		cout << "4. Materials" << endl;
		cout << "5. Specialization" << endl;
		cout << "6. Service" << endl;
		cout << "7. Client" << endl;
		cout << "0. Exit" << endl;
		cout << "\nEnter the item" << endl;

		cin >> variant;

		switch (variant) {
		case 1:
			//Moving Information info
			cout << "Staff transfer" << endl;
			cout << "1. List all staff transfer" << endl;
			cout << "2. Add a staff transfer" << endl;
			cout << "3. Edit a staff transfer" << endl;
			cout << "4. Delete staff transfer" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			staffTransferMenu(sec_variant, staff_transfer, staff_transfer_map, staff_transfers);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 2:
			//Staff menu
			cout << "Staff:" << endl;
			cout << "1. List all staffs" << endl;
			cout << "2. Add an staff" << endl;
			cout << "3. Edit an staff" << endl;
			cout << "4. Remove an staff" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			staffMenu(sec_variant, staff, staff_map, staffs);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 3:
			cout << "Master:" << endl;
			cout << "1. List all masters" << endl;
			cout << "2. Add an master" << endl;
			cout << "3. Edit an master" << endl;
			cout << "4. Remove an master" << endl;
			cout << "5. Add material to master" << endl;
			cout << "6. Remove material from master" << endl;
			cout << "7. Add specialization to master" << endl;
			cout << "8. Remove specialization from master" << endl;
			cin >> sec_variant;
			masterMenu(sec_variant, master, master_map, masters,
				material, materials_map, materials,
				specialization, specialization_map, specializations);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;

		case 4: //Material menu
			cout << "Materials:" << endl;
			cout << "1. List all materials" << endl;
			cout << "2. Add an material" << endl;
			cout << "3. Edit an material" << endl;
			cout << "4. Remove an material" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			materialMenu(sec_variant, material, materials_map, materials);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 5:
			//Specialization menu
			cout << "Specialization:" << endl;
			cout << "1. List all specializations" << endl;
			cout << "2. Add an specialization" << endl;
			cout << "3. Edit an specialization" << endl;
			cout << "4. Remove an specialization" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			specializationMenu(sec_variant, specialization, specialization_map, specializations);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 6:
			//Order menu
			cout << "Order:" << endl;
			cout << "1. List all orders" << endl;
			cout << "2. Add an order" << endl;
			cout << "3. Edit an order" << endl;
			cout << "4. Remove an order" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			orderMenu(sec_variant, service, service_map, services);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 7:
			//Client menu
			cout << "Client:" << endl;
			cout << "1. List all clients" << endl;
			cout << "2. Add an client" << endl;
			cout << "3. Edit an client" << endl;
			cout << "4. Remove an client" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			clientMenu(sec_variant, client, clients_map, clients);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 0:
			return;
		}
	}
}

int main() {
	setlocale(0, "");
	menu();
	return 0;
}
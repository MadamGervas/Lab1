#pragma once
#ifndef Operations_HEADER
#define Operations_HEADER
#include "DB.h"
#include <vector>

template<class T, class TypeID>
class Operations {
protected:
	DB& db;

public:
	Operations(DB& db);
	virtual void save(const T& date) = 0;
	virtual void remove(TypeID typeID) = 0;
	virtual T* findById(TypeID typeID) = 0;
	virtual std::vector<T*> findAll() = 0;
};

template<class T, class TypeID>
Operations<T, TypeID>::Operations(DB& db) : db(db) {}
#endif
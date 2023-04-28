#pragma once

#include <string>
#include "sha1.h"

class HashTable { // хэш таблица
public:

	HashTable();
	~HashTable();
	void add(const string& login, uint* psw_sha1_hash);

	void del(const string& login);
	uint* find(const string& login);
	void resize();
	void refresh();

private:

	enum enPairStatus {
		free, // свободен
		engaged, //занят
		deleted //удален
	};

	struct Pair { // пара ключ-значение

		Pair() 
		{
			psw_sha1_hash_ = 0,
			status_ = enPairStatus::free;
			//strcpy_s(login_, "");
		}
		Pair(const string& login, uint* psw_sha1) :
			login_(login),
			psw_sha1_hash_(psw_sha1),
			status_(enPairStatus::engaged) {}

		Pair& operator = (const Pair& other) {
			psw_sha1_hash_ = other.psw_sha1_hash_;
			login_ = other.login_;
			status_ = other.status_;

			return *this;
		}

		bool operator == (const Pair& other) {
			return  status_ == other.status_ &&
				(status_ != enPairStatus::engaged || (psw_sha1_hash_ == other.psw_sha1_hash_ && login_ == other.login_));
		}

		string login_;
		uint* psw_sha1_hash_;

		enPairStatus status_;
	};

	int hash_func(const string& login, int offset);

	Pair* array_;
	int mem_size_;
	int count_;
};
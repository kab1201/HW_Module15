#include "HashTable.h"

HashTable::HashTable() {
	count_ = 0;
	mem_size_ = 8;
	array_ = new Pair[mem_size_];
}
HashTable::~HashTable() {
	delete[] array_;
}

void HashTable::resize() {

	Pair* save_array = array_; // ���������� ������ ������
	int oldSize = mem_size_;

	mem_size_ *= 2;  // ����������� ������ � ��� ����  
	count_ = 0; // �������� ���������� ���������
	array_ = new Pair[mem_size_]; // �������� ����� ������

	for (int i = 0; i < oldSize; i++) {
		Pair& current = save_array[i];
		if (current.status_ == enPairStatus::engaged)
			add(current.login_, current.psw_sha1_hash_);
	}
	// ������ �� �����
	delete[] save_array;
}

void HashTable::refresh() {

	Pair* save_array = array_; // ���������� ������ ������
	int oldSize = mem_size_;

	count_ = 0; // �������� ���������� ���������
	array_ = new Pair[mem_size_]; // �������� ����� ������

	for (int i = 0; i < oldSize; i++) {
		Pair& current = save_array[i];
		if (current.status_ == enPairStatus::engaged)
			add(current.login_, current.psw_sha1_hash_);
	}
	// ������ �� �����
	delete[] save_array;
}

void HashTable::add(const string& login, uint* psw_sha1_hash) {
	int index = -1, i = 0;
	// ����� ����� �� ���� i �� 0 �� ������� �������
	for (; i < mem_size_; i++) {
		index = hash_func(login, i);
		if (array_[index].status_ == enPairStatus::free) {
			// ������� ������ ������, �������� ��
			break;
		}
	}
	if (i >= mem_size_) {
		resize(); // ��� ���������, ��� �����
		add(login, psw_sha1_hash);
	}
	else {
		// ������ � ��������� ������ ����
		array_[index] = Pair(login, psw_sha1_hash);
		++count_;
	}
}

int HashTable::hash_func(const string& login, int offset) {
	// ��������� ������
	double A = 0.7;
	int sum = 0, i = 0;
	for (; i < login.length(); ++i) {
		sum += login[i];
	}
	int K = int(mem_size_ * (A * sum - int(A * sum))) + (offset * offset);
	return int(mem_size_ * (A * K - int(A * K)));
}

void HashTable::del(const string& login) {
	int index = -1, i = 0;
	// ����� ����� �� ���� i �� 0 �� ������� �������
	for (; i < mem_size_; i++) {
		index = hash_func(login, i);
		if (array_[index].status_ == enPairStatus::engaged && array_[index].login_ == login) {
			array_[index].status_ = enPairStatus::deleted;
			--count_;
			break;
		}
		else if (array_[index].status_ == enPairStatus::free) {
			return;
		}
	}
}
uint* HashTable::find(const string& login) {
	// ���������� ��������, ��������������� ����� login
	// ���� ������ ����� ���� � �������, �� ���������� nullptr
	int index = -1, i = 0;
	// ����� ����� �� ���� i �� 0 �� ������� �������
	for (; i < mem_size_; ++i) {
		index = hash_func(login, i);
		if (array_[index].status_ == enPairStatus::engaged && array_[index].login_ == login) {
			return array_[index].psw_sha1_hash_;
		}
		else if (array_[index].status_ == enPairStatus::free) {
			return nullptr;
		}
	}
	return nullptr;
}
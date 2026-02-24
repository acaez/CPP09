#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data original;
	original.id = 42;
	original.name = "Flash";
	original.value = 3.14159;

	std::cout << "=== Original Data ===" << std::endl;
	std::cout << "Address: " << &original << std::endl;
	std::cout << "id:      " << original.id << std::endl;
	std::cout << "name:    " << original.name << std::endl;
	std::cout << "value:   " << original.value << std::endl;
	std::cout << std::endl;

	uintptr_t raw = Serializer::serialize(&original);
	std::cout << "=== Serialized ===" << std::endl;
	std::cout << "Raw value: " << raw << std::endl;
	std::cout << std::endl;

	Data* deserialized = Serializer::deserialize(raw);
	std::cout << "=== Deserialized Data ===" << std::endl;
	std::cout << "Address: " << deserialized << std::endl;
	std::cout << "id:      " << deserialized->id << std::endl;
	std::cout << "name:    " << deserialized->name << std::endl;
	std::cout << "value:   " << deserialized->value << std::endl;
	std::cout << std::endl;

	std::cout << "=== Verification ===" << std::endl;
	if (deserialized == &original) {
		std::cout << "SUCCESS: Pointers are equal!" << std::endl;
	} else {
		std::cout << "FAILURE: Pointers are NOT equal!" << std::endl;
	}
	return 0;
}

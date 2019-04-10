#include <iostream>
#include <cstring>

// ласс из проекта 08CopyConstructor
class StringB {
	char *data;
	size_t length;

public:
	StringB(char const *buff) {
		size_t length = strlen(buff);
		this->length = 0;
		if (nullptr != (data = new (std::nothrow) char[length + 1])) {
			std::copy(buff, buff + length + 1, data);
			this->length = length;
		}
	}

	StringB() : StringB("") {
	}

	// онструктор копировани€
	StringB(StringB const &src) : StringB(src.data) {//мы делегируем работу уже существующему конструктору
		std::cout << "Copying..." << std::endl;
	}

	void print() {
		if (nullptr == data)
			std::cout << "NULL" << std::endl;
		else
			std::cout << data << std::endl;
	}

	bool append(char const *buff) {
		size_t length = strlen(buff);
		if (!expand(this->length + length + 1)) return false;
		std::copy(buff, buff + length + 1, data + this->length);
		this->length += length;
		return true;
	}

	~StringB() {
		if (nullptr != data)
			delete[] data;
	}

private:
	bool expand(size_t new_length) {
		auto tmp = new (std::nothrow) char[new_length];
		if (nullptr == tmp) return false;
		std::copy(data, data + this->length + 1, tmp);
		delete[] data;
		data = tmp;
	}
};

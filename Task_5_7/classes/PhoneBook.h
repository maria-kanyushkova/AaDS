#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>

#include <functional>
#include <map>
#include <ctime>
#include <algorithm>
#include <random>

#include "../struct/Name.h"
#include "../struct/Number.h"
#include "../enum/Flag.h"

//  ласс телефонной книги, работающей на файловой хэш-таблице
class PhoneBook {
private:
	fstream file; // бинарный файл
	const double loadFactor = 0.9; // максимальный процент зан€тых €чеек таблицы, если он больше, то таблица увеличивает емкость
	size_t size;
	size_t capacity;

	// хэширует номер
	size_t hash(Number const& number) {
		size_t hash = 0;
		for (int i = 0; i < sizeof(number); i++) {
			hash *= 13;
			hash += number.data[i] - '0';
		}
		return hash;
	}

	// размер €чейки таблицы
	size_t getEntrySize() {
		return sizeof(Flag) + sizeof(Number) + sizeof(Name);
	}

	// позици€ i-го флага в таблице
	size_t posOfFlag(size_t index) {
		return 2 * sizeof(size_t) + index * getEntrySize();
	}

	// позици€ i-го номера в таблице
	size_t posOfNumber(size_t index) {
		return posOfFlag(index) + sizeof(Flag);
	}

	// позици€ i-го имени в таблице
	size_t posOfName(size_t index) {
		return posOfNumber(index) + sizeof(Number);
	}

	// размер файла дл€ заданной емкости таблицы
	size_t getFileSize(size_t capacity) {
		return posOfFlag(capacity);
	}

	// индекс номера в таблице
	size_t indexOf(Number const& number) {
		return hash(number) % capacity;
	}

	// считывает значение из бинарного файла
	template<typename T>
	T read(size_t pos) {
		file.seekg(pos);
		T val;
		file.read((char*)(&val), sizeof(T));
		return move(val);
	}

	// считывает размер таблицы
	void readSize() {
		size = read<size_t>(0);
	}

	// считывает емкость таблицы
	void readCapacity() {
		capacity = read<size_t>(sizeof(size_t));
	}

	// считывает i-й флаг
	Flag getFlag(size_t index) {
		return read<Flag>(posOfFlag(index));
	}

	// считывает i-й номер
	Number getNumber(size_t index) {
		return move(read<Number>(posOfNumber(index)));
	}

	// считывает i-е им€
	Name getName(size_t index) {
		return move(read<Name>(posOfName(index)));
	}

	// выводит в файл n символов дл€ его заполнени€
	void putn(char c, size_t n) {
		for (; n > 0; n--) {
			file.put(c);
		}
		// file.flush();
	}

	// пишет значение в бинарный файл
	template<typename T>
	void write(T const& val, size_t pos) {
		file.seekp(pos);
		file.write((char*)(&val), sizeof(T));
		// file.flush();
	}

	// пишет размер в файл
	void setSize(size_t newSize) {
		size = newSize;
		write(size, 0);
	}

	// пишет емкость в файл
	void setCapacity(size_t newCapacity) {
		capacity = newCapacity;
		write(capacity, sizeof(size_t));
	}

	// пишет i-й флаг в файл
	void setFlag(Flag flag, size_t index) {
		write(flag, posOfFlag(index));
	}

	// пишет i-й номер в файл
	void setNumber(Number const& number, size_t index) {
		write(number, posOfNumber(index));
	}

	// пишет i-е им€ в файл
	void setName(Name const& name, size_t index) {
		write(name, posOfName(index));
	}

	// находит ключ в таблице, если он есть
	size_t findIndex(Number const& number) {
		size_t startIndex = indexOf(number);
		size_t index = startIndex;

		Flag flag;
		while (true) {
			flag = getFlag(index);
			if (flag == Flag::empty) {
				return -1;
			}

			if (flag != Flag::removed && getNumber(index) == number) {
				return index;
			}

			cout << "#" << number.data << " " << index << " " << getNumber(index).data << endl;

			index = (index + 1) % capacity;
			if (index == startIndex) {
				return -1;
			}
		}
	}

	// забирает из таблицы все элементы и удал€ет их из таблицы
	vector <pair<Number, Name>> extractAllElements() {
		vector <pair<Number, Name>> data;
		for (size_t index = 0; index < capacity; index++) {
			if (getFlag(index) == Flag::occupied) {
				data.push_back({ getNumber(index), getName(index) });
			}
		}

		for (size_t index = 0; index < capacity; index++) {
			setFlag(Flag::empty, index);
		}

		setSize(0);
		return move(data);
	}

	// увеличивает емкость таблицы
	void resize(size_t newCapacity) {
		auto data = extractAllElements();

		file.seekp(getFileSize(capacity));
		putn('\0', (newCapacity - capacity) * getEntrySize());
		setCapacity(newCapacity);

		add(data);
	}

	void reserve(size_t size) {
		size_t newCapacity = size_t(size / loadFactor);
		if (newCapacity <= size) {
			newCapacity++;
		}

		if (newCapacity <= capacity) {
			return;
		}
		newCapacity = max(newCapacity, size_t(capacity / loadFactor));

		resize(newCapacity);
	}

public:
	// возвращает количество записей в телефонной книге
	size_t getSize() {
		return size;
	}

	// добавл€ет запись в телефонную книгу
	void set(Number const& number, Name const& name) {
		reserve(size + 1);

		size_t index = indexOf(number);
		while (getFlag(index) == Flag::occupied) {
			if (getNumber(index) == number) {
				break;
			}

			index = (index + 1) % capacity;
		}

		setFlag(Flag::occupied, index);
		setNumber(number, index);
		setName(name, index);
		setSize(size + 1);
	}

	void add(pair <Number, Name> const& entry) {
		set(entry.first, entry.second);
	}

	void add(vector <pair<Number, Name>> const& entries) {
		reserve(size + entries.size());
		for (auto& entry : entries) {
			add(entry);
		}
	}

	// находит запись в телефонной книге
	optional <Name> find(Number const& number) {
		size_t index = findIndex(number);
		if (index == -1) {
			return nullopt;
		}

		return getName(index);
	}

	// удал€ет запись из телефонной книги
	void remove(Number const& number) {
		size_t index = findIndex(number);
		if (index == -1) {
			return;
		}

		setFlag(Flag::removed, index);
		setSize(size - 1);
	}

	// сохран€ет телефонную книгу в другой файл
	bool save(string const& filepath) {
		ofstream outFile(filepath);
		if (!outFile) {
			return false;
		}

		file.seekg(0);
		outFile << file.rdbuf();

		return bool(outFile.flush());
	}

	PhoneBook(string const& filepath, bool isNew) : file(fstream(filepath, ios::in | ios::out | ios::binary | (isNew ? ios::trunc : 0))) {
		if (isNew) {
			putn('\0', posOfFlag(0));
			setSize(0);
			setCapacity(0);
		}
		else {
			readSize();
			readCapacity();
		}
	}
};
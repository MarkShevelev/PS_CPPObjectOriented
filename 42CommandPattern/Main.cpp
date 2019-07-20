#include <iostream>
#include <string>
#include <unordered_map>

//интерфейс команды, который позволяет создать универсальный алгоритм вызова команд
struct Command {
	virtual bool process() const = 0;
	virtual ~Command() { }
};

//класс CommandLineProcess реализует универсальный алгоритм вызова команд
class CommandLineProcess final {
public:
	void run() const { //основной метод, который использует map строк и команд для вызова
		bool proceed = true;
		while (proceed) {
			std::string user_command;
			std::cin >> user_command;
			auto command_it = command_processes.find(user_command); //необходимо найти в map command по ключу - вводимой строке
			if (command_it != command_processes.end()) {
				proceed = command_it->second->process(); //если нашли команду, то запускаем и получаем ответ - нужно ли продолжать
				//если команда вернёт false, то мы завершаем цикл
			}
			else {//ветка на случай, если команда не была найдена
				std::cout << "Unknown command!" << std::endl;
			}
		}
	}

private:
	//внутренние данные - это map, который хранит соответствие каждой вводимой строке какую-то команду, не обязательно различные и не обязательно принадлежат только этому объекту CommandLineProcess
	//отношение между CommandLineProcess и Command - агрегация
	//при агрегации мы выбираем shared_ptr
	std::unordered_map<std::string, std::shared_ptr<Command>> command_processes;

public:
	//конструктор для инициализации command_processes
	CommandLineProcess(std::unordered_map<std::string, std::shared_ptr<Command>> command_processes): command_processes(command_processes) { }
};

//Реализуем простейшую команду Exit
//Задача этой команды - завершение работы, т.е. метод process должен возвращать false
struct Exit final : Command {
	virtual bool process() const override { return false; } //всё, что делает эта команда, возвращает флаг для завершения цикла в методе run в классе CommandLineProcess
};

//Класс SimpleApp моделирует простейшее приложение с системой команд
//Такое приложение поддерживает только одну команду - exit
//во всех остальных случаях выводится Unknown command
class SimpleApp final {
	//статический метод необходим нам для инициализации map для CommandLineProcess в конструкторе SimpleApp
	static auto map_init() {
		//создаём и заполняем map соответствиями строка-команда
		std::unordered_map<std::string, std::shared_ptr<Command>> key_command;
		key_command["exit"] = std::make_shared<Exit>(); //выгоднее создвать shared_ptr посредством функции make_shared, вызов которой должен быть параметризован РЕАЛЬНЫМ, а не абстрактным, типом; далее за счёт ковариантности произойдёт преобразование в shared_ptr<Command>

		return key_command;
	}

public:
	SimpleApp(): clp(SimpleApp::map_init()) { }
	void run() const { clp.run(); }

private:
	CommandLineProcess const clp; //композиция!
};

//простейшая программа с использованием подхода шаблона команд
//при вводе exit завершается, при вводе любой другой команды выводит Unknown command
void simple_app_test() {
	SimpleApp().run();
}

//данный шаблон не ограничивает возможности команд
//можно создавать команды, которые имею внутренние данные и даже могут быть изменяемыми
class CountingCommand final: public Command {
public:
	virtual bool process() const override {
		std::cout << "The command called " << ++counter << " times" << std::endl;
		return true;
	}

private:
	mutable int counter = 0;
};

void app_with_counting_command() {
	using namespace std;
	unordered_map<string, shared_ptr<Command>> command_processes;
	command_processes["exit"] = make_shared<Exit>();
	command_processes["next"] = make_shared<CountingCommand>();

	CommandLineProcess(command_processes).run();
}

int main() {
	if (false) simple_app_test();
	if (false) app_with_counting_command();
}
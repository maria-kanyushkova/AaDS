// 
//		7. В файле имеется телефонный справочник, включающий имена
//	владельцев телефонов.Организовать быстрый поиск  по  номерам
//	телефонов   с   помощью   хеширования.Обеспечить  дополнение
//	справочника(10).

// Канюшкова Мария ПС-21

#include "Utils.h"
#include "Handler.h"

using namespace std;

int main() {
    while (true) {
        try {
            Utils::printMenu();
			if (!Handler::commandProcces(Utils::readCommand())) {
				return false;
			}

			cout << (clock() - Handler::start) * 1000 / CLOCKS_PER_SEC << " ms\n";

        } catch (exception const &ex) {
            cout << "Exception: " << ex.what() << endl;
        }
    }
}
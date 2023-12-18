#include <systemc.h>

SC_MODULE(MyModule) {
    // Porty wejściowe i wyjściowe
    sc_in<bool> clock;
    sc_out<int> data_out;

    // Proces symulacyjny
    void myProcess() {
        while (true) {
            // Czekaj na zbocze rosnące zegara
            wait();

            // Przykładowa logika - inkrementacja danych i wypisanie wartości w konsoli
            data_out.write(data_out.read() + 1);
            cout << "Wartosc na wyjsciu: " << data_out.read() << endl;
        }
    }

    // Konstruktor modułu
    SC_CTOR(MyModule) {
        // Ustawienie procesu symulacyjnego na zbocze rosnące zegara
        sensitive << clock.pos();

        // Rozpoczęcie procesu symulacyjnego w osobnym wątku
        SC_THREAD(myProcess);
    }
};

int sc_main(int argc, char* argv[]) {
    // Stworzenie instancji modułu
    MyModule myModule("myModule");

    // Definicja sygnałów
    sc_clock clock("clock", 10, SC_NS); // Zegar o okresie 10 ns
    sc_signal<int> data_out;

    // Połączenie portów modułu z sygnałami
    myModule.clock(clock);
    myModule.data_out(data_out);

    // Rozpoczęcie symulacji
    sc_start(100, SC_NS);

    // Dodanie sc_stop(), aby zatrzymać symulację po określonym czasie
    sc_stop();

    // Zakończenie programu
    return 0;
}

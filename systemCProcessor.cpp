#include <systemc.h>
using namespace sc_core;

SC_MODULE(ALU) {
    //Deklaracja portów
    sc_in<sc_int<16>> a; //szesnastobitowa liczba całkowita bez znaku
    sc_in<sc_int<16>> b;
    sc_in<sc_uint<4>> salu; //sygnał sterujący
    //sc_in<bool> LDF;
    sc_in<bool> clk;

    // Wyjścia
    sc_out<sc_int<16>> y; //wynik
    sc_out<bool> c; //przeniesienie
    sc_out<bool> z; //zero
    sc_out<bool> s; //znak

    sc_int<17> y_temp;
    
    sc_int <1> temp_z;
    sc_int <1> temp_s;

    //sc_int<17> a_temp;
    //sc_int<17> b_temp;

    // Proces główny
    void alu_process() {
        y_temp = y.read();

        // Przetwarzanie operacji w zależności od wartości Salu
        switch (salu.read().to_uint()) {
        case 0: 
            y_temp = a.read();
            std::cout << a.read().to_string(SC_BIN) << " = ";
            break;
        case 1: 
            y_temp = b.read(); 
            std::cout << b.read().to_string(SC_BIN) << " = ";
            break;

        case 2: 
            y_temp = a.read() + b.read();
            std::cout << a.read().to_string(SC_BIN) << " + " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 3: 
            y_temp = a.read() - b.read();
            
            std::cout << a.read().to_string(SC_BIN) << " - " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 4: 
            y_temp = (a.read() | b.read());
            std::cout << a.read().to_string(SC_BIN) << " OR " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 5: 
            y_temp = (a.read() & b.read()); 
            std::cout << a.read().to_string(SC_BIN) << " AND " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 6: 
            y_temp = (a.read() ^ b.read());
            std::cout << a.read().to_string(SC_BIN) << " XOR " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 7: 
            y_temp = ~(a.read() ^ b.read());
            if (y_temp[15] == 0) y_temp[15] = 1;
            else (y_temp[15] = 0);

            std::cout << a.read().to_string(SC_BIN) << " XNOR " << b.read().to_string(SC_BIN) << " = ";
            break;

        case 8: 
            y_temp = (~a.read());
            if (y_temp[15] == 0) y_temp[15] = 1;
            else (y_temp[15] = 0);

            std::cout << "~" << a.read().to_string(SC_BIN) << " = ";
            break;

        case 9:
            y_temp = a.read();
            std::cout << " -" << a.read().to_string(SC_BIN) << " = ";
            if (y_temp[16] == 0) y_temp[16] = 1;
            else (y_temp[16] = 0);
            break;

        case 10: 
            y_temp = 0;
            std::cout << "0 = ";
            z.write(1);
            break;
        case 11: 
            y_temp = a.read() + b.read() + c.read();
            std::cout << a.read().to_string(SC_BIN) << " + " << b.read().to_string(SC_BIN) << " + " << c << " = ";
            break;

        case 12: 
            y_temp = a.read() + b.read() - c.read();
            std::cout << a.read().to_string(SC_BIN) << " + " << a.read().to_string(SC_BIN) << " - " << c << " = ";
            break;

        case 13: 
            y_temp = (a.read() + 1);
            std::cout << a.read().to_string(SC_BIN) << " + 1 = ";
            break;

        case 14: 
            y_temp = (a.read() << 1);
            std::cout <<"(" << a.read().to_string(SC_BIN) << "<<1) = ";
            break;

        case 15: 
            y_temp = (a.read() >> 1);
            std::cout <<"(" << a.read().to_string(SC_BIN) << ">>1) = ";
            break;

        default: std::cout << "Nieprawidlowa operacja w ALU!"; break;
        }
        if (y_temp[15] == 1){ //bit przeniesienia
            c.write(1);
        }else {
            c.write(0);
        }

        if (y_temp[16] == 1) { //bit znaku
            s.write(1);
            y_temp[15] = 1;
        }
        else {
            s.write(0);
            y_temp[15] = 0;
        }

        if (y_temp == 0) { //bit zerowy
            z.write(1);
        }

        y.write(sc_int<16>(y_temp.range(15, 0)));

        std::cout << y.read().to_string(SC_BIN);

        std::cout <<">>" << y_temp.to_string(SC_BIN);

        
        
        
        //Wartości które testowo wypisuje za pierwszym obiegiem konsola są nieprawidłowe
        //Ale oblicza się prawidłowo (wystarczy sprawdzić je po zakończeniu symulacji w sc_main)
        std::cout << "\nBit przeniesienia: " << c;
        std::cout << "\nBit zerowy: " << z;
        std::cout << "\nBit znaku: " << s << "\n\n";

    }
    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        dont_initialize();
        sensitive << clk.pos();
    }
};

int sc_main(int argc, char* argv[]) {

    //Utworzenie sygnałów
    sc_signal<sc_int<16>> a_signal, b_signal, y_signal;
    sc_signal<bool> c_signal, z_signal, s_signal;
    sc_signal<sc_uint<4>> salu_signal;

    sc_clock clock("clock", 10, SC_NS);
    
    // Utwórz instancję ALU
    ALU alu("aluModule");

    //Przypisanie wartości z sygnałów do portów w module
    alu.a(a_signal);
    alu.b(b_signal);
    alu.salu(salu_signal);

    alu.y(y_signal);

    alu.c(c_signal);
    alu.z(z_signal);
    alu.s(s_signal);

    alu.clk(clock);

    a_signal.write(0b0100110000000001);
    b_signal.write(0b0110);
    salu_signal.write(15);

    c_signal.write(1);
    z_signal.write(0);
    s_signal.write(0);
 
    
    //Uruchomienie symulacji na czas 100 jednostek
    sc_start(100, SC_NS);

    //std:cout << y_signal.read();
    return 0;
}

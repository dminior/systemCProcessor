#include <systemc.h>
using namespace sc_core;

SC_MODULE(ALU) {
    //Deklaracja portów
    sc_in<sc_int<16>> a; //szesnastobitowa liczba ca³kowita bez znaku
    sc_in<sc_int<16>> b;
    sc_in<sc_bv<4>> salu; //sygna³ steruj¹cy
    sc_in<bool> LDF;
    sc_in<bool> clk;

    // Wyjœcia
    sc_out<sc_int<16>> y; //wynik
    sc_out<bool> c; //przeniesienie
    sc_out<bool> z; //zero
    sc_out<bool> s; //znak

    sc_int<17> y_temp;

    sc_int <1> temp_z;
    sc_int <1> temp_s;

    //Proces g³ówny
    void alu_process();
    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        dont_initialize();
        sensitive << clk.pos();
    }
};

SC_MODULE(Registers) {
    //Sygna³y wejœciowe
    sc_in<bool> clk;

    sc_in<sc_int<16>> DI; //Data Input - przenosi dane wejœciowe
    sc_in<sc_int<16>> BA; //Base Address - adres bazowy, u¿ywany w operacjach np. zapis, odczyt do pamiêci

    sc_in<sc_bv<4>> Sbb, Sbc, Sba; //który z rejestrów A, B, C ma byæ u¿ywany w danej operacji

    sc_in<sc_bv<3>> Sid; //sygna³ steruj¹cy dla dekodera instrukcji

    sc_in<sc_bv<2>> Sa; //sygna³ steruj¹cy akumulator - który ma byæ u¿yty w instrukcji


    //Sygna³y wyjœciowe
    sc_out<sc_int<16>> BB, BC; //Base B - sygna³ reprezentuj¹cy wartoœci rejestrów B i C
    sc_out<sc_int<16>> IRout; //Instruction Register Output - zawartoœæ rejestru instrukcji

    sc_out<sc_int<32>> ADR; //Address - wartoœæ adresu 

    //Rejestry ogólne
    sc_int<16> TMP; //Temporary Accumulator - do przechowywania danych tymaczsowych w trakcie operacji
    sc_int<16> A, B, C, D, E, F; //rejestry ogólnego przeznaczenia, A - akumulator
    sc_int<16> IR; //Instruction Register - przechowuje aktualnie wykonywan¹ instrukcjê

    sc_int<32> PC; //Program Counter - wskazuje nastêpn¹ instrukcjê w pamiêci
    sc_int<32> AD; //Address High i Low (AD)
    sc_int<32> SP; //Stack Pointer - aktualna pozycja stosu w pamiêci
    sc_int<32> ATMP; //Temporary Accumulator - rejestr mog¹cy byæ u¿ywany w trakcie obliczeñ


    //Proces g³ówny
	void register_process();
    //Konstruktor
    SC_CTOR(Registers) {
        SC_METHOD(register_process);
        sensitive << clk.pos();
    }
};
SC_MODULE(Busint) {
    //Sygna³y wejœciowe
    sc_in<bool> clk;
    sc_in<sc_int<32>> ADR; //Adres WEJŒCIOWE
    sc_in<sc_int<16>> DO; //Dane WEJŒCIOWE (IN)

    //Sygana³y steruj¹ce operacjami na magistrali
    sc_in<bool> Smar; // 0 - pamiêtanie adresu, 1 - zapis
    sc_in<bool> Smbr; // 0 - pamiêtanie danych, 1 - zapis
    sc_in<bool> WRin; // uruchom/zatrzymaj operacjê zapisu
    sc_in<bool> RDin; // uruchom/zatrzymaj operacjê odczytu

    //Sygna³y wyjœciowe
    sc_out<sc_int<32>> AD; //Adres WYJŒCIOWE
    sc_inout<sc_int<16>> D; //Dane IN-OUT
    sc_out<sc_int<16>> DI; //Dane OUT
    sc_out<bool> WR, RD; //Informuj¹ czy aktualnie operacja zapisu (WR) czy odczytu (RD)

    //Proces g³ówny
	void process();
    SC_CTOR(Busint) {
        SC_METHOD(process);
        sensitive << clk.pos();// << Smar << ADR << Smbr << DO << D << WRin << RDin;
    }
};

SC_MODULE(Control) {
    // Porty wejœciowe
    sc_in<bool> clk;

    sc_in<sc_int<16>> IR; // Wejœcie rejestru instrukcji

    sc_in<bool> reset; // Sygna³ resetu

    //Flagi
    sc_in<bool> C; //Flaga przeniesienia
    sc_in<bool> Z; //Flaga zerowa
    sc_in<bool> S; //Flaga znaku
    sc_in<bool> INT; //Flaga przerwania


    //Porty wyjœciowe
    sc_out<sc_bv<4>> Salu, Sbb, Sbc, Sba;
    sc_out<sc_bv<3>> Sid; //Wyjœcie reprezentuj¹ce sygna³ steruj¹cy dla dekodera instrukcji
    sc_out<sc_bv<2>> Sa; //Sygna³ steruj¹cy akumulatora

    sc_out<bool> LDF; //Sygna³ wczytywania danych
    sc_out<bool> Smar, Smbr; //Sygna³y aktywacji rejestru adresowego i danych
    sc_out<bool> WR, RD; //Sygna³y zapisu i odczytu

    sc_out<bool> INTA; //Sygna³ przerwania
    sc_out<bool> MIO; //Sygna³ Memory Input/Output

    //Typ wyliczeniowy dla stanów
    enum state_type {
        m0, m1, m10, m11, m12, m13, m14, m15, m16, m17, m20, m21, m22, m23, m24, m25, m26, m27, m28,
        m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m40, m41, m50, m51, m52, m53, m60, m61, m62, m63, m64, m65,
        m66, m67, m68, m80, m81, m82, m83, m84, m85, m86, m87, m88, m89, m90, m9
    };
    sc_signal<state_type> state;

    //Proces stanu
    void state_process();

    // Proces logiki
    void logic_process();

    // Konstruktor
    SC_CTOR(Control) {
        SC_METHOD(state_process);
        sensitive << clk.pos() << reset;

        SC_METHOD(logic_process);
        sensitive << state;
    }

};
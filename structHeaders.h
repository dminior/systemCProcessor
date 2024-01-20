#include <systemc.h>
using namespace sc_core;

SC_MODULE(ALU) {
    //Deklaracja port�w
    sc_in<sc_int<16>> a; //szesnastobitowa liczba ca�kowita bez znaku
    sc_in<sc_int<16>> b;
    sc_in<sc_bv<4>> salu; //sygna� steruj�cy
    sc_in<bool> LDF;
    sc_in<bool> clk;

    // Wyj�cia
    sc_out<sc_int<16>> y; //wynik
    sc_out<bool> c; //przeniesienie
    sc_out<bool> z; //zero
    sc_out<bool> s; //znak

    sc_int<17> y_temp;

    sc_int <1> temp_z;
    sc_int <1> temp_s;

    //Proces g��wny
    void alu_process();
    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        dont_initialize();
        sensitive << clk.pos();
    }
};

SC_MODULE(Registers) {
    //Sygna�y wej�ciowe
    sc_in<bool> clk;

    sc_in<sc_int<16>> DI; //Data Input - przenosi dane wej�ciowe
    sc_in<sc_int<16>> BA; //Base Address - adres bazowy, u�ywany w operacjach np. zapis, odczyt do pami�ci

    sc_in<sc_bv<4>> Sbb, Sbc, Sba; //kt�ry z rejestr�w A, B, C ma by� u�ywany w danej operacji

    sc_in<sc_bv<3>> Sid; //sygna� steruj�cy dla dekodera instrukcji

    sc_in<sc_bv<2>> Sa; //sygna� steruj�cy akumulator - kt�ry ma by� u�yty w instrukcji


    //Sygna�y wyj�ciowe
    sc_out<sc_int<16>> BB, BC; //Base B - sygna� reprezentuj�cy warto�ci rejestr�w B i C
    sc_out<sc_int<16>> IRout; //Instruction Register Output - zawarto�� rejestru instrukcji

    sc_out<sc_int<32>> ADR; //Address - warto�� adresu 

    //Rejestry og�lne
    sc_int<16> TMP; //Temporary Accumulator - do przechowywania danych tymaczsowych w trakcie operacji
    sc_int<16> A, B, C, D, E, F; //rejestry og�lnego przeznaczenia, A - akumulator
    sc_int<16> IR; //Instruction Register - przechowuje aktualnie wykonywan� instrukcj�

    sc_int<32> PC; //Program Counter - wskazuje nast�pn� instrukcj� w pami�ci
    sc_int<32> AD; //Address High i Low (AD)
    sc_int<32> SP; //Stack Pointer - aktualna pozycja stosu w pami�ci
    sc_int<32> ATMP; //Temporary Accumulator - rejestr mog�cy by� u�ywany w trakcie oblicze�


    //Proces g��wny
	void register_process();
    //Konstruktor
    SC_CTOR(Registers) {
        SC_METHOD(register_process);
        sensitive << clk.pos();
    }
};
SC_MODULE(Busint) {
    //Sygna�y wej�ciowe
    sc_in<bool> clk;
    sc_in<sc_int<32>> ADR; //Adres WEJ�CIOWE
    sc_in<sc_int<16>> DO; //Dane WEJ�CIOWE (IN)

    //Sygana�y steruj�ce operacjami na magistrali
    sc_in<bool> Smar; // 0 - pami�tanie adresu, 1 - zapis
    sc_in<bool> Smbr; // 0 - pami�tanie danych, 1 - zapis
    sc_in<bool> WRin; // uruchom/zatrzymaj operacj� zapisu
    sc_in<bool> RDin; // uruchom/zatrzymaj operacj� odczytu

    //Sygna�y wyj�ciowe
    sc_out<sc_int<32>> AD; //Adres WYJ�CIOWE
    sc_inout<sc_int<16>> D; //Dane IN-OUT
    sc_out<sc_int<16>> DI; //Dane OUT
    sc_out<bool> WR, RD; //Informuj� czy aktualnie operacja zapisu (WR) czy odczytu (RD)

    //Proces g��wny
	void process();
    SC_CTOR(Busint) {
        SC_METHOD(process);
        sensitive << clk.pos();// << Smar << ADR << Smbr << DO << D << WRin << RDin;
    }
};

SC_MODULE(Control) {
    // Porty wej�ciowe
    sc_in<bool> clk;

    sc_in<sc_int<16>> IR; // Wej�cie rejestru instrukcji

    sc_in<bool> reset; // Sygna� resetu

    //Flagi
    sc_in<bool> C; //Flaga przeniesienia
    sc_in<bool> Z; //Flaga zerowa
    sc_in<bool> S; //Flaga znaku
    sc_in<bool> INT; //Flaga przerwania


    //Porty wyj�ciowe
    sc_out<sc_bv<4>> Salu, Sbb, Sbc, Sba;
    sc_out<sc_bv<3>> Sid; //Wyj�cie reprezentuj�ce sygna� steruj�cy dla dekodera instrukcji
    sc_out<sc_bv<2>> Sa; //Sygna� steruj�cy akumulatora

    sc_out<bool> LDF; //Sygna� wczytywania danych
    sc_out<bool> Smar, Smbr; //Sygna�y aktywacji rejestru adresowego i danych
    sc_out<bool> WR, RD; //Sygna�y zapisu i odczytu

    sc_out<bool> INTA; //Sygna� przerwania
    sc_out<bool> MIO; //Sygna� Memory Input/Output

    //Typ wyliczeniowy dla stan�w
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
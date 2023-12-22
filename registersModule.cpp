#include <systemc.h>
using namespace sc_core;

SC_MODULE(Rejestry) {
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
    void process() {
        if (clk.posedge()) {

            //Sygna³ Sid
            switch (Sid.read().to_uint()) {
            case 1:
                PC++;
                break;
            case 2:
                SP++;
                break;
            case 3:
                SP--;
                break;
            case 4:
                AD++;
                break;
            case 5:
                AD--;
                break;
            default:
                break;
            }

            //Sygna³ Sba
            switch (Sba.read().to_uint()) {
            case 0:
                IR = BA;
                break;
            case 1:
                TMP = BA;
                break;
            case 2:
                A = BA;
                break;
            case 3:
                B = BA;
                break;
            case 4:
                C = BA;
                break; 
            case 5:
                D = BA;
                break;
            case 6:
                E = BA;
                break;
            case 7:
                F = BA;
                break;
            case 8:
                AD = (AD & 0xFFFF0000) | BA.read();
                break;
            case 9:
                AD = (AD & 0x0000FFFF) | BA.read();
                break;
            case 10:
                PC = (PC & 0xFFFF0000) | BA.read();
                break;
            case 11:
                PC = (PC & 0x0000FFFF) | BA.read();
                break;
            case 12:
                SP = (SP & 0xFFFF0000) | BA.read();
                break;
            case 13:
                SP = (SP & 0x0000FFFF) | BA.read();
                break;
            case 14:
                ATMP = (ATMP & 0xFFFF0000) | BA.read();
                break;
            case 15:
                ATMP = (ATMP & 0x0000FFFF) | BA.read();
                break;
            default:
                break;
            }
        }

        //Sygna³ Sbb
        switch (Sbb.read().to_uint()) {
        case 0:
            BB.write(DI);
            break;
        case 1:
            BB.write(TMP);
            break;
        case 2:
            BB.write(A);
            break;
        case 3:
            BB.write(B);
            break;
        case 4:
            BB.write(C);
            break;
        case 5:
            BB.write(D);
            break;
        case 6:
            BB.write(E);
            break;
        case 7:
            BB.write(F);
            break;
        case 8:
            BB.write(AD & 0xFFFF0000);
            break;
        case 9:
            BB.write(AD & 0x0000FFFF);
            break;
        case 10:
            BB.write(PC & 0xFFFF0000);
            break;
        case 11:
            BB.write(PC & 0x0000FFFF);
            break;
        case 12:
            BB.write(SP & 0xFFFF0000);
            break;
        case 13:
            BB.write(SP & 0x0000FFFF);
            break;
        case 14:
            BB.write(ATMP & 0xFFFF0000);
            break;
        case 15:
            BB.write(ATMP & 0x0000FFFF);
            break;
        default:
            break;
        }

        //Sygna³ Sbc
        switch (Sbc.read().to_uint()) {
        case 0:
            BC.write(DI);
            break;
        case 1:
            BC.write(TMP);
            break;
        case 2:
            BC.write(A);
            break;
        case 3:
            BC.write(B);
            break;
        case 4:
            BC.write(C);
            break;
        case 5:
            BC.write(D);
            break;
        case 6:
            BC.write(E);
            break;
        case 7:
            BC.write(F);
            break;
        case 8:
            BC.write(AD & 0xFFFF0000);
            break;
        case 9:
            BC.write(AD & 0x0000FFFF);
            break;
        case 10:
            BC.write(PC & 0xFFFF0000);
            break;
        case 11:
            BC.write(PC & 0x0000FFFF);
            break;
        case 12:
            BC.write(SP & 0xFFFF0000);
            break;
        case 13:
            BC.write(SP & 0x0000FFFF);
            break;
        case 14:
            BC.write(ATMP & 0xFFFF0000);
            break;
        case 15:
            BC.write(ATMP & 0x0000FFFF);
            break;
        default:
            break;
        }

        //Sygna³ Sa
        switch (Sa.read().to_uint()) {
        case 0:
            ADR.write(AD);
            break;
        case 1:
            ADR.write(PC);
            break;
        case 2:
            ADR.write(SP);
            break;
        case 3:
            ADR.write(ATMP);
            break;
        default:
            break;
        }



        std::cout << "\n\nTMP: " << TMP;
        std::cout << "\nA-F: " << A << " " << B << " " << C << " " << D << " " << E << " " << F;
        std::cout << "\nIR: " << IR;

        std::cout << "\nPC: " << PC;
        std::cout << "\nAD: " << AD;
        std::cout << "\nSP: " << SP;
        std::cout << "\nATMP: " << ATMP;

    }


    //Konstruktor
    SC_CTOR(Rejestry) {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};
                             
int sc_main(int argc, char* argv[]) {
    //Deklaracje sygna³ów
    sc_clock clock("clock", 20, SC_NS);
    sc_signal<sc_int<16>> DI, BA, BB, BC, IRout;
    sc_signal<sc_bv<4>> Sbb, Sbc, Sba;
    sc_signal<sc_bv<3>> Sid;
    sc_signal<sc_bv<2>> Sa;
    sc_signal<sc_int<32>> ADR;

    //Utworzenie instancji modu³u
    Rejestry rejestry("rejestry");

    //Po³¹czenie sygna³ów
    rejestry.clk(clock);

    rejestry.DI(DI);
    rejestry.BA(BA);

    rejestry.Sbb(Sbb);
    rejestry.Sbc(Sbc);
    rejestry.Sba(Sba);

    rejestry.Sid(Sid);
    rejestry.Sa(Sa);

    rejestry.BB(BB);
    rejestry.BC(BC);

    rejestry.IRout(IRout);

    rejestry.ADR(ADR);

    //Przyk³adowe wartoœci sygna³ów 
    BA.write(2);

    //Przyk³adowe wartoœci sygna³ów struj¹cych
    Sid.write(1);
    Sa.write(1);

    Sbb.write(0b1011); //PC(15-0) do BB
    Sbc.write(0b1011); //PC(15-0) do BC
    Sba.write(0b0010); //BA do A


    //Uruchomienie symulacji
    sc_start(20, SC_NS);

    //std::cout << rejestry.PC;

    std::cout << "\n\nBB: " << BB << " BC: " << BC; //Base B - sygna³ reprezentuj¹cy wartoœci rejestrów B i C
    std::cout << "\nIRout: " << IRout; //Instruction Register Output - zawartoœæ rejestru instrukcji
    std::cout << "\nADR: " << ADR; //Address - wartoœæ adresu 

    return 0;
}

#include <systemc.h>
#include "structHeaders.h"

int sc_main(int argc, char* argv[]) {
	// Deklaracje sygna��w
	sc_clock clock("clock", 20, SC_NS);
	sc_signal<sc_int<16>> IR;
	sc_signal<bool> reset, INT;
	sc_signal<bool> C, Z, S;
	sc_signal<sc_bv<4>> Salu, Sbb, Sbc, Sba;
	sc_signal<sc_bv<3>> Sid;
	sc_signal<sc_bv<2>> Sa;
	sc_signal<bool> Smar, Smbr;//, LDF, WR, RD, INTA, MIO;

	sc_in<sc_int<32>> ADR;
	sc_in<sc_int<16>> DO;
	sc_in<sc_int<16>> BA;
	sc_inout<sc_int<16>> D;

	//Utworzenie instancji modu�u rejestr�w
	Registers registers("MyRegisters");

	//Utworzenie instancji modu�u ALU
	ALU alu("aluModule");

	//Utworzenie instancji modu�u kontroli
	Control control("MyControl");

	// Utworzenie instancji obs�ugi danych
	Busint busint("MyBusint");

	// Po��czenie sygna��w
	/*control.Salu(Salu);
	control.Sbb(Sbb);
	control.Sbc(Sbc);
	control.Sba(Sba);
	control.Sid(Sid);
	control.Sa(Sa);
	control.Smar(Smar);
	control.Smbr(Smbr);*/

	control.clk(clock);
	control.IR(IR);
		
	alu.clk(clock);
	alu.salu(control.Salu);
	alu.a(registers.BB);
	alu.b(registers.BC);

	registers.clk(clock);
	registers.Sbb(control.Sbb);
	registers.Sbc(control.Sbc);
	registers.Sba(control.Sba);
	registers.Sid(control.Sid);
	registers.DI(busint.DI);
	registers.BA(alu.y);

	busint.clk(clock);
	busint.Smar(control.Smar);
	busint.Smbr(control.Smbr);
	busint.WRin(control.WR);
	busint.RDin(control.RD);
	busint.ADR(registers.ADR);
	busint.DO(alu.y); //???
	//busint.D(D);
	


	IR = 0b0000001100000011; //inc rej A
	//ADR.busint = 0;

	// Uruchomienie symulacji
	sc_start(1, SC_NS);

	std::cout << alu.a.read();

	return 0;
}
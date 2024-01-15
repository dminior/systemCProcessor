#include <systemc.h>
#include "structHeaders.h"

int sc_main(int argc, char* argv[]) {
	// Deklaracje sygna³ów
	sc_clock clock("clock", 20, SC_NS);
	sc_signal<sc_int<16>> IR;
	sc_signal<bool> reset, INT;
	sc_signal<bool> C, Z, S;
	sc_signal<sc_bv<4>> Salu, Sbb, Sbc, Sba;
	sc_signal<sc_bv<3>> Sid;
	sc_signal<sc_bv<2>> Sa;
	sc_signal<bool> LDF, Smar, Smbr, WR, RD, INTA, MIO;


	sc_signal<sc_int<16>> BA, BB, BC, IRout;
	sc_signal<sc_int<16>> DO, D, DI;
	sc_signal<sc_int<32>> ADR;

	sc_signal<sc_int<16>> a, b, y;
	sc_signal<sc_uint<4>> salu;

	sc_signal<bool> WRin, RDin;


	//Utworzenie instancji modu³u rejestrów
	Registers registers("MyRegisters");

	//Utworzenie instancji modu³u ALU
	ALU alu("aluModule");

	//Utworzenie instancji modu³u kontroli
	Control control("MyControl");

	// Utworzenie instancji obs³ugi danych
	Busint busint("MyBusint");

	// Po³¹czenie sygna³ów
	control.clk(clock);
	control.IR(IR);
	control.reset(reset);
	control.C(C);
	control.Z(Z);
	control.S(S);
	control.INT(INT);
	control.Salu(Salu);
	control.Sbb(Sbb);
	control.Sbc(Sbc);
	control.Sba(Sba);
	control.Sid(Sid);
	control.Sa(Sa);
	control.LDF(LDF);
	control.Smar(Smar);
	control.Smbr(Smbr);
	control.WR(WR);
	control.RD(RD);
	control.INTA(INTA);
	control.MIO(MIO);

	alu.clk(clock);
	alu.a(a);
	alu.b(b);
	alu.salu(salu);
	alu.y(y);
	alu.c(C);
	alu.z(Z);
	alu.s(S);

	registers.clk(clock);
	registers.DI(DI);
	registers.BA(BA);
	registers.Sbb(Sbb);
	registers.Sbc(Sbc);
	registers.Sba(Sba);
	registers.Sid(Sid);
	registers.Sa(Sa);
	registers.BB(BB);
	registers.BC(BC);
	registers.IRout(IRout);
	registers.ADR(ADR);

	busint.ADR(ADR);
	busint.DO(DO);
	busint.Smar(Smar);
	busint.Smbr(Smbr);
	busint.WRin(WRin);
	busint.RDin(RDin);
	busint.AD(ADR);
	busint.D(D);
	busint.DI(DI);
	busint.WR(WR);
	busint.RD(RD);

	IR = 0;
	reset = 0;
	C = 0;
	Z = 0;
	S = 0;
	INT = 0;

	// Przyk³adowe wartoœci sygna³ów
	IR.write(0x1234);

	S.write(false);
	C.write(false);
	Z.write(false);
	S.write(false);
	INT.write(false);

	//Sa.write(0b00);
	Sbb.write(1);
	Sba.write(1);
	Sid.write(0);
	Sbc.write(0b00);
	MIO.write(1);
	Smar.write(0);
	Smbr.write(0);
	WR.write(0);
	RD.write(0);
	Salu.write(0);
	//LDF.write(0b00);
	//INTA.write(0b00);

	Sbb = 0b0000;
	Sba = 0b0000;
	Sid = 0b000; Sbc = 0b0000; MIO = 1;
	Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;

	// Uruchomienie symulacji
	sc_start(1, SC_NS);

	return 0;
}
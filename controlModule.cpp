#include <systemc.h>

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
		m66, m67, m68, m69, m70, m80, m81, m82, m83, m84, m85, m86, m87, m88, m89, m90, m9
	};
	sc_signal<state_type> state;

	//Proces stanu
	void state_process() {
		if (reset.read() == true) {
			state = m0;
		}
		else if (clk.posedge()) { // Gdy zbocze narastaj¹ce
			switch (state) {
			case m0:
				state = m1;
				break;
			case m1:
				switch (IR.read().range(15, 13)) {
				case 000:
					switch (IR.read().range(12, 11)) {
					case 00:
						if (INT.read() == false) {
							state = m0;
						}
						else {
							state = m9;
						}
						break;
					case 01:
						state = m10;
						break;
					case 10:
						state = m11;
						break;
					case 11:
						state = m15;
						break;
					default:
						state = m0;
						break;
					}
					break;
				case 001:
					switch (IR.read().range(12, 8)) {
					case 00000:
						state = m20;
						break;
					case 00001:
						state = m21;
						break;
					case 00010:
						state = m23;
						break;
					case 00011:
						state = m24;
						break;
					case 00100:
						state = m25;
						break;
					case 00101:
						state = m26;
						break;
					case 00110:
						state = m27;
						break;
					case 00111:
						state = m28;
						break;
					case 01000:
						state = m29;
						break;
					case 01001:
						state = m30;
						break;
					case 01010:
						state = m31;
						break;
					case 01011:
						state = m32;
						break;
					case 01100:
						state = m33;
						break;
					case 01101:
						state = m34;
						break;
					case 01110:
						state = m35;
						break;
					case 01111:
						state = m36;
						break;
					case 10000:
						state = m37;
						break;
					case 10001:
						state = m38;
						break;
					default:
						state = m0;
						break;
					}
					break;
				case 010:
					state = m40;
					break;
				case 011:
					state = m50;
					break;
				case 100:
					state = m60;
					break;
				case 101:
					state = m80;
					break;
				default:
					state = m0;
					break;
				}
				break;
			case m10:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m10;
				}
				break;
			case m11:
				state = m12;
				break;
			case m12:
				state = m13;
				break;
			case m13:
				state = m14;
				break;
			case m14:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m15:
				state = m16;
				break;
			case m16:
				state = m17;
				break;
			case m17:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
			case m20:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m21:
				state = m22;
				break;
			case m22:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m23:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m24:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m25:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m26:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m27:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m28:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m29:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m30:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m31:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m32:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m33:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m34:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m35:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m36:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m37:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m38:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m40:
				if (IR.read().range(12, 11) == 00) {
					state = m41;
				}
				else if (IR.read().range(12, 11) == 01 && C) {
					state = m41;
				}
				else if (IR.read().range(12, 11) == 10 && Z) {
					state = m41;
				}
				else if (IR.read().range(12, 11) == 11 && S) {
					state = m41;
				}
				else if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m41:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m50:
				state = m51;
				break;
			case m51:
				state = m51;
				break;
			case m52:
				state = m51;
				break;
			case m53:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m60:
				switch (IR.read().range(12, 10)) {
				case 000:
					state = m61;
					break;
				case 001:
					state = m62;
					break;
				case 010:
					state = m63;
					break;
				case 011:
					state = m64;
					break;
				case 100:
					state = m65;
					break;
				case 101:
					state = m66;
					break;
				case 110:
					state = m67;
					break;
				case 111:
					state = m68;
					break;
				}
			case m61:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m62:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m63:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m64:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m65:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m66:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m67:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m68:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m80:
				switch (IR.read().range(12, 9)) {
				case 0000:
					state = m81;
					break;
				case 0001:
					state = m82;
					break;
				case 0010:
					state = m83;
					break;
				case 0011:
					state = m84;
					break;
				case 0100:
					state = m85;
					break;
				case 0101:
					state = m86;
					break;
				case 0110:
					state = m87;
					break;
				case 0111:
					state = m88;
					break;
				case 1000:
					state = m89;
					break;
				case 1001:
					state = m90;
					break;
				default:
					state = m9;
					break;
				}
			case m81:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m82:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m83:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m84:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m85:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m86:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m87:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m88:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m89:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m90:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;
			case m9:
				state = m9;
				break;
			}
		}
	}
	// Proces logiki
	void logic_process() {
		switch (state) {
		case m0:
			Sa = "01"; Sbb = "0000"; Sba = "0000"; Sid = "001"; Sbc = "0000"; MIO = '1';
			Smar = '1'; Smbr = '0'; WR = '0'; RD = '1'; Salu = "0000"; LDF = '0'; INTA = '0';
			break;
		case m1:
			Sa = "00"; Sbb = "0000"; Sba = "0000"; Sid = "000"; Sbc = "0000"; MIO = '1';
			Smar = '0'; Smbr = '0'; WR = '0'; RD = '0'; Salu = "0000"; LDF = '0'; INTA = '0';
			break;
		case m10:
			Sa = "00"; Sbb = "0000"; Sba = "0000"; Sid = "000"; Sbc = "0000"; MIO = '1';
			Smar = '0'; Smbr = '0'; WR = '0'; RD = '0'; Salu = "0000"; LDF = '0'; INTA = '0';
			break;
		case m11:
			Sa = "10"; Sbb = "1010"; Sba = "0000"; Sid = "011"; Sbc = "0000"; MIO = '1';
			Smar = '1'; Smbr = '1'; WR = '1'; RD = '0'; Salu = "0000"; LDF = '0'; INTA = '0';
			// ... (analogicznie do oryginalnego kodu)
			break;
			// ... (analogicznie do oryginalnego kodu)
		default:
			Sa = "00"; Sbb = "0000"; Sba = "0000"; Sid = "000"; Sbc = "0000"; MIO = '1';
			Smar = '0'; Smbr = '0'; WR = '0'; RD = '0'; Salu = "0000"; LDF = '0'; INTA = '0';
			break;
		}
	}

	// Konstruktor
	SC_CTOR(Control) {
		SC_METHOD(state_process);
		sensitive << clk.pos() << reset;

		SC_METHOD(logic_process);
		sensitive << state;
	}
};

int sc_main(int argc, char* argv[]) {
	// Deklaracje sygna³ów
	sc_clock clock("clock", 20, SC_NS);
	sc_signal<sc_int<16>> IR;
	sc_signal<bool> reset, C, Z, S, INT;
	sc_signal<sc_bv<4>> Salu, Sbb, Sbc, Sba;
	sc_signal<sc_bv<3>> Sid;
	sc_signal<sc_bv<2>> Sa;
	sc_signal<bool> LDF, Smar, Smbr, WR, RD, INTA, MIO;

	// Utworzenie instancji modu³u
	Control control("MyControl");

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

	// Przyk³adowe wartoœci sygna³ów
	IR.write(0x1234);

	reset.write(false);
	C.write(false);
	Z.write(false);
	S.write(false);
	INT.write(false);

	// Uruchomienie symulacji
	sc_start(1, SC_NS);

	return 0;
}

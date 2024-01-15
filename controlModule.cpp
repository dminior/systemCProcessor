#include <systemc.h>
#include "structHeaders.h"

	void Control::state_process() {
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
					/*case 00100:
						state = m25;
						break;*/
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
				/*case 011:
					state = m50;
					break;*/
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
				break;
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
			/*case m25:
				if (INT.read() == true) {
					state = m9;
				}
				else {
					state = m0;
				}
				break;*/
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
			/*case m50:
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
				break;*/
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
				break;
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
	void Control::logic_process() {
		switch (state) {
		case m0:
			Sa = 0b01; 
			Sbb = 0b0000; 
			Sba = 0b0000; 
			Sid = 0b001; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m1:
			Sa = 0b00; 
			Sbb = 0b0000; 
			Sba = 0b0000; 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m10:
			Sa = 0b00; 
			Sbb = 0b0000; 
			Sba = 0b0000; 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m11:
			Sa = 0b10; 
			Sbb = 0b1010; 
			Sba = 0b0000; 
			Sid = 0b011; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m12:
			Sa = 0b10; 
			Sbb = 0b1010; 
			Sba = 0b0001; 
			Sid = 0b011; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m13:
			Sa = 0b00; 
			Sbb = 0b1110; 
			Sba = 0b1011; 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m14:
			Sa = 0b00; 
			Sbb = 0b1111; 
			Sba = 0b1010; 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m15:
			Sa = 0b00; 
			Sbb = 0b0000; 
			Sba = 0b0001; 
			Sid = 0b010; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m16:
			Sa = 0b10; 
			Sbb = 0b0000; 
			Sba = 0b1010; 
			Sid = 0b010; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m17:
			Sa = 0b10; 
			Sbb = 0b0000; 
			Sba = 0b1011; 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m20:
			Sa = 0b10; 
			Sbb = IR.read().range(3, 0).to_int(); 
			Sba = 0b0001; Sid = 0b011; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m21:
			Sa = 0b00; 
			Sbb = 0b0000; 
			Sba = 0b0001; 
			Sid = 0b010; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m22:
			Sa = 0b10; 
			Sbb = 0b0000; Sba = IR.read().range(3, 0).to_int(); 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m23:
			Sa = 0b00; 
			Sbb = IR.read().range(3, 0).to_int(); 
			Sba = IR.read().range(3, 0).to_int(); 
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0101; LDF = 0; INTA = 0;
			break;
		case m24:
			Sa = 0b00; 
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b1101; LDF = 1; INTA = 0;
			break;
		case m26:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b1000; LDF = 0; INTA = 0;
			break;
		case m27:
			Sa = 0b00; 
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b1111; LDF = 0; INTA = 0;
			break;
		case m28:
			Sa = 0b00; 
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b1110; LDF = 0; INTA = 0;
			break;
		case m29:
			Sa = 0b00; 
			Sbb = 0b0000;
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m30:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m31:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0010; LDF = 1; INTA = 0;
			break;
		case m32:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m33:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m34:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0101; LDF = 1; INTA = 0;
			break;
		case m35:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0100; LDF = 1; INTA = 0;
			break;

		case m36:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0110; LDF = 1; INTA = 0;
			break;
		case m37:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 0;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m38:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 0;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m40:
			Sa = 0b01;
			Sbb = 0b0000;
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m41:
			Sa = 0b00;
			Sbb = 0b1011;
			Sba = 0b1011;
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0010; LDF = 1; INTA = 0;
			break;
		case m60:
			Sa = 0b01;
			Sbb = 0b0000;
			Sba = 0b0001;
			Sid = 0b001; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m61:
			Sa = 0b00;
			Sbb = 0b0001;
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m62:
			Sa = 0b00;
			Sbb = 0b1111;
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m63:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0010; LDF = 1; INTA = 0;
			break;
		case m64:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m65:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m66:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0101; LDF = 0; INTA = 0;
			break;
		case m67:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0100; LDF = 0; INTA = 0;
			break;
		case m68:
			Sa = 0b00;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0001; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0110; LDF = 1; INTA = 0;
			break;
		/*case m80:
			Sa = 0b01;
			Sbb = 0b0000;
			Sba = 0b10000;
			Sid = 0b001; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;

		case m81:
			Sa = 0b01;
			Sbb = 0b0000;
			Sba = 0b10001;
			Sid = 0b001; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;*/
		case m82:
			Sa = 0b11;
			Sbb = 0b0000;
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m83:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 1; WR = 1; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		case m84:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0010; LDF = 1; INTA = 0;
			break;
		case m85:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m86:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = 0b0001;
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0011; LDF = 1; INTA = 0;
			break;
		case m87:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0101; LDF = 0; INTA = 0;
			break;
		case m88:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0100; LDF = 0; INTA = 0;
			break;
		case m89:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 1; RD = 0; Salu = 0b0110; LDF = 1; INTA = 0;
			break;
		case m90:
			Sa = 0b11;
			Sbb = IR.read().range(3, 0).to_int();
			Sba = IR.read().range(3, 0).to_int();
			Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0110; LDF = 1; INTA = 0;
			break;

		case m9:
			Sa = 0b01; 
			Sbb = 0b0000; 
			Sba = 0b0000; 
			Sid = 0b001; Sbc = 0b0000; MIO = 1;
			Smar = 1; Smbr = 0; WR = 0; RD = 1; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		default:
			Sa = 0b00; Sbb = 0b0000; Sba = 0b0000; Sid = 0b000; Sbc = 0b0000; MIO = 1;
			Smar = 0; Smbr = 0; WR = 0; RD = 0; Salu = 0b0000; LDF = 0; INTA = 0;
			break;
		}
	}


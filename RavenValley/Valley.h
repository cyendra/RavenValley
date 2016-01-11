#pragma once

#include <vector>

namespace raven {

	class Valley {
	public:
		static enum Result {
			NotUnicodeFile,
			Success
		};
		
		static enum BOM_Type {
			UTF8,
			UTF16_BE,
			UTF16_LE,
			UTF32_BE,
			UTF32_LE,
			Error
		};

		typedef unsigned char Byte;
		typedef unsigned short DoubleByte;
		typedef unsigned long FourByte;

		const Byte BOM_UTF16_LE[2] = { 0xFF, 0xFE };
		const Byte BOM_UTF16_BE[2] = { 0xFE, 0xFF };
		const Byte BOM_UTF32_LE[4] = { 0xFF, 0xFE, 0x00, 0x00 };
		const Byte BOM_UTF32_BE[4] = { 0x00, 0x00, 0xFE, 0xFF };
		const Byte BOM_UTF8[3] = { 0xEF, 0xBB, 0xBF };

	private:
		std::vector<Byte> unicodes;
	public:
		Valley() {}
		~Valley() {}
		Result LoadUnicodeFile() {

		}
		
		BOM_Type GetBytesBomType(Byte* bytes, int len) {
			auto fEqual = [](const Byte* a, const Byte* b, const int len) -> bool {
				for (int i = 0; i < len; i++) {
					if (a[i] != b[i]) return false;
				}
				return true;
			};
			if (len >= 2) {
				if (fEqual(bytes, BOM_UTF16_LE, 2)) return BOM_Type::UTF16_LE;
				if (fEqual(bytes, BOM_UTF16_BE, 2)) return BOM_Type::UTF16_BE;
			}
			if (len >= 4) {
				if (fEqual(bytes, BOM_UTF32_LE, 4)) return BOM_Type::UTF32_LE;
				if (fEqual(bytes, BOM_UTF32_BE, 4)) return BOM_Type::UTF32_BE;
			}
			if (len >= 3) {
				if (fEqual(bytes, BOM_UTF8, 3)) return BOM_Type::UTF8;
			}
			return BOM_Type::Error;
		}

		std::string DisplayBomType(BOM_Type type) {
			switch (type) {
			case raven::Valley::UTF8:
				return std::string("UTF8");
			case raven::Valley::UTF16_BE:
				return std::string("UTF16_BE");
			case raven::Valley::UTF16_LE:
				return std::string("UTF16_LE");
			case raven::Valley::UTF32_BE:
				return std::string("UTF32_BE");
			case raven::Valley::UTF32_LE:
				return std::string("UTF32_LE");
			default:
				return std::string("Error");
			}
		}

	};

}




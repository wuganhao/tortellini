#include "./tortellini.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

static const wstring ini_text = LR"INI(
naked = no

[Sauce]
is-saucy = yes
tasty = yes
grams_of_fat = 100000
who-cares = nobody

[   Pasta   ]
whole-wheat = nah, fam!
al_dente=1
steam-levels = 42.9

invalid key = will be thrown out

[noodle face]
cute =        true
 smiling        = of course; you cannot deny it!

[HEXME]
color = 0xAABBCCDD
)INI";

int main() {
	tortellini::ini ini;

	std::wistringstream iss(ini_text);
	iss >> ini;

	ini[L"Runtime"][L"string"] = L"isn't this a beautiful string?"s;
	ini[L"Runtime"][L"some-int"] = 12345l;
	ini[L"Runtime"][L"some-true"] = true;
	ini[L"Runtime"][L"some-false"] = false;
	ini[L""][L"naked"] = true;
	ini[L"InTeGeRs"][L"int"] = -12345;
	ini[L"InTeGeRs"][L"int"] = (int) -12345;
	ini[L"InTeGeRs"][L"long"] = -12345L;
	ini[L"InTeGeRs"][L"longlong"] = -12345LL;
	ini[L"InTeGeRs"][L"uint"] = 12345u;
	ini[L"InTeGeRs"][L"uint"] = (unsigned int) 12345;
	ini[L"InTeGeRs"][L"ulong"] = 12345L;
	ini[L"InTeGeRs"][L"ulonglong"] = 12345LL;
	ini[L"InTeGeRs"][L"float"] = 12.34f;
	ini[L"InTeGeRs"][L"double"] = 12.34;
	ini[L"InTeGeRs"][L"longdouble"] = 12.34L;
	ini[L"othertest"][L"int"] = L"1234k";

	std::wstring foo = L"a string";
	ini[L"cpptypes"][L"string"] = foo;
	foo = ini[L"cpptypes"][L"string"] | L"nope";

	#define D(_s, _k, _f) std::wcerr << L"@@@ [" << (_s) << L"] " << (_k) << L" = " << (ini[(_s)][(_k)] | (_f)) << std::endl
	D(L"pasta", L"whole-wheat", L"isn't set!");
	D(L"RuNTiME", L"string", L"isn't set!");
	D(L"RuNTiME", L"string", true);
	D(L"nOODLE FACE", L"cute", false);
	D(L"nOODLE FACE", L"smiling", L"not set!");
	D(L"pasta", L"al_dente", false);
	D(L"HEXME", L"color", 0L);
	D(L"Integers", L"int", 10);
	D(L"Integers", L"int", (int) 10);
	D(L"Integers", L"long", 10L);
	D(L"Integers", L"longlong", 10LL);
	D(L"Integers", L"uint", 10);
	D(L"Integers", L"uint", (unsigned int) 10);
	D(L"Integers", L"ulong", 10UL);
	D(L"Integers", L"ulonglong", 10ULL);
	D(L"Integers", L"float", 10.0f);
	D(L"Integers", L"double", 10.0);
	D(L"Integers", L"longdouble", 10.0L);
	D(L"othertest", L"int", 100);
	#undef D
	std::wcout << std::endl << L"----------------" << std::endl << std::endl;

	std::wcout << ini;
	return 0;
}

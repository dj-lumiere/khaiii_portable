/**
 * @author  Jamie (jamie.lim@kakaocorp.com)
 * @copyright  Copyright (C) 2018-, Kakao Corp. All rights reserved.
 */


#include "khaiii/Morph.hpp"


//////////////
// includes //
//////////////
#include <cassert>
#include <string>
#include <vector>

#include "khaiii/util.hpp"


namespace khaiii {


using std::string;
using std::vector;
using std::wstring;
using std::wstringstream;


///////////////
// variables //
///////////////
static const char* _TAG_SET[POS_TAG_SIZE] = {
     "EC",  "EF",  "EP", "ETM", "ETN",  "IC",  "JC", "JKB", "JKC", "JKG",
    "JKO", "JKQ", "JKS", "JKV",  "JX", "MAG", "MAJ",  "MM", "NNB", "NNG",
    "NNP",  "NP",  "NR",  "SE",  "SF",  "SH",  "SL",  "SN",  "SO",  "SP",
     "SS",  "SW", "SWK",  "VA", "VCN", "VCP",  "VV",  "VX", "XPN",  "XR",
    "XSA", "XSN", "XSV",  "ZN",  "ZV",  "ZZ",
};


////////////////////
// ctors and dtor //
////////////////////
Morph::Morph(const wchar_t* wlex, pos_tag_t tag, const wchar_t* wbegin, int wlength)
        : wlex(wlex), wbegin(wbegin), wlength(wlength), _lex(wstr_to_utf8(wlex)) 
{
	assert(wlex);

	lex = _lex.c_str();
	this->tag = pos_str(tag);
	begin = -1;
	length = -1;
	next = nullptr;
}


/////////////
// methods //
/////////////
const char* Morph::pos_str(pos_tag_t num) {
    assert(0 < num && num <= POS_TAG_SIZE);
    return _TAG_SET[num-1];
}

void Morph::organize(const wchar_t* wraw, const vector<int>& wbegins, const vector<int>& wends) {
	assert(wraw);

	int begin_idx = wbegin - wraw;
	int end_idx = begin_idx + wlength - 1;

	assert(end_idx - begin_idx >= 0);

	begin = wbegins[begin_idx];
	length = wends[end_idx] - begin;
}



string Morph::str() {
    return wstr_to_utf8(wstr().c_str());
}


wstring Morph::wstr() {
    wstringstream wss;
    wss << wlex << L"/" << tag << L":" << begin << L"," << length;
    return wss.str();
}


}    // namespace khaiii

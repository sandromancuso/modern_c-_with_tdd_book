#include "gmock/gmock.h"    //<label id="code.include"/>
#include "Soundex.h"
#include <iostream>
#include <iosfwd>

using namespace std;
using namespace testing;

class SoundexEncoding: public Test {
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
   ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
	ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
	EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
	EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
	EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
	EXPECT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
	ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonantsWithDigits) {
	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
	ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
	ASSERT_THAT(soundex.encode("Baeiouhycdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombineDuplicateEncodings) {
	ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));

	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

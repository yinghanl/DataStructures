#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		//TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
		// TODO: Add more Compression test cases

		//TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative runs test");
		//TEST_CASE_DESCRIBE(testABABAB, "Basic ABABAB runs test");
		//TEST_CASE_DESCRIBE(testBasicCombonationRuns, "Basic combonation runs test");
		//TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test");
		//TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test");
		//TEST_CASE_DESCRIBE(testLongCombonationRuns, "Long combonation runs test");
		TEST_CASE_DESCRIBE(testZeroes, "Zeroes runs test");
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testBasicNegativeRuns()
	{
		char test[] = "abcdefghijklmnopqrstuvwxyz";

		char expected[] = "\xE6" "abcdefghijklmnopqrstuvwxyz";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testABABAB()
	{
		char test[] = "ababab";
		
		char expected[] = "\xFA" "ababab";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testBasicCombonationRuns()
	{
		char test[] = "aaa" "bcdbcd" "aaa" "bcdbcd";

		char expected[] = "\x03" "a" "\xFA" "bcdbcd" "\x03" "a" "\xFA" "bcdbcd";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testBasicCombonationRuns2()
	{
		char test[] = "bcdbcd" "aaa" "bcdbcd" "aaa";

		char expected[] = "\xFA" "bcdbcd" "\x03" "a" "\xFA" "bcdbcd" "\x03" "a";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	//TODO:
	//Make a test for an extremely long case
	
	void testLongPositiveRuns()
	{
		char test[] = "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa";

		char expected[] = "\x7F" "a" "\x7f" "a"  "\x2E" "a";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testLongNegativeRuns()
	{
		char test[] = "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab";

		char expected[] = "\x81" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "abababa"
			"\x81" "bab" "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab" "abab"
			"\xD2" "ababababab" "ababababab" "ababababab" "ababababab" "ababab";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testLongCombonationRuns()
	{
		char test[] = "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"

			"cbabababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"

			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa";

		char expected[] = "\x7F" "a" "\x7f" "a"  "\x2E" "a"
			"\x81" "cbabababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "abababa"
			"\x81" "bab" "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab" "abab"
			"\xD2" "ababababab" "ababababab" "ababababab" "ababababab" "ababab"
			"\x7F" "a" "\x7f" "a"  "\x2E" "a";

		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testZeroes()
	{
		char test[] = "\x00" "\x00" "\x00";
		char expected[] = "\x03" "\x00";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive run test");
		// TODO: Add more Decompression test  cases
		TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative run test");
		TEST_CASE_DESCRIBE(testBasicCombonationRuns, "Basic negative run test");
		TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test");
		TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test");
		TEST_CASE_DESCRIBE(testLongCombonationRuns, "Long combonation runs test");

	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "\x28" "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testBasicNegativeRuns()
	{
		char test[] = "\xE6" "abcdefghijklmnopqrstuvwxyz";
		char expected[] = "abcdefghijklmnopqrstuvwxyz";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testBasicCombonationRuns()
	{
		char test[] = "\x03" "a" "\xFA" "bcdbcd" "\x03" "a" "\xFA" "bcdbcd";
		char expected[] = "aaa" "bcdbcd" "aaa" "bcdbcd";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testLongPositiveRuns()
	{
		char test[] = "\x7F" "a" "\x7f" "a"  "\x2E" "a";

		char expected[] = "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testLongNegativeRuns()
	{
		char test[] = "\x81" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "abababa"
			"\x81" "bab" "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab" "abab"
			"\xD2" "ababababab" "ababababab" "ababababab" "ababababab" "ababab";

		char expected[] = "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testLongCombonationRuns()
	{

		char test[] = "\x7F" "a" "\x7f" "a"  "\x2E" "a"
			"\x81" "cbabababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "abababa"
			"\x81" "bab" "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab"  "ababababab" "abab"
			"\xD2" "ababababab" "ababababab" "ababababab" "ababababab" "ababab"
			"\x7F" "a" "\x7f" "a"  "\x2E" "a";

		char expected[] = "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"

			"cbabababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"
			"ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab" "ababababab"

			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa"
			"aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa" "aaaaaaaaaa";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	//RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	//RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

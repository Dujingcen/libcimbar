#include "unittest.h"

#include "CimbReader.h"

#include "CimbCommon.h"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
using std::string;

namespace {
	std::string get_sample(std::string filename)
	{
		return std::string(LIBCIMBAR_PROJECT_ROOT) + "/samples/" + filename;
	}
}

TEST_CASE( "CimbReaderTest/testSimple", "[unit]" )
{
	string sample_path = get_sample("4.png");

	CimbReader cr(sample_path);

	// read
	unsigned bits1 = cr.read();
	assertEquals(8, bits1);

	unsigned bits2 = cr.read();
	assertEquals(50, bits2);

	unsigned bits3 = cr.read();
	assertEquals(4, bits3);

	unsigned bits4 = cr.read();
	assertEquals(47, bits4);

	while (!cr.done())
		cr.read();
	assertTrue(cr.done());
}
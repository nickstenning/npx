#include "nk/nk.h"
#include "ga/genome.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(nk_landscape)

BOOST_AUTO_TEST_CASE(has_unique_id)
{
	nk::Landscape nkl(8, 0);
	BOOST_CHECK( nkl.id() );
}

BOOST_AUTO_TEST_SUITE_END()

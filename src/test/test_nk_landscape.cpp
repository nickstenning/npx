#include "nk/landscape.h"
#include "ga/genome.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(nk_landscape);

BOOST_AUTO_TEST_CASE(has_unique_id)
{
	nk::Landscape nkl1;
  nk::Landscape nkl2;
	BOOST_CHECK( nkl1.id() != nkl2.id() );
}

BOOST_AUTO_TEST_CASE(has_default_zeros)
{
  nk::Landscape nkl;
  BOOST_CHECK( nkl.n() == 0 );
  BOOST_CHECK( nkl.k() == 0 );
}

BOOST_AUTO_TEST_CASE(evaluate_default_zero)
{
  nk::Landscape nkl;
  ga::Genome g;
  BOOST_CHECK( nkl.evaluate(g) == 0 );
}

BOOST_AUTO_TEST_CASE(evaluate_throws_if_wrong_size)
{
  nk::Landscape nkl;
  ga::Genome g(2);
  BOOST_CHECK_THROW( nkl.evaluate(g), nk::Landscape::InvalidGenomeSize );
}

BOOST_AUTO_TEST_CASE(evaluate_same_for_same_genome)
{
  nk::Landscape nkl(8, 0);
  ga::Genome g(8);
  BOOST_CHECK( nkl.evaluate(g) == nkl.evaluate(g) );
}

BOOST_AUTO_TEST_CASE(evaluate_different_for_different_genomes)
{
  nk::Landscape nkl(8, 0);
  ga::Genome g(8);
  ga::Genome h(g);
  h[4].flip();
  BOOST_CHECK( nkl.evaluate(g) != nkl.evaluate(h) );
}

BOOST_AUTO_TEST_CASE(evaluate_between_zero_and_one)
{
  nk::Landscape nkl(8, 0);
  ga::Genome g(8);
  BOOST_CHECK( nkl.evaluate(g) > 0 );
  BOOST_CHECK( nkl.evaluate(g) < 1 );
}

BOOST_AUTO_TEST_CASE(evaluate_position)
{
  nk::Landscape nkl(1, 0);
  ga::Genome g(1);
  BOOST_CHECK( nkl.evaluate_position(0, g) );
}

BOOST_AUTO_TEST_CASE(evaluate_position_throws_if_invalid_position)
{
  nk::Landscape nkl;
  ga::Genome g;
  BOOST_CHECK_THROW( nkl.evaluate_position(0, g), nk::Landscape::InvalidPosition );
}

BOOST_AUTO_TEST_CASE(evaluate_position_no_epistasis)
{
  nk::Landscape nkl(8, 0);
  ga::Genome g(8);
  double before = nkl.evaluate_position(0, g);
  g[1].flip();
  double after = nkl.evaluate_position(0, g);
  BOOST_CHECK( before == after );
}

BOOST_AUTO_TEST_CASE(evaluate_position_epistasis)
{
  nk::Landscape nkl(8, 1);
  ga::Genome g(8);
  double before = nkl.evaluate_position(0, g);
  g[1].flip();
  double after = nkl.evaluate_position(0, g);
  BOOST_CHECK( before != after );
}

BOOST_AUTO_TEST_CASE(evaluate_position_maximal_epistasis)
{
  nk::Landscape nkl(4, 3);
  ga::Genome g(4);
  double before = nkl.evaluate_position(0, g);
  double after;

  g[1].flip();
  after = nkl.evaluate_position(0, g);
  BOOST_CHECK( before != after );

  g[1].flip();
  g[2].flip();
  after = nkl.evaluate_position(0, g);
  BOOST_CHECK( before != after );

  g[2].flip();
  g[3].flip();
  after = nkl.evaluate_position(0, g);
  BOOST_CHECK( before != after );
}

BOOST_AUTO_TEST_SUITE_END();

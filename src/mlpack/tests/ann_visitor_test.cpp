/**
 * @file tests/ann_visitor_test.cpp
 *
 * Tests for testing visitors in ANN's of mlpack.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#include <mlpack/core.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/layer/layer_types.hpp>
#include <mlpack/methods/ann/visitor/bias_set_visitor.hpp>
#include <mlpack/methods/ann/visitor/weight_set_visitor.hpp>
#include <mlpack/methods/ann/visitor/reset_visitor.hpp>

#include "catch.hpp"
#include "test_catch_tools.hpp"

using namespace mlpack;
using namespace mlpack::ann;

/**
 * Test that the BiasSetVisitor works properly.
 */
TEST_CASE("BiasSetVisitorTest", "[ANNVisitorTest]")
{
  LayerTypes<> linear = new Linear<>(10, 10);

  arma::mat layerWeights(110, 1);
  layerWeights.zeros();

  ResetVisitor resetVisitor;

  boost::apply_visitor(WeightSetVisitor(layerWeights, 0), linear);

  boost::apply_visitor(resetVisitor, linear);

  arma::mat weight = {"1 2 3 4 5 6 7 8 9 10"};

  size_t biasSize = boost::apply_visitor(BiasSetVisitor(weight, 0), linear);

  REQUIRE(biasSize == 10);

  arma::mat input(10, 1), output;
  input.randu();

  boost::apply_visitor(ForwardVisitor(input, output), linear);

  REQUIRE(arma::accu(output) == 55);

  boost::apply_visitor(DeleteVisitor(), linear);
}

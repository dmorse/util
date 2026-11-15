/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu) 
* Distributed under the terms of the GNU General Public License.
*/

#include "AverageStage.h"
#include <util/format/Int.h>
#include <util/format/Dbl.h>

#include <math.h>

namespace Util
{

   /*
   * Constructor for rootPtr AverageStage, with stageId = 0.
   */
   AverageStage::AverageStage(int blockFactor)
    : shift_(0.0),
      sum_(0.0),
      sumSq_(0.0),
      blockSum_(0.0),
      nSample_(0),
      nBlockSample_(0),
      stageInterval_(1),
      childPtr_(0),
      rootPtr_(0),
      stageId_(0),
      blockFactor_(blockFactor)
   {  rootPtr_ = this; }

   /*
   * Constructor for dynamically generated objects with stageId > 0 (private).
   */
   AverageStage::AverageStage(long stageInterval, int stageId, 
                              AverageStage* rootPtr, int blockFactor)
    : shift_(0.0),
      sum_(0.0),
      sumSq_(0.0),
      blockSum_(0.0),
      nSample_(0),
      nBlockSample_(0),
      stageInterval_(stageInterval),
      childPtr_(0),
      rootPtr_(rootPtr),
      stageId_(stageId),
      blockFactor_(blockFactor)
   {}

   /*
   * Destructor.
   */
   AverageStage::~AverageStage()
   {
      if (childPtr_) {
         delete childPtr_;
      }
   }

   /*
   * Reset the block factor.
   */
   void AverageStage::setBlockFactor(int blockFactor)
   {
      if (nSample_ > 0) {
         UTIL_THROW("Attempt to reset block factor when nSample > 0");
      }
      if (blockFactor < 2) {
         UTIL_THROW("Invalid value of blockFactor");
      }
      blockFactor_ = blockFactor;
   }

   void AverageStage::registerDescendant(AverageStage* descendantPtr)
   {}

   /*
   * Reset all accumulators and counters to zero.
   */
   void AverageStage::clear()
   {
      shift_        = 0.0;
      sum_          = 0.0;
      sumSq_        = 0.0;
      blockSum_     = 0.0;
      nSample_      = 0;
      nBlockSample_ = 0;
      if (childPtr_) {
         // The child's destructor deletes its own descendants.
         delete childPtr_;
         childPtr_ = 0;
      }
   }

   /*
   * Add a sampled value to the ensemble.
   */
   void AverageStage::sample(double value)
   {

      // Increment global accumulators. The sums are taken relative to
      // shift_, the first sampled value (or, after loading, the average
      // of the loaded values): sumSq/n - (sum/n)^2 of raw values loses
      // all precision when the standard deviation is small compared to
      // the mean (it can even be negative).
      if (nSample_ == 0) {
         shift_ = value;
      }
      const double d = value - shift_;
      sum_ += d;
      sumSq_ += d*d;
      ++nSample_;

      // Increment block accumulators
      blockSum_ += value;
      ++nBlockSample_;

      if (nBlockSample_ == blockFactor_) {

         if (!childPtr_) {
            long nextStageInterval = stageInterval_*blockFactor_;
            int  nextStageId       = stageId_ + 1;
            childPtr_ = new AverageStage(nextStageInterval, nextStageId, 
                                         rootPtr_, blockFactor_);
            rootPtr_->registerDescendant(childPtr_);
         }

         // Add block average to child ensemble
         childPtr_->sample(blockSum_ / double(blockFactor_));

         // Reset block accumulators
         blockSum_ = 0.0;
         nBlockSample_ = 0;

      }

   }

   /*
   * Return the average of all sampled values.
   */
   double AverageStage::average() const
   {  return shift_ + sum_/double(nSample_); }

   /*
   * Return the variance of all sampled values
   */
   double AverageStage::variance() const
   {
      double rSample_ = double(nSample_);
      double ave   = sum_/rSample_;
      double aveSq = sumSq_/rSample_;
      double var = aveSq - ave*ave;
      // Rounding errors can make var slightly negative
      return (var < 0.0) ? 0.0 : var;
   }

   /*
   * Return the standard deviation of all sampled values.
   */
   double AverageStage::stdDeviation() const
   {  return sqrt(variance()); }

   /*
   * Return the number of sampled values.
   */
   long AverageStage::nSample() const
   {  return nSample_; }

   /*
   * Return the number of measured values per sample at this stage.
   */
   long AverageStage::stageInterval() const
   {  return stageInterval_; }

   /*
   * Estimated statistical error of the average.
   */
   double AverageStage::error() const
   {  return sqrt(variance()/double(nSample_-1)); }

}

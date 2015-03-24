// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2015.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Hendrik Weisser $
// $Authors: Sven Nahnsen, Hendrik Weisser $
// --------------------------------------------------------------------------

#include <OpenMS/ANALYSIS/ID/ConsensusIDAlgorithm.h>
#include <OpenMS/CONCEPT/LogStream.h>

using namespace std;

#define DEBUG_ID_CONSENSUS
#undef  DEBUG_ID_CONSENSUS

namespace OpenMS
{
  ConsensusIDAlgorithm::ConsensusIDAlgorithm() :
    DefaultParamHandler("ConsensusIDAlgorithm")
  {
    defaults_.setValue("considered_hits", 10, "The number of top hits that are used for the consensus scoring ('0' for all hits).");
    defaults_.setMinInt("considered_hits", 0);

    defaultsToParam_();
  }


  ConsensusIDAlgorithm::~ConsensusIDAlgorithm()
  {
  }


  void ConsensusIDAlgorithm::updateMembers_()
  {
    considered_hits_ = param_.getValue("considered_hits");
  }


  void ConsensusIDAlgorithm::apply(vector<PeptideIdentification>& ids)
  {
    // abort if no IDs present
    if (ids.empty())
    {
      return;
    }

    // @TODO: what if there's only one ID run?!

    // prepare data here, so that it doesn't have to happen in each algorithm:
    for (vector<PeptideIdentification>::iterator pep_it = ids.begin(); 
         pep_it != ids.end(); ++pep_it)
    {
      pep_it->sort();
      if ((considered_hits_ > 0) && 
          (pep_it->getHits().size() > considered_hits_))
      {
        pep_it->getHits().resize(considered_hits_);
      }
    }

    apply_(ids); // actual (subclass-specific) processing
    ids[0].assignRanks();

#ifdef DEBUG_ID_CONSENSUS
    const vector<PeptideHit>& hits = ids[0].getHits();
    for (Size i = 0; i < hits2.size(); ++i)
    {
      LOG_DEBUG << "  " << hits2[i].getSequence() << " "
                << hits2[i].getScore() << endl;
    }
#endif
  }


  void ConsensusIDAlgorithm::compareChargeStates_(Int& recorded_charge, 
                                                  Int new_charge,
                                                  const AASequence& peptide)
  {
    if (recorded_charge == 0) // update recorded charge
    {
      recorded_charge = new_charge;
    }
    else if ((new_charge != 0) && (recorded_charge != new_charge))
    { // maybe TODO: calculate correct charge from prec. m/z and peptide mass?
      String msg = "Conflicting charge states found for peptide '" +
        peptide.toString() + "': " + String(recorded_charge) + ", " + 
        String(new_charge);
      throw Exception::InvalidValue(__FILE__, __LINE__, __PRETTY_FUNCTION__, 
                                    msg, String(new_charge));
    }
  }

} // namespace OpenMS

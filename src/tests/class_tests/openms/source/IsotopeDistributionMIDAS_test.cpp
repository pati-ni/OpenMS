// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
//
//
//
//
//
// --------------------------------------------------------------------------
// $Maintainer: Nikos Patikas $
// $Authors: Nikos Patikas $
// --------------------------------------------------------------------------


///////////////////////////

// This one is going to be tested.
#include <OpenMS/CHEMISTRY/IsotopeDistributionMIDAS.h>

///////////////////////////

// More headers

#include <OpenMS/CONCEPT/ClassTest.h>
#include <OpenMS/test_config.h>



/////////////////////////////////////////////////////////////

START_TEST(IsotopeDistributionMIDAS, "$Id$")

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

using namespace OpenMS;
using namespace std;

IsotopeDistributionMIDAS* nullPointer = 0;


START_SECTION(IsotopeDistributionMIDAS())
    IsotopeDistributionMIDAS *ptr = 0;
    ptr = new IsotopeDistributionMIDAS();
  TEST_NOT_EQUAL(ptr, nullPointer);
    delete ptr;
END_SECTION



END_TEST

#pragma clang diagnostic pop

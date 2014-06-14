//
// Unit tests for block-chain checkpoints
//
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../checkpoints.h"
#include "../util.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p10000 = uint256("0x7b50ea3b42e613e65ec2aca6797a5780e1c545a617e4a610577fb4b040f0035b");
    uint256 p121000 = uint256("0x1d286956120cf256bed13bcc1f5fe79a98347c80f2225ded92bbbdfc1147b5f5");
    BOOST_CHECK(Checkpoints::CheckBlock(10000, p10000));
    BOOST_CHECK(Checkpoints::CheckBlock(121000, p121000));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(10000, p121000));
    BOOST_CHECK(!Checkpoints::CheckBlock(121000, p10000));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(10000+1, p121000));
    BOOST_CHECK(Checkpoints::CheckBlock(121000+1, p10000));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 121000);
}    

BOOST_AUTO_TEST_SUITE_END()

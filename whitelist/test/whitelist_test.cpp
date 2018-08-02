// Copyright (C) 2018 Bluzelle
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License, version 3,
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <mocks/mock_node_base.hpp>
#include <mocks/mock_session_base.hpp>
#include <mocks/mock_boost_asio_beast.hpp>
#include <whitelist/whitelist.hpp>

using namespace ::testing;

namespace
{
    const char* WHITELISTED_UUID    {"1234567809000000000000000000000000000000000000000000000000000000"};
    const char* NOT_WHITELISTED_UUID{"e81ca538a2224add8cb8065c8b65a391"};
}


TEST(whitelist_test, test_that_is_member_returns_true_if_is_uuid_found_in_whitelist)
{
    bzn::whitelist sut;
    EXPECT_TRUE(sut.is_member(WHITELISTED_UUID));
}


TEST(whitelist_test, test_that_is_member_returns_false_if_uuid_found_in_whitelist)
{
    bzn::whitelist sut;
    EXPECT_FALSE(sut.is_member(NOT_WHITELISTED_UUID));
}

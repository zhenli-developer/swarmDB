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

#pragma once

#include <whitelist/whitelist_base.hpp>
#include <gmock/gmock.h>

namespace bzn {
    class Mockwhitelist_base : public whitelist_base
    {
        public:
        MOCK_METHOD1(is_member,
                bool(const bzn::uuid_t& uuid));
    };
}

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

#include <cstdint>
#include <include/bluzelle.hpp>
#include <proto/bluzelle.pb.h>
#include <pbft/pbft_operation.hpp>

namespace bzn
{

    class pbft_service_base
    {
    public:

        virtual void commit_operation(std::shared_ptr<pbft_operation> operation) = 0;

        virtual ~pbft_service_base() = default;

    };

}

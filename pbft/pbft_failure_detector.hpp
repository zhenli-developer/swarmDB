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

#include <proto/bluzelle.pb.h>
#include <include/boost_asio_beast.hpp>
#include "pbft_operation.hpp"

namespace bzn
{

    class pbft_failure_detector
    {
    public:
        pbft_failure_detector(std::shared_ptr<bzn::asio::io_context_base>);

        void see_request(pbft_request& req);

        void execute_request(pbft_request& req);

        void register_failure_handler(std::function<void()> handler);

    private:

        std::shared_ptr<bzn::asio::io_context_base> io_context;

        std::list<bzn::hash_t> ordered_requests;
        std::unordered_set<bzn::hash_t> outstanding_requests;
    };

}

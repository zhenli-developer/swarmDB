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

#include <pbft/pbft_failure_detector.hpp>

using namespace bzn;

pbft_failure_detector::pbft_failure_detector(std::shared_ptr<bzn::asio::io_context_base> io_context)
        : io_context(std::move(io_context))
{
}

void
pbft_failure_detector::see_request(pbft_request& /*req*/)
{
    //...
}

void
pbft_failure_detector::register_failure_handler(std::function<void()> /*handler*/)
{
    // ...
}
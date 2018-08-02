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

#include "whitelist_base.hpp"
#include <curl/curl.h>
#include <string>

namespace bzn
{
    class whitelist : whitelist_base {
    public:
        whitelist();
        virtual ~whitelist();

        bool is_member(const std::string& uuid) override;

    private:
        static size_t writefunction(void* ptr, size_t size, size_t nmemb, void* stream);
        char* build_post_fields(const std::string& uuid);

        CURL* curl;
        static std::string response;
    };
}

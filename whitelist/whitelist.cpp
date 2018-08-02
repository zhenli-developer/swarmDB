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

#include <whitelist/whitelist.hpp>
#include <functional>
#include <iostream>
#include <json/json.h>
#include <json/reader.h>


namespace
{
    const char* ROPSTEN_URL{"https://ropsten.infura.io"};
    const char* ROPSTEN_DATA{"{\"jsonrpc\":\"2.0\",\"method\":\"eth_call\",\"params\":[{\"to\":\"0x58261EEc3fCD83DACB5E0532277c27f1cA58270E\",\"data\": \"0x3a4e44a0%s\" },\"latest\"],\"id\":1}"};
}


namespace bzn
{
    whitelist::whitelist()
    {
        const CURLcode result = curl_global_init(CURL_GLOBAL_DEFAULT);
        if (result != CURLE_OK)
        {
            throw std::runtime_error(std::string("curl_global_init() in whitelist failed with error: ") + curl_easy_strerror(result));
        }

        this->curl = curl_easy_init();
        if (NULL == this->curl)
        {
            throw std::runtime_error("curl_easy_init() in whitelist returned null");
        }

        curl_easy_setopt(this->curl, CURLOPT_URL, ROPSTEN_URL);
        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, reinterpret_cast<void*>(whitelist::write_function));
    }


    whitelist::~whitelist()
    {
        curl_easy_cleanup(this->curl);
    }


    size_t
    whitelist::write_function(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }


    char*
    whitelist::build_post_fields(const std::string& uuid)
    {
        static char retval[256];
        std::snprintf(retval, 256, ROPSTEN_DATA, uuid.c_str());
        return retval;
    }


    bool
    whitelist::is_member(const std::string &uuid)
    {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, (this->build_post_fields(uuid)));
        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, -1L);

        CURLcode res = curl_easy_perform(this->curl);
        if (res != CURLE_OK)
        {
            LOG(error) << "curl_easy_perform() failed in whitelist: %s\n", curl_easy_strerror(res);
            return false;
        }

        bzn::message response;
        Json::Reader reader;
        if (!reader.parse(readBuffer, response))
        {
            LOG(error) << "Unable to parse response from Ropsten - could not validate peer";
            return false;
        }

        // result must be "0x0000000000000000000000000000000000000000000000000000000000000000"
        // or "0x0000000000000000000000000000000000000000000000000000000000000001" we will only
        // accept a value of 1 as true.
        return (std::stoul(response["result"].asString().c_str(), nullptr, 16) == 1);
    }
}

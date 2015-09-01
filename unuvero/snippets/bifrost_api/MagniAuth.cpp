/*
 * MagniAuth.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gsilverman
 */
#include <boost/program_options.hpp>
#include <boost/network/protocol/http.hpp>
#include <string>
#include <utility>
#include <iostream>
#include <sstream>
#include <vector>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <boost/algorithm/string/replace.hpp>

#include "MagniAuth.hpp"

using namespace boost::network;

MagniAuth::MagniAuth() {
	// TODO Auto-generated constructor stub

}

MagniAuth::~MagniAuth() {
	// TODO Auto-generated destructor stub
}

bool
MagniAuth::authenticate
  (FILE *fp)
{
	bool rc = false;

	std::string source = "https://magni-staging.memeo.com/thor/auth/magni?email=greg.silverman%40mailinator.com&password=passw0rd1&web_session=false";

	typedef boost::network::http::basic_client<
			boost::network::http::tags::http_async_8bit_tcp_resolve, 1, 0> http_client;

	http_client::request request(source);
	http_client client;
	http_client::response response = client.post(request);
	headers_range<http_client::response>::type headers_ = response.headers();
	for(auto&& header : headers_) {
		fprintf(fp,"%s: %s\n",header.first.c_str(),header.second.c_str());
	}
	std::ostringstream oss;
	body_range<http_client::response>::type body_;


	body_ = body(response).range();

	oss.str("");
	oss << body_;

	Json::Value jvalue;
	Json::Reader jreader;

	jreader.parse(oss.str(), jvalue);

	fprintf(fp,"%s\n",Json::StyledWriter().write(jvalue).c_str());

	return rc;
}

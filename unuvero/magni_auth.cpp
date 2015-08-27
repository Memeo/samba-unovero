//          Copyright Dean Michael Berris 2008.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//[ http_client_main
/*`
  This application takes a URL as a command line argument and prints
  the resource to the console.
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

class MagniLinks {
public:
	static const std::string admin;
	static const std::string home;
	static const std::string logout;
	MagniLinks(Json::Value p_links) :
		_admin(p_links[admin].asString()),
		_home(p_links[home].asString()),
		_logout(p_links[logout].asString())
	{}
	const std::string& getHome() const {
		return this->_home;
	}
	const std::string& getAdmin() const {
		return this->_admin;
	}
	const std::string& getLogout() const {
		return this->_logout;
	}
private:
	std::string _admin;
	std::string _home;
	std::string _logout;

};

const std::string MagniLinks::admin = "admin";
const std::string MagniLinks::home = "home";
const std::string MagniLinks::logout = "logout";

class MagniAuthResponse {
public:
	MagniAuthResponse(Json::Value jvalue) : _magni_links(jvalue["links"]) {}

	const MagniLinks& getLinks() const {
		return this->_magni_links;
	}

private:
	MagniLinks _magni_links;
	Json::Value _magni_auth_response;

};
namespace po = boost::program_options;

int main(int argc, const char * argv[]) {
    using namespace boost::network;


    for(int i=1;i<argc;++i) {
    	std::string argv_i(argv[i]);
    	if(std::string(argv[i])==std::string("-s")) {
    	    std::string url_arg(argv[i+1]);
    	    boost::algorithm::ireplace_all(url_arg,"%26","&");
    	    argv[i+1] = strdup(url_arg.c_str());
    	}
    }


    po::options_description options("Allowed options");
    std::string output_filename, source;
    bool show_headers;
    options.add_options()
        ("help,h", "produce help message")
        ("headers,H", "print headers")
        ("source,s", po::value<std::string>(&source), "source URL")
        ;

    po::positional_options_description positional_options;
    positional_options.add("source", 1);
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(options).positional(positional_options).run(),
            vm);
        po::notify(vm);
    } catch(std::exception & e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << options << std::endl;
        return EXIT_FAILURE;
    };

    if (vm.count("help")) {
        std::cout << options << std::endl;
        return EXIT_SUCCESS;
    };

    if (vm.count("source") < 1) {
        std::cout << "Error: Source URL required." << std::endl;
        std::cout << options << std::endl;
        return EXIT_FAILURE;
    };

    show_headers = vm.count("headers") ? true : false ;


    typedef boost::network::http::basic_client<boost::network::http::tags::http_async_8bit_tcp_resolve, 1, 0>
        http_client;

    http_client::request request(source);

    request << ::boost::network::header("Connection", "keep-alive");
    http_client::options client_options;
    http_client client(client_options.follow_redirects(true));
    http_client::response response = client.post(request);

    if (show_headers) {
        headers_range<http_client::response>::type headers_ = response.headers();
        typedef std::pair<std::string, std::string> header_type;
        BOOST_FOREACH(header_type const & header, headers_) {
          std::cout << header.first << ": " << header.second << std::endl;
        }
        std::cout << std::endl;
    };


    body_range<http_client::response>::type body_ = body(response).range();

    std::ostringstream oss;
    oss << body_;


    std::cout << "oss = " << oss.str() << std::endl;std::cout.flush();

    Json::Value  jvalue;
    Json::Reader jreader;


    jreader.parse(oss.str(),jvalue);

    Json::Value::Members memberNames = jvalue.getMemberNames();
    for(auto&& name : memberNames) {
    	std::cout << name << std::endl;
    }
    std::cout << Json::StyledWriter().write(jvalue) << std::endl;
    std::cout << jvalue["magni_token"].asString() << std::endl;

    MagniLinks magni_links(jvalue["links"]);
    std::cout << magni_links.getAdmin() << " " << magni_links.getHome() << " " << magni_links.getLogout() << std::endl;

    MagniAuthResponse mar(jvalue);
    std::cout << mar.getLinks().getAdmin() << " " << mar.getLinks().getHome() << " " << mar.getLinks().getLogout() << std::endl;


    std::cout << std::endl;

    request.uri("https://magni-staging.memeo.com");

    return EXIT_SUCCESS;
}

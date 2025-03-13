#include "http_lib_test.h"

// https://github.com/yhirose/cpp-httplib

// TODO Figure out how to add libssl and libcrypto to this
// This doesn't work
#ifdef _TEST1
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib.h"

httplib::Client cli("https://dashy.internal.kelsoncraft.net");

void HttpTest::test() {
	auto res = cli.Get("/");
	std::cout << res->status;
	std::cout << res->body;
}
#endif //_TEST1
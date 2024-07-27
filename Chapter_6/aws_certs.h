#include <pgmspace.h>
 
#define CERTS                       
 
// Amazon Root CA 1
static const char aws_root_ca[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
"Please copy your aws root ca here"
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                              
static const char aws_certificate[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
"Please copy your certs here"
-----END CERTIFICATE-----
 
)KEY";
 
// Device Private Key                                               
static const char aws_private_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
"Please copy your private key here"
-----END RSA PRIVATE KEY-----
 
 
)KEY";
#include <pgmspace.h>

#define SECRET
// Amazon Root CA 1,  
static const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
//Put VeriSign-Class 3-Public-Primary-Certification-Authority-G5  here
-----END CERTIFICATE-----
)EOF";

// Device Certificate Pem                                               
static const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
// Put your device certificate pem here.
-----END CERTIFICATE-----
)EOF";

// Device Private Pem                                         
static const char AWS_PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
// Put your private key here.
-----END RSA PRIVATE KEY-----
)EOF";

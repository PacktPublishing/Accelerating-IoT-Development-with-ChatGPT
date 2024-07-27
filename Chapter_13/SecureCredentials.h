#include <pgmspace.h>

#define SECRET
// Amazon Root CA 1, VeriSign-Class 3-Public-Primary-Certification-Authority-G5
static const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
"download https://cacerts.digicert.com/pca3-g5.crt.pem, use an edit software to open it, copy its contents and paste it here."
-----END CERTIFICATE-----
)EOF";

// Device Certificate Pem                                               
static const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
"use an edit software to open the downloaded file, copy its contents and paste it here."
-----END CERTIFICATE-----
)EOF";

// Device Private Pem                                         
static const char AWS_PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
"use an edit software to open the downloaded file, copy its contents and paste it here."
-----END RSA PRIVATE KEY-----
)EOF";

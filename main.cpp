//#include <QDebug>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
#include "broker.h"
#include "nng/supplemental/nanolib/conf.h"
}

/*
 * FLAGS USED FOR NANOMQ BUILD:
-DNNG_ENABLE_QUIC=OFF
-DNNG_ENABLE_TLS=OFF
-DBUILD_CLIENT=OFF
-DBUILD_ZMQ_GATEWAY=OFF
-DBUILD_NFTP=OFF
-DBUILD_DDS_PROXY=OFF
-DBUILD_BENCH=OFF
-DENABLE_JWT=OFF
-DNNG_ENABLE_SQLITE=OFF
-DBUILD_STATIC_LIB=ON
-DBUILD_SHARED_LIBS=OFF
-DDEBUG=OFF
-DASAN=OFF
-DDEBUG_TRACE=OFF
-DNOLOG=1
-DENABLE_RULE_ENGINE=OFF

in <project>/third_party/: Commands:
git clone https://github.com/emqx/nanomq.git
cd nanomq
git submodule update --init --recursive
mkdir build && cd build
cmake -G "Visual Studio 17 2022" -A x64 -DNNG_ENABLE_QUIC=OFF -DNNG_ENABLE_TLS=OFF -DBUILD_CLIENT=OFF -DBUILD_ZMQ_GATEWAY=OFF -DBUILD_NFTP=OFF -DBUILD_DDS_PROXY=OFF -DBUILD_BENCH=OFF -DENABLE_JWT=OFF -DNNG_ENABLE_SQLITE=OFF -DBUILD_STATIC_LIB=ON -DBUILD_SHARED_LIBS=OFF -DDEBUG=OFF -DASAN=OFF -DDEBUG_TRACE=OFF -DNOLOG=1 -DENABLE_RULE_ENGINE=OFF ..
cmake --build . --config Release
cmake --build . --config Debug
*/

// Match no ACL support to avoid nullptr access
#define ACL_SUPP 0

int main(int argc, char *argv[])
{
    conf nanomq_conf;
    conf_init(&nanomq_conf);

    /*using conf_parse, nanomq.conf should be just this:
                # Basic configuration
                url = nmq-tcp://0.0.0.0:1883
                allow_anonymous = false

                # Authentication
                auth.1.login = myUser
                auth.1.password = myPassword

                # ACL settings
                acl_nomatch = allow

        to then use:
        nanomq_conf.conf_file = _strdup( <path_to_nanomq.conf> );
        conf_parse(&nanomq_conf);
            */

    //We should inject the config instead of parsing to have no file dependencies

    // Broker URL is localhost:1883, auth on MQTT is enforced
    nanomq_conf.url = _strdup("nmq-tcp://0.0.0.0:1883");
    nanomq_conf.allow_anonymous = false;

    // Authorization on MQTT protocol
    nanomq_conf.auths.enable = true;
    nanomq_conf.auths.count = 1;
    nanomq_conf.auths.usernames = (char**)malloc(sizeof(char *) * nanomq_conf.auths.count);
    nanomq_conf.auths.passwords = (char**)malloc(sizeof(char *) * nanomq_conf.auths.count);
    nanomq_conf.auths.usernames[0] = _strdup("myUser");
    nanomq_conf.auths.passwords[0] = _strdup("myPassword");

    // Necessary to avoid nullptr accesses in broker_start
    nanomq_conf.exchange.encryption = nullptr;
    nanomq_conf.tcp_list.count = 0;
    nanomq_conf.tls_list.count = 0;

    //START BROKER and let nanoMQ manage the memory
    return static_cast<int>(reinterpret_cast<intptr_t>(broker_start_with_conf(&nanomq_conf)));
}

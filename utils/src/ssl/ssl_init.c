#include "utils.h"
#include "protocol.h"

static SSL_CTX *init_ctx(t_app_type type) {
    const SSL_METHOD *method;
    SSL_CTX *ctx = NULL;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    if (type == CLIENT)
        method = DTLS_client_method();
    else if (type == SERVER)
        method = DTLS_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX\n");
    }
    return ctx;
}

static void load_client_certificates(t_ssl_con *ssl) {
    if (SSL_CTX_use_certificate_file(ssl->ctx, ssl->cert_file,
                                     SSL_FILETYPE_PEM) != 1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_use_certificate_file\n");
    }
    SSL_CTX_set_default_passwd_cb_userdata(ssl->ctx, ssl->password);
    if (SSL_CTX_use_PrivateKey_file(ssl->ctx, ssl->key_file,
                                    SSL_FILETYPE_PEM) != 1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_use_PrivateKey_file\n");
    }
    if (!SSL_CTX_check_private_key(ssl->ctx)) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_check_private_key\n");
    }
}

static void load_server_certificates(t_ssl_con *ssl) {
    if (!SSL_CTX_load_verify_locations(ssl->ctx, ssl->cert_file,
                                      ssl->key_file)) {
        mx_logger(MX_LOG_FILE, LOGERR, "SSL_CTX_load_verify_locations\n");
    }
    if (!SSL_CTX_set_default_verify_paths(ssl->ctx))
        mx_logger(MX_LOG_FILE, LOGERR, "SSL_CTX_set_default_verify_paths\n");
    if (SSL_CTX_use_certificate_file(ssl->ctx, ssl->cert_file,
                                     SSL_FILETYPE_PEM) != 1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_use_certificate_file\n");
    }
    SSL_CTX_set_default_passwd_cb_userdata(ssl->ctx, ssl->password);
    if (SSL_CTX_use_PrivateKey_file(ssl->ctx, ssl->key_file,
                                    SSL_FILETYPE_PEM) != 1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_use_PrivateKey_file\n");
    }
    if (!SSL_CTX_check_private_key(ssl->ctx))
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_CTX_check_private_key\n");
    SSL_CTX_set_verify(ssl->ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    SSL_CTX_set_verify_depth(ssl->ctx, 4);
}

t_ssl_con *mx_init_ssl(t_app_type type) {
    t_ssl_con *ssl = mx_malloc(sizeof(t_ssl_con));

    ssl->cert_file = MX_CERT_FILE;
    ssl->key_file = MX_KEY_FILE;
    ssl->password = MX_KEY_PASSWORD;
    SSL_library_init();
    ssl->ctx = init_ctx(type);
    if (type == CLIENT)
        load_client_certificates(ssl);
    else if (type == SERVER)
        load_server_certificates(ssl);
    return ssl;
}

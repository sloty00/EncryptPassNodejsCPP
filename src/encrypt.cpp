#include <node.h>
#include <v8.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include "base64.h" // Asegúrate de que esta biblioteca esté disponible

using namespace v8;

std::string Encrypt(const std::string& plaintext) {
    // Set up encryption
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL);

    // Generate key and IV (In a real application, use secure key management)
    unsigned char key[32];
    unsigned char iv[16];
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    // Set the key and IV
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);

    // Encrypt the plaintext
    std::vector<unsigned char> ciphertext(plaintext.length() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    int len;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (unsigned char*)plaintext.c_str(), plaintext.length());
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Convert ciphertext to Base64
    std::string base64_encoded = base64_encode(ciphertext.data(), ciphertext_len);
    return base64_encoded;
}

void EncryptWrapped(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() < 1 || !args[0]->IsString()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "String argument required").ToLocalChecked()));
        return;
    }

    String::Utf8Value str(isolate, args[0]);
    std::string plaintext(*str);
    std::string ciphertext = Encrypt(plaintext);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, ciphertext.c_str()).ToLocalChecked());
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "encrypt", EncryptWrapped);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

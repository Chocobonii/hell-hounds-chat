//   __  __ _____ ____ ____    _    ____ _____   _____ _   _  ____ ______   ______ _____ ___ ___  _   _ 
//  |  \/  | ____/ ___/ ___|  / \  / ___| ____| | ____| \ | |/ ___|  _ \ \ / /  _ \_   _|_ _/ _ \| \ | |
//  | |\/| |  _| \___ \___ \ / _ \| |  _|  _|   |  _| |  \| | |   | |_) \ V /| |_) || |  | | | | |  \| |
//  | |  | | |___ ___) |__) / ___ \ |_| | |___  | |___| |\  | |___|  _ < | | |  __/ | |  | | |_| | |\  |
//  |_|  |_|_____|____/____/_/   \_\____|_____| |_____|_| \_|\____|_| \_\|_| |_|    |_| |___\___/|_| \_|
//                                                                                                      
// -------------------------------------------------------------------
using namespace CryptoPP;
class Phoenix_encryptor {
    public:
        int psk[40] = {
            0x4f ,0x62 ,0x21 ,0x79, 0x6b, 0x4a, 0x24, 0x35, // 
            0x36 ,0x30 ,0x69 ,0x75, 0x26, 0x72, 0x4f, 0x56, // For the low time I have to code all this
            0x26 ,0x43 ,0x67 ,0x65, 0x24, 0x6e, 0x69, 0x65, // I'm leaving a default password for the encryption
            0x69 ,0x74 ,0x32 ,0x30, 0x21, 0x36, 0x61, 0x48, // but to prevent easy reverse engineering and make it
            0x67 ,0x58 ,0x26 ,0x43, 0x67, 0x31, 0x79, 0x65  // way too hard, I'll hide the password as hexadecimal array
        };// ------------------------------------------------------------------------------------------------------------
        std::string gpassword;                             // like this it can't be seen with conventional string methods
        SecByteBlock key;                                  // THIS IS THE KEY
        SecByteBlock iv;                                   // THIS IS A SECONDARY KEY
        // --------------------------------------------------------------------------------------------------------------
        Phoenix_encryptor();                                // this is my class constructor just for the common setup
        // --------------------------------------------------------------------------------------------------------------
        void decompress_passwd();                           // THIS WILL CONVERT THE PASSWORD TO A STRING
        SecByteBlock Derive_key(std::string _secret);       // THIS WILL MAKE A VARIATION OF THE PASSWORD TO SECURE IT
        std::string Phoenix_encrypt(std::string _emessage); // THIS WILL ENCRYPT OUR MESSAGE
        std::string Phoenix_decrypt(std::string _emessage); // THIS WILL DECRYPT OUR MESSAGE
        // ---------------------------------------------------------------------------------------------------------------
        std::string Phoenix_b64_enc(std::string _string); // THIS ENCODES THE STRING AS BASE 64
        std::string Phoenix_b64_dec(std::string _string); // THIS DECODES THE STRING MESSAGE
};
// *******************************************************************************************
// * THESE ARE THE ROUTINES FROM THE CLASS IMPLEMENTED IN ORDER TO PROTECT OUR COMMUNICATION *
// *******************************************************************************************
Phoenix_encryptor::Phoenix_encryptor(){     // WHEN THE OBJECT IS CREATED
    decompress_passwd();                    // THE PASSWORD WILL START TO DECOMPRESS
    key = Derive_key(gpassword);
    iv = Derive_key(Phoenix_b64_enc(gpassword));
}
// --------------------------------------------------------------------------------------------
void Phoenix_encryptor::decompress_passwd(){    // 
    for(int i = 0; i < 40; i++){                // NOW TO DECOMPRESS THE PASSWORD
        if(psk[i]!=NULL ||psk[i]!=0x00) {       // WE ARE GOING TO TEST IF THE CHARACTERS ARE NOT NULL
            gpassword += char(psk[i]);          // AND AFTER THAT ADD THE CHARACTER TO THE STRING
        }                                       // SO BASICALLY WE CONVERT FROM HEX TO STRING
    }                                           // THIS ADDS A LAYER OF PROTECTION AGAINST REVERSE ENGINEERING
    std::cout<<"decompression process completed! ..."<<std::endl;
}
// ----------------------------------------------------------------------------------------------
std::string Phoenix_encryptor::Phoenix_b64_enc(std::string _string){
    try{                                             // 
      std::string encoded;                           // THIS WILL TRY
      Base64Encoder encoder;                         // IF IT IS POSSIBLE TO
      StringSource source(_string, true,             // ENCODE THE STRING OF OUR MESSAGE
      new Base64Encoder(new StringSink(encoded)));   // AND IF ANY ERROR HAPPENS
      return encoded;                                //
    } catch (const Exception &e) {                   // IT CATCHES THE EXCEPTION
        std::cerr<<e.what()<<std::endl;              // OTHERWISE IT RETURNS A BASE64 
        return "";                                   // ENCODED STRING
    }
}
// -----------------------------------------------------------------------------------------------
std::string Phoenix_encryptor::Phoenix_b64_dec(std::string _string){
    try{                                             // 
      std::string decoded;                           // THIS WILL TRY
      Base64Decoder decoder;                         // IF IT IS POSSIBLE TO
      StringSource source(_string, true,             // DECODE THE STRING OF OUR MESSAGE
      new Base64Decoder(new StringSink(decoded)));   // AND IF ANY ERROR HAPPENS
      return decoded;                                //
    } catch (const Exception &e) {                   // IT CATCHES THE EXCEPTION
        std::cerr<<e.what()<<std::endl;              // OTHERWISE IT RETURNS A BASE64 
        return "";                                   // DECODED STRING
    }
}
// -----------------------------------------------------------------------------------------------
SecByteBlock Phoenix_encryptor::Derive_key(std::string _secret){
    SecByteBlock key(AES::MAX_KEYLENGTH);                            // THIS IS THE PART WHERE THE BYTEBLOCK DEFINES IT SIZE
    std::string salt = "Xj9.$dfgMyLove092D$@3";                      // AND THIS IS THE SALT (USED FOR DERIVATION AND ALSO PROVIDES SECURITY)
                                                                     // 
    try{                                                             // SO WE ARE GOING TO TRY IF WE CAN 
        HKDF<SHA256> hkdf;                                           // CREATE OUR KEY BASED ON SHA256 ALGORITHM
        hkdf.DeriveKey(key, key.size(),                              // AS THE RUST VERSION
                        (const byte *)_secret.data(), _secret.size(),// THIS IS DONE TO CREATE A SECURE KEY
                        (const byte *)salt.data(), salt.size(),      // AND MAKE IT STRONG ENOUGH TO REQUIRE
                        NULL, 0                                      // A LOT OF COMPUTATION POWER TO CRACK
        );                                                           // 
    } catch(const Exception& ex) {                                   // 
        std::cerr << ex.what() << std::endl;                         // BUT IF IT FAILS IT WILL DIE AND RETURN
        return SecByteBlock(0);                                      // A NULL KEY
    }                                                                // 
    return key;                                                      // 
}   
// ------------------------------------------------------------------
std::string Phoenix_encryptor::Phoenix_encrypt(std::string _emessage){
    std::string _result;
    try{                                            // THIS IS THE ENCRYPTION ROUTINE
    CBC_Mode<AES>::Encryption dcipher;              // CBC MODE REFERS TO CIPHER BLOCK CHAINING
    dcipher.SetKeyWithIV(key, key.size(), iv);      // IN THIS PART WE INITIALIZE IT WITH 
                                                    // 
    StringSource source(_emessage, true,            // THIS IS BASICALLY
        new StreamTransformationFilter(dcipher,     // THE PART THAT ACTUALLY DOES
        new StringSink(_result)                     // THE ENCRYPTION
    ));                                             // 
    }catch(const Exception& e){                     // THIS PART 
            std::cerr << e.what() << std::endl;     // AS ALWAYS
            return "";                              // HANDLES THE EXCEPTION
    }                                               // TO PREVENT ERRORS KILLING THE PROGRAM
    return Phoenix_b64_enc(_result);                // 
}
// --------------------------------------------------------------------
std::string Phoenix_encryptor::Phoenix_decrypt(std::string _emessage){
    std::string _result;                                        // 
    try{                                                        // THIS IS THE DECRYPTION SEGMENT
    CBC_Mode<AES>::Decryption dcipher;                          // BASICALLY LOOKS THE SAME AS THE ENCRYPTION
    dcipher.SetKeyWithIV(key, key.size(), iv);                  // WITH THE DIFFERENCE THAT IN THIS PART
                                                                // FIRST WE DECODE THE BASE 64 TO GET THE
    StringSource source(Phoenix_b64_dec(_emessage), true,       // ORIGINAL CIPHER TEXT
        new StreamTransformationFilter(dcipher,                 // AND SEND IT TO THE SERVER
        new StringSink(_result)                                 // 
    ));                                                         // 
    }catch(const Exception& e){                                 // THIS PART 
            std::cerr << e.what() << std::endl;                 // AS ALWAYS
            return "";                                          // HANDLES THE EXCEPTION
    }                                                           // TO PREVENT ERRORS KILLING THE PROGRAM
    return _result;                                             // 
}
// --------------------------------------------------------------------
Phoenix_encryptor *care_hound = new Phoenix_encryptor();
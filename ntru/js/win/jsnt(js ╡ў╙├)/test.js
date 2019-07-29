var app = require("./index");
const CRYPTO_SECRETKEYBYTES = 2604
const CRYPTO_PUBLICKEYBYTES = 2065
var yx = "adasadadasdasdasdad";
var msg = "Whatever is worth doing is worth doing wel";
var sm1 = "Whatever is worth doing is worth doing wex";

app.intial(yx);
var sk = app.getprivateKey();
var pk = app.getpublicKey();
var smsg = app.pqsign(msg,sk);
var result = app.sign_verify(msg,smsg,pk,CRYPTO_PUBLICKEYBYTES+msg.length);
var pubkey = app.Secret2pub(sk);

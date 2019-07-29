
"use strict"
var ffi = require("ffi");
//var ref = require("ref");
//const iconv = require('iconv-lite')
//const refArray = require('ref-array')
//const sk = refArray(ref.types.uchar,2604);
//const pk = refArray(ref.types.uchar,2065);
//var csk = new sk();
//var cpk = new pk();
//var msgss1 = new ss();
var libhel = ffi.Library('ntrusign.dll',{
	'Initial':['int',['string']],
	'Ntrusign':['uchar*',['string','uchar*']],
	'GetPublicKey':['uchar*',[]],
	'GetPrivateKey':['uchar*',[]],
	'Ntrusign_Verify':['int',['string','string','uchar*','int']],
	'Secrect2Pub':['uchar*',['uchar*']]
});



var yx = "adasadadasdasdasdad";
var msg = "Whatever is worth doing is worth doing wel";
var sm1 = "Whatever is worth doing is worth doing wel";
console.log(msg.length);
//const ss = refArray(ref.types.uchar,(2065+msg.length));

function intial(str){
	libhel.Initial(str);
}
//libhel.Initial(yx);

function getprivateKey(){
	var csk = libhel.GetPrivateKey();
	return csk;
}
//var csk = libhel.GetPrivateKey();

function getpublicKey(){
	var cpk = libhel.GetPublicKey();
	return cpk;
}
//var cpk = libhel.GetPublicKey();

function Secret2pub(skey){
	var cpk = libhel.Secrect2Pub(skey);
	return cpk;
}

function pqsign(message,cryptosk){
	var m = libhel.Ntrusign(message,cryptosk);
	return m;
}
//var msgss1 = libhel.Ntrusign(msg,cryptosk);

function sign_verify(message, smesssage, cryptopk,len){
	var bo = libhel.Ntrusign_Verify(message,smesssage,cryptopk,len);
	return bo;
}
//libhel.Ntrusign_Verify(sm1,msgss1,cpk,2065+msg.length);
exports.intial = intial;
exports.getprivateKey = getprivateKey;
exports.getpublicKey = getpublicKey;
exports.pqsign = pqsign;
exports.sign_verify = sign_verify;
exports.Secret2pub = Secret2pub;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ntrusign;

import org.apache.commons.codec.binary.Base64;

/**
 *
 * @author yLIEx
 */
public class asu {

    final static int CRYPTO_SECRETKEYBYTES = 2604;
    final static int CRYPTO_PUBLICKEYBYTES = 2065;

    public byte[] SecTrans(byte[] Skey) {
        byte[] tmp = new byte[CRYPTO_SECRETKEYBYTES];
        for (int i = 0; i < CRYPTO_SECRETKEYBYTES; i++) {
            tmp[i] = Skey[i];
        }
        return tmp;
    }

    public static byte[] PubTrans(byte[] Pkey) {
        byte[] tmp = new byte[CRYPTO_PUBLICKEYBYTES];
        for (int i = 0; i < CRYPTO_PUBLICKEYBYTES; i++) {
            tmp[i] = Pkey[i];
        }
        return tmp;
    }

    public static String ByteToString(byte[] bytes) {

        StringBuilder strBuilder = new StringBuilder();
        for (int i = 0; i < bytes.length; i++) {
            if (bytes[i] != 0) {
                strBuilder.append((char) bytes[i]);
            } else {
                break;
            }

        }
        return strBuilder.toString();
    }

    public static String byte2Base64StringFun(byte[] b) {

        return Base64.encodeBase64String(b);

    }

    public static byte[] base64String2ByteFun(String base64Str) {

        return Base64.decodeBase64(base64Str);

    }

    public static void main(String[] args) {
        String str = "";
        String msg = "Whatever is worth doing is worth doing well";
        String sm1 = "Whatever is worth doing is worth doing well1";
        Ntrusign test = new Ntrusign();
        byte sk[] = new byte[CRYPTO_SECRETKEYBYTES];
        byte pk[] = new byte[CRYPTO_PUBLICKEYBYTES];
        byte[] key =  test.InitialKey(msg);
        for(int i = 0; i< CRYPTO_PUBLICKEYBYTES;i++)
            pk[i] =  key[i];
        for(int j = CRYPTO_PUBLICKEYBYTES,k=0; j< CRYPTO_SECRETKEYBYTES+CRYPTO_PUBLICKEYBYTES;j++,k++)
            sk[k] =  key[j];
        byte[] newkey = PubTrans(pk);
        byte[] sm = test.Sign(msg.getBytes(), sk);
        test.Verify(sm, msg.getBytes(), newkey);
    /*    byte[] pk = test.GetPublicKey();
        byte[] newkey = PubTrans(pk);
        String n = ByteToString(newkey);
        String n1 = byte2Base64StringFun(newkey);
        byte[] n2 = base64String2ByteFun(n1);
        byte[] ppk = test.Secret2Public(sk);
        byte[] sm = test.Sign(msg.getBytes(), sk);
        test.Verify(sm, msg.getBytes(), ppk);*/

    }

}

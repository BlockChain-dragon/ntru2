/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ntrusign;

/**
 *
 * @author yLIEx
 */
public class Ntrusign {

    /**
     * @param args the command line arguments
     */
    static{
        System.loadLibrary("ntrusign");
    }
    public native byte[] InitialKey(String key);
    public native byte[] Sign(byte[] msg,byte[] sk);
    public native int Verify(byte[] smsg,byte[] msg,byte[] pk);
   // public native byte[]  GetPrivateKey();
   // public native byte[] GetPublicKey();
    public native byte[] Secret2Public(byte[] sk);
   
}

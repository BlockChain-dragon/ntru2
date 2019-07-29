/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ntrusign;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

/**
 *
 * @author yLIEx
 */
public class Ntrusign {

    /**
     * @param args the command line arguments
     */
    static{
        System.load("/home/zz/app/hashnet/ntru/ntrusign/libntrusign.so");
    }
    public native void InitialKey(String key);
    public native byte[] Sign(byte[] msg,byte[] sk);
    public native boolean Verify(byte[] smsg,byte[] msg,byte[] pk);
    public native byte[]  GetPrivateKey();
    public native byte[] GetPublicKey();
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ntrusign;

import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 *
 * @author yLIEx
 */
public class asu {

//    public interface Dll extends Library {
//        Dll instance = (Dll) Native.loadLibrary("libhelloworld", Dll.class);
//        public  void InitialKey(String key);
//        public  byte[] Sign(byte[] msg,byte[] sk);
//        public  boolean Verify(byte[] smsg,byte[] msg,byte[] pk);
//        public  byte[]  GetPrivateKey();
//        public  byte[] GetPublicKey();
//    }


        public static void main(String[] args) {

//           byte[] pri = Dll.instance.GetPrivateKey();



//            String property = System.getProperty("java.library.path");
//            System.out.println(property);
            String str ="";

            String msg = "Whatever is worth doing is worth doing well";

            Ntrusign test = new Ntrusign();
            test.InitialKey(str);
            byte sk[] = test.GetPrivateKey();
            byte pk[] = test.GetPublicKey();
            byte[] sm = test.Sign(msg.getBytes(), sk);
            boolean bl = test.Verify(sm,msg.getBytes(),pk);
            System.out.println("_----------------------");
            System.out.println(bl);
    }



    
}

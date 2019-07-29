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
public class asu {
        public static void main(String[] args) {
     String str ="";
       String msg = "Whatever is worth doing is worth doing well";
       String sm1 = "Whatever is worth doing is worth doing well1";
       Ntrusign test = new Ntrusign();
       test.InitialKey(msg);
     byte sk[] = test.GetPrivateKey();
     byte pk[] = test.GetPublicKey();
      byte[] sm = test.Sign(msg.getBytes(), sk);
    test.Verify(sm,sm1.getBytes(),pk);
    byte[] ppk = test.Secret2Public(sk);
    }
    
}

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
        String msg1 = "Whatever is worth doing is worth doing we1l11";
        Ntrusign test = new Ntrusign();
        test.InitialKey(str);
        byte sk[] = test.GetPrivateKey();
        byte pk[] = test.GetPublicKey();

        byte kk[] = test.Secret2Public(sk);

    }
    
}

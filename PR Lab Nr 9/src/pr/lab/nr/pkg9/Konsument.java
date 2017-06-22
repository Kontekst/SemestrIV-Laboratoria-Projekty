package pr.lab.nr.pkg9;

import java.util.Random;

public class Konsument extends Thread{
    public int maximum=15;
    public Magazyn magazyn=null;
    Random generator = new Random();
    
    public Konsument(Magazyn mag) {
        this.magazyn = mag;
    }
    
    @Override
    public void run () {
        magazyn.odejmijTowar(generator.nextInt(3),generator.nextInt(3));
    }
}

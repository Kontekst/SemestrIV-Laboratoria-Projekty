package pr.lab.nr.pkg9;

import java.util.Random;

public class Producent extends Thread{
    public Magazyn magazyn=null;
    Random generator = new Random();
    public Producent(Magazyn mag) {
        this.magazyn = mag;
    }
    
    @Override
    public void run () {
        magazyn.dodajTowar(generator.nextInt(3),generator.nextInt(5));
    }
}

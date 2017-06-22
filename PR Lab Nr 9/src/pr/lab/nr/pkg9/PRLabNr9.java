package pr.lab.nr.pkg9;

import java.util.Random;

/**
 *
 * @author Kontekstowy
 */
public class PRLabNr9 {

    public static void main(String[] args) throws InterruptedException {
        
    Magazyn magazyn = new Magazyn();
    Konsument konsument = new Konsument (magazyn);
    Producent producent = new Producent(magazyn);
    Random generator = new Random();
    
    
    while(true){
        new Thread(producent).start();
        Thread.sleep(generator.nextInt(1000));
        new Thread(konsument).start();
        Thread.sleep(generator.nextInt(1000));
        magazyn.wypisz();
    }
    }
}
    


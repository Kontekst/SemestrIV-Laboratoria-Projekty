package pr.lab.nr.pkg9;

public class Magazyn {
    public int maximum=15;
    public int[] typy= new int[3];
     public Magazyn() {
        typy[0]=0;
        typy[1]=0;
        typy[2]=0;
    }
     
     public int sumaTowarow(){
         return (typy[0]+typy[1]+typy[2]);
     }
     
     public void wypisz(){
         System.out.println("Magazyn - zajęcie ("+typy[0]+","+typy[1]+","+typy[2]+")");
     }
     
     public synchronized void dodajTowar(int towar,int ile){
         if(sumaTowarow()+ile<maximum){
             typy[towar]+=ile;
             System.out.println("Producent wyprodukował "+ile+ " sztuk towaru nr "+towar);
         }else{             
             typy[towar]+=maximum-sumaTowarow();
             System.out.println("Producent wyprodukował "+(maximum-sumaTowarow())+ " sztuk towaru nr "+towar + " choc troche wyrzucilismy");
         }
         
     }
     
     public synchronized void odejmijTowar(int towar,int ile){
         if(typy[towar] > ile){
             typy[towar]-=ile;
             System.out.println("Konsument kupil "+ile+ " sztuk towaru nr "+towar);
         }else{             
             System.out.println("Konsument kupil niewiele bo "+typy[towar]+ " sztuk towaru nr "+towar );
             typy[towar]=0;
         }   
     }   
}
